#ifndef __GeometryDash__MultilineBitmapFont__
#define __GeometryDash__MultilineBitmapFont__

#include "cocos2d.h"

class MultilineBitmapFont : public cocos2d::CCSprite {
public:
	MultilineBitmapFont* createWithFont(char const*, std::string text, float, float, cocos2d::CCPoint position, int);
	bool initWithFont(char const*, std::string, float, float, cocos2d::CCPoint, int);

	cocos2d::CCArray* field_0x668; // 0x668
	cocos2d::CCArray* field_0x66c; // 0x66c
	cocos2d::CCArray* field_0x670; // 0x670

	CC_SYNTHESIZE_READONLY(float, m_textHeight, TextHeight); // 0x680
	CC_SYNTHESIZE_READONLY(float, m_textWidth, TextWidth); // 0x684
	CC_SYNTHESIZE_READONLY(cocos2d::CCPoint, m_textPos, TextPos); // 0x688
	CC_SYNTHESIZE_READONLY(float, m_sizeHeight, SizeHeight); // 0x690
};

#endif