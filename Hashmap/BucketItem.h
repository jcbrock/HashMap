#ifndef BUCKETITEM_H
#define BUCKETITEM_H

// Basically a helper class for representing an item that exists in the hash map's bucket/slot
// Assuming chaining... points to static array 

template<class T>
struct KeyValuePair
{
	KeyValuePair() { std::cout << "DEBUG: KeyValuePair default constructor called" << std::endl; };
	T key;
	T value;
};

template<typename T>
class BucketItem
{
public:
	BucketItem() { std::cout << "DEBUG: BucketItem default constructor called" << std::endl; };
	~BucketItem();

	bool Initialize(const T key, const T value); //byref?
	void Finalize();
	
	T GetKey() const;
	T GetValue() const;

	T Lookup(const T key) const;



private:
	//
	// Pointer to array of items containing the items that map to this bucket
	//
	KeyValuePair<T> items;

	//
	// Size of the array pointed at by the bucket (i.e. number of items allowed to a bucket)
	//
	const static int kCollisionArraySize = 5;
};

template<typename T>
bool BucketItem<T>::Initialize(const T key, const T value)
{
		items.key = key;
		items.value = value;

	return true;

}

template<typename T>
T BucketItem<T>::GetKey() const
{
	return items.key;
}

template<typename T>
T BucketItem<T>::GetValue() const
{
	return items.value;
}

template<typename T>
T BucketItem<T>::Lookup(const T key) const
{
	for (int i = 0; i < kCollisionArraySize; ++i)
	{
		if (items[i].key == key)
		{
			return items[i].value;
		}
	}

	return "not found";
}

template<typename T>
BucketItem<T>::~BucketItem()
{

}

#endif