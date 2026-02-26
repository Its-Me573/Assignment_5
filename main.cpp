#include <iostream>
#include "String.h"

int main(){
    String testString("Hello");
    testString.printString();
    std::cout << "The length of this string is: " << testString.size() << std::endl;
    String copyString(" world");
    copyString.printString();
    std::cout << "The length of this string is: " << copyString.size() << std::endl;

    std::cout << "Appending values from copyString into testString" << std::endl;

    testString.append(copyString);
    testString.printString();
    std::cout << "THe length of the new string is: " << testString.size() << std::endl;


}