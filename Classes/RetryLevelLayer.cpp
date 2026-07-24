#include "RetryLevelLayer.h"
#include "GameManager.h"
#include "GameSoundManager.h"
USING_NS_CC;

RetryLevelLayer* RetryLevelLayer::create()
{
	RetryLevelLayer* pRet = new RetryLevelLayer();
	if (pRet && pRet->init(" "))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

void RetryLevelLayer::customSetup()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	
	CCLabelBMFont* lvlNameLabel = CCLabelBMFont::create(PLAY_LAYER->getLevel()->getLevelName().c_str(), "bigFont.fnt");
	lvlNameLabel->setPosition(ccp(winSize.width * 0.5f, (winSize.height * 0.5f) + 80.0f));

	CCPoint layerPos = m_endPosition;
	m_internalLayer->addChild(lvlNameLabel);
	
	this->setupLastProgress();
	
	m_internalLayer->removeChildByTag(0, true);
	m_internalLayer->removeChildByTag(1, true);
	m_uiMenu->setVisible(false);

	layerPos = m_endPosition + ccp(0.0f, 5.0f);
	CCPoint jumpLabelPos = ccp(winSize.width * 0.5f, (winSize.height * 0.5f) - 10.0f);
	
	CCLabelBMFont* jumpsLabel = CCLabelBMFont::create(CCString::createWithFormat("Jumps: %i", PLAY_LAYER->getJumps())->getCString(), "goldFont.fnt");
	m_internalLayer->addChild(jumpsLabel, 3);

	jumpsLabel->setPosition(jumpLabelPos);
	jumpsLabel->setScale(0.8f);

	// the timer......

	m_buttonMenu = CCMenu::create();
	m_internalLayer->addChild(m_buttonMenu, 1);
	CCPoint buttonBasePos = m_buttonMenu->convertToNodeSpace(m_internalLayer->convertToWorldSpace(ccp(winSize.width * 0.5f, (winSize.height * 0.5f) - 115.0f - 10.0f)));
	
	CCSprite* replayBtnSpr = CCSprite::createWithSpriteFrameName("GJ_replayBtn_001.png");
	CCMenuItemSpriteExtra* replayBtnExtra = CCMenuItemSpriteExtra::create(replayBtnSpr, nullptr, this, menu_selector(RetryLevelLayer::onReplay));
	m_buttonMenu->addChild(replayBtnExtra);
	replayBtnExtra->setPosition(buttonBasePos + ccp(-100.0f, 0.0f));

	CCSprite* menuBtnSpr = CCSprite::createWithSpriteFrameName("GJ_menuBtn_001.png");
	CCMenuItemSpriteExtra* menuBtnExtra = CCMenuItemSpriteExtra::create(menuBtnSpr, nullptr, this, menu_selector(RetryLevelLayer::onMenu));
	m_buttonMenu->addChild(menuBtnExtra);
	menuBtnExtra->setPosition(buttonBasePos + ccp(100.0f, 0.0f));
	
	m_internalLayer->setPosition(layerPos);
	
	// "Rate Geometry Dash!" or something like that
	// PlatformToolbox::tryShowRateDialog("Geometry Dash");
}

void RetryLevelLayer::setupLastProgress()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	CCSprite* progressBar = CCSprite::create("GJ_progressBar_001.png");
	progressBar->setColor(ccc3(0, 0, 0)); // yet again robtop could've used ccWHITE here but didn't
	progressBar->setOpacity(125);
	progressBar->setScale(1.0f);
	m_internalLayer->addChild(progressBar, 3);
	progressBar->setPosition(ccp(winSize.width * 0.5f, (winSize.height * 0.5f) + 25.0f));

	CCSprite* progressFill = CCSprite::create("GJ_progressBar_001.png");
	progressFill->setScaleX(0.992f);
	progressFill->setScaleY(0.86f);
	progressFill->setColor(ccGREEN);
	progressBar->addChild(progressFill);
	progressFill->setAnchorPoint(ccp(0.0f, 0.5f));

	float fillInset = progressBar->getContentSize().width - (progressBar->getContentSize().width * 0.992f);
	progressFill->setPosition(ccp(fillInset * 0.5f, progressBar->getContentSize().height * 0.5f));

	int lastRunPct = PLAY_LAYER->getLastRunPercent();
	float progressBarW = progressFill->getContentSize().width;
	float progressFillW = progressBarW * (lastRunPct / 100.0f);
	if (progressFillW < progressBarW)
		progressFillW = progressBarW * (lastRunPct / 100.0f);
	progressFill->setTextureRect(CCRect(0, 0, progressFillW, progressFill->getContentSize().height));

	CCLabelBMFont* pctLabel = CCLabelBMFont::create(CCString::createWithFormat("%i%%", PLAY_LAYER->getLastRunPercent())->getCString(), "bigFont.fnt");
	m_internalLayer->addChild(pctLabel, 4);
	pctLabel->setPosition(progressBar->getPosition());
	pctLabel->setScale(0.5f);

	CCLabelBMFont* atetemptLabel = CCLabelBMFont::create(CCString::createWithFormat("Attempt %i", PLAY_LAYER->getAttempts())->getCString(), "bigFont.fnt");
	m_internalLayer->addChild(atetemptLabel, 4);
	atetemptLabel->setPosition(progressBar->getPosition() + ccp(0.0f, 23.0f));
	atetemptLabel->setScale(0.5f);
}

void RetryLevelLayer::enterAnimFinished()
{
	if (GM->getRecordGameplay() && !PLAY_LAYER->getPracticeMode())
		PLAY_LAYER->getTestMode();
}

void RetryLevelLayer::showLayer(bool instantShow)
{
	m_internalLayer->stopAllActions();
	this->layerVisible();

	if (instantShow) {
		m_internalLayer->setPosition(m_endPosition);
		this->setOpacity(100);
		this->enterAnimFinished();
	}

	m_internalLayer->setScale(0.1f);
	CCEaseElasticOut* action = CCEaseElasticOut::create(CCScaleTo::create(0.5f, 1.0f), 0.6f);
	CCCallFunc* callback = CCCallFunc::create(this, callfunc_selector(RetryLevelLayer::enterAnimFinished));
	m_internalLayer->runAction(CCSequence::create(action, callback, nullptr));
	this->setOpacity(0);
	this->runAction(CCFadeTo::create(0.5f, 100));
}

void RetryLevelLayer::keyBackClicked()
{
	onMenu(nullptr);
}

void RetryLevelLayer::onReplay(CCObject* sender)
{
	PLAY_LAYER->resetLevel();
	CCNode::removeMeAndCleanup();
}

void RetryLevelLayer::onMenu(CCObject* sender)
{
	PLAY_LAYER->onQuit();
	this->exitLayer(false);
	GameSoundManager::sharedManager()->playEffect("quitSound_01.ogg", 1.0f, 0.0f, 0.7f);
}

void RetryLevelLayer::onEveryplay(CCObject* sender) {}