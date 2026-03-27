#ifndef _COLOR_ACTION_H_
#define _COLOR_ACTION_H_

#include "cocos2d.h"

class ColorAction : public cocos2d::CCNode {
public:
	static ColorAction* create(cocos2d::ccColor3B fromColor, cocos2d::ccColor3B toColor, float duration, double timeStamp);
	bool init(cocos2d::ccColor3B fromColor, cocos2d::ccColor3B toColor, float duration, double timeStamp);

	CC_SYNTHESIZE(cocos2d::ccColor3B, m_fromColor, FromColor); // 0xe8
	CC_SYNTHESIZE(cocos2d::ccColor3B, m_toColor, ToColor); // 0xeb
	CC_SYNTHESIZE(float, m_duration, Duration); // 0xf0
	CC_SYNTHESIZE(double, m_timeStamp, TimeStamp); // 0xf8

};

#endif