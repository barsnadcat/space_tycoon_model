#include <gtest/gtest.h>
#include <EntityArray.h>

TEST(EntityArray, GetById) 
{
	// We should be able to retrive entity pointer by id
	EXPECT_TRUE(false);
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
