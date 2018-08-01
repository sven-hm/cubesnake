#ifndef __BRiCK_H__
#define __BRiCK_H__

#include <memory>
#include <vector>

namespace cubesnake
{
    enum Direction
    {
        AHEAD,
        CURVE
    };

    class Chain
    {
    public:

        void Add(Direction dir)
        {
            path.push_back(dir);
        }

        std::vector<Direction> path;
    };

    class Brick
    {
    public:
        Brick(const std::array<int, 3> pos)
        {
            position = pos;
        }
        std::array<int, 3> position;

        Brick operator+(const Brick& rhs) const
        {
            return Brick(std::array<int, 3>({
                        this->position[0] + rhs.position[0],
                        this->position[1] + rhs.position[1],
                        this->position[2] + rhs.position[2]}));
        }

        Brick operator-(const Brick& rhs) const
        {
            return Brick(std::array<int, 3>({
                        this->position[0] - rhs.position[0],
                        this->position[1] - rhs.position[1],
                        this->position[2] - rhs.position[2]}));
        }

        std::vector<Brick> GetNextBricks(const Brick& before, const Direction dir) const
        {
            std::vector<Brick> return_vector;
            if (dir == AHEAD)
            {
                return_vector.push_back(*this - before + *this);
            }
            else if (dir == CURVE)
            {
                // get all four orthogonals
            }
            return return_vector;
        }
    };
}

#endif /* __BRiCK_H__ */
