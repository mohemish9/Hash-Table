/**
 * \file ourtests.cpp
 * \author hmc-tuna-f18, hmc-squirrel-f18
 * \brief Tests the implementation of HashSet
 */

#include "hashset.hpp"
#include "stringhash.hpp"
#include "testing-logger.hpp"
#include <ostream> // For std::ostream
#include <cstddef> // For size_t

#include "signal.h" // For signal
#include "unistd.h" // For alarm

using namespace std;

// Explicitly instantiate the entire templated class (normally C++ is lazy
// and only instantiates the things it needs as it needs them, here we make
// it do everything.)
size_t djb2(std::string const& s) {
    unsigned long hash = 5381;
    for (auto c : s) {
        hash = (hash << 5) + hash + c; /* hash * 33 + c */
    }
    return hash;
}

size_t myhash(const string& str)
{
  
    return djb2(str);
}

template class HashSet<string>;

/*****************************************************
 * Tests
 * ***************************************************/


bool stringhash_constructor_test()
{
    // Set up the TestingLogger object
    TestingLogger log{"constructor test"};

    HashSet<string> hashset;

    affirm(hashset.size() == 0);

    // Print a summary of the all the affirmations and return true
    // if they were all successful.
    return log.summarize();

}

bool stringhash_smallTest()
{
    TestingLogger log{"smallTest"};

    HashSet<string> hashset;
    affirm(hashset.size() == 0);

    hashset.insert("abc"); 
    affirm(hashset.size() == 1);

    affirm(hashset.exists("abc"));
    return log.summarize();
}

bool stringhash_bigTest()
{
    TestingLogger log{"bigTest"};
    HashSet<string> hashset;
    affirm(hashset.size() == 0);
    hashset.insert("hgl");
    affirm(hashset.size() == 1);
    hashset.insert("apple");
    hashset.insert("bacon");
    hashset.insert("avocado");
    hashset.insert("lemon");
    hashset.insert("cake");
    hashset.insert("whiteboard");
    hashset.insert("computer");
    hashset.insert("soda");
    affirm(hashset.size() == 9);
    hashset.exists("avocado");

    return log.summarize();
}

bool stringhash_resizeTest()
{
    TestingLogger log{"resizeTest"};
    HashSet<string> hashset; //it has 2 buckets
    hashset.insert("apple");
    hashset.insert("bacon");
    hashset.insert("avocado");
    affirm(hashset.buckets() == 2);
    affirm(hashset.reallocations() == 0);
    hashset.insert("lemon");
    hashset.insert("barfoo");
    affirm(hashset.buckets() == 4);
    affirm(hashset.reallocations() == 1);
    return log.summarize();
}

bool stringhash_maximalTest()
{
    TestingLogger log{"maximalTest"};
    HashSet<string> hashset; //it has 2 buckets
    hashset.insert("apple");
    hashset.insert("apple");
    hashset.insert("apple");
    affirm(hashset.maximal() == 3);
    hashset.insert("apple");
    hashset.insert("apple");
    affirm(hashset.maximal() == 5);
    return log.summarize();
}

bool stringhash_collisionsTest()
{
    TestingLogger log{"collisionsTest"};
    HashSet<string> hashset; //it has 2 buckets
    hashset.insert("apple");
    hashset.insert("apple");
    hashset.insert("apple");
    affirm(hashset.collisions() == 2);
    hashset.insert("banana");
    hashset.insert("banana");
    hashset.insert("banana");
    affirm(hashset.collisions() == 4);
    return log.summarize();
}


/****************************
 * Boilerplate main function
 * **************************/

// Called if the test runs too long.
static void timeout_handler(int)
{
    // We go super-low-level here, because we can't trust anything in
    // the C/C++ library to really be working right.
    write(STDERR_FILENO, "Timeout occurred!\n", 18);
    abort();
}

/// Run tests
int main()
{
    // Initalize testing environment
    TestingLogger alltests{"All tests"};

    signal(SIGALRM, timeout_handler);   // Call this when the timer expires
    alarm(10);                          // set the timer at 10 seconds

    // Add calls to your tests here...
    affirm(stringhash_constructor_test());
    affirm(stringhash_smallTest());
    affirm(stringhash_bigTest());
    affirm(stringhash_resizeTest());
    affirm(stringhash_maximalTest());
    affirm(stringhash_collisionsTest());

    if (alltests.summarize(true)) {
        return 0;       // Error code of 0 == Success!
    } else {
        return 2;       // Arbitrarily chosen exit code of 2 means tests failed.
    }

}

