#ifndef __FILE_READER_H__
#define __FILE_READER_H__

#include <iostream>
#include <string>

#include "area.h"
#include "brick.h"

namespace cubesnake
{
    class FileReader
    {
    public:
        FileReader(char* filename)
        {
            std::fstream file(filename, std::ios_base::in);

            std::string name;
            // create area
            file >> name;
            assert(name == "area");
            file >> name;
            assert(name == "cube");

            int size;
            file >> size;

            area.AddCondition([size](const Brick& brick){return brick.position[0] >= 0;});
            area.AddCondition([size](const Brick& brick){return brick.position[0] < size;});
            area.AddCondition([size](const Brick& brick){return brick.position[1] >= 0;});
            area.AddCondition([size](const Brick& brick){return brick.position[1] < size;});
            area.AddCondition([size](const Brick& brick){return brick.position[2] >= 0;});
            area.AddCondition([size](const Brick& brick){return brick.position[2] < size;});

            std::string line;
            // first line
            std::getline(file, line);
            std::cout << line << std::endl;

            // second line
            file >> name;
            int length;
            file >> length;

            std::string chainstring;
            file >> chainstring;
            assert(length == chainstring.length());
            for(char& cc : chainstring)
            {
                if (cc == 'S')
                {
                    chain.Add(STRAIGHT);
                }
                else if (cc == 'T')
                {
                    chain.Add(TURN);
                }
                else
                {
                    std::cout << "unknown character: " << cc << std::endl;
                }
            }

            int x, y, z;
            file >> x >> y >> z;
            auto first_brick =  std::make_unique<Brick>(std::array<int, 3>{x, y, z});
            file >> x >> y >> z;
            auto second_brick = std::make_unique<Brick>(std::array<int, 3>{x, y, z});

            //std::cout << *first_brick << std::endl;
            //std::cout << *second_brick << std::endl;

            solution_tree = SolutionTree<Brick> (
                    area, chain,
                    std::move(first_brick), std::move(second_brick));
        
            while (file >> x >> y >> z)
            {
                auto brick =  std::make_unique<Brick>(std::array<int, 3>{x, y, z});
                //std::cout << *brick << std::endl;
                solution_tree.AddBrick(std::move(brick));
            }
        }

    public:
        SolutionTree<Brick> solution_tree;

    private:
        Area<Brick> area;
        Chain chain;
    };
}

#endif /* __FILE_READER_H__ */
