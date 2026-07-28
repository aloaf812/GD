#include "OptionsLayer.h"
#include "TutorialLayer.h"
#include "PlatformToolbox.h"
#include "GameManager.h"
#include "ButtonSprite.h"
#include "RT_COCOS/CCMenuItemToggler.h"
USING_NS_CC;

OptionsLayer* OptionsLayer::create()
{
    OptionsLayer* pRet = new OptionsLayer();
    if (pRet && pRet->init("Options"))
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

void OptionsLayer::createToggleButton(std::string text, SEL_MenuHandler callback, bool toggled, CCMenu* menu, CCPoint position)
{
	CCSprite* onSprite = CCSprite::createWithSpriteFrameName("GJ_checkOn_001.png");
	CCSprite* offSprite = CCSprite::createWithSpriteFrameName("GJ_checkOff_001.png");

	onSprite->setScale(0.8f);
	offSprite->setScale(0.8f);

	CCMenuItemToggler* toggler = CCMenuItemToggler::create(onSprite, offSprite, this, callback);
	toggler->toggle(toggled);

	menu->addChild(toggler);
	toggler->setPosition(menu->convertToNodeSpace(position));
	toggler->setSizeMult(1.5f);

	CCLabelBMFont* label = CCLabelBMFont::create(text.c_str(), "bigFont.fnt");
	this->addChild(label);

	label->setAnchorPoint(ccp(0.0f, 0.5f));

	float checkHalfW = onSprite->getContentSize().width * 0.5f;
	label->setPosition(ccpAdd(position, ccp(checkHalfW * 0.8f + 6.0f, 0.0f)));

	if (label->getContentSize().width > 110.0f)
		label->setScale(110.0f / label->getContentSize().width);

	if (label->getScale() > 0.5f)
		label->setScale(0.5f);
}

void OptionsLayer::customSetup()
{
	unk_0x1bd = false;
	unk_0x1bc = false;
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	ButtonSprite* supportSpr = ButtonSprite::create("Support", 130, 0, 1.0f, true);
	CCMenuItemSpriteExtra* supportExtra = CCMenuItemSpriteExtra::create(supportSpr, NULL, this, menu_selector(OptionsLayer::onSupport));

	ButtonSprite* helpSpr = ButtonSprite::create("How to play", 130, 0, 1.0f, true);
	CCMenuItemSpriteExtra* helpExtra = CCMenuItemSpriteExtra::create(helpSpr, NULL, this, menu_selector(OptionsLayer::onHelp));

	m_optionsMenu = CCMenu::create(supportExtra, helpExtra, nullptr);
	m_optionsMenu->alignItemsHorizontallyWithPadding(10.0f);
	m_optionsMenu->setPosition(ccp(winSize.width * 0.5f, (winSize.height * 0.5f) + 80.0));

	float buttonHeight = supportExtra->getContentSize().height * supportExtra->getScaleY();

	ButtonSprite* rateSpr = ButtonSprite::create("Rate", 130, 0, 1.0f, true);
	CCMenuItemSpriteExtra* rateExtra = CCMenuItemSpriteExtra::create(rateSpr, NULL, this, menu_selector(OptionsLayer::onRate));
	m_optionsMenu->addChild(rateExtra);
	rateExtra->setPosition(supportExtra->getPosition() + ccp(0.0f, -buttonHeight - 10.0f));

	ButtonSprite* stSptr = ButtonSprite::create("Soundtracks", 130, 0, 1.0f, true);
	CCMenuItemSpriteExtra* stExtra = CCMenuItemSpriteExtra::create(stSptr, NULL, this, menu_selector(OptionsLayer::onSoundtracks));
	m_optionsMenu->addChild(stExtra);
	stExtra->setPosition(helpExtra->getPosition() + ccp(0.0f, -buttonHeight - 10.0f));

	m_internalLayer->addChild(m_optionsMenu, 1);

	CCMenu* toggleMenu = CCMenu::create();
	createToggleButton("Music", menu_selector(OptionsLayer::onMusic), !GM->getMusicEnabled(), toggleMenu, ccp((winSize.width * 0.5f) - 140.0f, winSize.height * 0.5f));
	createToggleButton("SFX", menu_selector(OptionsLayer::onFX), !GM->getFxEnabled(), toggleMenu, ccp((winSize.width * 0.5f) + 40.0f, winSize.height * 0.5f));
	createToggleButton("Auto-Checkpoints", menu_selector(OptionsLayer::onAutoCheckpoints), !GM->getAutoCheckpoints(), toggleMenu, ccp((winSize.width * 0.5f) - 140.0f, (winSize.height * 0.5f) - 40.0f));
	createToggleButton("Auto-Retry", menu_selector(OptionsLayer::onAutoRetry), !GM->getAutoRetryLevel(), toggleMenu, ccp((winSize.width * 0.5f) + 40.0f, (winSize.height * 0.5f) - 40.0f));

	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	// GooglePlayManager::sharedState()->setDelegate(m_gPlayDelegate);
	CCSprite* gpSignIn = CCSprite::createWithSpriteFrameName("gplusSignIn_001.png");
	CCSprite* gpSignOut = CCSprite::createWithSpriteFrameName("gplusSignOut_001.png");

	m_gpSignIn = CCMenuItemSpriteExtra::create(gpSignIn, NULL, this, menu_selector(OptionsLayer::onGPSignIn));
	m_gpSignOut = CCMenuItemSpriteExtra::create(gpSignOut, NULL, this, menu_selector(OptionsLayer::onGPSignOut));
	
	toggleMenu->addChild(m_gpSignIn);
	toggleMenu->addChild(m_gpSignOut);

	m_gpSignIn->setPosition(toggleMenu->convertToNodeSpace(ccp(winSize.width * 0.5f, (winSize.height * 0.5f) - 80.0f)));
	m_gpSignOut->setPosition(m_gpSignIn->getPosition());
	#endif

	// TL;DR fix GJDropDownLayer and its buttons before deciding to work on any GJDropDownLayer classes

	this->toggleGP();
	m_internalLayer->addChild(toggleMenu);
}

void OptionsLayer::toggleGP()
{
	// idk
}

void OptionsLayer::onGC(CCObject* sender)
{
	GM->setGameCenterEnabled(!GM->getGameCenterEnabled());
	if (GM->getGameCenterEnabled())
		PlatformToolbox::activateGameCenter();
}

void OptionsLayer::onGPSignIn(CCObject* sender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	if (PlatformToolbox::isSignedInGooglePlay())
		toggleGP();
	else
		PlatformToolbox::signInGooglePlay();
#endif
}

void OptionsLayer::onGPSignOut(CCObject* sender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	if (!PlatformToolbox::isSignedInGooglePlay())
		toggleGP();
	else
		PlatformToolbox::signOutGooglePlay();
	
	GM->setDidSyncAchievements(false);
	m_gpSignIn->setVisible(true);
	m_gpSignOut->setVisible(false);
#endif
}

void OptionsLayer::onSupport(CCObject* sender)
{
	unk_0x1bc = true;
	unk_0x1bd = false;
	// this->exitLayer();
}

void OptionsLayer::onSoundtracks(CCObject* sender)
{
	unk_0x1bd = true;
	unk_0x1bc = false;
	// this->exitLayer();
}

void OptionsLayer::onHelp(CCObject* sender)
{
	TutorialLayer::create()->show();
}

void OptionsLayer::onRate(CCObject* sender)
{
	GM->rateGame();
}

void OptionsLayer::onMusic(CCObject* sender)
{
	GM->toggleMusic();
}

void OptionsLayer::onFX(CCObject* sender)
{
	GM->toggleFX();
}

void OptionsLayer::onAutoCheckpoints(CCObject* sender)
{
	GM->setAutoCheckpoints(!GM->getAutoCheckpoints());
}

void OptionsLayer::onAutoRetry(CCObject* sender)
{
	GM->setAutoRetryLevel(!GM->getAutoRetryLevel());
}