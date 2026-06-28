// decompiled by ItzZyann

#ifndef __MULTILINEBITMAPFONT_H__
#define __MULTILINEBITMAPFONT_H__

#include "cocos2d.h"
#include "ColoredSection.h"
#include <string>

class FontObject {
public:
	float getFontWidth(int charId);
};

class BitmapFontCache {
public:
	static BitmapFontCache* sharedFontCache();
	FontObject* fontWithConfigFile(const char* fontFile, float scale);
};

class MultilineBitmapFont : public cocos2d::CCSprite {
public:
	MultilineBitmapFont();

	static MultilineBitmapFont* createWithFont(const char* fontFile, const char* text, float scale, float width, cocos2d::CCPoint* align, float lineSpace);
	bool initWithFont(const char* fontFile, const char* text, float scale, float width, cocos2d::CCPoint* align, float lineSpace);

	void readColorInfo(std::string* outStr, MultilineBitmapFont* font, std::string text);
	void stringWithMaxWidth(std::string* outStr, MultilineBitmapFont* font, std::string text, float maxWidth, float scale);

	cocos2d::CCArray* m_lines;         // 0x668
	cocos2d::CCArray* m_characters;    // 0x66C
	cocos2d::CCArray* m_unkArray;      // 0x670

	float m_fontWidths[300];           // 0x1B8

	int m_order;                       // 0x674
	bool m_fadeInFinished;             // 0x678

	CC_SYNTHESIZE_READONLY(float, m_textHeight, TextHeight); // 0x680
	CC_SYNTHESIZE_READONLY(float, m_textWidth, TextWidth); // 0x684
	CC_SYNTHESIZE_READONLY(cocos2d::CCPoint, m_textPos, TextPos); // 0x688
	CC_SYNTHESIZE_READONLY(float, m_sizeHeight, SizeHeight); // 0x690
};

#endif