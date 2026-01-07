#ifndef __GeometryDash__TextArea__
#define __GeometryDash__TextArea__

#include "cocos2d.h"

#include <stdio.h>

class TextArea : public cocos2d::CCSprite {
public:
    // some of these variable names match those of geode, some don't
    // i'll see what they do and rename them to their appropriate names
    bool init(char const*, float, int, cocos2d::CCPoint, char const*, float);
    static TextArea* create(char const*, float, int, cocos2d::CCPoint, char const*, float);
};

#endif /* defined(__GeometryDash__TextArea__) */
