#include <limits.h>
#include "MyHashMap.h"
#include "gtest\gtest.h"

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

//BucketItem
// - init
// - 

//Insert - bad params (nothing, long values), non collision, collision
TEST(Insert, Emtpy) {    
    MyHashMap<int> map;
    EXPECT_ANY_THROW(map.Insert("", 123));    
    EXPECT_EQ(0, map.mSize);
}

TEST(Insert, Long) {
    MyHashMap<int> map;
    map.Insert("keykey", 123);
    EXPECT_EQ(1, map.mSize);
}

TEST(Insert, NoCollision) {
    MyHashMap<int> map;
    map.Insert("keykey", 123);

    EXPECT_EQ(1, map.mSize);    
}

TEST(Insert, Collision) {    
    MyHashMap<int> map;
    map.Insert("keykey", 123);
    map.Insert("foobar", 123);

    EXPECT_EQ(1, map.mCollisionCount);
    EXPECT_EQ(2, map.mSize);    
}

//search returns value, so T
TEST(Search, EmptyHashMap) {
    MyHashMap<int> map;
    int* value = map.Lookup("key");

    EXPECT_EQ(nullptr, value);    
}

TEST(Search, VeryFullMap) {
    MyHashMap<int> map;
    map.Insert("", 123);
    //...

    ASSERT_EQ(5, map.mSize);
    int* value = map.Lookup("key");

    ASSERT_TRUE(value != nullptr);
    EXPECT_EQ(123, *value);
}

TEST(Search, NotFound) {
    MyHashMap<int> map;
    map.Insert("foo", 123);    
    ASSERT_EQ(1, map.mSize);

    int* value = map.Lookup("key");

    
    EXPECT_EQ(nullptr, value);
}

TEST(Search, FoundNoCollision) {
    MyHashMap<int> map;
    map.Insert("foo", 123);
    ASSERT_EQ(1, map.mSize);
    int* value = map.Lookup("foo");

    ASSERT_TRUE(value != nullptr);
    EXPECT_EQ(123, *value);
}

TEST(Search, FoundCollision) {
    MyHashMap<int> map;
    map.Insert("foo1", 123);
    map.Insert("foo2", 123);
    ASSERT_EQ(2, map.mSize);
    ASSERT_EQ(1, map.mCollisionCount);
    int* value = map.Lookup("foo2");

    ASSERT_TRUE(value != nullptr);
    EXPECT_EQ(123, *value);
}

TEST(Search, EmptyInput) {
    MyHashMap<int> map;
    int* value = map.Lookup("");

    EXPECT_EQ(nullptr, value);
}

TEST(Delete, NotFoundItem) {
    MyHashMap<int> map;
    map.Insert("key", 123);
    ASSERT_EQ(1, map.mSize);
    map.Delete("key2");
    EXPECT_EQ(1, map.mSize);
}

TEST(Delete, EmptyMap) {
    MyHashMap<int> map;    
    map.Delete("key");
    EXPECT_EQ(0, map.mSize);
}

TEST(Delete, FoundNoCollisionItem) {
    MyHashMap<int> map;
    map.Insert("key", 123);

    ASSERT_EQ(1, map.mSize);
    map.Delete("key");
    EXPECT_EQ(0, map.mSize);
}

TEST(Delete, FoundCollidedItem) {
    MyHashMap<int> map;
    map.Insert("key", 123);
    map.Insert("foo", 123);
    ASSERT_EQ(1, map.mCollisionCount);
    ASSERT_EQ(2, map.mSize);

    map.Delete("foo");
    EXPECT_EQ(1, map.mCollisionCount);
    EXPECT_EQ(1, map.mSize);
}