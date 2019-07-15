#include "Cap.h"
#include <algorithm>

#include "BulletTime.h"

namespace cap
{

    float bullet_time_ = 0;
    
    NOTMEME __BULLET_TIME_IN()
    {
        //
    }

    NOTMEME __BULLET_TIME_OUT()
    {
        //
    }

    NOTMEME __BULLET_TIME_FRAME()
    {
        bullet_time_ += 0.5f;

        std::clamp(bullet_time_, 0.f, 1.f);
    }
}
