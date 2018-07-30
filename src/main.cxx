#include <iostream>

#include "area.h"
#include "chain.h"
#include "tree.h"

using namespace cubesnake;

int main(int argc, char* argv[])
{
    // 1. define area, simple box
    Area<Brick<Position>> box;
    box.AddCondition([](const Brick<Position>& brick){return brick.position[0] > 0;});
    box.AddCondition([](const Brick<Position>& brick){return brick.position[0] < 4;});
    box.AddCondition([](const Brick<Position>& brick){return brick.position[1] > 0;});
    box.AddCondition([](const Brick<Position>& brick){return brick.position[1] < 4;});
    box.AddCondition([](const Brick<Position>& brick){return brick.position[2] > 0;});
    box.AddCondition([](const Brick<Position>& brick){return brick.position[2] < 4;});

    // 2. create chain
    Chain<Direction> chain;
    chain.Add(AHEAD);
    chain.Add(AHEAD);
    chain.Add(CURVE);
    chain.Add(CURVE);
    chain.Add(AHEAD);
    chain.Add(CURVE);
    chain.Add(AHEAD);

    // 3. set start position of chain
    SolutionTree<Direction, Brick<Position>> solution_tree(box, chain);

    // 4. create solution-tree

}
