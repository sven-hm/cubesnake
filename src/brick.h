#ifndef __BRiCK_H__
#define __BRiCK_H__

#include <memory>
#include <vector>
#include <iostream>
#include <cassert>

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

    template<int Dimension>
    class BrickDirection;

    template<int Dimension>
    class Brick
    {
    public:
        Brick(const std::array<int, Dimension> pos)
            : position(pos)
        {}

        int GetPosition(int dim) const
        {
            assert(dim >= 0 && dim < Dimension);
            return position[dim];
        }

        Brick operator+(const Brick& rhs) const
        {
            std::array<int, Dimension> new_pos;
            for (int i = 0; i < Dimension; i++)
                new_pos[i] = this->GetPosition(i) + rhs.GetPosition(i);
            return Brick(new_pos);
        }

        Brick operator-(const Brick& rhs) const
        {
            std::array<int, Dimension> new_pos;
            for (int i = 0; i < Dimension; i++)
                new_pos[i] = this->GetPosition(i) - rhs.GetPosition(i);
            return Brick(new_pos);
        }

        bool operator==(const Brick& rhs) const
        {
            for (int i = 0; i < Dimension; i++)
                if (this->GetPosition(i) != rhs.GetPosition(i))
                    return false;
            return true;
        }

        std::vector<Brick> GetNextBricks(const Brick& before, const Direction dir) const
        {
            std::vector<Brick> return_vector;

            BrickDirection<Dimension> direction(*this - before);

            if (dir == STRAIGHT)
                return_vector.push_back(direction + *this);
            else if (dir == TURN)
                AddBricks(return_vector, *this, direction.GetDirectionDimension());

            return return_vector;
        }

        friend std::ostream& operator<<(std::ostream& out, const Brick& brick)
        {
            out << "[";
            for (int i = 0; i < Dimension; i++)
                out << " " << brick.GetPosition(i);
            out << " ]";
            return out;
        }
    private:
        void AddBricks(std::vector<Brick>& new_bricks,
                       Brick start_brick,
                       const int fixed_Dimension) const
        {
            for (int i = 0; i < Dimension; i++)
                if (i != fixed_Dimension)
                    for (int j : {-1, 1})
                    {
                        std::array<int, Dimension> new_brick_position;
                        for (int k = 0; k < Dimension; k++)
                            new_brick_position[k] = start_brick.GetPosition(k);
                        new_brick_position[i] += j;
                        new_bricks.push_back(Brick(new_brick_position));
                    }
        }
        const std::array<int, Dimension> position;
    };

    template<int Dimension>
    class BrickDirection : public Brick<Dimension>
    {
    public:
        BrickDirection(const Brick<Dimension>& brick)
            : Brick<Dimension>(brick)
        {}
        int GetDirectionDimension()
        {
            for (int i = 0; i < Dimension; i++)
                if (this->GetPosition(i) != 0)
                    return i;
        }
    };
}

#endif /* __BRiCK_H__ */
