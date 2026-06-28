#ifndef __GeometryDash__TextArea__
#define __GeometryDash__TextArea__

#include "cocos2d.h"
#include "MultilineBitmapFont.h"
#include <string>

class TextArea : public cocos2d::CCSprite {
public:
	TextArea();
	virtual void onExit();

	static TextArea* create(char const* text, float width, int order, cocos2d::CCPoint align, char const* fontFile, float height);
	static TextArea* create(char const* text, float width, int order, cocos2d::CCPoint align, char const* fontFile);

	bool init(char const* text, float width, int order, cocos2d::CCPoint align, char const* fontFile, float height);

	void setString(char const* text);
	void hideAll();
	void showAll();
	void stopAllCharacterActions();
	void colorAllCharactersTo(cocos2d::ccColor3B color);

	MultilineBitmapFont* m_label; // 0x1b8
	float m_width; // 0x1bc
	std::string m_fontFileName; // 0x1c4
	CC_SYNTHESIZE(int, m_order, Order); // 0x1c8
	CC_SYNTHESIZE(float, m_lineSpace, LineSpace); // 0x1cc
	CC_SYNTHESIZE(bool, m_onTimer, onTimer); // 0x1d0
	CC_SYNTHESIZE(bool, m_fadeInFinished, FadeInFinished); // 0x1dc
	CC_SYNTHESIZE(cocos2d::CCPoint, m_align, Align); // 0x1d4
	CC_SYNTHESIZE_READONLY(float, m_textHeight, TextHeight); // 0x1e0
	CC_SYNTHESIZE_READONLY(float, m_textWidth, TextWidth); // 0x1e8
	CC_SYNTHESIZE_READONLY(float, m_sizeWidth, SizeWidth); // 0x1e8
	CC_SYNTHESIZE_READONLY(cocos2d::CCPoint, m_textPosition, TextPosition); // 0x1ec
};

#endif /* defined(__GeometryDash__TextArea__) */
