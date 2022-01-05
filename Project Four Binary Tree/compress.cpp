#include "binaryTree.h"
#include "huffmanTree.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

void countFreq(ifstream &ifile, int *freq) {
    // REQUIRE: freq has the length of 28 at least.
    // MODIFIES: ifile, freq
    // EFFECTS: Count the frequency for all the possible characters 'a'-'z', ' ', and '\n'.
    char c;
    while (ifile.get(c)) {
        if (c == ' ')
            freq[26]++;
        else if (c == '\n')
            freq[27]++;
        else
            freq[c - 97]++;
    }
}

bool compareNode(const Node *a, const Node *b) {
    // EFFECTS: Return the descending order of two nodes by their numbers; if their numbers are equal, sort with the lexicographic order.
    if (a->getnum() != b->getnum())
        return b->getnum() < a->getnum();
    else
        return b->getstr() < a->getstr();
}

void printBincode(ifstream& ifile, const int freq[], HuffmanTree& huffmanTree) {
    // REQUIRE: freq has the length of 28 at least.
    // MODIFIES: ifile, freq
    // EFFECTS: Print the binary code according to the order in the original sequence.
    char c;
    ifile.clear();
    ifile.seekg(0);
    string bincode[28];
    for (int i = 0; i < 26; i++) {
        if (freq[i] > 0)
            bincode[i] = huffmanTree.findPath(string(1, char(i + 97)));
    }
    if (freq[26])
        bincode[26] = huffmanTree.findPath(" ");
    if (freq[27])
        bincode[27] = huffmanTree.findPath("\n");
    while (ifile.get(c)) {
        if (c == ' ')
            cout << bincode[26] << " ";
        else if (c == '\n')
            cout << bincode[27] << " ";
        else
            cout << bincode[c - 97] << " ";
    }
}

int main(int argc, char *argv[]) {
    // TODO: implement this function
    // REQUIRES: two or three arguments; if there are three arguements, the third argument should be "-tree".
    // EFFECTS: Compress the text in the file.
    string s, filename = (argc == 2) ? argv[1] : argv[2];
    bool flag = (argc == 3 && string(argv[1]) == "-tree");
    ifstream ifile(filename);
    int freq[28] = {0};
    vector<Node *> nodes;
    countFreq(ifile, freq);
    for (int i = 0; i < 26; i++) {
        if (freq[i])
            nodes.push_back(new Node(string(1, char(i + 97)), freq[i], nullptr, nullptr));
    }
    if (freq[26])
        nodes.push_back(new Node(" ", freq[26], nullptr, nullptr));
    if (freq[27])
        nodes.push_back(new Node("\n", freq[27], nullptr, nullptr));
    sort(nodes.begin(), nodes.end(), compareNode);
    while (nodes.size() > 1) {
        Node *rightnode = nodes.back();
        nodes.pop_back();
        Node *leftnode = nodes.back();
        nodes.pop_back();
        nodes.push_back(Node::mergeNodes(leftnode, rightnode));
        sort(nodes.begin(), nodes.end(), compareNode);
    }
    HuffmanTree huffmanTree(nodes.front());
    if (flag)
        huffmanTree.printTree();
    else
        printBincode(ifile, freq, huffmanTree);
    ifile.close();
}