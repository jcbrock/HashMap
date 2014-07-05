#include <limits.h>
#include "BucketItem.h"
#include "gtest\gtest.h"
#include <string>

// Tests factorial of negative numbers.
//TEST(FactorialTest, Negative) {
	// This test is named "Negative", and belongs to the "FactorialTest"
	// test case.
	//EXPECT_EQ(1, Factorial(-5));
	//EXPECT_EQ(1, Factorial(-1));
	//EXPECT_GT(Factorial(-10), 0);

	// <TechnicalDetails>
	//
	// EXPECT_EQ(expected, actual) is the same as
	//
	//   EXPECT_TRUE((expected) == (actual))
	//
	// except that it will print both the expected value and the actual
	// value when the assertion fails.  This is very helpful for
	// debugging.  Therefore in this case EXPECT_EQ is preferred.
	//
	// On the other hand, EXPECT_TRUE accepts any Boolean expression,
	// and is thus more general.
	//
	// </TechnicalDetails>
//}

// Tests factorial of negative numbers.
TEST(BucketItem, InitializeInts) {
	int key = 1;
	int value = 100;

	BucketItem<int>* item = new BucketItem<int>();

	EXPECT_TRUE(item != nullptr);

	bool ok = item->Initialize(key, value);
	
	EXPECT_TRUE(ok);
	EXPECT_EQ(key, item->GetKey());
	EXPECT_EQ(value, item->GetValue());
}

TEST(BucketItem, InitializeIntsNegative) {
	int key = -1;
	int value = -100;

	BucketItem<int>* item = new BucketItem<int>();

	EXPECT_TRUE(item != nullptr);

	bool ok = item->Initialize(key, value);

	EXPECT_TRUE(ok);
	EXPECT_EQ(key, item->GetKey());
	EXPECT_EQ(value, item->GetValue());
}

TEST(BucketItem, GetIntKeyBeforeInit) {
	BucketItem<int>* item = new BucketItem<int>();

	EXPECT_TRUE(item != nullptr);
	EXPECT_EQ(0, item->GetKey());
}

TEST(BucketItem, GetIntValueBeforeInit) {
	BucketItem<int>* item = new BucketItem<int>();

	EXPECT_TRUE(item != nullptr);
	EXPECT_EQ(0, item->GetValue());
}

TEST(BucketItem, GetCharKeyBeforeInit) {
	BucketItem<char*>* item = new BucketItem<char*>();

	EXPECT_TRUE(item != nullptr);
	EXPECT_EQ("", item->GetKey());
}

TEST(BucketItem, GetCharValueBeforeInit) {
	BucketItem<char*>* item = new BucketItem<char*>();

	EXPECT_TRUE(item != nullptr);
	EXPECT_EQ("", item->GetValue());
}

TEST(BucketItem, InitializeDoubles) {
	double key = 1.05;
	double value = 100.022;

	BucketItem<double>* item = new BucketItem<double>();

	EXPECT_TRUE(item != nullptr);

	bool ok = item->Initialize(key, value);

	EXPECT_TRUE(ok);
	EXPECT_EQ(key, item->GetKey());
	EXPECT_EQ(value, item->GetValue());
}

TEST(BucketItem, InitializeDoublesNegative) {
	double key = -1.111;
	double value = -100.0091;

	BucketItem<double>* item = new BucketItem<double>();

	EXPECT_TRUE(item != nullptr);

	bool ok = item->Initialize(key, value);

	EXPECT_TRUE(ok);
	EXPECT_EQ(key, item->GetKey());
	EXPECT_EQ(value, item->GetValue());
}

TEST(BucketItem, InitializeChars) {
	char* key = "hello";
	char* value = "world";

	BucketItem<char*>* item = new BucketItem<char*>();

	EXPECT_TRUE(item != nullptr);

	bool ok = item->Initialize(key, value);

	EXPECT_TRUE(ok);
	EXPECT_EQ(key, item->GetKey());
	EXPECT_EQ(value, item->GetValue());
}

TEST(BucketItem, InitializeStrings) {
	std::string key = "foo";
	std::string value = "bar";

	BucketItem<std::string>* item = new BucketItem<std::string>();

	EXPECT_TRUE(item != nullptr);

	bool ok = item->Initialize(key, value);

	EXPECT_TRUE(ok);
	EXPECT_EQ(key, item->GetKey());
	EXPECT_EQ(value, item->GetValue());
	}