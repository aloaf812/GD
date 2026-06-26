// decompiled by ItzZyann
// from GD 1.71 binary

#ifndef __BUTTONSPRITE_H__
#define __BUTTONSPRITE_H__

#include "cocos2d.h"
#include "cocos-ext.h"

class ButtonSprite : public cocos2d::CCSprite {
public:
	ButtonSprite();
	virtual ~ButtonSprite();

	static ButtonSprite* create(cocos2d::CCSprite* sprite, int width, int height, float scale, float customScale, bool absoluteWidth, const char* bgImage, const char* font);
	static ButtonSprite* create(cocos2d::CCSprite* sprite, int width, int height, const char* text, float scale, float customScale, bool absoluteWidth);
	static ButtonSprite* create(cocos2d::CCSprite* sprite, bool absoluteWidth);
	static ButtonSprite* create(const char* caption, int width, int height, float scale, bool absoluteWidth, const char* font, const char* bgImage, float absoluteHeight);
	static ButtonSprite* create(const char* caption, int width, int height, float scale, bool absoluteWidth, const char* font, const char* bgImage);
	static ButtonSprite* create(const char* caption, int width, int height, float scale, bool absoluteWidth);
	static ButtonSprite* create(const char* caption, float scale);
	static ButtonSprite* create(const char* caption);

	bool init(cocos2d::CCSprite* sprite, int width, int height, float scale, float customScale, bool absoluteWidth, const char* bgImage);
	bool init(const char* caption, int width, int height, float scale, bool absoluteWidth, const char* font, const char* bgImage, float absoluteHeight);

	void updateSpriteBGSize();
	void setString(const char* text);
	void updateBGImage(const char* bgImage);
	virtual void setColor(const cocos2d::ccColor3B& color) override;

	CC_SYNTHESIZE(int, m_buttonType, ButtonType);
	CC_SYNTHESIZE(float, m_width, Width);
	CC_SYNTHESIZE(float, m_height, Height);
	CC_SYNTHESIZE(float, m_customScale, CustomScale);
	CC_SYNTHESIZE(float, m_absoluteHeight, AbsoluteHeight);
	CC_SYNTHESIZE(bool, m_absoluteWidth, AbsoluteWidth);
	CC_SYNTHESIZE(cocos2d::CCLabelBMFont*, m_label, Label);
	CC_SYNTHESIZE(cocos2d::CCSprite*, m_subSprite, SubSprite);
	CC_SYNTHESIZE(cocos2d::extension::CCScale9Sprite*, m_bgSprite, BgSprite);
	CC_SYNTHESIZE(cocos2d::CCPoint, m_textPositionOffset, TextPositionOffset);
	CC_SYNTHESIZE(const char*, m_textStr, TextStr);
};

#endif