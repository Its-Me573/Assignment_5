#ifndef MY_STRING_H
#define MY_STRING_H

//delete before turning in, or it wont compile
#include <iostream>

class String {

private:
    static const int SMALL_SIZE = 16;


    //small string are 15 characters long with the 16th being '\0'
    char small[SMALL_SIZE]; // always present, used when length < 15

    //points to array inside of the heap, will be nullptr when the 
    //small string is used
    char* large; // NULL if using small buffer, otherwise heap

    /**
     * siez of the string in the array
     * Does not include the last character which is '\0'
     */
    int len; // actual number of characters(not counting null)


    bool using_small() const {
        return large == nullptr;
    }
    // Internal helper: copy characters from src to dst (up to n chars)
    void copy_chars(char* dst, const char* src, int n){
        for (int i = 0; i < n; ++i) {
            dst[i] = src[i];
        }
    }
    // Internal helper: set terminator
    void set_null_terminator() {
        if (using_small()) {
            small[len] = '\0';
        } else {
            large[len] = '\0';
        }
    }
    // Internal helper: set terminator
    bool is_whitespace(char c) {
        return c == ' ' || c == '\t' || c == '\n' || c == '\r';
    }

    // Internal helper: grow to at least new_capacity characters (excluding null)

public:

    void grow_if_needed(int new_capacity_needed);
    
    String(); // empty string
    String(const char* cstr); // from null-terminated C string
    String(const String& other); // copy
    ~String();

    //Helper functions for debugging
    void printString() const;
    int returnLength() const;


    void set(const char* cstr);
    // void set(const String& other);
    
    // int size() const { return len; }
    // int length() const { return len; }
    // int capacity() const;
    // bool is_empty() const { return len == 0; }
    // const char* c_str() const;
    // char get_at(int index) const;
    
    // void clear();
    // void append_char(char ch);
    // void append_cstr(const char* cstr);
    // void append(const String& other);
    // // void prepend_char(char ch);
    // // void prepend_cstr(const char* cstr);
    // // void prepend(const String& other);
    // void erase(int pos, int count = 1);
    
    // void make_upper();
    // void make_lower();
    
    // void trim_left();
    // void trim_right();
    // void trim();
    
    // void insert(int pos, const String& other);
    // void insert_cstr(int pos, const char* cstr);
    // void insert_char(int pos, char ch);
    
    // void reverse();
    
    // int compare(const String& other) const;
    // bool equals(const String& other) const;
    // bool equals_ignore_case(const String& other) const;
    // int find(const String& pattern) const;
    // int find_cstr(const char* pattern) const;
    // int find_char(char ch) const;
    
    // void print() const;
};
#endif // MY_STRING_H