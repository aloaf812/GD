#include "UILayer.h"
#include "GameManager.h"
#include "GameToolbox.h"
USING_NS_CC;

bool UILayer::init()
{
	if (!CCLayerColor::initWithColor(ccc4(0, 0, 0, 0)))
		return false;

	this->setTouchEnabled(true);
	this->setKeypadEnabled(true);

	CCDirector* pDirector = CCDirector::sharedDirector();
	CCSize winSize = pDirector->getWinSize();

	CCSprite* pauseButton = CCSprite::createWithSpriteFrameName("GJ_pauseBtn_clean_001.png");
	pauseButton->setOpacity(75);
	m_pauseBtn = CCMenuItemSpriteExtra::create(pauseButton, NULL, this, menu_selector(UILayer::onPause));
	//m_pauseBtn->setVolume(0);
	m_pauseBtn->setSizeMult(4.0f);
	CCMenu* pauseBtnMenu = CCMenu::create(m_pauseBtn, 0);
	this->addChild(pauseBtnMenu, 16);
	pauseBtnMenu->setPosition(pDirector->getScreenRight() - 15.0, pDirector->getScreenTop() - 15.0);

	m_checkpointMenu = CCMenu::create();
	this->addChild(m_checkpointMenu, 16);
	CCSprite* addCheckSpr = CCSprite::createWithSpriteFrameName("GJ_checkpointBtn_001.png");
	CCMenuItemSpriteExtra* addCheckBtn = CCMenuItemSpriteExtra::create(addCheckSpr, NULL, this, menu_selector(UILayer::onCheck));
	m_checkpointMenu->addChild(addCheckBtn);
	//addCheckBtn->setScaleVar(1.1f);

	CCSprite* deleteCheckSpr = CCSprite::createWithSpriteFrameName("GJ_removeCheckBtn_001.png");
	CCMenuItemSpriteExtra* deleteCheckBtn = CCMenuItemSpriteExtra::create(deleteCheckSpr, NULL, this, menu_selector(UILayer::onDeleteCheck));
	m_checkpointMenu->addChild(deleteCheckBtn);
	//deleteCheckBtn->setScaleVar(1.1f);

	CCArray* checkArray = CCArray::create();
	checkArray->addObject(addCheckBtn);
	checkArray->addObject(deleteCheckBtn);
	CCPoint targetPos = m_checkpointMenu->convertToNodeSpace(ccp(winSize.width * 0.5f, pDirector->getScreenBottom() + 40.0));
	//GameToolbox::alignItemsHorisontally(checkArray, 10.0f, targetPos);
	addCheckBtn->setSizeMult(1.5f);
	deleteCheckBtn->setSizeMult(1.5f);
	this->toggleCheckpointsMenu(false);

	return true;
}

void UILayer::onPause(CCObject* sender)
{
	PLAY_LAYER->pauseGame();
}

void UILayer::onCheck(CCObject* sender)
{
	//PLAY_LAYER->markCheckpoint();
	//PLAY_LAYER->getPlayer()->removePendingCheckpoint();
}

void UILayer::onDeleteCheck(CCObject* sender)
{
	//PLAY_LAYER->removeLastCheckpoint();
}

bool UILayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	PLAY_LAYER->getPlayer()->pushButton(PlayerButton::Jump);
	return true;
}

void UILayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	PLAY_LAYER->getPlayer()->releaseButton(PlayerButton::Jump);
}

void UILayer::registerWithTouchDispatcher()
{
	// uses field_0xe8 but idk how it's defined
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

void UILayer::keyBackClicked()
{
	if (m_pauseBtn->isEnabled()) {
		onPause(nullptr);
	}
}

void UILayer::enableMenu()
{
	m_pauseBtn->setEnabled(true);
}

void UILayer::disableMenu()
{
	m_pauseBtn->setEnabled(false);
}

void UILayer::toggleCheckpointsMenu(bool visible)
{
	m_checkpointMenu->setVisible(visible);
}