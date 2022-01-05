#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include "dlist_impl.h"

using namespace std;

template <class T>
class Stack {
    // OVERVIEW: contains a stack based on Dlist (double-ended list)
 public:
    void push(T *op);
    T *pop();
    T *top();
    bool empty();
 private:
    Dlist<T> dlist;
};

template <class T>
void Stack<T>::push(T *op) {
    // MODIFIES: this
    // EFFECTS: push op at the top of the stack
    dlist.insertFront(op);
}

template <class T>
T *Stack<T>::pop() {
    // MODIFIES: this
    // EFFECTS: pop op at the top of the stack
    return dlist.removeFront();
}

template <class T>
T *Stack<T>::top() {
    // EFFECTS: return the top of the stack
    T *topop = pop();
    push(topop);
    return topop;
}

template <class T>
bool Stack<T>::empty() {
    // EFFECTS: returns true if stack is empty, false otherwise
    return dlist.isEmpty();
}

bool isOperand(const string& s) {
    // EFFECTS: return true if string s is an operand
    return (s == "0") ? true : atoi(s.c_str());
}

bool getRPN(const char c, string& output, const int precedence[], Stack<char>& operators) {
    // REQUIRES: precedence includes paranthesis and the four operators in order.
    // MODIFIES: output, operators
    // EFFECTS: convert an infix expression to an RPN one; return true if successfully got RPN.
    if ((c >= 48 && c <= 57) || (c == ' ' && output.back() != ' ' && !output.empty())) {
        output += c;
        return true;
    }
    else if (c == '+' || c == '-' || c == '*' || c == '/') {
        while (!operators.empty() && precedence[*operators.top() - 40] >= precedence[c - 40] && *operators.top() != '(') {
            char *op = operators.pop();
            output += *op;
            output += " ";
            delete op;
        }
        operators.push(new char (c));
        return true;
    }
    else if (c == '(') {
        operators.push(new char (c));
        return true;
    }
    else if (c == ')') {
        while (!operators.empty() && *operators.top() != '(') {
            char *op = operators.pop();
            if (output.back() != ' ')
                output += " ";
            output += *op;
            delete op;
        }
        if (!operators.empty() && *operators.top() == '(') {
            char *op = operators.pop();
            delete op;
            return true;
        }
        else {
            cout << "ERROR: Parenthesis mismatch" << endl;
            return false;
        }
    }
    else
        return true;
}

void calculateRPN(Stack<int>& operands, const string& token, int *operand) {
    // REQUIRES: operand is '+', '-', '*', or '/'.
    // MODIFIES: operands, operand
    // EFFECTS: operate the result according to the operand.
    int *result = operands.pop();
    switch (*token.c_str()) {
        case '+':
            *result += *operand;
            break;
        case '-':
            *result -= *operand;
            break;
        case '*':
            *result *= *operand;
            break;
        case '/':
            *result /= *operand;
            break;
        default:
            break;
    }
    delete operand;
    operands.push(result);
}

bool getVAL(const string& token, Stack<int>& operands) {
    // MODIFIES: operands
    // EFFECTS: evaluate an RPN expression; return true if successfully got value.
    if (isOperand(token)) {
        operands.push(new int (stoi(token)));
        return true;
    }
    else {
        int *operand = operands.pop();
        if (operands.empty()) {
            cout << "ERROR: Not enough operands" << endl;
            delete operand;
            return false;
        }
        else if (token == "/" && *operand == 0) {
            cout << "ERROR: Divide by zero" << endl;
            delete operand;
            return false;
        }
        else {
            calculateRPN(operands, token, operand);
            return true;
        }
    }
}

int main() {
    // EFFECTS: implement a reverse polish notation calculator.
    char c;
    int precedence[8] = {};
    precedence[0] = 2;
    precedence[1] = 2;
    precedence[2] = 1;
    precedence[7] = 1;
    string output, token;
    Stack<char> operators;
    Stack<int> operands;
    while (cin.get(c)) {
        if (c == '\n')
            break;
        else if (!getRPN(c, output, precedence, operators))
            return 0;
    }
    while (!operators.empty()) {
        if (*operators.top() == '(' || *operators.top() == ')') {
            cout << "ERROR: Parenthesis mismatch" << endl;
            return 0;
        }
        if (output.back() != ' ')
            output += " ";
        char *op = operators.pop();
        output += *op;
        delete op;
    }
    cout << output << endl;
    istringstream iss(output);
    while (iss >> token) {
        if (!getVAL(token, operands))
            return 0;
    }
    if (operands.empty())
        cout << "ERROR: Not enough operands" << endl;
    else {
        int *result = operands.pop();
        if (!operands.empty())
            cout <<  "ERROR: Too many operands" << endl;
        else
            cout << *result << endl;
        delete result;
    }
}