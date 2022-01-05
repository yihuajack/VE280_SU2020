#include <iostream>
#include "my_stack.h"

int main()
{
    try{
        Stack<int> s1, s2;
        s2.push(6);
        s1 = s2;
    }
    catch(stackEmpty){
        std::cout << "Oops, looks like I'm empty!\n";
    }
}