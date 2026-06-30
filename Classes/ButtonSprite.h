// decompiled by ItzZyann
#ifndef __BUTTONSPRITE_H__
#define __BUTTONSPRITE_H__

#include "cocos2d.h"
#include "cocos-ext.h"

class ButtonSprite : public cocos2d::CCSprite {
public:
	ButtonSprite();

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
	void setColor(cocos2d::ccColor3B color);

	int m_buttonType; // 0x1b8
	float m_width; // 0x1bc
	float m_height;
	CC_SYNTHESIZE(float, m_customScale, CustomScale);
	CC_SYNTHESIZE(float, m_absoluteHeight, AbsoluteHeight);
	CC_SYNTHESIZE(bool, m_absoluteWidth, AbsoluteWidth);
	cocos2d::CCLabelBMFont* m_label; // 0x1d0
	cocos2d::CCSprite* m_subSprite; // 0x1d4
	cocos2d::extension::CCScale9Sprite* m_bgSprite; // 0x1d8
	CC_SYNTHESIZE(cocos2d::CCPoint, m_textPositionOffset, TextPositionOffset);
	const char* m_textStr; // 0x1e4
};

#endif