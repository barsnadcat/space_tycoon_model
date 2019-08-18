#include <gtest/gtest.h>
#include <SpaceTycoonModel.h>
#include <easylogging++.h>

INITIALIZE_EASYLOGGINGPP

TEST(Dummy, Pass) 
{
    EXPECT_TRUE(Do(1));
}


int main(int argc, char **argv) 
{
    ::testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS();
}

#include <easylogging++.cc>