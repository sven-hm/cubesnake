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

TEST(brick, addition_1)
{
    Brick<1> b1({1});
    Brick<1> b2({2});
    Brick<1> b3({3});

    EXPECT_EQ(b1 + b2, b3);
}

TEST(brick, addition_3)
{
    Brick<3> b1({1,2,3});
    Brick<3> b2({4,5,6});
    Brick<3> b3({5,7,9});

    EXPECT_EQ(b1 + b2, b3);
}

TEST(brick, substraction)
{
    Brick<3> b1({4,5,6});
    Brick<3> b2({1,2,3});
    Brick<3> b3({3,3,3});

    EXPECT_EQ(b1 - b2, b3);
}

TEST(brick, next_brick_straight_3)
{
    Brick<3> b1({1,1,0});
    Brick<3> b2({1,1,1});

    auto bricks = b2.GetNextBricks(b1, STRAIGHT);

    EXPECT_EQ(bricks.size(), 1);
    EXPECT_EQ(bricks[0], Brick<3>({1,1,2}));
}

TEST(brick, next_brick_turn_3)
{
    Brick<3> b1({1,1,0});
    Brick<3> b2({1,1,1});

    auto bricks = b2.GetNextBricks(b1, TURN);

    EXPECT_EQ(bricks.size(), 4);
    EXPECT_EQ(bricks[0], Brick<3>({0,1,1}));
    EXPECT_EQ(bricks[1], Brick<3>({2,1,1}));
    EXPECT_EQ(bricks[2], Brick<3>({1,0,1}));
    EXPECT_EQ(bricks[3], Brick<3>({1,2,1}));
}

TEST(brick, next_brick_straight_5)
{
    Brick<5> b1({1,1,1,1,0});
    Brick<5> b2({1,1,1,1,1});

    auto bricks = b2.GetNextBricks(b1, STRAIGHT);

    EXPECT_EQ(bricks.size(), 1);
    EXPECT_EQ(bricks[0], Brick<5>({1,1,1,1,2}));
}

TEST(brick, next_brick_turn_5)
{
    Brick<5> b1({1,1,1,1,0});
    Brick<5> b2({1,1,1,1,1});

    auto bricks = b2.GetNextBricks(b1, TURN);

    EXPECT_EQ(bricks.size(), 8);
    EXPECT_EQ(bricks[0], Brick<5>({0,1,1,1,1}));
    EXPECT_EQ(bricks[1], Brick<5>({2,1,1,1,1}));
    EXPECT_EQ(bricks[2], Brick<5>({1,0,1,1,1}));
    EXPECT_EQ(bricks[3], Brick<5>({1,2,1,1,1}));
    EXPECT_EQ(bricks[4], Brick<5>({1,1,0,1,1}));
    EXPECT_EQ(bricks[5], Brick<5>({1,1,2,1,1}));
    EXPECT_EQ(bricks[6], Brick<5>({1,1,1,0,1}));
    EXPECT_EQ(bricks[7], Brick<5>({1,1,1,2,1}));
}
