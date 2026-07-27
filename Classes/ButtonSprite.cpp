// decompiled by ItzZyann
#include "ButtonSprite.h"
#include "RT_COCOS/CCMenuItemSpriteExtra.h"

USING_NS_CC;
USING_NS_CC_EXT;

ButtonSprite::ButtonSprite() {
	m_buttonType = 0;
	m_width = 0.0f;
	m_height = 0.0f;
	m_customScale = 0.0f;
	m_absoluteHeight = 0.0f;
	m_absoluteWidth = false;
	m_label = nullptr;
	m_subSprite = nullptr;
	m_bgSprite = nullptr;
	m_textPositionOffset = cocos2d::CCPoint(0.0f, 0.0f);
	m_textStr = "";
}

void ButtonSprite::updateSpriteBGSize() {
	float finalWidth = 0.0f;
	if (m_absoluteWidth) {
		finalWidth = m_width;
	}
	else {
		float spriteW = m_subSprite->getContentSize().width;
		if (m_height < (spriteW * m_subSprite->getScale())) {
			finalWidth = m_subSprite->getContentSize().width * m_subSprite->getScale();
		}
		else {
			finalWidth = m_height;
		}
	}

	float rectH = 40.0f;
	float finalWidthOffset = finalWidth + 8.0f;
	float spriteH = m_subSprite->getContentSize().height;
	float finalHeight = 0.0f;

	if (rectH >= ((spriteH * m_subSprite->getScale()) + 8.0f)) {
		finalHeight = 40.0f;
	}
	else {
		finalHeight = (m_subSprite->getContentSize().height * m_subSprite->getScale()) + 8.0f;
	}

	m_bgSprite->setContentSize(CCSize(finalWidthOffset, finalHeight));
	this->setContentSize(CCSize(m_bgSprite->getContentSize().width, m_bgSprite->getContentSize().height));

	float halfWidth = this->getContentSize().width * 0.5f;
	float halfHeight = this->getContentSize().height * 0.5f;

	m_subSprite->setPosition(ccp(halfWidth + 0.0f, halfHeight + 2.0f));
	m_bgSprite->setPosition(ccp(halfWidth, halfHeight));

	if (this->getParent()) {
		CCMenuItemSpriteExtra* parentNode = dynamic_cast<CCMenuItemSpriteExtra*>(this->getParent());
		if (parentNode) {
			parentNode->setContentSize(this->getContentSize());
			this->setPosition(ccp(this->getContentSize().width * 0.5f, this->getContentSize().height * 0.5f));
		}
	}
}

bool ButtonSprite::init(cocos2d::CCSprite* sprite, int width, int height, float scale, float customScale, bool absoluteWidth, const char* bgImage) {
	if (!cocos2d::CCSprite::init()) {
		return false;
	}

	m_subSprite = sprite;
	m_customScale = customScale;
	m_buttonType = 0;
	m_width = (float)width;
	m_absoluteWidth = absoluteWidth;
	m_height = (float)height;

	this->addChild(sprite, 1);

	m_bgSprite = CCScale9Sprite::create(bgImage, CCRect(0.0f, 0.0f, 40.0f, 40.0f));
	m_bgSprite->setContentSize(CCSize(16.0f, 16.0f));
	this->addChild(m_bgSprite, 0);

	if (m_width > 0.0f) {
		if (m_subSprite->getContentSize().width > m_width) {
			m_subSprite->setScale(m_width / m_subSprite->getContentSize().width);
		}
	}

	if (scale > 0.0f && m_subSprite->getContentSize().height > scale) {
		float heightScale = scale / m_subSprite->getContentSize().height;
		if (heightScale < m_subSprite->getScale()) {
			m_subSprite->setScale(scale / m_subSprite->getContentSize().height);
		}
	}

	float finalScale = m_subSprite->getScale();
	if (finalScale <= m_customScale) {
		finalScale = m_customScale;
	}
	m_subSprite->setScale(finalScale);

	this->updateSpriteBGSize();
	return true;
}

