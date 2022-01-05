/*
 * This is an exercise of VE280 Lab 1, SU2020.
 * Written by Martin Ma.
 * Latest Update: 5/10/2020.
 * Copyright © 2020 Mars-tin. All rights reserved.
 */

#include <iostream>
using namespace std;


// EFFECTS: return the trace of the Laplacian of the weight matrix.
int traceLaplacian(int weight[][50], int size){
    // TODO: Implement this function.
    int D[50][50] = {};
    int L[50][50] = {};
    int tr = 0;
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            D[i][i] += weight[i][j];
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            L[i][j] = D[i][j] - weight[i][j];
    for (int i = 0; i < size; ++i)
        tr += L[i][i];
    return tr;
}


int main(){
    int size, trace;
    int weight[50][50] = {};
    cin >> size;
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            cin >> weight[i][j];
    trace = traceLaplacian(weight, size);
    cout << trace << endl;
}
