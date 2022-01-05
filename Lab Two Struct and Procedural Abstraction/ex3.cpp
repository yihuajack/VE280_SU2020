/*
 * Lab2 Ex3 VE280 20SU
 * Created by: Yiqing Fan
 * Last update: May 25, 2020
 */

#include <cmath>
#include <iostream>

using namespace std;

#define MAX_LEN 1024

int square[MAX_LEN][MAX_LEN];

void initSquare(int len) {
    for (int i = 0; i < len; ++i) {
        for (int j = 0; j < len; ++j) {
            square[i][j] = 1;
        }
    }
}

// REQUIRES: the square with left-upper corner at (x,y)
//           and length len is within square[MAX_LEN][MAX_LEN]
// MODIFIES: square[][]
// EFFECTS: fully update the specified square
void updateSquare(int x, int y, int len) {
    // TODO: check boundary condition
    len /= 2;
    if (len < 1) return;
    // TODO: update left upper square
    for (int i = x; i < x + len; ++i) {
        for (int j = y; j < y + len; ++j) {
            square[i][j] = 0;
        }
    }
    // TODO: recursive call for remaining 3 squares
    updateSquare(x + len, y, len);
    updateSquare(x, y + len, len);
    updateSquare(x + len, y + len, len);
}

void printSquare(int len) {
    for (int i = 0; i < len; ++i) {
        for (int j = 0; j < len; ++j) {
            cout << square[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    // TODO: read input
    int n;
    cin >> n;
    int len = pow(2, n);
    // TODO: init, update, and print square
    initSquare(len);
    updateSquare(0, 0, len);
    printSquare(len);
    return 0;
}
