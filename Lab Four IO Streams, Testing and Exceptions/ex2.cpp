#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>

using namespace std;

struct Apple {
    string variety;
    double price;
    double weight;
    double average() {
        return price / weight;
    }
};

int lowest_average(Apple apple[], int n) {
    int i, lowest = 0;
    double current = apple[0].average();
    for (i = 0; i < n; ++i) {
        if (apple[i].average() < current) {
            current = apple[i].average();
            lowest = i;
        }
    }
    return lowest;
}

int main(int argc, char* argv[]) {
    ifstream pricelist;
    pricelist.open(argv[1]);
    string line;
    int lowest, t = 0, n = 0;
    while(getline(pricelist, line)) {
        n++;
    }
    pricelist.close();
    Apple apple[n];
    pricelist.open(argv[1]);
    while(getline(pricelist, line)) {
        istringstream info;
        info.str(line);
        info >> apple[t].variety >> apple[t].price >> apple[t].weight;
        t++;
    }
    lowest = lowest_average(apple, n);
    cout << apple[lowest].variety << " " << setiosflags(ios::fixed) << setprecision(2) << apple[lowest].price << " " << apple[lowest].weight << endl;
    pricelist.close();
}