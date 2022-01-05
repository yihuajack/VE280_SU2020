/*
 * This is an exercise of VE280 Lab 1, SU2020.
 * Written by Martin Ma.
 * Latest Update: 5/10/2020.
 * Copyright © 2020 Mars-tin. All rights reserved.
 */

#include <iostream>
#include <cctype>
#include <cstring>
using namespace std;


// EFFECTS: return true if the password is a valid one
bool isValidPassword(char password[]){
    // TODO: Implement this function.
    bool alpha = 0, num = 0, non = 0;
    int len;
    len = strlen(password);
    for (int i = 0; i < len; i++) {
        if (isalpha(password[i]))
            alpha = 1;
        if (isdigit(password[i]))
            num = 1;
        if (ispunct(password[i]))
            non = 1;
    }
    if (alpha && num && non)
        return true;
    else
        return false;
}


int main(){
    char password[50] = {};
    cin >> password;
    cout << isValidPassword(password) << endl;
}
