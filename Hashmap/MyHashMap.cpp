#include "MyHashMap.h"


unsigned int CrappyHashFunc(const char* key, const unsigned int size)
{
	//lol... so dumb
	return size;
}


void MyHashMap::Insert(const char* key, const char* value, const unsigned int size)
{
	unsigned int index = CrappyHashFunc(key, size);

	//BucketItem newItem;
	//newItem

	//buckets[index];
}