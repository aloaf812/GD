#ifndef _CC_MENU_ITEM_TOGGLER_H
#define _CC_MENU_ITEM_TOGGLER_H

#include "cocos2d.h"
#include "CCMenuItemSpriteExtra.h"

class CCMenuItemToggler : public cocos2d::CCMenuItem {
public:
	static CCMenuItemToggler* create(cocos2d::CCNode* normalSprite, cocos2d::CCNode* selectedSprite, cocos2d::CCObject* target, cocos2d::SEL_MenuHandler selector);
	bool init(cocos2d::CCNode* normalSprite, cocos2d::CCNode* selectedSprite, cocos2d::CCObject* target, cocos2d::SEL_MenuHandler selector);

	CCMenuItemSpriteExtra* activeItem();

	void activate();
	void selected();
	void unselected();

	void toggle(bool active);

	void normalTouch(cocos2d::CCObject* sender);
	void selectedTouch(cocos2d::CCObject* sender);

	void setEnabled(bool enabled);
	void setSizeMult(float sizeMult);

	CC_SYNTHESIZE_READONLY(CCMenuItemSpriteExtra*, m_normalButton, NormalButton); // 0x108
	CC_SYNTHESIZE_READONLY(CCMenuItemSpriteExtra*, m_selectedButton, SelectedButton); // 0x10c
	CC_SYNTHESIZE_READONLY(bool, m_isActive, IsActive); // 0x110
	CC_SYNTHESIZE(bool, m_dontToggle, DontToggle); // 0x111
};
#endif