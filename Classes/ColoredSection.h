#ifndef _COLORED_SECTION_H_
#define _COLORED_SECTION_H_

#include "cocos2d.h"

class ColoredSection : public cocos2d::CCObject {
public:
	static ColoredSection* create(cocos2d::ccColor3B col, int startPos, int endPos);
	bool init(cocos2d::ccColor3B col, int startPos, int endPos);

	CC_SYNTHESIZE(cocos2d::ccColor3B, m_col, Col); // 0x18
	CC_SYNTHESIZE(float, m_startPos, StartPos); // 0x1c
	CC_SYNTHESIZE(int, m_endPos, EndPos); // 0x20

};

#endif