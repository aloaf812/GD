#ifndef __GeometryDash__TextArea__
#define __GeometryDash__TextArea__

#include "cocos2d.h"

#include <stdio.h>

class TextArea : public cocos2d::CCSprite {
public:
    // some of these variable names match those of geode, some don't
    // i'll see what they do and rename them to their appropriate names
    bool init(std::string str, const char* font, float separation, float width, cocos2d::CCPoint anchor, float lineSeparation, bool plainText);
    static TextArea* create(std::string str, const char* font, float separation, float width, cocos2d::CCPoint anchor, float lineSeparation, bool plainText);
};

#endif /* defined(__GeometryDash__TextArea__) */
