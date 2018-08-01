#include "brick.h"

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
                    new_bricks.push_back(start_brick);
                    new_bricks.back().position[i] += j;
                }
            }
        }
    }

    std::vector<Brick> Brick::GetNextBricks(const Brick& before, const Direction dir) const
    {
        std::vector<Brick> return_vector;

        Brick orientation = *this - before;

        if (dir == STRAIGHT)
        {
            return_vector.push_back(orientation + *this);
        }
        else if (dir == TURN)
        {
            if (orientation.position[0] != 0)
            {
                AddBricks(return_vector, *this, 0);
            }
            else if (orientation.position[1] != 0)
            {
                AddBricks(return_vector, *this, 1);
            }
            else if (orientation.position[2] != 0)
            {
                AddBricks(return_vector, *this, 2);
            }
        }
        return return_vector;
    }

    std::ostream& operator<<(std::ostream &out, const Brick& brick)
    {
        out << "[" << brick.position[0]
            << " " << brick.position[1]
            << " " << brick.position[2] << "]";
        return out;  
    }
}
