#ifndef __CHAIN_H__
#define __CHAIN_H__

#include <memory>
#include <vector>

namespace cubesnake
{
    enum Direction
    {
        AHEAD,
        CURVE
    };

    template<typename D>
    class Chain
    {
    public:

        void Add(D dir)
        {
            path.push_back(dir);
        }

        D Get(int n)
        {
            if (n > path.size())
            {
                throw 0;
            }
            return path[n];
        }

    protected:
        std::vector<D> path;
    };

}

#endif /* __CHAIN_H__ */
