#include <iostream>
#include <cmath>
#include <string>
#include <cstdlib>
using namespace std;
bool triangle_number(int n);
bool palindrome(int n);
bool power_number(int n);
bool abundant_number(int n);
int main() {
    int n, p;
    bool t = false;
    cout << "Please enter the integer and the test number: ";
    cin >> n >> p;
    while (n <= 0 || n > 10000000 || p < 1 || p > 4) {
        cout << "Please enter the integer and the test number: ";
        cin >> n >> p;
    }
    if (p == 1)
        t = triangle_number(n);
    else if (p == 2)
        t = palindrome(n);
    else if (p == 3)
        t = power_number(n);
    else if (p == 4)
        t = abundant_number(n);
    cout << t << endl;
}
// This function checks whether a positive integer is a triangle number.
bool triangle_number(int n) {
    int i = sqrt(2 * n);
    return (n == i * (i + 1) / 2) ? true : false;
}
// This function checks whether a positive integer is a palindrome.
bool palindrome(int n) {
    int i = 0;
    int s = n;
    while (s > 0) {
        i = i * 10 + s % 10;
        s /= 10;
    }
    return (i == n) ? true : false;
}
// This function checks whether a positive integer is a power number.
bool power_number(int n) {
    // Since n is a positive integer, we can suppose m >= 1 and is a prime number.
    if (n == 1) return true;
    for (int i = 2; i <= sqrt(n); i++)
        if (log(n) / log(i) == int(log(n) / log(i)))
            return true;
    /* An alternative way running for 5.7×10^(-6) less seconds than the way above testing n = 4826809
    If we use float instead of double, then it cannot deal with some large integers such as 2^23 and 17^5 correctly for the same accuracy.
    For example, if the accuracy is 0.0000001, then it cannot identify 1419857 but mistakes 8388609.
    As we use double here, for the accuracy 0.00000001 it just passes all tests for n <= 10000000.
    If the accuracy is 0.0000001, then it mistakes 4826810.
    Here to prevent any risks of deduction I still use the way above.
    for (int i = 2; i <= log(n) / log(2); i++)
        if (abs(pow(n, (double)1 / i) - int (pow(n, (double)1 / i))) <= 0.00000001)
            return true; */
    return false;
}
// This function checks whether a positive integer is a power number.
bool abundant_number(int n) {
    int sum = 1;
    for (int i = 2; i <= sqrt(n); i++)
        if (n % i == 0)
            sum += i + n/i;
    return (sum > n) ? true : false;
}