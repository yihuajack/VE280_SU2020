#include <iostream>
#include "node.h"

using namespace std;

Node::Node(int _value, int _n): value(_value), child_num(0), n(_n), parent(nullptr), children(new Node*[_n]) {}

Node::~Node() {
    for (int i = 0; i < child_num; i++) {
         delete children[i];
    }
    delete[] children; 
}

void Node::addChild(Node *child) {
    if (child->child_num == n)
        throw tooManyChildren();
    child->parent = this;
    children[child_num++] = child;
}

void Node::addChild(int _value) {
    if (this->child_num == n)
        throw tooManyChildren();
    Node *p = new Node(_value,n);
    addChild(p);
}

void Node::traverse() {
    cout << this->value << " ";
    for (int i = 0; i < child_num; i++) {
        children[i]->traverse();
    }
}

bool Node::contain(Node *sub) {
    int i;
    bool flag = true;
    if (this->child_num == 0) {
        return (sub->value == value && sub->child_num == 0) ? 1 : 0;
    }
    if (sub->value == value && sub->child_num == child_num) {
        for (i = 0; i < child_num; i++) {
            flag = flag && children[i]->contain(&((*sub)[i]));
        }
        return flag;
    }
    else {
        for (i = 0; i < child_num; i++) {
            if (children[i]->contain(sub)) {
                flag = false;
                break;
            }
        }
        return !flag;
    }
}

int Node::getHeight() {
    if (child_num == 0)
        return 0;
    else {
        int height = children[0]->getHeight();
        for (int i = 0; i < child_num; i++) {
            if (children[i]->getHeight() > height)
                height = children[i]->getHeight();
        }
        return ++height;
    }
}

Node &Node::operator[](int i) {
    if (i < 0 || i >= child_num)
        throw invalidIndex();
    else
        return *(children[i]);
}
