#include <iostream>
#include "String.h"

int main(){
    String testString("Hello");
    testString.printString();
    std::cout << "The length of this string is:" << testString.returnLength() << std::endl;

    //set new string to the array
    testString.set("Hola Mundo");
    testString.printString();
    std::cout << "The length of this string is:" << testString.returnLength() << std::endl;
}