/**
 * \file stringutil.hpp
 * \author CS 70 Provided Code.
 *
 * \brief Miscellaneous utility code for strings
 */
#ifndef STRINGUTIL_HPP_INCLUDED
#define STRINGUTIL_HPP_INCLUDED 1

#include <iosfwd>
#include <string>

/**
 * \brief Reads a word from input stream in, where a word is the longest
 *        possible sequence of alphabetical characters. Reads (and ignores)
 *        one non-alphabetic character at the end of the word. Saves the 
 *        result in the input string parameter
 *
 * \returns true if a word is found; otherwise returns false
 *
 * \remarks  Only handles words with alphabetic characters;
 *               does not skip leading whitespace
 **/

bool getWord(std::istream& in, std::string& word);


/**
 * \brief Converts a word to all lowercase letters
 * 
 * \returns the lower case version of the input string
 **/
std::string toLower(const std::string& word);

#endif // STRINGUTIL_HPP_INCLUDED
