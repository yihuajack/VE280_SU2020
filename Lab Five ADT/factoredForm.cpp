//
// Created by Zhuoer Zhu on 10/06/2020.
//

#include "factoredForm.h"

quadraticFunction::quadraticFunction(float a_in, float b_in, float c_in) {
    // TODO: implement this constructor
    a = a_in;
    float delta = pow(b_in, 2) - 4 * a_in * c_in;
    if (delta == 0) {
        r1.real = -b_in / (2 * a_in);
        r2.real = -b_in / (2 * a_in);
        r1.imaginary = 0;
        r2.imaginary = 0;
    }
    else if (delta > 0) {
        r1.real = (-b_in - sqrt(delta)) / (2 * a_in);
        r2.real = (-b_in + sqrt(delta)) / (2 * a_in);
        r1.imaginary = 0;
        r2.imaginary = 0;
    }
    else {
        r1.real = -b_in / (2 * a_in);
        r2.real = -b_in / (2 * a_in);
        r1.imaginary = -sqrt(-delta) / (2 * a);
        r2.imaginary = sqrt(-delta) / (2 * a);
    }
}

float quadraticFunction::getA() const {
    return a;
}

float quadraticFunction::getB() const {
    // TODO: implement this function
    return -a * (r1.real + r2.real);
}

float quadraticFunction::getC() const {
    // TODO: implement this function
    return a * (r1.real * r2.real - r1.imaginary * r2.imaginary);
}

float quadraticFunction::evaluate(float x) {
    // TODO: implement this function
    return a * x * x + getB() * x + getC();
}

root quadraticFunction::getRoot() {
    // TODO: implement this function
    root r;
    float delta = pow(getB(), 2) - 4 * getA() * getC();
    r.roots[0].real = r1.real;
    r.roots[0].imaginary = r1.imaginary;
    r.roots[1].real = r2.real;
    r.roots[1].imaginary = r2.imaginary;
    if (delta == 0)
        r.realRootNum = 1;
    else if (delta > 0)
        r.realRootNum = 2;
    else
        r.realRootNum = 0;
    return r;
}

int quadraticFunction::intersect(quadraticFunction g) {
    // TODO: implement this function
    if (getA() != g.getA())
        return (pow(getB() - g.getB(), 2) - 4 * (getA() - g.getA()) * (getC() - g.getC()) >= 0) ? 1 : 0;
    else {
        return (getB() == g.getB() && getC() != g.getC()) ? 0 : 1;
    }
}