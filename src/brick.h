#ifndef __BRiCK_H__
#define __BRiCK_H__

#include <memory>

namespace cubesnake
{
    using Position = std::array<int, 3>;

    template<typename P>
    class Brick
    {
    public:
        Brick(const P& pos)
        {
            position = pos;
        }
        P position;
    };
}

#endif /* __BRiCK_H__ */
