#ifndef MYHASHMAP_H
#define MYHASHMAP_H

#include "BucketItem.h"
//First off, how do I want to handle collisions?
// Chaining 
// - Performance degrades linarily as more items are added to the hash (i.e. there are more collisions)
// Next slot (open addressing)
// - Performance degrades dramatically when hash table gets around 70% full (i.e. there are lots of collisions, inserts getting placed all over the bucket list)
// - Deletion can be a bitch, you have to shift elements so that future searches will work. For example, if three things hash to the same key and then get placed
//	in sequential slots, and you delete the first one, you have to shift the previously collided items because otherwise future searches would see that slot open
//	(since the item there was deleted) and assume there are no more items that wanted that slot
// There are others, like 2-choice hashing (having two hashing functions): http://en.wikipedia.org/wiki/Hash_table but going to focus on chainging / open addressing

// How do I know if this is my item? i.e. if I have multiple things mapped to a hash bucket, how do I know which one is the one I want?
// - Oh, derp. You store the key/value pair as the "value", and then you can compare the search key too.
// - looking up "jeff": "jeff" -> hash func -> index 123      buckets[123] value == {"jeff":"myvalue"}
// - looking up "jeff" with previous collision (chained). HashBucketKeyValue is Key (a pointer), Value (key/value pair):
//		"jeff" -> hash func -> index 123      buckets[123] value == (ptr to next item, {"bro":"myvalue"}). "bro" != "jeff", take pointer
//		next item: (null, {"jeff":"mytruevalue"}), yay - found it!

//NOTE: Although hash maps are usually used because of their speed, keep in mind that they may be slower than an inner loop for a sequential list or search tree.
// i.e. Hash table data isn't stored continous, so you may spend quite a bit of time swapping memory around when accessing a bunch of items sequentially
//  - this is called poor "locality of reference": http://en.wikipedia.org/wiki/Locality_of_reference

//NOTE: Obviously like I've seen using unordered_mapIf the keys are not stored (because the hash function is collision-free), 
// there may be no easy way to enumerate the keys that are present in the table at any given moment.//How do I want to do my bucket containers?
//Options
// - Dynamic Array
// - LL
// - 
class MyHashMap
{
public:
	void Insert(const char* key, const char* value, const unsigned int size);
	void Lookup(const char* key) const;


private:
	BucketItem buckets[100];
};


#endif