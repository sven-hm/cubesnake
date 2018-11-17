#include <iostream>
#include <gtest/gtest.h>

#include <brick.h>

using namespace cubesnake;

TEST(chain, creation)
{
    Chain c;
    c.Add(STRAIGHT);
    c.Add(STRAIGHT);
    c.Add(TURN);

    EXPECT_EQ(c.Get(0), STRAIGHT);
    EXPECT_EQ(c.Get(2), TURN);
}

TEST(brick, addition)
{
    Brick b1({1,2,3});
    Brick b2({4,5,6});
    Brick b3({5,7,9});

    EXPECT_EQ(b1 + b2, b3);
}

TEST(brick, substraction)
{
    Brick b1({4,5,6});
    Brick b2({1,2,3});
    Brick b3({3,3,3});

    EXPECT_EQ(b1 - b2, b3);
}

TEST(brick, next_brick_straight)
{
    Brick b1({1,1,0});
    Brick b2({1,1,1});

    auto bricks = b2.GetNextBricks(b1, STRAIGHT);

    EXPECT_EQ(bricks.size(), 1);
    EXPECT_EQ(bricks[0], Brick({1,1,2}));
}

TEST(brick, next_brick_turn)
{
    Brick b1({1,1,0});
    Brick b2({1,1,1});

    auto bricks = b2.GetNextBricks(b1, TURN);

    EXPECT_EQ(bricks.size(), 4);
    EXPECT_EQ(bricks[0], Brick({0,1,1}));
    EXPECT_EQ(bricks[1], Brick({2,1,1}));
    EXPECT_EQ(bricks[2], Brick({1,0,1}));
    EXPECT_EQ(bricks[3], Brick({1,2,1}));
}
