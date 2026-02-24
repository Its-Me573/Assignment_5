#include "String.h"

/**
 * Default constructor for String objects
 * Sets the large array pointer = nullptr
 */
String::String(){
    //create a "String", string are arrays of characters
    small[0] = '\0';//small and large arrays coexist, but their usage
                    //depends on the size of the current string
    large = nullptr;//prevent free() core dump error
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
        large = nullptr;
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

/**
 * Private helper for Strings
 * Will increase the size of a string if the needed space is greater than the current len
 * Will compare needed size with the length of small[] for string stored using small and will copy value to a larger dynamic
 * Compared the size of needed with large arrays and will copy the values into a larger dynamic array
 * 
 * @return void
 */
void String::grow_if_needed(int needed){//increases the size of the array if needed, without changing the length of the characters in it
//The buffer is just the indexes for the characters of th string
//checks if the current string can hold the required size and increases the size of the array if needed

//First check which type of storage is being used for the string
    if(len <= 15){//using small[]
         //If the size of the array-1 is < needed, allocate a array in the heap whose size will be needed and move all charcters over
        if(needed > SMALL_SIZE-1){

            //large is always nullptr when small is being used
            large = new char[needed + 1];//needed is all the character, +1 is the '\0'

            for(int i = 0; i < len+1; i++){//loop until the index of '\0'
                large[i] = small[i];
            }
            small[0] = '\0';//set small to an empty string
            len = needed;//set the current array length to the needed length, else the length of the new array wont be known
            std::cout << "From small to large" << std::endl;
        }else{//needed length does not exceed 15 characters
            std::cout << "From small to nothing, size doesnt exceed" << std::endl;
            return;
        }
    }else if(len > 15){//using large
        if(needed > len){//(needed characters excluding '\0') > (current length of characters excluding '\0')
            char* tempLarge = new char[needed + 1];//temp pointer for array of size needed + 1 for the '\0'

            //copy characters from large to tempLarge
            for(int i = 0; i < len + 1; i++){
                tempLarge[i] = large[i];
            }

            //delete the array for large, set large to nullptr
            delete[] large;
            large = nullptr;
            //allocate a new array for large whose size is equal to tempLarge
            large = new char[needed + 1];

            //copy characters from tempLarge to large
            for(int i = 0; i < needed + 1; i++){
                large[i] = tempLarge[i];
            }

            //delete the array for tempLarge and set to nullptr
            delete[] tempLarge;
            tempLarge = nullptr;
            //set len to the needed size that the array was changed to
            std::cout << "From large of size -> " << len << " <- to large of size -> " << needed;

            len = needed;
        }else{//needed size does exceed length of the characters in the array
            std::cout << "Large does not need the size changed" << std::endl; 
            return;
        }
    }
}


void String::set(const char* cstr){
//see storage being used for the string and deallocate those indexes
    if(len <= 15){//small is being used
        for(int i = 0; i < 16; i++){
            small[i] = '\0';
        }
    }else if(len > 15){//large is being used
        delete[] large;
        large = nullptr;
    }
    len = 0;

//get the values from cstr and move them into their respective storage
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
    //string smaller than 16 characters --------->check in future for any error regarding <= 15
    if(len <= 15){
        for(int i = 0; i < len; i++){
            //set each value of the dereferenced pointer at the index i
            small[i] = *(cstr + i);
        }
        ///this index will have '\0' to signify the end of the string
        small[len] = '\0';
        large = nullptr;
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
}