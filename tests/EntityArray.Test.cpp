#include <gtest/gtest.h>
#include <EntityArray.h>
#include <easylogging++.h>

TEST(EntityArray, GetByInvalidId) 
{
	// We should get null pointer by invalid id
	EntityArray<int> array;
	int* val = array.Get({});
	EXPECT_EQ(val, nullptr);
}

TEST(EntityArray, GetById) 
{
	// We should be able to retrive entity pointer by id
	EntityArray<int> array;
	EntityArray<int>::Id id = array.Allocate();
	int* val = array.Get(id);
	ASSERT_TRUE(val);
	*val = 6;
	val = array.Get(id);
	EXPECT_EQ(*val, 6);
}

TEST(EntityArray, Delete)
{
	// After deltion we should get null entity pointer
	EntityArray<int> array;
	EntityArray<int>::Id id = array.Allocate();
	int* val = array.Get(id);
	EXPECT_TRUE(val);
	array.Delete(id);
	val = array.Get(id);
	EXPECT_EQ(val, nullptr);
}

TEST(EntityArray, DoubleDelete)
{
	// Deletion should be reentrant
	EntityArray<int> array;
	array.Allocate();
	EntityArray<int>::Id id1 = array.Allocate();
	EntityArray<int>::Id id2 = array.Allocate();
	array.Delete(id1);	
	array.Delete(id2);
	array.Delete(id2);
	array.Allocate();
	EXPECT_FALSE(array.Get(id1));
	EXPECT_FALSE(array.Get(id2));
}

TEST(EntityArray, Reuse)
{
	// Entity id of deleted entity should return null entity pointer, even after new entity was put in same place
	EntityArray<int> array;
	array.Allocate();
	EntityArray<int>::Id id2 = array.Allocate();
	array.Allocate();
	EntityArray<int>::Id id3 = array.Allocate();
	array.Allocate();

	int* val2 = array.Get(id2);
	int* val3 = array.Get(id3);
	array.Delete(id3);
	array.Delete(id2);
	EntityArray<int>::Id id4 = array.Allocate();
	EntityArray<int>::Id id5 = array.Allocate();
	EXPECT_NE(id2, id5);
	EXPECT_NE(id2, id4);
	EXPECT_NE(id3, id5);
	EXPECT_NE(id3, id4);

	EXPECT_EQ(val3, array.Get(id5));
	EXPECT_EQ(val2, array.Get(id4));
	EXPECT_FALSE(array.Get(id2));
	EXPECT_FALSE(array.Get(id3));
}

TEST(EntityArray, Iterate)
{
	// We should be able to iterate over existing entities, scipping deleted
	EXPECT_TRUE(false);
}
