#include <iostream>
#include <gtest/gtest.h>

#include <area.h>

using namespace cubesnake;

TEST(create, area_1)
{
    Area<Brick<1>> area;

    int size = 2;

    area.AddCondition([size](const Brick<1>& brick){return brick.position[0] >= 0;});
    area.AddCondition([size](const Brick<1>& brick){return brick.position[0] < size;});

    Brick<1> b1({1});
    Brick<1> b2({4});

    EXPECT_EQ(area.In(b1), true);
    EXPECT_EQ(area.In(b2), false);
}

TEST(create, area_3)
{
    Area<Brick<3>> area;

    int size = 4;

    area.AddCondition([size](const Brick<3>& brick){return brick.position[0] >= 0;});
    area.AddCondition([size](const Brick<3>& brick){return brick.position[0] < size;});
    area.AddCondition([size](const Brick<3>& brick){return brick.position[1] >= 0;});
    area.AddCondition([size](const Brick<3>& brick){return brick.position[1] < size;});
    area.AddCondition([size](const Brick<3>& brick){return brick.position[2] >= 0;});
    area.AddCondition([size](const Brick<3>& brick){return brick.position[2] < size;});

    Brick<3> b1({1,2,3});
    Brick<3> b2({4,5,6});
    Brick<3> b3({5,7,9});
    Brick<3> b4({-1,0,0});

    EXPECT_EQ(area.In(b1), true);
    EXPECT_EQ(area.In(b2), false);
    EXPECT_EQ(area.In(b3), false);
    EXPECT_EQ(area.In(b4), false);
}

TEST(create, area_5)
{
    Area<Brick<5>> area;

    int size = 4;

    area.AddCondition([size](const Brick<5>& brick){return brick.position[0] >= 0;});
    area.AddCondition([size](const Brick<5>& brick){return brick.position[0] < size;});
    area.AddCondition([size](const Brick<5>& brick){return brick.position[1] >= 0;});
    area.AddCondition([size](const Brick<5>& brick){return brick.position[1] < size;});
    area.AddCondition([size](const Brick<5>& brick){return brick.position[2] >= 0;});
    area.AddCondition([size](const Brick<5>& brick){return brick.position[2] < size;});
    area.AddCondition([size](const Brick<5>& brick){return brick.position[3] >= 0;});
    area.AddCondition([size](const Brick<5>& brick){return brick.position[3] < size;});
    area.AddCondition([size](const Brick<5>& brick){return brick.position[4] >= 0;});
    area.AddCondition([size](const Brick<5>& brick){return brick.position[4] < size;});

    Brick<5> b1({1,2,3,3,2});
    Brick<5> b2({4,5,6,3,6});
    Brick<5> b3({5,7,9,3,6});
    Brick<5> b4({-1,0,0});

    EXPECT_EQ(area.In(b1), true);
    EXPECT_EQ(area.In(b2), false);
    EXPECT_EQ(area.In(b3), false);
    EXPECT_EQ(area.In(b4), false);
}
