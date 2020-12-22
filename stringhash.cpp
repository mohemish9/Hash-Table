/**
 * \file stringhash.hpp
 * \author hmc-tuna-f18, hmc-squirrel-f18
 *
 * \brief Hash function for strings
 */

#include "stringhash.hpp"

using std::string;

// Hash Function Gallery
//
// These are the hash functions our group has examined, one of them is used
// as myhash (see later code in the file)
//
// All the code below is in an anonymous namespace, so these function names
// are hidden from other code.
namespace {


/**
 * This is the FNV-1a algorithm. 
 *
 * /remarks Source: https://www.programmingalgorithms.com/algorithm/fnv-hash?lang=C%2B%2B
 *
 */
size_t FNVHash(std::string const& str) 
{
	const unsigned int fnv_prime = 0x811C9DC5;
	unsigned int hash = 0;
	unsigned int i = 0;
	unsigned int len = str.length();

	for (i = 0; i < len; i++)
	{
		hash *= fnv_prime;
		hash ^= (str[i]);
	}

	return hash;
}

/**
 * This is a hash function called djb2 by Dan Bernstein. 
 *
 * /remarks djb2 hash function from http://www.cse.yorku.ca/~oz/hash.html
 *  and https://stackoverflow.com/questions/19892609/djb2-by-dan-bernstein-for-c
 */
size_t djb2(std::string const& s) {
    unsigned long hash = 5381;
    for (auto c : s) {
        hash = (hash << 5) + hash + c; /* hash * 33 + c */
    }
    return hash;
}

/**
 * This is the SDBM hashing algorithm. 
 * /remarks Source: http://www.partow.net/programming/hashfunctions/#SDBMHashFunction
 */
size_t SDBMHash(std::string const& str)
{
   unsigned int hash = 0;
   unsigned int i    = 0;
   unsigned int length = str.length();

   for (i = 0; i < length; ++i)
   {
      hash = (str[i]) + (hash << 6) + (hash << 16) - hash;
   }
   return hash;
}


} // end of anonymous namespace

size_t myhash(const string& str)
{
  
    return djb2(str);
}

// You don't have to fully understand this code, but it is used to provide a
// table used by stringhash-test.cpp, all you need to do is list the name
// of your hash function (for printing) and the actual function name from
// above.
std::initializer_list<HashFunctionInfo> hashInfo = {
    {"djb2 hash algorithm",     djb2},
    {"sdbm hash algorithm",     SDBMHash},
    {"FNVHash",                 FNVHash}  // No comma for last one
};

