#include <iostream>
#include <fstream>
#include <memory>

#include "brick.h"
#include "area.h"
#include "tree.h"
#include "file_reader.h"

using namespace cubesnake;

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cout << "Usage: cubesnake infile.txt" << std::endl;
        return 1;
    }

    FileReader fr(argv[1]);

    for (int ii = 0; ii < 23; ii++)
        fr.solution_tree.BuildNextLayer();

    fr.solution_tree.DumpSolutions();
}
//    // 1. define area, simple box
//    Area<Brick> box;
//    box.AddCondition([](const Brick& brick){return brick.position[0] >= 0;});
//    box.AddCondition([](const Brick& brick){return brick.position[0] <= 2;});
//    box.AddCondition([](const Brick& brick){return brick.position[1] >= 0;});
//    box.AddCondition([](const Brick& brick){return brick.position[1] <= 2;});
//    box.AddCondition([](const Brick& brick){return brick.position[2] >= 0;});
//    box.AddCondition([](const Brick& brick){return brick.position[2] <= 2;});
//
//    Chain chain;
//    /*
//    chain.Add(STRAIGHT);// 1
//    chain.Add(TURN);
//    chain.Add(TURN);
//    chain.Add(STRAIGHT);
//    chain.Add(TURN);
//    chain.Add(STRAIGHT);
//    chain.Add(TURN);
//    chain.Add(TURN);
//    chain.Add(STRAIGHT);
//    chain.Add(TURN);// 10
//    chain.Add(TURN);
//    chain.Add(TURN);
//    chain.Add(STRAIGHT);
//    chain.Add(TURN);
//    chain.Add(STRAIGHT);
//    chain.Add(TURN);
//    chain.Add(TURN);
//    chain.Add(TURN);
//    chain.Add(TURN);
//    chain.Add(STRAIGHT);// 20
//    chain.Add(TURN);
//    chain.Add(STRAIGHT);
//    chain.Add(TURN);
//    chain.Add(STRAIGHT);
//    chain.Add(TURN);
//    chain.Add(STRAIGHT);
//    chain.Add(STRAIGHT);
//    -------------------------
//    */
//    chain.Add(STRAIGHT);// 1
//    chain.Add(STRAIGHT);
//    chain.Add(TURN);
//    chain.Add(TURN);
//    chain.Add(TURN);
//    chain.Add(TURN);
//    chain.Add(TURN);
//    chain.Add(TURN);
//    chain.Add(TURN);
//    chain.Add(TURN); // 10
//    chain.Add(TURN);
//    chain.Add(STRAIGHT);
//    chain.Add(TURN);
//    chain.Add(TURN);
//    chain.Add(TURN);
//    chain.Add(TURN);
//    chain.Add(TURN);
//    chain.Add(TURN);
//    chain.Add(TURN);
//    chain.Add(STRAIGHT);// 20
//    chain.Add(TURN);
//    chain.Add(STRAIGHT);
//    chain.Add(TURN);
//    chain.Add(TURN);
//    chain.Add(TURN);
//    chain.Add(TURN);
//    chain.Add(STRAIGHT);
//    /*
//    ======================
//    chain.Add(STRAIGHT); // 1
//    chain.Add(STRAIGHT);
//    chain.Add(TURN);
//    chain.Add(TURN);
//    chain.Add(TURN);
//    chain.Add(STRAIGHT);
//    chain.Add(TURN);
//    chain.Add(TURN);
//    chain.Add(STRAIGHT);
//    chain.Add(TURN); // 10
//    chain.Add(TURN);
//    chain.Add(TURN);
//    chain.Add(STRAIGHT);
//    chain.Add(TURN);
//    chain.Add(STRAIGHT);
//    chain.Add(TURN);
//    chain.Add(TURN);
//    chain.Add(TURN);
//    chain.Add(TURN);
//    chain.Add(STRAIGHT); // 20
//    chain.Add(TURN);
//    chain.Add(STRAIGHT);
//    chain.Add(TURN);
//    chain.Add(STRAIGHT);
//    chain.Add(TURN);
//    chain.Add(STRAIGHT);
//    chain.Add(STRAIGHT);
//    */
//
//    // 3. 
//    auto first_brick =  std::make_unique<Brick>(std::array<int, 3>{0, 0, 0});
//    auto second_brick = std::make_unique<Brick>(std::array<int, 3>{1, 0, 0});
//
//    std::cout << *first_brick << std::endl;
//    std::cout << *second_brick << std::endl;
//
//    SolutionTree<Brick> solution_tree(
//            box, chain,
//            std::move(first_brick), std::move(second_brick));
//
//    auto brick3 = std::make_unique<Brick>(std::array<int, 3>{2, 0, 0});
//    auto brick4 = std::make_unique<Brick>(std::array<int, 3>{2, 1, 0});
//    solution_tree.AddBrick(std::move(brick3));
//    solution_tree.AddBrick(std::move(brick4));
//
//    // 4.
//    for (int ii = 0; ii < 23; ii++)
//        solution_tree.BuildNextLayer();
//
//    solution_tree.DumpSolutions();
//}
