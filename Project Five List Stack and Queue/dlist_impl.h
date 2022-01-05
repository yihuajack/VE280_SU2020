#ifndef __DLIST_IMPL_H__
#define __DLIST_IMPL_H__

#include "dlist.h"

template <class T>
bool Dlist<T>::isEmpty() const {
    // EFFECTS: returns true if list is empty, false otherwise
    return !first;
}

template <class T>
void Dlist<T>::insertFront(T *op) {
    // MODIFIES this
    // EFFECTS inserts o at the front of the list
    node *insertnode = new node({nullptr, nullptr, op});
    if (isEmpty())
        first = last = insertnode;
    else {
        insertnode->next = first;
        first->prev = insertnode;
        first = insertnode;
    }
}

template <class T>
void Dlist<T>::insertBack(T *op) {
    // MODIFIES this
    // EFFECTS inserts o at the back of the list
    node *insertnode = new node({nullptr, nullptr, op});
    if (isEmpty())
        first = last = insertnode;
    else {
        insertnode->prev = last;
        last->next = insertnode;
        last = insertnode;
    }
}

template <class T>
T *Dlist<T>::removeFront() {
    // MODIFIES this
    // EFFECTS removes and returns first object from non-empty list
    //         throws an instance of emptyList if empty
    if (isEmpty())
        throw emptyList();
    else {
        node *victim = first;
        first = first->next;
        if (!first)
            last = nullptr;
        else
            first->prev = nullptr;
        T *operation = victim->op;
        delete victim;
        return operation;
    }
}

template <class T>
T *Dlist<T>::removeBack() {
    // MODIFIES this
    // EFFECTS removes and returns last object from non-empty list
    //         throws an instance of emptyList if empty
    if (isEmpty())
        throw emptyList();
    else {
        node *victim = last;
        last = last->prev;
        if (!last)
            first = nullptr;
        else
            last->next = nullptr;
        T *operation = victim->op;
        delete victim;
        return operation;
    }
}

template <class T>
T *Dlist<T>::remove(bool (*cmp)(const T*, const T*), T* ref) {
    // MODIFIES this
    // REQUIRES there is only one or zero node in the list satisfying cmp(op, ref) == true
    // EFFECTS traverses through the whole list
    //         if `op` in a node satisfies cmp(op, ref) == true,
    //         removes and returns this object from the list
    //         returns NULL pointer if no such node exists
    if (isEmpty())
        return nullptr;
    else if (cmp(first->op, ref))
        return removeFront();
    else if (cmp(last->op, ref))
        return removeBack();
    else if (!first->next)
        return nullptr;
    else {
        node *victim = first->next;
        while (victim != last) {
            if (cmp(victim->op, ref)) {
                victim->next->prev = victim->prev;
                victim->prev->next = victim->next;
                T *operation = victim->op;
                delete victim;
                return operation;
            }
            victim = victim->next;
        }
        return nullptr;
    }
}

template <class T>
Dlist<T>::Dlist(): first(nullptr), last(nullptr) {
    // constructor
}

template <class T>
Dlist<T>::Dlist(const Dlist &l): first(nullptr), last(nullptr) {
    // copy constructor
    removeAll();
    copyAll(l);
}

template <class T>
Dlist<T> &Dlist<T>::operator=(const Dlist &l) {
    // assignment operator
    removeAll();
    copyAll(l);
    return *this;
}

template <class T>
Dlist<T>::~Dlist() {
    // destructor
    removeAll();
}

template<class T>
void Dlist<T>::removeAll() {
    // EFFECT: called by destructor/operator= to remove and destroy
    //         all list elements
    if (isEmpty())
        return;
    else {
        node *victim = first;
        while (victim != last) {
            victim = victim->next;
            delete victim->prev->op;
            delete victim->prev;
        }
        delete victim->op;
        delete victim;
        first = last = nullptr;
    }
}

template<class T>
void Dlist<T>::copyAll(const Dlist &l) {
    // EFFECT: called by copy constructor/operator= to copy elements
    //         from a source instance l to this instance
    if (l.isEmpty())
        return;
    else {
        node *temp = l.first;
        while (temp != l.last) {
            insertBack(new T(*temp->op));
            temp = temp->next;
        }
        insertBack(new T(*temp->op));
    }
}

#endif