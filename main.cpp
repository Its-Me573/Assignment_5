#include <iostream>
#include "String.h"

int main(){
    //small to small-works
    //small to large-works
    //large to large-works
    //small and add nothing-works
    //large and add nothing-works
    //empty and add small-works
    //empty and add large-works
    String testString("");//length of 22
    testString.printString();
    std::cout << "The length of this string is: " << testString.size() << std::endl << std::endl << std::endl;
    
    testString.append_cstr("Hello World and others");//length of 22 and together 22
    testString.printString();
    std::cout << "The length of this string is: " << testString.size() << std::endl;

}