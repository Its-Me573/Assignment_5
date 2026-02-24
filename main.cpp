#include <iostream>
#include "String.h"

int main(){
    String testString;//20 large
    testString.printString();
    std::cout << "The length of this string is:" << testString.returnLength() << std::endl;
}