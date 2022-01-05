//
// Created by cyx on 20-5-29.
//

#ifndef INTLIST_IMPL_H
#define INTLIST_IMPL_H

#include <iostream>
#include "mylist.h"

template <class T>
void List<T>::print()
{
    node_t<T>* itr = first;
    while(itr){
        std::cout << itr->val;
        itr = itr->next;
    }
    std::cout << "\n";
}

template <class T>
void List<T>::removeAll() {
    while (!isEmpty()) {
        node_t<T> *victim = first;
        first = victim->next;
        delete victim;
    }
    last = nullptr;
}

template <class T>
void List<T>::copyFrom(const List &l) {
    if (l.isEmpty())
        return;
    if (!isEmpty())
        removeAll();
    node_t<T> *node = l.first;
    while (node) {
        insertBack(node->val);
        node = node->next;
    }
}

template <class T>
bool List<T>::isEmpty() const {
    return (first == nullptr) ? 1 : 0;
}

template <class T>
void List<T>::insertBack(T val) {
    if (isEmpty()) {
        first = new node_t<T>({nullptr, val});
        last = first;
    }
    else {
        last->next = new node_t<T>({nullptr, val});
        last = last->next;
    }
}

template <class T>
T List<T>::removeFront() {
    if (isEmpty())
        throw emptyList();
    else {
        node_t<T> *victim = first;
        first = first->next;
        if (!first)
            last = first;
        T result = victim->val;
        delete victim;
        return result;
    }
}

template <class T>
const node_t<T>* List<T>::returnHead() const {
    return first;
}

template <class T>
List<T>::List(): first(nullptr), last(nullptr) {}

template <class T>
List<T>::List(const List &l): first(nullptr), last(nullptr) {
    copyFrom(l);
}

template <class T>
List<T> &List<T>::operator=(const List &l) {
    if (this != &l)
        copyFrom(l);
    return *this;
}

template <class T>
List<T>::~List() {
    removeAll();
}

bool isLarger(const List<int> &a, const List<int> &b) {
    if (a.isEmpty() && b.isEmpty())
        return false;
    else {
        int i = 0, j = 0, k = 0, l = 0;
        const node_t<int> *p = a.returnHead();
        const node_t<int> *q = b.returnHead();
        while (p != nullptr) {
            i = 10 * i + p->val;
            p = p->next;
        }
        while (q != nullptr) {
            j = 10 * j + q->val;
            q = q->next;
        }
        while (i) {
            k = k * 10 + i % 10;
            i /= 10;
        }
        while (j) {
            l = l * 10 + j % 10;
            j /= 10;
        }
        return (k > l) ? 1 : 0;
    }
}

List<int> Add(const List<int> &a, const List<int> &b) {
    if (a.isEmpty())
        return b;
    if (b.isEmpty())
        return a;
    int i = 0, j = 0, k = 0, l = 0;
    const node_t<int> *p = a.returnHead();
    const node_t<int> *q = b.returnHead();
    List<int> list;
    while (p != nullptr) {
        i = 10 * i + p->val;
        p = p->next;
    }
    while (q != nullptr) {
        j = 10 * j + q->val;
        q = q->next;
    }
    while (i) {
        k = k * 10 + i % 10;
        i /= 10;
    }
    while (j) {
        l = l * 10 + j % 10;
        j /= 10;
    }
    i = k + l;
    while (i) {
        list.insertBack(i % 10);
        i /= 10;
    }
    return list;
}

#endif //INTLIST_IMPL_H
