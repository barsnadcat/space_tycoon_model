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
	EntityArray<int>::Id id = array.Insert(6);
	ASSERT_TRUE(array.Get(id));
	EXPECT_EQ(*array.Get(id), 6);
}

TEST(EntityArray, Delete)
{
	// After deltion we should get null entity pointer
	EntityArray<int> array;
	auto id = array.Insert({});
	EXPECT_TRUE(array.Get(id));

	array.Delete(id);
	EXPECT_FALSE(array.Get(id));
}

TEST(EntityArray, DoubleDelete)
{
	// Deletion should be reentrant
	EntityArray<int> array;
	array.Insert({});
	auto id1 = array.Insert({});
	auto id2 = array.Insert({});
	array.Delete(id1);	
	array.Delete(id2);
	array.Delete(id2);
	array.Insert({});
	EXPECT_FALSE(array.Get(id1));
	EXPECT_FALSE(array.Get(id2));
}

TEST(EntityArray, Reuse)
{
	// Entity id of deleted entity should return null entity pointer, even after new entity was put in same place
	EntityArray<int> array;
	array.Insert({});
	auto id2 = array.Insert({});
	array.Insert({});
	auto id3 = array.Insert({});
	array.Insert({});

	int* pVal2 = array.Get(id2);
	int* pVal3 = array.Get(id3);
	array.Delete(id3);
	array.Delete(id2);
	auto id4 = array.Insert({});
	auto id5 = array.Insert({});
	EXPECT_NE(id2, id5);
	EXPECT_NE(id2, id4);
	EXPECT_NE(id3, id5);
	EXPECT_NE(id3, id4);

	EXPECT_EQ(pVal3, array.Get(id5));
	EXPECT_EQ(pVal2, array.Get(id4));
	EXPECT_FALSE(array.Get(id2));
	EXPECT_FALSE(array.Get(id3));
}

TEST(EntityArray, Iterate)
{
	// We should be able to iterate over existing entities, scipping deleted
	EntityArray<int> array;
	array.Insert(1);
	auto id = array.Insert(1);
	array.Insert(2);
	array.Insert(3);
	array.Delete(id);
	int sum = 0;
	for(int* pValue: array)
	{
		sum += *pValue;
	}
	
	EXPECT_EQ(sum, 6);
}
