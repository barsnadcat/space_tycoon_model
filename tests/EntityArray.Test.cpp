#include <gtest/gtest.h>
#include <EntityArray.h>
#include <easylogging++.h>

TEST(EntityArray, GetByInvalidId) 
{
	// We should get null pointer by invalid id
	EntityArray<int> array;
	int* val = array.Get(EntityId());
	EXPECT_EQ(val, nullptr);
}

TEST(EntityArray, GetById) 
{
	// We should be able to retrive entity pointer by id
	EntityArray<int> array;
	EntityId id = array.Allocate();
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
	EntityId id = array.Allocate();
	int* val = array.Get(id);
	EXPECT_TRUE(val);
	array.Delete(id);
	val = array.Get(id);
	EXPECT_EQ(val, nullptr);
}

TEST(EntityArray, Reuse)
{
	// Entity id of deleted entity should return null entity pointer, even after new entity was put in same place
	EntityArray<int> array;
	array.Allocate();
	EntityId id = array.Allocate();
	array.Allocate();
	int* val = array.Get(id);
	array.Delete(id);
	EntityId newId = array.Allocate();
	EXPECT_EQ(val, array.Get(newId));
	EXPECT_FALSE(array.Get(id));
	EXPECT_NE(id, newId);
}

TEST(EntityArray, Iterate)
{
	// We should be able to iterate over existing entities, scipping deleted
	EXPECT_TRUE(false);
}
