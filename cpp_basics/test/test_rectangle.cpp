#include "gtest/gtest.h"
#include "rectangle.hpp"

TEST(RectangleTest, addtest)
{
    EXPECT_EQ(sumas(2,3),5);
}
TEST(RectangleTest, classtest)
{
    Rectangle test1(4, 1, 1, 1);
    EXPECT_EQ(test1.show_field(),4);
    test1.scale(2);
    EXPECT_EQ(test1.show_field(),16);
    EXPECT_EQ(test1.show_field(),16);
}