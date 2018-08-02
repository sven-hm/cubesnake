#ifndef __TREE_H__
#define __TREE_H__

#include <memory>
#include <cassert>

#include "area.h"
#include "brick.h"

namespace cubesnake
{
    template<typename T>
    class TreeNode
    {
    public:
        TreeNode(std::shared_ptr<TreeNode> _father, std::unique_ptr<T> _data)
            : father(_father),
              data(std::move(_data))
        {}

        TreeNode(std::unique_ptr<T> _data)
            : father(nullptr),
              data(std::move(_data))
        {}

        std::shared_ptr<TreeNode> GetFather() const
        { return father; }

        T ReadData() const
        { return *data; }

        T* GetData()
        { return data.release(); }

        bool IsRoot() const
        { return !father; }

    protected:
        std::shared_ptr<TreeNode<T>> father;
        std::unique_ptr<T> data;
    };

    template<typename B>
    class SolutionTree
    {
    public:
        SolutionTree(){}
        SolutionTree(
                Area<B>& _area,
                Chain& _chain,
                std::unique_ptr<B> first_brick,
                std::unique_ptr<B> second_brick)
            : area(_area),
              chain(_chain),
              root(std::make_shared<TreeNode<B>>(std::move(first_brick))),
              current_layer_number(0)
        {
            current_layer.push_back(std::make_shared<TreeNode<B>>(root, std::move(second_brick)));
            current_layer_number++;
        }

        void AddBrick(std::unique_ptr<B> next_brick)
        {
            assert(current_layer.size() == 1);
            next_layer.push_back(std::make_shared<TreeNode<B>>(
                        current_layer[0], std::move(next_brick)));
            next_layer.swap(current_layer);
            next_layer.clear();
            current_layer_number++;
        }

        bool IntersectWithPrevious(std::shared_ptr<TreeNode<B>> father, B& brick)
        {
            if (brick == father->ReadData())
            {
                return true;
            }
            else if (father->IsRoot())
            {
                return false;
            }
            else
            {
                return IntersectWithPrevious(father->GetFather(), brick);
            }
        }

        bool BuildNextLayer()
        {
            for (auto node : current_layer)
            {
                // get position of node`s father and node
                auto new_bricks = node->ReadData().GetNextBricks(
                        node->GetFather()->ReadData(),
                        chain.Get(current_layer_number));

                for (auto b : new_bricks)
                {
                    // check if b fits in area
                    // check if b does not intersect with previous bricks
                    // push to next_layer
                    if (area.In(b) && !IntersectWithPrevious(node->GetFather(), b))
                    {
                        next_layer.push_back(std::make_shared<TreeNode<B>>(
                                    node, std::make_unique<B>(b)));
                    }
                }
            }

            if (next_layer.size() == 0)
                return false;

            next_layer.swap(current_layer);
            next_layer.clear();
            current_layer_number++;
            return true;
        }

        void Solve(int number_steps=0)
        {
            if (number_steps == 0)
                while(BuildNextLayer());
            else
                for (int ii = 0; ii < number_steps; ii++)
                    BuildNextLayer();

        }

        void DumpSolutions()
        {
            std::cout << "Layer " << current_layer_number << " has " << current_layer.size() << " solutions." << std::endl;
            for (auto node : current_layer)
            {
                std::cout << "============================" << std::endl;
                std::vector<B> solution;
                GetBranch(solution, node);
                for (auto rit = solution.rbegin(); rit < solution.rend(); rit++)
                {
                    std::cout << *rit << std::endl;
                }
            }
        }

        void GetBranch(std::vector<B>& solution, std::shared_ptr<TreeNode<B>> node)
        {
            solution.push_back(node->ReadData());
            if (!node->IsRoot())
            {
                GetBranch(solution, node->GetFather());
            }
        }

    private:
        std::shared_ptr<TreeNode<B>> root;
        std::vector<std::shared_ptr<TreeNode<B>>> current_layer;
        int current_layer_number;
        std::vector<std::shared_ptr<TreeNode<B>>> next_layer;
        Area<B> area;
        Chain chain;
    };
}

#endif /* __TREE_H__ */
