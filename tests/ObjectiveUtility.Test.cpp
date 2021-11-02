#include <src/easylogging++.h>
#include <gtest/gtest.h>

#include <ObjectiveUtility.h>

TEST(ObjectiveUtility, Farm)
{
    ObjectiveUtility u(1.0f, 1, 2, 3);
    EXPECT_FLOAT_EQ(u.GetTotalUtility(0), 0.0f);
    EXPECT_FLOAT_EQ(u.GetTotalUtility(1), 1.0f);
    EXPECT_FLOAT_EQ(u.GetTotalUtility(2), 1.0f);
    EXPECT_FLOAT_EQ(u.GetTotalUtility(3), 0.0f);
    EXPECT_FLOAT_EQ(u.GetMarginalUtility(1, 0), 0.0f);
    EXPECT_FLOAT_EQ(u.GetMarginalUtility(1, 1), 0.0f);
    EXPECT_FLOAT_EQ(u.GetMarginalUtility(0, 1), 1.0f);
    EXPECT_FLOAT_EQ(u.GetMarginalUtility(2, 1), -1.0f);
    EXPECT_FLOAT_EQ(u.GetMarginalUtility(1, -1), -1.0f);
}
