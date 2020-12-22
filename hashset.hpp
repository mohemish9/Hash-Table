/**
 * \file hashset.hpp
 *
 * \author What are your CS70 aliases?
 *
 * \brief Provides HashSet<T>, a set class template, using hash tables
 */

#ifndef HASHSET_HPP_INCLUDED
#define HASHSET_HPP_INCLUDED 1

#include "stringhash.hpp"
#include <iostream>
#include <list>
#include <string>
#include <iostream>


using namespace std;
// Any header files that are needed to typecheck the class
// declaration should be #included here.

// Templated interfaces (e.g., the HashSet class declarations) go here


// Most users of this header file would be interested in interfaces: how does
// one use a HashSet<T>? What member functions does it provide? What parameters
// do they take?
//
// Because the hashset code is templated, it must appear in this header file
// instead of a normal .cpp file. We do this by moving the nasty implementation
// details into hashset-private.hpp, and recursively including that here.  This
// way, readers don't see the actual code unless they want to, and aren't forced
// to manually include two separate header files every time they want to use
// this hash table.

template <typename T>

class HashSet
{
public:
    HashSet();
    HashSet(size_t numBuckets, size_t reallocations);
    HashSet(const HashSet<T>&) = delete;
    HashSet<T>& operator=(HashSet<T> rhs) = delete; 
    ~HashSet();
    size_t size();
    void insert(const T& e);
    bool exists(const T& e) const;
    size_t buckets() const;
    size_t reallocations() const;
    size_t collisions() const;
    size_t maximal() const; 
    void swap(HashSet<T>& rhs);
    /**
     * \struct Bucket
     * \brief an individual bucket of a hashset 
     */
    struct Bucket
    {
        std::list<T> items_; //items hashed in the same bucket
        using bucket_iter_t = typename std::list<T>::iterator;
    };
    
    void checkResize();
    void checkCollisions(size_t bin);
    void checkMaximal(size_t bin);
    
    ostream& showStatistics(ostream& out);
private: 
    size_t numBuckets_;
    Bucket* buckets_;
    size_t size_;
    size_t reallocations_;
    size_t collisions_;
    size_t maximal_;

    static const double LOAD_FACTOR;
};
#include "hashset-private.hpp"
#endif
