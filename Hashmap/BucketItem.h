#ifndef BUCKETITEM_H
#define BUCKETITEM_H

// Basically a helper class for representing an item that exists in the hash map's bucket/slot
// Assuming chaining... points to static array 

struct KeyValuePair
{
	char key[5];
	char value[5];
};

class BucketItem
{
public:
	
	bool Initialize(const char* key, const char* value){ return false; };

	char* Lookup(const char* key) const;



private:
	//
	// Pointer to array of items containing the items that map to this bucket
	//
	KeyValuePair* items;

	//
	// Size of the array pointed at by the bucket (i.e. number of items allowed to a bucket)
	//
	const static int kCollisionArraySize = 5;
};


#endif