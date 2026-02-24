#include <iostream>
#include "String.h"

int main(){
    String testString("Hello World this should always be working");
    testString.printString();
    std::cout << "The length is: " << testString.returnLength() << std::endl;

    String copiedString(testString);
    copiedString.printString();
    std::cout << "The length is: " << copiedString.returnLength() << std::endl;

}