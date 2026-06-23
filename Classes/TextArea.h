#ifndef __TEXTAREA_H__
#define __TEXTAREA_H__

#include "cocos2d.h"
#include "MultilineBitmapFont.h"
#include <string>

class MultilineBitmapFont;

class TextArea : public cocos2d::CCSprite {
public:
	TextArea();
	virtual ~TextArea();
	virtual void onExit();

	static TextArea* create(char const* text, float width, int order, cocos2d::CCPoint align, char const* fontFile, float height);
	static TextArea* create(char const* text, float width, int order, cocos2d::CCPoint align, char const* fontFile);

	bool init(char const* text, float width, int order, cocos2d::CCPoint align, char const* fontFile, float height);

	void setString(char const* text);
	void hideAll();
	void showAll();
	void stopAllCharacterActions();
	void colorAllCharactersTo(cocos2d::ccColor3B color);

private:
	MultilineBitmapFont* m_label;
	float m_width;
	int m_unk1C0;
	std::string m_fontFileName;
	int m_order;
	float m_lineSpace;
	bool m_onTimer;
	cocos2d::CCPoint m_align;
	bool m_fadeInFinished;
	float m_textHeight;
	float m_textWidth;
	float m_sizeWidth;
	cocos2d::CCPoint m_textPosition;
};

#endif