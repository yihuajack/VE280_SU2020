/*
 * Lab2 Ex1 VE280 20SU
 * Created by: Yiqing Fan
 * Last update: May 25, 2020
 */

#include <iostream>
#include <cmath>

using namespace std;

#define RANGE 100000

bool isPrime[RANGE + 1];

// MODIFIES: isPrime[]
// EFFECTS: fill in isPrime[], true for prime, false otherwise
void generateIsPrime() {
    // TODO: implement Eratosthenes Sieve Algorithm
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i <= RANGE; i++)
        isPrime[i] = true;
    for (int i = 2; i < sqrt(RANGE) + 1; i++)
        if (isPrime[i])
            for (int j = i * i; j <= RANGE; j += i)
                isPrime[j] = false;
}

int main() {
    // TODO: generate lookup table

    // TODO: read input and check if each num is prime
    int i, n, t = 0;
    cin >> n;
    int array[n], output[n];
    for (i = 0; i < n; i++) {
        cin >> array[i];
    }
    generateIsPrime();
    for (i = 0; i < n; i++) {
        if (isPrime[array[i]])
            output[t++] = array[i];
    }
    for (i = 0; i < t; i++)
        cout << output[i] << " ";
    cout << endl;
    return 0;
}