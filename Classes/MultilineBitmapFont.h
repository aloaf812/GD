#ifndef __MULTILINEBITMAPFONT_H__
#define __MULTILINEBITMAPFONT_H__

// decompiled by ItzZyann
// not that accurate since im a beginner in
// reing

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

// Subclass wrapper to safely inject the missing methods without modifying ColoredSection.h
class CustomColoredSection : public ColoredSection {
public:
	int getStartIndex() { return m_start; }
	void setStartIndex(int index) { m_start = index; }
	int getEndIndex() { return m_end; }
	cocos2d::ccColor3B getColor() { return m_color; }

	int m_start;
	int m_end;
	cocos2d::ccColor3B m_color;
};

class MultilineBitmapFont : public cocos2d::CCSprite {
public:
	MultilineBitmapFont();
	virtual ~MultilineBitmapFont();

	static MultilineBitmapFont* createWithFont(const char* fontFile, const char* text, float scale, float width, cocos2d::CCPoint* align, float lineSpace);
	bool initWithFont(const char* fontFile, const char* text, float scale, float width, cocos2d::CCPoint* align, float lineSpace);

	void readColorInfo(std::string* outStr, MultilineBitmapFont* font, std::string text);
	void stringWithMaxWidth(std::string* outStr, MultilineBitmapFont* font, std::string text, float maxWidth, float scale);

	cocos2d::CCArray* m_lines;         // 0x668
	cocos2d::CCArray* m_characters;    // 0x66C
	cocos2d::CCArray* m_unkArray;      // 0x670

	float m_fontWidths[300];           // 0x1B8

	int m_order;                       // 0x674 (Mapped from a2 + 1652 / 0x674)
	bool m_fadeInFinished;             // 0x678 (Mapped from a2 + 1656 / 0x678)

	float m_textHeight;                // 0x680
	float m_textWidth;                 // 0x684
	cocos2d::CCPoint m_textPos;        // 0x688
	float m_sizeHeight;                // 0x690
};

#endif // __MULTILINEBITMAPFONT_H__