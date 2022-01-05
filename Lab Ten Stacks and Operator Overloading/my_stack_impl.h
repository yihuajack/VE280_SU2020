/*
 * This is an exercise of VE280 Lab 10, SU2020.
 * Written by Martin Ma.
 * Latest Update: 7/17/2020.
 * Copyright © 2020 Mars-tin. All rights reserved.
 */

#ifndef MY_STACK_IMPL_H
#define MY_STACK_IMPL_H

#include <iostream>
#include "my_stack.h"

template <class T>
void Stack<T>::removeAll() {
    while (!isEmpty()) {
        Node<T> *victim = head;
        head = victim->next;
        delete victim;
    }
}

template <class T>
void Stack<T>::copyFrom(const Stack &s) {
    if (s.isEmpty())
        removeAll();
    else {
        if (!isEmpty())
            removeAll();
        Node<T> *temp = s.head;
        Node<T> *end = new Node<T>({nullptr, temp->val});
        head = end;
        temp = temp->next;
        while (temp) {
            end->next = new Node<T>({nullptr, temp->val});
            end = end->next;
            temp = temp->next;
        }
        end->next = nullptr;
    }
}

template <class T>
Stack<T>::Stack(): head(nullptr) {}

template <class T>
Stack<T>::Stack(const Stack &s): head(nullptr) {
    copyFrom(s);
}

template <class T>
Stack<T> &Stack<T>::operator = (const Stack &s) {
    if (this != &s)
        copyFrom(s);
    return *this;
}

template <class T>
Stack<T>::~Stack() {
    removeAll();
}

template <class T>
void Stack<T>::print()
{
    Node<T>* itr = head;
    while(itr){
        std::cout << itr->val;
        itr = itr->next;
    }
    std::cout << "\n";
}

template <class T>
bool Stack<T>::isEmpty() const {
    return !head;
}

template <class T>
size_t Stack<T>::size() const {
    size_t s = 0;
    Node<T> *node = head;
    while (node) {
        node = node->next;
        s++;
    }
    return s;
}

template <class T>
void Stack<T>::push(T val) {
    Node<T> *temp = new Node<T>({head, val});
    head = temp;
}

template <class T>
void Stack<T>::pop() {
    if (isEmpty()) {
        stackEmpty stackempty;
        throw stackempty;
    }
    else {
        Node<T> *temp = head;
        head = head->next;
        delete temp;
    }
}

template <class T>
T Stack<T>::top() const {
    if (isEmpty()) {
        stackEmpty stackempty;
        throw stackempty;
    }
    else
        return head->val;
}

template <class T>
void reverse(Stack<T> &s) {
    Stack<T> reversedStack;
    while (!s.isEmpty()) {
        reversedStack.push(s.top());
        s.pop();
    }
    s = reversedStack;
}

template <class T>
Stack<T> operator +(Stack<T> &s, T val) {
    Stack<T> newStack = s;
    reverse(newStack);
    newStack.push(val);
    reverse(newStack);
    return newStack;
}

template <class T>
Stack<T> operator +(Stack<T> &first, Stack<T> &second) {
    Stack<T> newStack = first, temp = second;
    reverse(newStack);
    while (!temp.isEmpty()) {
        newStack.push(temp.top());
        temp.pop();
    }
    reverse(newStack);
    return newStack;
}

#endif //MY_STACK_IMPL_H