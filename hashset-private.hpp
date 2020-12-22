
/**
 * \file hashset-private.hpp
 *
 * \author hmc-tuna-f18, hmc-squirrel-f18
 *
 * \brief Implements HashSet<T>, a hash-table class template
 *
 * \remark There is no include-guard for this file, because it is
 *         only #included by hashset.hpp, inside hashset.hpp's
 *         own include guard.
 */

// Includes required for your templated code go here

// Templated code for member functions goes here

template <typename T>
const double HashSet<T>::LOAD_FACTOR = 2;

/**
 * \brief Default Constructor for HashSet
 *
 * \details Default constructs a hashset and initializes it with
 *          two buckets
 */
template <typename T>
HashSet<T>::HashSet()
 : numBuckets_(2), 
   size_(0),
   reallocations_(0),
   collisions_(0),
   maximal_(0)
{
  buckets_ = new Bucket[numBuckets_];
}

/**
 * \brief swap function
 *
 * \details works like an assignment operator but uses std::swap
 */
template <typename T>
void HashSet<T>::swap(HashSet<T>& rhs)
{
  using std::swap;
  swap(numBuckets_, rhs.numBuckets_);
  swap(size_, rhs.size_);
  swap(reallocations_, rhs.reallocations_);
  swap(collisions_, rhs.collisions_);
  swap(maximal_, rhs.maximal_);
  swap(buckets_, rhs.buckets_);
}

/**
 * \brief Parameterized constructor
 *
 * \details used in resize; takes numBuckets and reallocations as arguments
 */
template <typename T>
HashSet<T>::HashSet(size_t numBuckets, size_t reallocations)
  : numBuckets_(numBuckets),
    size_(0),
    reallocations_(reallocations),
    collisions_(0),
    maximal_(0)
{
  buckets_ = new Bucket[numBuckets_];
}

/**
 * \brief Destructor for HashSet
 *
 * \details deletes buckets_ from the heap
 */
template <typename T>
HashSet<T>::~HashSet()
{
  delete[] buckets_;
} 

/**
 * \brief size function
 *
 * \details Returns the size of the hash table
 */
template <typename T>
size_t HashSet<T>::size()
{
  return size_;
}

/**
 * \brief buckets function
 *
 * \details returns the number of buckets in a hash table
 */
template <typename T>
inline size_t HashSet<T>::buckets() const
{
    return numBuckets_;
}

/**
 * \brief reallocations function
 *
 * \details returns the number of times the hash table has resized itself
 */
template <typename T>
inline size_t HashSet<T>::reallocations() const
{
    return reallocations_;
}

/**
 * \brief collisions function
 *
 * \details returns the number of times an insert into the 
 *          current hash table finds a non-empty bucket
 */
template <typename T>
inline size_t HashSet<T>::collisions() const
{
    return collisions_;
}

/**
 * \brief maximal function
 *
 * \details returns the length of the longest chain in our hash table
 *          because we are using separate chaining
 */
template <typename T>
inline size_t HashSet<T>::maximal() const
{
    return maximal_;
}

/**
 * \brief checkCollisions function
 *
 * \details helper function for insert that checks if we need to 
 *          update collisions_
 */
template <typename T>
void HashSet<T>::checkCollisions(size_t bin) 
{
  if(buckets_[bin].items_.size() != 0)
  {
    ++collisions_;
  }
}

/**
 * \brief checkMaximal function
 *
 * \details helper function for insert that checks if we need to 
 *          update maximal_
 */
template <typename T>
void HashSet<T>::checkMaximal(size_t bin) 
{
  if(buckets_[bin].items_.size() == maximal_)
  {
    ++maximal_;
  }
}

/**
 * \brief checkResize function
 *
 * \details helper function for insert that resizes the hash table
 */
template <typename T>
void HashSet<T>::checkResize()
{
  HashSet<T> newHashSet(numBuckets_*2, reallocations_ + 1);
  for(size_t i = 0; i < numBuckets_ ; ++i)
  {
    for(typename HashSet<T>::Bucket::bucket_iter_t j = buckets_[i].items_.begin(); j != buckets_[i].items_.end(); ++j)
    {
      newHashSet.insert(*j);
    }
  }
  swap(newHashSet);
}

/**
 * \brief insert function
 *
 * \details inserts an object into our HashSet and resizes and updates
 *          private data members accordingly
 */
template <typename T>
void HashSet<T>::insert(const T& e) 
{
  double currentLF = size_ / numBuckets_;
  if(currentLF >= HashSet::LOAD_FACTOR)
  {
    checkResize();
  }
  size_t hashValue = myhash(e);
  size_t bin = hashValue % numBuckets_;
  checkCollisions(bin);
  checkMaximal(bin);
  buckets_[bin].items_.push_back(e);
  ++size_;
}

/**
 * \brief exists function
 *
 * \details checks if an object already exists in our hash table
 */
template <typename T>
bool HashSet<T>::exists(const T& e) const
{
  size_t hashValue = myhash(e);
  size_t bin = hashValue % numBuckets_;
  if (buckets_[bin].items_.size() != 0)
  {
    for(typename HashSet<T>::Bucket::bucket_iter_t j = buckets_[bin].items_.begin(); j != buckets_[bin].items_.end(); ++j)
    {
      if (*j == e)
      {
        return true;
      }
    }
  }
  return false;
}

/**
 * \brief showStatistics function
 *
 * \details helper function for spellchecker that returns # of collisions
 */
template <typename T>
ostream& HashSet<T>::showStatistics(ostream& out)
{
  out << "number of collisions:" << collisions_ << endl;
  return out;
}