/*
 * VE280 Lab 3, SU2020.
 * Written by Guoxin Yin
 */

#include <iostream>

using namespace std;

const int MAXSIZE = 10;

bool canWin(int count, int arr[], int position) {
    // EFFECTS: return whether the player can win given the start position
    // and the card sequence
    
    // TODO: implement this function
    if (arr[position] == 280) return 1;
    else if (arr[position] != -1 && position + arr[position] >= 0 && position + arr[position] < count) {
        return canWin(count, arr, position + arr[position]);
        arr[position] = -1;
    }
    else if (arr[position] != -1 && position - arr[position] >= 0 && position - arr[position] < count) {
        return canWin(count, arr, position - arr[position]);
        arr[position] = -1;
    }
    else return 0;
}

int main() {
    int count;
    cin >> count;
    int arr[MAXSIZE];
    for (int i = 0; i < count; ++i) {
        cin >> arr[i];
    }
    int position;
    cin >> position;
    cout << canWin(count, arr, position);
}