#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main() {
    int i, n = 0, t = 0;
    string::size_type pos = 0;
    string line;
    getline(cin, line);
    pos = line.find(' ', pos);
    while (pos != string::npos) {
        line.erase(pos, 1);
        pos = line.find(' ', pos);
    }
    pos = 0;
    while(line.find(",", pos) != string::npos) {
        pos = line.find(",", pos) + 1;
        n++;
    }
    n++;
    string names[n];
    pos = 0;
    while(line.find(",", pos) != string::npos) {
        istringstream istream;
        istream.str(line.substr(pos, line.find(",", pos) - pos));
        istream >> names[t++];
        pos = line.find(",", pos) + 1;
    }
    names[t] = line.substr(pos, line.size());
    for (i = 0; i < n; ++i) {
        cout << names[i] << endl;
    }
    cout << n << endl;
}