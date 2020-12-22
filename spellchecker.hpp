/**
 * \file spellchecker.hpp
 * \author CS 70 Sample Solution -- DO NOT SHARE OR COPY.
 * \brief Provides the SpellChecker class, a simple spell-checking engine
 * \note  Written to use randomized BSTs, but you can adapt the code
 *        for hash tables.
 */

#ifndef SPELLCHECKER_HPP_INCLUDED
#define SPELLCHECKER_HPP_INCLUDED 1

#include "hashset.hpp"
#include <string>
#include <vector>
#include <fstream>


/**
 * \class SpellChecker
 * \brief Engine for spell-checking.
 *
 * \details
 *  Learns words from a dictionary and then suggests corrections for
 *  misspelt words.
 */
class SpellChecker {
public:
    /**
     * \brief We provide a constructor
     * \remarks
     *   Copying and assignment are disabled. We need an AbstractSet*
     *   to be able to change which storage_option we use, thus we
     *   need heap allocated data.
     * \throws
     *   std::logic_error if somehow passed a kind that doesn't
     *   correspond to a Set type.
     */ 
    SpellChecker();
    /// Provide a destructor to handle AbstractSet*.
    ~SpellChecker();


    /**
     * \brief Load a dictionary from a file
     *
     * \param dictionary        Name of dictionary file to load.
     *
     * \throws std::runtime_error thrown if the dictionary can't be found
     */
    void load(const std::string& dictionary);


    /**
     * \brief Learn a word (add it to the dictionary)
     *
     * \param word      Word to add to dictionary
     */
    void learn(const std::string& word);

    /**
     * \brief Ignore a word (add it to the ignored set)
     *
     * \param word      Word to ignore
     */
    void ignore(const std::string& word);

    /**
     * \enum location_t
     *
     * \brief Describes the result of a lookup.
     */
    enum location_t { IN_DICTIONARY, ///< Found in dictionary
                      IS_IGNORED,    ///< Not in dictionary, in ignored list
                      NOT_FOUND      ///< Not in dictionary or ignored list
                    };

    /**
     * \brief Check a word for spelling error
     *
     * \param word      Word to check for error
     *
     * \returns         Returns a location_t, possible answers are
     *                  IN_DICTIONARY, IS_IGNORED, NOT_FOUND
     *
     * \remarks For dictionary lookups, the word is first looked up as
     *          lower case; if it isn't found, we try again "as is" looking
     *          in the dictionary (only).
     */
    location_t lookup(const std::string& word);

    /**
     * \brief   Data structure to store word corrections.
     *          Supports begin() and end(), which return corrections_iter_t
     *          iterators.
     * \remarks Calling any member functions on the dictionary invalidates the
     *          corrections_t object and its iterators.
     *          At present, corrections_t is a STL list with kinder
     *          invalidation rules, but programmers should not rely on that.
     *          It could be a custom object that computes corrections
     *          on-the-fly.
     */
    typedef std::vector<std::string> corrections_t;
    /// Iterator for corrections_t, supporting forward iteratation.
    typedef std::vector<std::string>::const_iterator corrections_iter_t;

    /**
     * \brief Provide possible corrections for word.
     *
     * \param word      Word to correct
     */
    corrections_t corrections(const std::string& word);


    /**
     * \brief Print dictionary statistics to stream out.
     *
     * \param out       ostream to recieve statistics.
     */
    std::ostream& showStatistics(std::ostream& out);

private:
    /// Disable copy constructor
    SpellChecker(const SpellChecker& orig) = delete;
    /// Disable assignment operator
    SpellChecker& operator=(const SpellChecker& rhs) = delete;
    
    /// Data structure to store the dictionary
    HashSet<string>* dictionary_;  ///< Dictionary structure
    HashSet<string>* ignored_;     ///< Words that have been corrected already
};
template class HashSet<string>;

#endif // SPELLCHECKER_HPP_INCLUDED
