#include <iostream>
#include <sstream>
#include "dlist.h"

using namespace std;

struct block {
    size_t address;
    int data;
};

bool cmpAddress(const block *a, const block *b) {
    // EFFECTS: return true if the addresses of a and b are the same.
    return a->address == b->address;
}

// void writeBlock(Dlist<block>& cache, block *cacheblock, block *target, size_t& num_cache, const size_t cachesize, int mainmemory[]) {}

void printCache(istringstream& iss, const Dlist<block>& cache) {
    // MODIFIES: iss
    // EFFECTS: Print the content of the cache. Each line contains the <address> and the <data> of one
    //      block and blocks are ordered from the most recently used to the least recently used.
    string temp;
    if (iss >> temp)
        cout << "ERROR: Too many operands" << endl;
    else {
        Dlist<block> temp = cache;
        while (!temp.isEmpty()) {
            block *topblock = temp.removeFront();
            cout << topblock->address << " " << topblock->data << endl;
            delete topblock;
        }
    }
}

void printMem(istringstream& iss, const int mainmemory[], const size_t mainmemorysize) {
    // MODIFIES: iss
    // EFFECTS: Print the content of the memory in a line, starting from address 0 and separating adjacent data with a space.
    string temp;
    if (iss >> temp)
        cout << "ERROR: Too many operands" << endl;
    else {
        for (size_t i = 0; i < mainmemorysize; i++) {
            cout << mainmemory[i] << " ";
        }
        cout << endl;
    }
}

int main() {
    // EFFECTS: simulate a least-recently-used cache.
    int data;
    size_t cachesize, mainmemorysize, address, num_cache = 0;
    cin >> cachesize >> mainmemorysize >> ws;
    int mainmemory[mainmemorysize];
    for (size_t i = 0; i < mainmemorysize; i++) {
        mainmemory[i] = 0;
    }
    string instruction, operation;
    Dlist<block> cache;
    while (getline(cin, instruction)) {
        istringstream iss(instruction);
        iss >> operation;
        if (operation == "READ" || operation == "WRITE") {
            if (!(iss >> address))
                cout << "ERROR: Not enough operands" << endl;
            else if (operation == "READ" && !iss.eof())
                cout << "ERROR: Too many operands" << endl;
            else if (address >= mainmemorysize)
                cout << "ERROR: Address out of bound" << endl;
            else if (operation == "WRITE" && !(iss >> data))
                cout << "ERROR: Not enough operands" << endl;
            else if (!iss.eof())
                cout << "ERROR: Too many operands" << endl;
            else {
                block *cacheblock = new block{address, data};
                block *target = cache.remove(cmpAddress, cacheblock);
                if (operation == "READ") {
                    if (target) {
                        cacheblock->data = target->data;
                        cache.insertFront(cacheblock);
                    }
                    else {
                        cacheblock->data = mainmemory[address];
                        cache.insertFront(cacheblock);
                        if (num_cache < cachesize)
                            num_cache++;
                        else {
                            block *victim = cache.removeBack();
                            mainmemory[victim->address] = victim->data;
                            delete victim;
                        }
                    }
                    delete target;
                    cout << cacheblock->data << endl;
                }
                else {
                    cache.insertFront(cacheblock);
                    if (target)
                        delete target;
                    else {
                        if (num_cache < cachesize)
                            num_cache++;
                        else {
                            block *victim = cache.removeBack();
                            mainmemory[victim->address] = victim->data;
                            delete victim;
                        }
                        delete target;
                    }
                }
            }
        }
        else if (operation == "PRINTCACHE") {
            printCache(iss, cache);
        }
        else if (operation == "PRINTMEM") {
            printMem(iss, mainmemory, mainmemorysize);
        }
        else if (operation == "EXIT") {
            if (!iss.eof())
                cout << "ERROR: Too many operands" << endl;
            else
                break;
        }
        else
            cout << "ERROR: Unknown instruction" << endl;
    }
}