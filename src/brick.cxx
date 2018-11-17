#include "brick.h"
#include <cassert>

namespace cubesnake
{
    Brick Brick::operator+(const Brick& rhs) const
    {
        return Brick(std::array<int, 3>({
                    this->position[0] + rhs.position[0],
                    this->position[1] + rhs.position[1],
                    this->position[2] + rhs.position[2]}));
    }

    Brick Brick::operator-(const Brick& rhs) const
    {
        return Brick(std::array<int, 3>({
                    this->position[0] - rhs.position[0],
                    this->position[1] - rhs.position[1],
                    this->position[2] - rhs.position[2]}));
    }

    bool Brick::operator==(const Brick& rhs) const
    {
        return (this->position[0] == rhs.position[0]
             && this->position[1] == rhs.position[1]
             && this->position[2] == rhs.position[2]);
    }

    void Brick::AddBricks(std::vector<Brick>& new_bricks,
                   Brick start_brick,
                   const int fixed_dimension) const
    {
        for (int i : {0, 1, 2})
        {
            if (i != fixed_dimension)
            {
                for (int j : {-1, 1})
                {
                    std::array<int, 3> new_brick_position
                        = start_brick.position;
                    new_brick_position[i] += j;
                    new_bricks.push_back(Brick(new_brick_position));
                }
            }
        }
    }

    std::vector<Brick> Brick::GetNextBricks(
            const Brick& before, const Direction dir) const
    {
        std::vector<Brick> return_vector;

        BrickDirection direction(*this - before);

        if (dir == STRAIGHT)
            return_vector.push_back(direction + *this);
        else if (dir == TURN)
            AddBricks(return_vector, *this, direction.GetDirectionDimension());

        return return_vector;
    }

    std::ostream& operator<<(std::ostream &out, const Brick& brick)
    {
        out << "[" << brick.position[0]
            << " " << brick.position[1]
            << " " << brick.position[2] << "]";
        return out;
    }


    int BrickDirection::GetDirectionDimension()
    {
        for (int i : {0, 1, 2})
            if (this->position[i] != 0)
                return i;
        assert(false);
    }
}
