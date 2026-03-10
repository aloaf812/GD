#ifndef __GeometryDash__TextArea__
#define __GeometryDash__TextArea__

#include "cocos2d.h"

#include <stdio.h>

class TextArea : public cocos2d::CCSprite {
public:
    bool init(char const*, float scale, int order, cocos2d::CCPoint align, char const*, float);
    static TextArea* create(char const*, float scale, int order, cocos2d::CCPoint align, char const*, float);

	// MultilineBitmapFont* m_label; // 0x1b8
	float m_scale; // 0x1bc

	CC_SYNTHESIZE(int, m_order, Order); // 0x1c8
	CC_SYNTHESIZE(float, m_lineSpace, LineSpace); // 0x1cc
};

#endif /* defined(__GeometryDash__TextArea__) */
