#ifndef __BRiCK_H__
#define __BRiCK_H__

#include <memory>
#include <vector>
#include <iostream>

namespace cubesnake
{
    enum Direction
    {
        STRAIGHT,
        TURN
    };

    class Chain
    {
    public:

        void Add(Direction dir)
        {
            path.push_back(dir);
        }

        Direction Get(int index) const
        {
            return path[index];
        }

        std::vector<Direction> path;
    };

    class Brick
    {
    public:
        Brick(const std::array<int, 3> pos)
            : position(pos)
        {}
        const std::array<int, 3> position;

        Brick operator+(const Brick& rhs) const;
        Brick operator-(const Brick& rhs) const;
        bool operator==(const Brick& rhs) const;

        std::vector<Brick> GetNextBricks(const Brick& before, const Direction dir) const;

        friend std::ostream& operator<<(std::ostream &out, const Brick& brick);
    protected:
        void AddBricks(std::vector<Brick>& new_bricks,
                       Brick start_brick,
                       const int fixed_dimension) const;
    };

    class BrickDirection : public Brick
    {
    public:
        BrickDirection(const Brick& brick)
            : Brick(brick)
        {}
        int GetDirectionDimension();
    };
}

#endif /* __BRiCK_H__ */
