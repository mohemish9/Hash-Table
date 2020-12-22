/**
 * \file myspell.cpp
 *
 * \author CS 70 Sample Solution -- DO NOT SHARE OR COPY.
 *
 * \brief Implements the UI for the spelling checker
 *
 * \details For usage, see \ref use_sec.
 *
 * \remarks Most of the spellchecking work is done in the SpellChecker class.
 *
 */
#include <list>
#include <string>
#include <iostream>
#include <fstream>
#include <cctype>
#include <cstdlib>
#include <stdexcept>
#include <sys/time.h>

#include "spellchecker.hpp"
#include "stringutils.hpp"

using namespace std;

/**
 * \brief Process input from cin and compare against the dictionary.
 *        If the word is not found and has not been seen before, spelling
 *        corrections are output to cout.
 */
void spellcheck(const string& dictfile,  ///< Name of dictionary file
                bool debug /**< Corresponds to -d flag*/)
{
    SpellChecker checker;
    checker.load(dictfile);

    if (debug)
        checker.showStatistics(cerr);

    string word;

    while (getWord(cin, word)) {
        switch (checker.lookup(word)) {
        case SpellChecker::IN_DICTIONARY:
            // do nothing
            break;

        case SpellChecker::IS_IGNORED:
            // do nothing
            break;

        case SpellChecker::NOT_FOUND:
            SpellChecker::corrections_t alts = checker.corrections(word);
            cout << word << ":";

            for (SpellChecker::corrections_iter_t i = alts.begin();
                    i != alts.end();
                    ++i)
                cout << " " << *i;

            cout << endl;
            checker.ignore(word);
            break;
        }
    }
}


/**
 * \brief Option Processing, as the name implies.
 * \details
 *   Sets various settings via various variables passed by reference.
 *
 *   Will return with an exit error of 2 if receives a usage problem.
 *
 * \param options       Input of options from command line.
 * \param args          Output of dictionary name
 * \param debug         Output of debug flag
 */
void processOptions(list<string>& options, list<string>& args, bool& debug)
{
    while (!options.empty()) {
        string option = options.front();
        options.pop_front();

        if (option.empty() || option[0] != '-') {
            args.push_back(option);
        } else if (option == "-d" || option == "--debug") {
            debug = true;

        } else {
            cerr << "Unrecognized option: " << option << endl;
            exit(2);
        }
    }

    if (args.size() != 1) {
        cerr << "Usage: ./myspell [-d] dict"
             << endl;
        exit(2);
    }
}

/**
 * \brief Main function, processes inputs and runs spellcheck
 * \remarks
 *   Initializes Random Number Generator to ensure it is initialized
 *   only once during execution. Random Numbers are used in HashSet.
 */
int main(int argc, const char** argv)
{
    // Initialize random number generator.
    struct timeval tp;
    gettimeofday(&tp, nullptr);
    srandom(tp.tv_usec * tp.tv_sec);

    bool debug = false;

    // Option-processing crud.
    list<string> options(argv + 1, argv + argc);
    list<string> args;
    processOptions( options, args, debug);

    // Check that spelling!
    try {
        spellcheck(args.front(), debug);
    } catch (std::runtime_error err) {
        cerr << err.what() << endl;
        return 1;
    }

    return 0;
}
