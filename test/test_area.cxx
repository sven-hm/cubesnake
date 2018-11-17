#include <iostream>
#include <gtest/gtest.h>

#include <area.h>

using namespace cubesnake;

TEST(create, area)
{
    Area<Brick> area;

    int size = 4;

    area.AddCondition([size](const Brick& brick){return brick.position[0] >= 0;});
    area.AddCondition([size](const Brick& brick){return brick.position[0] < size;});
    area.AddCondition([size](const Brick& brick){return brick.position[1] >= 0;});
    area.AddCondition([size](const Brick& brick){return brick.position[1] < size;});
    area.AddCondition([size](const Brick& brick){return brick.position[2] >= 0;});
    area.AddCondition([size](const Brick& brick){return brick.position[2] < size;});

    Brick b1({1,2,3});
    Brick b2({4,5,6});
    Brick b3({5,7,9});
    Brick b4({-1,0,0});

    EXPECT_EQ(area.In(b1), true);
    EXPECT_EQ(area.In(b2), false);
    EXPECT_EQ(area.In(b3), false);
    EXPECT_EQ(area.In(b4), false);
}
