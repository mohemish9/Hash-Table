/**
 * \file  spellchecker.cpp
 * \author CS 70 Sample Solution -- DO NOT SHARE OR COPY.
 *
 * \brief Implements the SpellChecker class, a simple spell-checking engine
 * \note  Written to use randomized BSTs, but you can adapt the code
 *        for hash tables.
 */

#include "spellchecker.hpp"
#include "stringutils.hpp"
#include "hashset.hpp"
#include <cstddef>
#include <string>
#include <stdexcept>
#include <iostream>

using namespace std;

SpellChecker::SpellChecker()
    : dictionary_(nullptr), ignored_(nullptr)
{
    dictionary_ = new HashSet<string>;
    ignored_    = new HashSet<string>;
}

SpellChecker::~SpellChecker()
{
    delete dictionary_;
    delete ignored_;
}

void SpellChecker::load(const string& dictFile)
{
    ifstream in(dictFile.c_str());

    if (!in) {
        throw std::runtime_error("Can't load dictionary `" + dictFile + "'");
    }

    string word;

    while (getWord(in, word))
        learn(word);
}


void SpellChecker::learn(const string& word)
{
    dictionary_->insert(word);
}


void SpellChecker::ignore(const string& word)
{
    ignored_->insert(toLower(word));
}


SpellChecker::location_t SpellChecker::lookup(const string& word)
{
    string lower = toLower(word);

    if (dictionary_->exists(lower))
        return IN_DICTIONARY;
    else if (ignored_->exists(lower))
        return IS_IGNORED;
    else
        return NOT_FOUND;
}


SpellChecker::corrections_t SpellChecker::corrections(const std::string& word)
{
    // We use an array of letters to try to allow future enhancements, such
    // as adding apostrophes and upper-case letters.
    static const char letters[] = "abcdefghijklmnopqrstuvwxyz";

    string current(toLower(word));
    corrections_t results;

    for (size_t i = 0; i < current.size(); ++i) {
        // For each position, try every possible replacement letter.
        for (char letter : letters) {
            current[i] = letter;

            if (dictionary_->exists(current))
                results.push_back(current);
        }

        // And then reset that position back its original letter
        current[i] = tolower(word[i]);
    }

    return results;
}


ostream& SpellChecker::showStatistics(ostream& out)
{
    return dictionary_->showStatistics(out);
}



