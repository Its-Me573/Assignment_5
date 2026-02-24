#include <iostream>
#include "String.h"

int main(){
    String testString("Hello World much bigger array");//20 large
    testString.printString();
    const char* testPTR = testString.c_str();
    std::cout << "The current value at test string is: " << *(testPTR+6) << std::endl;

    std::cout << testString.get_at(29) << std::endl;
}