/*#include "BucketItem.h"

template<typename T>
bool BucketItem<T>::Initialize(const T key, const T value)
{
	if (items == NULL)
	{
		items = new KeyValuePair<T>();
		items->key = key;
		items->value = value;
	}
	else
	{
		items->key = key;
		items->value = value;
	}

	return true;

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
	if (items != nullptr)
	{
		delete items;
	}
}*/