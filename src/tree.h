#ifndef __TREE_H__
#define __TREE_H__

#include <memory>

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
        SolutionTree(Area<B>& area, Chain& chain,
                std::unique_ptr<B> first_brick, std::unique_ptr<B> second_brick)
        {
            root = std::make_shared<TreeNode<B>>(std::move(first_brick));
            current_layer.push_back(std::make_shared<TreeNode<B>>(root, std::move(second_brick)));
        }
        void BuildNextLayer()
        {
            // 1. iterate on every current node
            for (auto node : current_layer)
            {
                // get position of node`s father and node
                // get direction from chain
                // iterate on all possible bricks
                // if brick fits in area create new node and push it into next_layer
            }

            next_layer.swap(current_layer);
        }

    private:
        std::shared_ptr<TreeNode<B>> root;
        std::vector<std::shared_ptr<TreeNode<B>>> current_layer;
        std::vector<std::shared_ptr<TreeNode<B>>> next_layer;
    };
}

#endif /* __TREE_H__ */
