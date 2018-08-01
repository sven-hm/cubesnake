#include <iostream>
#include <memory>

#include "brick.h"
#include "area.h"
#include "tree.h"

using namespace cubesnake;

int main(int argc, char* argv[])
{
    // 1. define area, simple box
    Area<Brick> box;
    box.AddCondition([](const Brick& brick){return brick.position[0] > 0;});
    box.AddCondition([](const Brick& brick){return brick.position[0] < 4;});
    box.AddCondition([](const Brick& brick){return brick.position[1] > 0;});
    box.AddCondition([](const Brick& brick){return brick.position[1] < 4;});
    box.AddCondition([](const Brick& brick){return brick.position[2] > 0;});
    box.AddCondition([](const Brick& brick){return brick.position[2] < 4;});

    // 2. create chain
    Chain chain;
    chain.Add(AHEAD);
    chain.Add(AHEAD);
    chain.Add(CURVE);
    chain.Add(CURVE);
    chain.Add(AHEAD);
    chain.Add(CURVE);
    chain.Add(AHEAD);

    // 3. 
    auto first_brick =  std::make_unique<Brick>(std::array<int, 3>{0, 0, 0});
    auto second_brick = std::make_unique<Brick>(std::array<int, 3>{1, 0, 0});
    SolutionTree<Brick> solution_tree(
            box, chain,
            std::move(first_brick), std::move(second_brick));

    // 4.
    solution_tree.BuildNextLayer();

}
