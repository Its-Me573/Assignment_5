#include "String.h"

/**
 * Default constructor for String objects
 * Sets the large array pointer = nullptr
 */
String::String(){
    //create a "String", string are arrays of characters
    small[0] = '\0';//small and large arrays coexist, but their usage
                    //depends on the size of the current string
    large = nullptr;
    len = 0;
}

/** Constructor for String objects, takes a C-style string as an input
 * If the string is empty, the string stored in the array will be empty with the size of 0
 * Strings whose size is less than 16 will be stored in the small[] array
 * String whose size is bigger than 16 will be stored in a dynamic array of the length of the string
 * @param cstr the C-style string which the char pointer is pointing to
 */
String::String(const char* cstr){
    //Note:The size of the string will be 1 bigger than every normal character
    //Since the character '\0' is meant to be at the end of every string
    //read from the C-style string(cstr), and gets the size of the string
    
    //store the initial value of *cstr to reference back
    const char* tempCSTR = cstr; 
    int tempLen = 0;    
    
    //loop through array until '\0' is found
    while(*cstr != '\0') {    
        tempLen++;
        cstr++;
    }

    len = tempLen;
    cstr = tempCSTR;
    
    //empty string------------------------------------------------------------
    if(len == 0) {
        small[0] = '\0';
    }
    //-------------------------------------------------------------------------
    //string smaller than 16 characters --------->check in future for any error regarding < 16
    if(len <= 15){
        for(int i = 0; i < len; i++){
            //set each value of the dereferenced pointer
            small[i] = *(cstr + i);
        }
        ///this index will have '\0' to signify the end of the string
        small[len] = '\0';
    }
    //--------------------------------------------------------------------------
    if(len > 15){
        //create new heap array of size len
        large = new char[len + 1];

        for(int i = 0; i < len; i++){
            large[i] = *(cstr + i);
        }
        large[len] = '\0';
    }

    // std::cout << "This string has a length of: " << len << std::endl;
    // for(int i = 0; i < len+1; i++){
    //     if(large[i] == '\0'){
    //         std::cout << "\\0" << std::endl;
    //         break;
    //     }
    //     std::cout << large[i];
    // }
    
    /**
    std::cout << "This string has a length of: " << len << std::endl;
    std::cout << "The small string array is: ";
    for(int i = 0; i < len+1; i++){
        if(small[i] == '\0'){
            std::cout << " End of the string" << std::endl;
            break;
        }
        std::cout << small[i];
        
    }
    std::cout << std::endl;
    */
}

/** Creates a deep copy of the other object
 * Sets this.length = other.length
 * check which string storage is being used and iterates through it 
 * copying values
 * @param other The String object whose value is being copied from
 */
String::String(const String& other){
    this->len = other.len;
    //check if other uses small or large string storage
    if(other.len > 15){// more than 15 characters which is the max for small[]
        large = new char[other.len + 1];
        for(int i = 0; i < len + 1; i++){
            large[i] = other.large[i];
        }
    }else if(other.len <= 15){//less than or equal to 15 characters which is the required amount for small
        for(int i = 0; i < len + 1; i++){
            small[i] = other.small[i];
        }
    }
}

void String::printString() const{
    std::cout << "The current string is: ";
    if(len > 15){//print from the pointer
        for(int i = 0; i < len + 1; i++){
            if(large[i] == '\0'){
                std::cout << "\\0";
                continue;
            }
            std::cout << large[i];
        }
    }else{//print from the small[]
        for(int i = 0; i < len + 1; i++){
            if(small[i] == '\0'){
                std::cout << "\\0";
                continue;
            }
            std::cout << small[i];
        }
    }
    std::cout << std::endl;
}

int String::returnLength() const{
    return len;
}

/**
 * Destructor for the String class
 * Deletes the char heap array if large is not a nullptr 
 */
String::~String(){
    if(large != nullptr){
        delete[] large;
        large = nullptr;
    }
}