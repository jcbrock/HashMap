#ifndef MYHASHMAP_H
#define MYHASHMAP_H

#include "HashMapItem.h"
#include <string>
#include <exception>
//First off, how do I want to handle collisions?
// Chaining 
// - Performance degrades linearly as more items are added to the hash (i.e. there are more collisions)
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
// i.e. Hash table data isn't stored continuous, so you may spend quite a bit of time swapping memory around when accessing a bunch of items sequentially
//  - this is called poor "locality of reference": http://en.wikipedia.org/wiki/Locality_of_reference

//NOTE: Obviously like I've seen using unordered_mapIf the keys are not stored (because the hash function is collision-free), 
// there may be no easy way to enumerate the keys that are present in the table at any given moment.//How do I want to do my bucket containers?
//Options
// - Dynamic Array
// - LL
// - 



//Think again about what I want to expose to the user.
template<typename T>
class MyHashMap
{
public:
    MyHashMap() : mCollisionCount(0), mSize(0){
        mBuckets = new HashMapItem<T>[10]();
        memset(mBuckets, 0, sizeof(HashMapItem<T>) * 10);
        buckets2 = new HashMapItem<T>*[10]();
        memset(buckets2, 0, sizeof(HashMapItem<T>*) * 10);
    };
    ~MyHashMap()
    {
        //Free all items first
        //for (int i = 0; i < 10; ++i)
        // {
        // DeleteChain(buckets[i].nextItem);
        //}

        //Free array
        delete[] mBuckets;

    };

    void Insert(const std::string& key, const T value);
    T* Lookup(const std::string& key) const;
    void Delete(const std::string& key);

public:
    unsigned int mCollisionCount;
    unsigned int mSize;

private:
    unsigned int CrappyHashFunc(const std::string& key, const unsigned int size) const;
    void DeleteChain(HashMapItem<T>* item);

    //private:
public:
    HashMapItem<T>* mBuckets;
    HashMapItem<T>** buckets2;

private:
    HashMapItem<T>* MyMemory = new HashMapItem<T>[512]();
    int slotCount = 0;
};

template<typename T>
unsigned int MyHashMap<T>::CrappyHashFunc(const std::string& key, const unsigned int size) const
{
    //lol... so dumb
    return size % 10;
}

template<typename T>
void MyHashMap<T>::Insert(const std::string& key, const T value)
{
    if (key.empty())
    {
        std::exception ex;
        throw ex;
    }
    unsigned int index = CrappyHashFunc(key, key.size());

    int size = sizeof(HashMapItem<T>);
    size = size;
    //buckets[0] = HashMapItem<T>(key.c_str(), value);
    //if (buckets[index].key == nullptr)
    if (mBuckets[index].key.empty())
    {
        //I went over this shit yesterda,y hashmapitem is constructed here on the stack. stack will unravel.
        //but it gets copied into buckets...

        //what the fuck am I not understanding here?
        //
        //auto foo = HashMapItem<T>(key.c_str(), value);
        //buckets[index] = foo; //should copy construct, right?
        //buckets[index] = HashMapItem<T>(key.c_str(), key.size(), value); //should copy construct, right?
        mBuckets[index] = HashMapItem<T>(key, value); //should copy construct, right?
        ++mSize;

        //foo definitely destructs when goes out of this scope. before it was a temp variable when it was on one line
        //so I don't think the compiler respects what is in buckets cuz it isn't a real object? 

        //buckets2[index] = new HashMapItem<T>(key.c_str(), value);//should be on the heap...


        //Ok, problem summary
        //I'd pass in a char*, and rather than copy the value of it (the contents it was pointing to),
        //I was just coping the pointer. Of course the original pointer gets fucked later because I had no intention
        //of keeping it around, it was stored on the stack, etc...
        //This is a hard part of working with char *
        //   I wasn't doing anything to manage the memory of my char* member variable, I was just assigning it to the pointer passed in....
        //  This makes sense why it was getting erased once I got out of the function.
    }
    else
    {
        ++mCollisionCount;
        HashMapItem<T>* item = &mBuckets[index];
        while (item->nextItem != nullptr)
        {
            item = item->nextItem;
            ++mCollisionCount;
        }
        //item->nextItem = new HashMapItem<T>(key.c_str(), key.size(), value);
        item->nextItem = new (MyMemory, slotCount) HashMapItem<T>(key, value);
        item->nextItem = new (MyMemory) HashMapItem<T>(key, value);
               ++slotCount;
        ++mSize;
    }
}

template<typename T>
T* MyHashMap<T>::Lookup(const std::string& key) const
{
    unsigned int index = CrappyHashFunc(key, key.size());

    HashMapItem<T>* currentItem = &mBuckets[index];

    while (currentItem != nullptr && currentItem->key != "")
    {
        if (currentItem->key == key)
        {
            return &currentItem->value;
        }

        currentItem = currentItem->nextItem;
    }

    return nullptr;
}

template<typename T>
void MyHashMap<T>::Delete(const std::string& key)
{
    unsigned int index = CrappyHashFunc(key, key.size());
    bool needsDelete = false;
    HashMapItem<T>* currentItem = &mBuckets[index];        
    HashMapItem<T>* prevItem = nullptr;

    while (currentItem != nullptr && currentItem->key != "")
    {
        if (currentItem->key == key)
        {
            if (prevItem != nullptr)
            {
                prevItem->nextItem = currentItem->nextItem;
            }
            if (needsDelete)
            {
                delete currentItem;
                
            }
            currentItem = nullptr;
            --mSize;
            return;
        }

        needsDelete = true;
        currentItem = currentItem->nextItem;
    }    
}


template<typename T>
void MyHashMap<T>::DeleteChain(HashMapItem<T>* item)
{
    HashMapItem<T>* nextItem = item;
    while (nextItem != nullptr)
    {
        HashMapItem<T>* temp = nextItem->nextItem;
        delete nextItem;
        nextItem = temp;
        --mSize;
    }
}

#endif