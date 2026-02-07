#include "UILayer.h"
#include "GameManager.h"
USING_NS_CC;

bool UILayer::init()
{
	if (!CCLayerColor::initWithColor(ccc4(0, 0, 0, 0)))
		return false;

	CCSprite* pauseButton = CCSprite::createWithSpriteFrameName("GJ_pauseBtn_clean_001.png");
	pauseButton->setOpacity(75);
	m_pauseBtn = CCMenuItemSpriteExtra::create(pauseButton, NULL, this, menu_selector(UILayer::onPause));
	//m_pauseBtn->setSizeMult(4.0f);
	CCMenu* mainMenu = CCMenu::create(m_pauseBtn, 0);
	CCDirector* pDirector = CCDirector::sharedDirector();
	mainMenu->setPosition(CCPoint(pDirector->getScreenRight() - 15.0f, pDirector->getScreenTop() - 15.0f));
	this->addChild(mainMenu);

	return true;
}

void UILayer::onPause(CCObject* sender)
{
	PLAY_LAYER->pauseGame();
}


bool UILayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	PLAY_LAYER->getPlayer()->pushButton(PlayerButton::Jump);
	return true;
}
