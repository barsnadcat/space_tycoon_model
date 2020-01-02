#include <gtest/gtest.h>
#include <EntityArray.h>

TEST(EntityArray, GetByInvalidId) 
{
	// We should get null pointer by invalid id
	EntityArray<int> array;
	int* val = array.Get(0);
	EXPECT_EQ(val, nullptr);
}

TEST(EntityArray, GetById) 
{
	// We should be able to retrive entity pointer by id
	EntityArray<int> array;
	size_t id = array.Allocate();
	int* val = array.Get(id);
	*val = 6;
	val = array.Get(id);
	EXPECT_EQ(*val, 6);
}

TEST(EntityArray, Delete)
{
	// After deltion we should get null entity pointer
	EXPECT_TRUE(false);
}

TEST(EntityArray, Reuse)
{
	// Entity id of deleted entity should return null entity pointer, even after new entity was put in same place
	EXPECT_TRUE(false);
}

TEST(EntityArray, Iterate)
{
	// We should be able to iterate over existing entities, scipping deleted
	EXPECT_TRUE(false);
}
