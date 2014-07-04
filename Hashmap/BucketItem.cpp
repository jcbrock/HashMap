#include "BucketItem.h"

char* BucketItem::Lookup(const char* key) const
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