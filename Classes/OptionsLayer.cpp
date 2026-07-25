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
	// unk_0x1bd = 0;
	// unk_0x1bc = 0;
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	ButtonSprite* supportSpr = ButtonSprite::create("Support", 128, 0, 1.0f, true);
	CCMenuItemSpriteExtra* supportExtra = CCMenuItemSpriteExtra::create(supportSpr, NULL, this, menu_selector(OptionsLayer::onSupport));

	ButtonSprite* helpSpr = ButtonSprite::create("How to play", 128, 0, 1.0f, true);
	CCMenuItemSpriteExtra* helpExtra = CCMenuItemSpriteExtra::create(helpSpr, NULL, this, menu_selector(OptionsLayer::onHelp));

	m_optionsMenu = CCMenu::create(supportExtra, helpExtra, nullptr);
	m_optionsMenu->alignItemsHorizontallyWithPadding(10.0f);
	m_optionsMenu->setPosition(ccp(winSize.width * 0.5f, (winSize.height * 0.5f) + 80.0));

	ButtonSprite* rateSpr = ButtonSprite::create("Rate", 128, 0, 1.0f, true);
	CCMenuItemSpriteExtra* rateExtra = CCMenuItemSpriteExtra::create(rateSpr, NULL, this, menu_selector(OptionsLayer::onRate));
	m_optionsMenu->addChild(rateExtra);

	// soundtracks button and placement and all that other stuff though it won't be worked on rn

	m_internalLayer->addChild(m_optionsMenu, 1);

	CCMenu* toggleMenu = CCMenu::create();
	createToggleButton("Music", menu_selector(OptionsLayer::onMusic), !GM->getMusicEnabled(), toggleMenu, ccp((winSize.width * 0.5f) - 140.0f, winSize.height * 0.5f));
	createToggleButton("SFX", menu_selector(OptionsLayer::onFX), !GM->getFxEnabled(), toggleMenu, ccp((winSize.width * 0.5f) - 140.0f, winSize.height * 0.5f));
	createToggleButton("Auto-Checkpoints", menu_selector(OptionsLayer::onAutoCheckpoints), !GM->getAutoCheckpoints(), toggleMenu, ccp((winSize.width * 0.5f) - 140.0f, winSize.height * 0.5f));
	createToggleButton("Auto-Retry", menu_selector(OptionsLayer::onAutoRetry), !GM->getAutoRetryLevel(), toggleMenu, ccp((winSize.width * 0.5f) - 140.0f, winSize.height * 0.5f));

	// this still needs more work but it's not worth working on if the buttons themselves dont even work
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

	if (PlatformToolbox::isSignedInGooglePlay())
		toggleGP();
	else
		PlatformToolbox::signInGooglePlay();
}

void OptionsLayer::onSupport(CCObject* sender)
{
	/*unk_0x1bc = 1;
	unk_0x1bd = 0;
	this->exitLayer();*/
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