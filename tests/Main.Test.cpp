#include <gtest/gtest.h>
#include <SpaceTycoonModel.h>
#include <easylogging++.h>

INITIALIZE_EASYLOGGINGPP


int main(int argc, char **argv) 
{
    ::testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS();
}

#include <easylogging++.cc>