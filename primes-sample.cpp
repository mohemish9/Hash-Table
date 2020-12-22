/* These are the headers that this code needs, in addition to your hashset
 * header.
 */

#include <cstddef>
#include <climits>
#include <cassert>

/* If you need prime numbers close to a power of two, pick *one* of
   these functions and add it to your HashSet class as a private
   *static* member function (i.e., declared static in the header file
   that declares the HashSet class template).  It is "static" because
   it does not need or use the "this" data for a HashSet object.

   It *must* be part of the HashSet class because of the assignment
   requirement that the only code we should need to have to use a
   HashSet is the hashset class and a hash function.

   These functions return an unsigned long, which is guaranteed to be
   at least as large as a size_t.  The code is a little more complex
   than it might otherwise be because it handles making the right
   function on 64-bit and 32-bit systems (it uses the macro LONG_BIT
   which specifies how many bits there are in a long).
 */

template <typename HashKey>
size_t HashSet<HashKey>::primeAbove(size_t power)
{
    // Table of differences between nearest prime and power of two. We
    // use unsigned char (i.e., an 8-bit unsigned int) to make the
    // table tiny.
    static unsigned char offset[] = {
        0, 0, 1, 3, 1, 5, 3, 3, 1, 9, 7, 5, 3, 17, 27, 3, 1, 29, 3,
        21, 7, 17, 15, 9, 43, 35, 15, 29, 3, 11, 3, 11
#if LONG_BIT == 32
        // No more entries needed
#elif LONG_BIT == 64
        , 15, 17, 25, 53, 31, 9, 7, 23, 15, 27, 15, 29, 7, 59, 15, 5,
        21, 69, 55, 21, 21, 5, 159, 3, 81, 9, 69, 131, 33, 15, 135, 29
#else
#error Expected long to be 32-bit or 64-bit.
#endif
    };
    assert (power > 0 && power < LONG_BIT);
    return (1UL << power) + offset[power];
}

template <typename HashKey>
size_t HashSet<HashKey>::primeBelow(size_t power)
{
    // Table of differences between nearest prime and power of two. We
    // use unsigned char (i.e., an 8-bit unsigned int) to make the
    // table tiny.
    static const unsigned char offset[65] = {
        0, 0, 1, 1, 3, 1, 3, 1, 5, 3, 3, 9, 3, 1, 3, 19, 15, 1, 5, 1,
        3, 9, 3, 15, 3, 39, 5, 39, 57, 3, 35, 1, 5
#if LONG_BIT == 32
        // No more entries needed
#elif LONG_BIT == 64
        , 9, 41, 31, 5, 25, 45, 7, 87, 21, 11, 57, 17, 55, 21, 115, 59,
        81, 27, 129, 47, 111, 33, 55, 5, 13, 27, 55, 93, 1, 57, 25, 59
#else
#error Expected long to be 32-bit or 64-bit.
#endif
    };
    assert (power > 0 && power <= LONG_BIT);
    // If you were thinking of writing (1ULL << power), read Section 5.8
    // of the C++ Standard and cry.
    return (2UL << (power - 1)) - offset[power];
}
