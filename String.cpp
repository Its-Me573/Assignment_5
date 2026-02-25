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
void String::grow_if_needed(int needed) {
//First check which type of storage is being used for the string
    if(using_small()){//using small[]
         //If the size of the array-1 is < needed, allocate a array in the heap whose size will be needed and move all charcters over
        if(needed > SMALL_SIZE-1){

            //large is always nullptr when small is being used
            large = new char[needed + 1];//needed is all the character, +1 is the '\0'

            for(int i = 0; i < len+1; i++){//loop until the index of '\0'
                large[i] = small[i];
            }
            small[0] = '\0';//set small to an empty string
            //len = needed;//set the current array length to the needed length, else the length of the new array wont be known
            //std::cout << "From small to large" << std::endl;
        }else{//needed length does not exceed 15 characters
            //std::cout << "From small to nothing, size doesnt exceed" << std::endl;
            return;
        }
    }else{//using large
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
            //std::cout << "From large of size -> " << len << " <- to large of size -> " << needed;

            //len = needed;
        }else{//needed size does exceed length of the characters in the array
            //std::cout << "Large does not need the size changed" << std::endl; 
            return;
        }
    }
}

/** Sets the current string storage to the value of cstr
 * Deallocates any current storage and allocates new storage if needed
 * before copying characters from cstr
 * 
 * @param cstr The C-style string which cstr is pointing to
 * @return void
 */
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

/** Sets len to 0, deallocates large is its being used, deletes all characters from small if being used
 * Sets this.len to other.len
 * Copies over all characters if small is being used
 * Copies over all characters after allocating a dynamic array if large is being used
 * 
 * @param other The other object which *ths is copying from
 * @return void
 */
void String::set(const String& other){
      //see storage being used for the string and deallocate those indexes
    if(len <= 15){//small is being used
        for(int i = 0; i < 16; i++){
            small[i] = '\0';
        }
        large = nullptr;
    }else if(len > 15){//large is being used
        delete[] large;
        large = nullptr;
    }

    //get the size that other will be
    len = other.len;

    if(other.len <= 15){
        for(int i = 0; i < other.len + 1; i++){
            small[i] = other.small[i];
        }
        large = nullptr;
    }else if(other.len > 15){
        large = new char[other.len + 1];
        for(int i = 0; i < other.len + 1; i++){
            large[i] = other.large[i];
        }
    }
}

/** Checks what storeage type is being used
 * If storage is small the capacity will be 15 due to small only storing 15 characters
 * If storage is large, capacity will be the length of the characters, '\0' is not included in length of strings
 * @return 15 or the length of the characters, '\0' is not included in the length of strings
 */
int String::capacity() const{//the storage capacity of the current object
    if(len <= 15){
        return 15;
    }else{
        return len;
    }
}

/** Checks the current string storage being used
 * If small is being used, return small
 * If large is being used, return large 
 * 
 * @return pointer to small array or large dynamic array
 */
const char* String::c_str() const{
    if(using_small()){
        return small;
    }else{
        return large;
    }
}

/** Checks is index is within the bounds of the string
 * Returns the character at index if within range and '\0' if out of bounds
 * @param index The index of the character whose character is returned
 * @return The character at index or '\0'
 */
char String::get_at(int index) const {
     if(index < 0 || index > len-1){
        return '\0';
     }
     if(using_small()){
        return small[index];
     }else{
        return large[index];
     }
}

/** Check for the storage type
 * and set the first character to '\0' to signify an empty string
 * Set len to 0
 * 
 * @return void
 */
void String::clear(){
    len = 0;
    if(using_small()){
        small[0] = '\0';
    }else{
        large[0] = '\0';
    }
}

/** Grow the string if it can't hold 1 more character at the end
 * Check whether small or large storage is being used and
 * put ch at the end of the character arrays\
 * Increases the len by 1 for the new character
 * @param ch The character appended to the end of the string
 * @return void
 */
void String::append_char(char ch){
    //check if the string needs to grow to store 1 at the end
    grow_if_needed(len + 1);

    //anything after this will be valid
    if(using_small()){
        small[len] = ch;
    }else{
        large[len] = ch;
    }
    len++;
}

/** Adds the parameter string to the end of the current objects string
 * First gets the length of cstr and grows the string to the length of the new string
 * which is current length + cstr length
 * Insert values into the current string starting at the length of the previous string
 * and until the length of the new string, adding each character of cstr including '\0'
 * 
 * @param cstr the C-style string being added
 * @return void
 */
void String::append_cstr(const char* cstr){
    //first get the parameter string size
    int appendStrLen = 0;
    int lengthOfNewString = 0;
    const char* tempCSTR = cstr;//starting position
    while(*cstr != '\0'){
        appendStrLen++;
        cstr++;
    }
    cstr = tempCSTR;//reset  cstr back to beginning position
    lengthOfNewString = len + appendStrLen;
    //std::cout << "The length of the parameter string is: " << appendStrLen << std::endl;

    grow_if_needed(lengthOfNewString);//increase size of array without changing the len
    /**
    std::cout << "Length is: " << len << std::endl;
    std::cout << "Length of new string is: " << lengthOfNewString << std::endl;
    std::cout << "cstr is currently pointing to: " << *cstr << std::endl;
    **/
    for(int i = len; i < lengthOfNewString + 1; i++){//includes '\0' in the string because of +1
        if(using_small()){
            small[i] = cstr[i - len];
        }else{
            large[i] = cstr[i - len];
        }  
    }
    len = lengthOfNewString;
}

void String::append(const String& other){
    /**
     *void append(const String& other);
     */
    //first get the parameter string size
        int appendStrLen = other.len;
        int lengthOfNewString = len + other.len;

        grow_if_needed(lengthOfNewString);

        for(int i = 0; i < lengthOfNewString + 1; i++){
            if(using_small()){//current object is using small storage after resizing
                if(other.using_small()){//current object is small and the other object is small

                }else{//current object is small and other object is large

                }
            }else{//current object will use large storage after resizing
                if(other.using_small()){//current object is large and other object is small

                }else{//current object is using large and other object is using large

                }
            }
        }
        

}