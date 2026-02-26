#include <iostream>
#include "String.h"

int main(){
    
    String testString("gnirts elpmaxE xelpmoC");
    testString.printString();
    std::cout << "The length of this string is: " << testString.size() << std::endl;
    
    testString.reverse();
    testString.printString();
}

