#ifndef _INF_INT_H_
#define _INF_INT_H_

#include <iostream>
#include <string>
#include <regex>
using namespace std;

class inf_int
{
private :
    string digits;
    unsigned int length;
    bool thesign;            // true if positive , false if negative.
                             // ex) 15311111111111111 -> digits="11111111111111351", length=17, thesign=true;
                             // ex) 12345555555555 -> digits="12345555555555", length=14, thesign=false
    void erasePreZeros();    // Remove prefixed 0

public :
    inf_int();               // assign 0 as a default value
    inf_int(int);            // interger contructor
    inf_int(const inf_int&); // copy constructor
    inf_int(string);         // base constuctor (all contructor call this constructor)
    ~inf_int();              // destructor

    inf_int& operator=(const inf_int&); // assignment operator

    friend bool operator==(const inf_int& , const inf_int&);
    friend bool operator!=(const inf_int& , const inf_int&);
    friend bool operator>(const inf_int& , const inf_int&);
    friend bool operator<(const inf_int& , const inf_int&);

    friend inf_int operator+(const inf_int& , const inf_int&);
    friend inf_int operator-(const inf_int& , const inf_int&);
    friend inf_int operator*(const inf_int& , const inf_int&);
    // friend inf_int operator/(const inf_int& , const inf_int&); // not required

    friend ostream& operator<<(ostream& , const inf_int&);
    friend istream& operator>>(istream& , inf_int&);
};

#endif