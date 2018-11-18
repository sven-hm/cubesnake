#ifndef __FILE_READER_H__
#define __FILE_READER_H__

#include <iostream>
#include <string>
#include <exception>

#include "area.h"
#include "brick.h"
#include "tree.h"
#include "logger.h"

#define DIMENSION (3)

namespace cubesnake
{
    enum area_type
    {
        CUBE,
        CUBOID,
        UNKNOWN
    };

    area_type getAreaType(std::string instr)
    {
        if (instr == "cube") return CUBE;
        else if (instr == "cuboid") return CUBOID;
        else return UNKNOWN;
    };

    class FileReader
    {
    public:
        FileReader(std::string filename, int number_of_threads)
        {
            std::fstream file(filename, std::ios_base::in);

            auto logger = std::make_shared<Logger>(filename + ".log");
            logger->AddMessage("");

            std::string name;

            // check dimension
            file >> name;
            assert(name == "dimension");
            int dimension;
            file >> dimension;
            assert(dimension == DIMENSION);

            // create area
            file >> name;
            assert(name == "area");

            file >> name;
            int size, sizex, sizey, sizez;
            switch (getAreaType(name))
            {
                case CUBE:
                    file >> sizex;
                    sizey = sizez = sizex;
                    break;

                case CUBOID:
                    file >> sizex, sizey, sizez;
                    break;

                case UNKNOWN:
                default:
                    throw std::runtime_error("file format error :/");
                    break;
            }

            size = sizex * sizey * sizez;

            area.AddCondition([]
                    (const Brick<DIMENSION>& brick){return brick.position[0] >= 0;});
            area.AddCondition([sizex]
                    (const Brick<DIMENSION>& brick){return brick.position[0] < sizex;});
            area.AddCondition([]
                    (const Brick<DIMENSION>& brick){return brick.position[1] >= 0;});
            area.AddCondition([sizey]
                    (const Brick<DIMENSION>& brick){return brick.position[1] < sizey;});
            area.AddCondition([]
                    (const Brick<DIMENSION>& brick){return brick.position[2] >= 0;});
            area.AddCondition([sizez]
                    (const Brick<DIMENSION>& brick){return brick.position[2] < sizez;});

            std::string line;
            // first line
            std::getline(file, line);
            std::cout << line << std::endl;

            // second line
            file >> name;
            assert(name == "chain");
            int length;
            file >> length;
            assert(length == size);

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
            auto first_brick =  std::make_unique<Brick<DIMENSION>>(std::array<int, DIMENSION>{x, y, z});
            file >> x >> y >> z;
            auto second_brick = std::make_unique<Brick<DIMENSION>>(std::array<int, DIMENSION>{x, y, z});

            //std::cout << *first_brick << std::endl;
            //std::cout << *second_brick << std::endl;

            solution_tree = SolutionTree<Brick<DIMENSION>> (
                    area, chain,
                    std::move(first_brick), std::move(second_brick),
                    logger, number_of_threads);
        
            while (file >> x >> y >> z)
            {
                auto brick =  std::make_unique<Brick<DIMENSION>>(std::array<int, DIMENSION>{x, y, z});
                //std::cout << *brick << std::endl;
                solution_tree.AddBrick(std::move(brick));
            }
        }

    public:
        SolutionTree<Brick<DIMENSION>> solution_tree;

    private:
        Area<Brick<DIMENSION>> area;
        Chain chain;
    };
}

#endif /* __FILE_READER_H__ */
