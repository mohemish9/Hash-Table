/**
 * \file stringutil.cpp
 * \author CS 70 Provided Code.
 *
 * \brief Miscellaneous utility code for strings
 */
#include "stringutils.hpp"

#include <iostream>
#include <cctype>

using namespace std;

bool getWord(istream& in, string& word)
{
    bool returnValue = false;
    
    word = "" ;           // ensure "word" is empty
    char c;               // The most recently-read character

    while(in.get(c) && isspace(c)) {
        //fist, munch up any leading whitespace
    }

    // c now contains the first non-whitespace character
    if (isalpha(c)){
        word += c;
        returnValue = true;
    }
        
    // Loop until end of input (or we break out of the loop,
    // whichever comes first).
    while (in.get(c)) {
        
        // Abort the loop after encountering whitespace
        if (isspace(c)) break;

        // Abort the loop after reading a non-letter
        if (! isalpha(c)) break;

        // otherwise, we've read a letter; append to our word
        word += c;
    }

    return returnValue;
}


string toLower(const string& word)
{
    string result;
    for (string::const_iterator i = word.begin(); i != word.end(); ++i) {
        result += tolower(*i);
    }
    return result;
}


