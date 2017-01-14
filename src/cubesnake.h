#include "cubesnake_version.h"

#include <memory>
#include <iostream>
#include <fstream>
#include <vector>
#include <deque>

using Brick = std::vector<int>;

template<typename T>
class Field
{
    public:
        Field(int asizex, int asizey, int asizez, T value)
            : sizex(asizex),
              sizey(asizey),
              sizez(asizez)
        {
            field = std::vector< std::vector< std::vector< T > > >(sizex,
                        std::vector< std::vector < T > >(sizey,
                            std::vector< T >(sizez, value)));
        }

        void set(Brick b, T value)
        {
            set(b[0], b[1], b[2], value);
        }

        void set(int x, int y, int z, T value)
        {
            field[x][y][z] = value;
        }

        bool is(Brick b, T ovalue, T nvalue)
        {
            return is(b[0], b[1], b[2], ovalue, nvalue);
        }

        bool checkvalidity(T ovalue, T nvalue)
        {
            return checkconnectivity(ovalue, nvalue);
        }

        bool is(int x, int y, int z, T ovalue, T nvalue)
        {
            bool isoldvalue = false;
            try
            {
                if (field.at(x).at(y).at(z) == ovalue)
                {
                    isoldvalue = true;
                }
            }
            catch (std::out_of_range)
            {
                //std::cout << "out of range" << std::endl;
            }
            if (isoldvalue)
                set(x, y, z, nvalue);
            return isoldvalue;

        }

        bool are(Brick b1, Brick b2, T ovalue, T nvalue)
        {
            unsigned int count = 0;
            unsigned int dir = 0;
            for (auto i : {0, 1, 2})
                if (b1[i] != b2[i])
                {
                    dir = i;
                    count++;
                }

            if (count == 0)
                return is(b1, ovalue, nvalue);
            else if (count == 1)
            {
                int pmin = std::min(b1[dir], b2[dir]);
                int pmax = std::max(b1[dir], b2[dir]);
                int fac = 1;
                if (pmin == b2[dir])
                    fac = -1;
                unsigned int l = pmax - pmin;
                unsigned int count2 = 0;
                for (unsigned int i = 1; i <= l; i++)
                {
                    if (dir == 0)
                    {
                        if (is(b1[0] + fac * i, b1[1], b1[2], ovalue, nvalue))
                            count2++;
                    }
                    else if (dir == 1)
                    {
                        if (is(b1[0], b1[1] + fac * i, b1[2], ovalue, nvalue))
                            count2++;
                    }
                    else if (dir == 2)
                    {
                        if (is(b1[0], b1[1], b1[2] + fac * i, ovalue, nvalue))
                            count2++;
                    }
                }
                if (count2 == l)
                    return true;
                else
                    return false;
            }
            else 
                throw std::runtime_error("bricks have to be placed \"in a row\"");
        }

    private:
        bool checkconnectivity(T ovalue, T nvalue)
        {
            Field<T> tmpfield = *this;

            Brick start;
            bool startfound = false;
            int number_of_ovalues = 0;

            // count "free" bricks and pick a (random) start brick
            for (int i = 0; i < sizex; i++)
                for (int j = 0; j < sizey; j++)
                    for (int k = 0; k < sizez; k++)
                        if (tmpfield.is(i, j, k, ovalue, ovalue))
                        {
                            number_of_ovalues++;
                            if (!startfound)
                            {
                                start = {i, j, k};
                                startfound = true;
                            }
                        }
            // 
            if (number_of_ovalues == 0)
                return true;

            // count "neighbours" of start brick
            int number_of_neighbours = 0;
            std::function<void(Brick)> counter
                = [&](Brick brick) 
                {
                    if (tmpfield.is(brick, nvalue, nvalue))
                        return;
                    else if (tmpfield.is(brick, ovalue, nvalue))
                    {
                        number_of_neighbours++;
                        std::vector<Brick> nd =
                            {
                                {-1, 0, 0},
                                { 1, 0, 0},
                                { 0,-1, 0},
                                { 0, 1, 0},
                                { 0, 0,-1},
                                { 0, 0, 1},
                            };
                        for (auto& d : nd)
                        {
                            Brick nb = {brick[0] + d[0],
                                        brick[1] + d[1],
                                        brick[2] + d[2]};
                            counter(nb);
                        }
                    }
                };
            counter(start);

            if (number_of_ovalues == number_of_neighbours)
                return true;
            else
                return false;
        }

        int sizex, sizey, sizez;
        std::vector< std::vector< std::vector< T > > > field;
};

template<typename T>
class TreeNode
{
    public:
        std::shared_ptr<Field<T>> field;
        std::shared_ptr<TreeNode> father;
        Brick position;
        bool valid;

    public:
        Field<T> GetField()
        { return *field; }

        void DeleteField()
        {
            field = nullptr;
        }

