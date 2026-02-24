#include <iostream>
#include "String.h"

int main(){
    String testString("Hello World");//20 large
    testString.printString();
    const char* testPTR = testString.c_str();
    std::cout << "The current value at test string is: " << *(testPTR+6) << std::endl;
}