ButtonSprite* ButtonSprite::create(cocos2d::CCSprite* sprite, int width, int height, float scale, float customScale, bool absoluteWidth, const char* bgImage, const char* font) {
	ButtonSprite* pRet = new ButtonSprite();
	if (pRet && pRet->init(sprite, width, height, scale, customScale, absoluteWidth, bgImage)) {
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return nullptr;
}

ButtonSprite* ButtonSprite::create(cocos2d::CCSprite* sprite, int width, int height, const char* text, float scale, float customScale, bool absoluteWidth) {
	return ButtonSprite::create(sprite, width, height, scale, customScale, absoluteWidth, "GJ_button_01.png", text);
}

ButtonSprite* ButtonSprite::create(cocos2d::CCSprite* sprite, bool absoluteWidth) {
	return ButtonSprite::create(sprite, 0, 0, 0.0f, 1.0f, absoluteWidth, "GJ_button_01.png", nullptr);
}

void ButtonSprite::setString(const char* text) {
	if (m_buttonType == 1) {
		m_label->setScale(1.0f);
		m_label->setString(text);
		m_textStr = text;

		if (m_width > 0.0f) {
			if (m_label->getContentSize().width > m_width) {
				m_label->setScale(m_width / m_label->getContentSize().width);
			}
		}

		float scaleCheck = m_label->getScale();
		if (scaleCheck <= m_customScale) {
			scaleCheck = m_customScale;
		}
		m_label->setScale(scaleCheck);

		float finalWidth = 0.0f;
		if (m_absoluteWidth) {
			finalWidth = m_width;
		}
		else {
			float labelW = m_label->getContentSize().width;
			if (m_height < (labelW * m_label->getScale())) {
				finalWidth = m_label->getContentSize().width * m_label->getScale();
			}
			else {
				finalWidth = m_height;
			}
		}

		float targetHeight = m_absoluteHeight;
		bool isZeroHeight = (targetHeight == 0.0f);
		if (isZeroHeight) {
			targetHeight = 4.0f;
		}
		if (isZeroHeight) {
			targetHeight = m_label->getContentSize().height + targetHeight;
		}

		m_bgSprite->setContentSize(CCSize(finalWidth + 16.0f, targetHeight));
		this->setContentSize(CCSize(m_bgSprite->getContentSize().width, m_bgSprite->getContentSize().height));

		float xPos = m_textPositionOffset.x + (this->getContentSize().width * 0.5f);
		float yPos = m_textPositionOffset.y + (this->getContentSize().height * 0.5f);
		m_label->setPosition(ccp(xPos, yPos));

		m_bgSprite->setPosition(ccp(this->getContentSize().width * 0.5f, this->getContentSize().height * 0.5f));

		if (this->getParent()) {
			CCMenuItemSpriteExtra* parentNode = dynamic_cast<CCMenuItemSpriteExtra*>(this->getParent());
			if (parentNode) {
				parentNode->setContentSize(this->getContentSize());
				this->setPosition(ccp(this->getContentSize().width * 0.5f, this->getContentSize().height * 0.5f));
			}
		}
	}
}

void ButtonSprite::updateBGImage(const char* bgImage) {
	m_bgSprite->removeMeAndCleanup();
	m_bgSprite = CCScale9Sprite::create(bgImage, CCRect(0.0f, 0.0f, 40.0f, 40.0f));
	m_bgSprite->setContentSize(CCSize(16.0f, 16.0f));
	this->addChild(m_bgSprite, 0);

	if (m_buttonType == 1)
		this->setString(m_textStr);
	else
		this->updateSpriteBGSize();
}

bool ButtonSprite::init(const char* caption, int width, int height, float scale, bool absoluteWidth, const char* font, const char* bgImage, float absoluteHeight)
{
	if (!CCSprite::init())
		return false;

	m_buttonType = 1;
	m_customScale = scale;
	m_width = (float)width;
	m_absoluteWidth = absoluteWidth;
	m_absoluteHeight = absoluteHeight;
	m_height = (float)height;

	m_textPositionOffset = ccp(0.0f, 2.0f);

	if (!strcmp(font, "bigFont.fnt")) {
		m_textPositionOffset = ccp(-1.0f, 2.0f);
	}

	m_label = CCLabelBMFont::create("", font);
	this->addChild(m_label, 1);

	m_bgSprite = CCScale9Sprite::create(bgImage, CCRect(0.0f, 0.0f, 40.0f, 40.0f));
	m_bgSprite->setContentSize(CCSize(16.0f, 16.0f));
	this->addChild(m_bgSprite, 0);

	this->setString(caption);
	return true;
}

ButtonSprite* ButtonSprite::create(const char* caption, int width, int height, float scale, bool absoluteWidth, const char* font, const char* bgImage, float absoluteHeight) {
	ButtonSprite* pRet = new ButtonSprite();
	if (pRet && pRet->init(caption, width, height, scale, absoluteWidth, font, bgImage, absoluteHeight)) {
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return nullptr;
}

ButtonSprite* ButtonSprite::create(const char* caption, int width, int height, float scale, bool absoluteWidth, const char* font, const char* bgImage) {
	return ButtonSprite::create(caption, width, height, scale, absoluteWidth, font, bgImage, 0.0f);
}

ButtonSprite* ButtonSprite::create(const char* caption, int width, int height, float scale, bool absoluteWidth) {
	return ButtonSprite::create(caption, width, height, scale, absoluteWidth, "goldFont.fnt", "GJ_button_01.png", 0.0f);
}

ButtonSprite* ButtonSprite::create(const char* caption, float scale) {
	return ButtonSprite::create(caption, 0, 0, scale, false);
}

ButtonSprite* ButtonSprite::create(const char* caption) {
	return ButtonSprite::create(caption, 0, 0, 1.0f, false);
}

void ButtonSprite::setColor(ccColor3B color) {
	if (m_label)
		m_label->setColor(color);

	if (m_subSprite)
		m_subSprite->setColor(color);

	m_bgSprite->setColor(color);
}