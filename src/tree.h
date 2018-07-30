#ifndef __TREE_H__
#define __TREE_H__

#include <memory>

#include "area.h"
#include "chain.h"

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

    template<typename D, typename B>
    class SolutionTree
    {
    public:
        SolutionTree(Area<B>& area, Chain<D>& chain)
        {}
        void SetInitialBricks(B& first_brick, B& second_brick)
        {}
        void BuildNextLayer();
        // 1. iterate on every current node
        // 2. check on all children if they fit in area
        // 3. push fitting children into next current layer

    private:
        //TreeNode<B> root;
    };
}

#endif /* __TREE_H__ */
