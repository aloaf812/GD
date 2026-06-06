#include "CCMenuItemToggler.h"
USING_NS_CC;

CCMenuItemToggler* CCMenuItemToggler::create(CCNode* normalSprite, CCNode* selectedSprite, CCObject* target, SEL_MenuHandler selector)
{
	CCMenuItemToggler *pRet = new CCMenuItemToggler();
	if (pRet && pRet->init(normalSprite, selectedSprite, target, selector))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}

bool CCMenuItemToggler::init(CCNode* normalSprite, CCNode* selectedSprite, CCObject* target, SEL_MenuHandler selector)
{
	if (!CCMenuItem::initWithTarget(target, selector)) 
		return false;

	m_normalButton = CCMenuItemSpriteExtra::create(normalSprite, NULL, this, menu_selector(CCMenuItemToggler::normalTouch));
	m_selectedButton = CCMenuItemSpriteExtra::create(selectedSprite, NULL, this, menu_selector(CCMenuItemToggler::selectedTouch));

	this->addChild(m_normalButton);
	this->addChild(m_selectedButton);

	m_normalButton->getNormalImage()->setAnchorPoint(ccp(0.5f, 0.5f));
	m_selectedButton->getNormalImage()->setAnchorPoint(ccp(0.5f, 0.5f));

	m_normalButton->getNormalImage()->setPosition(m_normalButton->convertToNodeSpace(CCPointZero));
	m_selectedButton->getNormalImage()->setPosition(m_selectedButton->convertToNodeSpace(CCPointZero));

	m_dontToggle = false;
	toggle(false);

	return true;
}

CCMenuItemSpriteExtra* CCMenuItemToggler::activeItem()
{
	if (m_isActive)
		return m_selectedButton;
	else
		return m_normalButton;
}


void CCMenuItemToggler::activate()
{
	CCMenuItem::activate();
	activeItem()->activate();
}

void CCMenuItemToggler::selected()
{
	CCMenuItem::selected();
	activeItem()->selected();
}

void CCMenuItemToggler::unselected()
{
	CCMenuItem::unselected();
	activeItem()->unselected();
}

void CCMenuItemToggler::toggle(bool active)
{
	m_isActive = active;
	m_normalButton->setVisible(!active);
	m_selectedButton->setVisible(active);
	
	CCSize contentSize = activeItem()->getContentSize();
	this->setContentSize(contentSize);

	CCPoint pos = ccp(contentSize.width * 0.5f, contentSize.height * 0.5f);
	m_normalButton->setPosition(pos);
	m_selectedButton->setPosition(pos);
}

void CCMenuItemToggler::normalTouch(CCObject* sender)
{
	if (!m_dontToggle)
		toggle(true);
}

void CCMenuItemToggler::selectedTouch(CCObject* sender)
{
	if (!m_dontToggle)
		toggle(false);
}

void CCMenuItemToggler::setEnabled(bool enabled)
{
	CCMenuItem::setEnabled(enabled);
	m_normalButton->setEnabled(enabled);
	m_selectedButton->setEnabled(enabled);
}

void CCMenuItemToggler::setSizeMult(float sizeMult)
{
	m_normalButton->setSizeMult(sizeMult);
	m_selectedButton->setSizeMult(sizeMult);
	toggle(m_isActive);
}