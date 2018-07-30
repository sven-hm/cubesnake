#ifndef __AREA_H__
#define __AREA_H__

#include <memory>
#include <vector>

#include "brick.h"

namespace cubesnake
{
    template<typename B>
    using Condition = std::function<bool(const B&)>;

    template<typename B>
    class Area
    {
    public:
        void AddCondition(const Condition<B>& cond)
        {
            conditions.push_back(cond);
        }

        bool In(const B& brick) const
        {
            for (auto cond : conditions)
                if (!cond(brick))
                    return false;
            return true;
        }

    protected:
        std::vector<Condition<B>> conditions;
    };
}

#endif /* __AREA_H__ */
