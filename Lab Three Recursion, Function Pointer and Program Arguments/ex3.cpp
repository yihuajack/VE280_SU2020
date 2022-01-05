#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

int main(int argc, char *argv[]) {
    int i, j, m, n, sint, sum = 0;
    bool dataoperation = false;
    cin >> n;
    int arr[n];
    for (i = 0; i < n; i++) {
        cin >> arr[i];
        sum += arr[i];
    }
    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--help") == 0) {
            cout << "Hey, I love Integers." << endl;
            return 0;
        }
    }
    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--add") == 0) {
            dataoperation = true;
            for (j = 1; j < argc; j++) {
                if (strcmp(argv[j], "--verbose") == 0)
                    cout << "This is add operation." << endl;
            }
            cout << sum << endl;
        }
    }
    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--small") == 0) {
            dataoperation = true;
            sint = atoi(argv[i + 1]);
            m = arr[0];
            for (j = 0; j < n; j++) {
                if (arr[j] < m)
                    m = arr[j];
            }
            for (j = 1; j < argc; j++) {
                if (strcmp(argv[j], "--verbose") == 0)
                    cout << "This is small operation." << endl;
            }
            cout << sint + m << endl;
        }
    }
    if (dataoperation == false)
        cout << "No work to do!" << endl;
}