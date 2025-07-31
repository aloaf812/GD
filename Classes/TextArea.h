//
//  TextArea.h
//  GeometryDash
//
//  Created by bryan on 7/29/25.
//
//

#ifndef __GeometryDash__TextArea__
#define __GeometryDash__TextArea__

#include "cocos2d.h"

class TextArea : public cocos2d::CCSprite {
    static TextArea* create(char const* font, float scale, float width, cocos2d::CCPoint anchor, float lineHeight, bool disableColor);
};

#endif /* defined(__GeometryDash__TextArea__) */
