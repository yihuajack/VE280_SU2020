//
// Created by Zhuoer Zhu on 10/06/2020.
//

#include <cmath>
#include "standardForm.h"

quadraticFunction::quadraticFunction(float a_in, float b_in, float c_in) {
    // TODO: implement this constructor
    a = a_in;
    b = b_in;
    c = c_in;
}

float quadraticFunction::getA() const {
    return a;
}

float quadraticFunction::getB() const {
    return b;
}

float quadraticFunction::getC() const {
    return c;
}

float quadraticFunction::evaluate(float x) {
    // TODO: implement this function
    return getA() * x * x + getB() * x + getC();
}

root quadraticFunction::getRoot() {
    // TODO: implement this function
    root r;
    float delta = pow(getB(), 2) - 4 * getA() * getC();
    if (delta == 0) {
        r.realRootNum = 1;
        r.roots[0].real = -getB() / (2 * getA());
        r.roots[1].real = -getB() / (2 * getA());
        r.roots[0].imaginary = 0;
        r.roots[1].imaginary = 0;
    }
    else if (delta > 0) {
        r.realRootNum = 2;
        r.roots[0].real = (-getB() - sqrt(delta)) / (2 * getA());
        r.roots[1].real = (-getB() + sqrt(delta)) / (2 * getA());
        r.roots[0].imaginary = 0;
        r.roots[1].imaginary = 0;
    }
    else {
        r.realRootNum = 0;
        r.roots[0].real = -getB() / (2 * getA());
        r.roots[1].real = -getB() / (2 * getA());
        r.roots[0].imaginary = -sqrt(-delta) / (2 * a);
        r.roots[1].imaginary = sqrt(-delta) / (2 * a);
    }
    return r;
}

int quadraticFunction::intersect(quadraticFunction g){
    // TODO: implement this function
    if (getA() != g.getA())
        return (pow(getB() - g.getB(), 2) - 4 * (getA() - g.getA()) * (getC() - g.getC()) >= 0) ? 1 : 0;
    else {
        return (getB() == g.getB() && getC() != g.getC()) ? 0 : 1;
    }
}