        Brick GetPosition() const
        { return position; }
        
        Brick GetFatherPosition() const
        { return father->GetPosition(); }
        
        std::shared_ptr<TreeNode> GetFather() const
        { return father; }

        bool IsValid(T ovalue, T nvalue) const
        {
            return (valid and field->checkvalidity(ovalue, nvalue));
        }

        bool IsRoot() const
        {
            if (!father)
                return true;
            else
                return false;
        }

        /*
         * Constructor for root node
         */
        TreeNode(Brick pos, Field<T> tmpfield, T ovalue, T nvalue)
            : father(nullptr),
              position(pos)
        {
            field = std::make_shared<Field<T>> (tmpfield);

            if (field->is(position, ovalue, nvalue))
                valid = true;
            else
                valid = false;
        }

        /*
         * Constructor for child nodes
         */
        TreeNode(Brick pos, const std::shared_ptr<TreeNode>& node, T ovalue, T nvalue)
            : father(node),
              position(pos)
        {
            field = std::make_shared<Field<T>> (node->GetField());

            // check if it fits
            valid = field->are(node->GetPosition(), position, ovalue, nvalue);
        }
};

template<typename T>
using TreeLevel = std::vector< std::shared_ptr< TreeNode<T> > >;

std::vector<Brick> NewPositions(Brick b1, Brick b2, int length)
{
    std::vector<Brick> newpos;
    unsigned int count = 0;
    unsigned int dir = 0;
    for (auto i : {0, 1, 2})
        if (b1[i] != b2[i])
        {
            dir = i;
            count++;
        }

    if (count == 1)
    {
        for (auto sign : {-1, 1})
        {
            Brick newpnt1;
            Brick newpnt2;
            if (dir == 0)
            {
                newpnt1 = {b2[0],
                           b2[1] + sign * length,
                           b2[2]};
                newpnt2 = {b2[0],
                           b2[1],
                           b2[2] + sign * length};
            }
            else if (dir == 1)
            {
                newpnt1 = {b2[0] + sign * length,
                           b2[1],
                           b2[2]};
                newpnt2 = {b2[0],
                           b2[1],
                           b2[2] + sign * length};
            }
            else if (dir == 2)
            {
                newpnt1 = {b2[0] + sign * length,
                           b2[1],
                           b2[2]};
                newpnt2 = {b2[0],
                           b2[1] + sign * length,
                           b2[2]};
            }

            newpos.push_back(newpnt1);
            newpos.push_back(newpnt2);
        }
    }
    return newpos;
};

void run(std::vector<Brick> startvalues,
         Field<bool> field,
         std::deque<int> Sequence)
{
    if (startvalues.size() < 2)
        return;

    field.is(startvalues[0], false, true);
    auto root = std::make_shared<TreeNode<bool>> (startvalues[0], field, false, true);
    
    auto nextnode = std::make_shared<TreeNode<bool>> (startvalues[1], root, false, true);

    for (auto startvalue : startvalues)
        nextnode = std::make_shared<TreeNode<bool>> (startvalue, nextnode, false, true);

    TreeLevel<bool> CurrentLevel = {nextnode};

    std::cout << "step\tnumber of candidates" << std::endl;

    for (unsigned int i = startvalues.size() - 1; i < Sequence.size(); i++)
    {
        TreeLevel<bool> NewLevel;

        //for (auto it = CurrentLevel.begin(); it != CurrentLevel.end(); it++)
        for (auto&& node : CurrentLevel)
        {
            std::vector<Brick> newpos =
                NewPositions(node->GetFatherPosition(), node->GetPosition(), Sequence[i]);

            //for (auto pit = newpos.begin(); pit != newpos.end(); pit++)
            for (auto&& brick : newpos)
            {
                TreeNode<bool> newnode(brick, node, false, true);
                if (newnode.IsValid(false, true))
                {
                    NewLevel.push_back(std::make_shared<TreeNode<bool>>(newnode));
                }
            }
            node->DeleteField();
        }
        if (NewLevel.size() == 0)
        {
            std::cout << "\n... no solution :/\n";
            break;
        }
        CurrentLevel = NewLevel;

        std::cout << i + 1 << "\t" << CurrentLevel.size() << "\n";
    }

    std::cout << std::endl;

    for (auto it = CurrentLevel.begin(); it != CurrentLevel.end(); it++)
    {
        auto ptr = (*it);

        do
        {
            std::cout << "(" << ptr->GetPosition()[0]
                      << "," << ptr->GetPosition()[1]
                      << "," << ptr->GetPosition()[2] << ")-";

            ptr = ptr->GetFather();
        } while (!ptr->IsRoot());

        std::cout << "(" << ptr->GetPosition()[0]
                  << "," << ptr->GetPosition()[1]
                  << "," << ptr->GetPosition()[2] << ")\n";
    }
};
