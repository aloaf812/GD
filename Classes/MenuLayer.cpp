// Partially decompiled by ProjectReversio: https://github.com/ProjectReversio/GeometryDash/blob/master/GeometryDash/Classes/MenuLayer.cpp
#include "MenuLayer.h"

#include "AppDelegate.h"
#include "RT_COCOS/CCMenuItemSpriteExtra.h"
#include "MenuGameLayer.h"

// main button layers
#include "LevelSelectLayer.h"
#include "GJGarageLayer.h"
#include "CreatorLayer.h"

#include "PlatformToolbox.h"
#include "GameManager.h"
#include "GameToolbox.h"
#include "GameLevelManager.h"
#include "OptionsLayer.h"
#include "GJMoreGamesLayer.h"
#include "MoreGamesManager.h"
USING_NS_CC;

CCScene* MenuLayer::scene(){
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    // create() should be renamed to node()
    AppDelegate* pApp = AppDelegate::get();
    pApp->setScenePointer(scene);
    
    // 'layer' is an autorelease object
    MenuLayer* layer = MenuLayer::node();
    
    // add layer as a child to scene
    scene->addChild(layer);
    // return the scene
    return scene;
}


void MenuLayer::onMoreGames(CCObject* sender)
{
    PlatformToolbox::logEvent("MoreGames");
	GameManager::sharedState()->reportAchievementWithID("geometry.ach.moreGames", 100, false);
	GJMoreGamesLayer* moreGamesLayer = GJMoreGamesLayer::create();
	this->addChild(moreGamesLayer, 100);
	moreGamesLayer->showLayer(false);
}

void MenuLayer::onPlay(CCObject* sender)
{
    this->willClose();
	GameManager::sharedState()->setLastScene(LastGameScene::unk8);
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCScene *pScene = LevelSelectLayer::scene(0);
    CCTransitionFade* fade = CCTransitionFade::create(0.5f, pScene);
    pDirector->replaceScene(fade);
}

void MenuLayer::onGarage(CCObject* sender)
{
    this->willClose();
	GameManager::sharedState()->setClickedGarage(true);
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCScene *pScene = GJGarageLayer::scene();
    CCTransitionFade* fade = CCTransitionFade::create(0.5f, pScene);
    pDirector->replaceScene(fade);
}

void MenuLayer::onCreator(CCObject* sender)
{
    this->willClose();
	GameManager::sharedState()->setClickedEditor(true);
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCScene *pScene = CreatorLayer::scene();
    CCTransitionFade* fade = CCTransitionFade::create(0.5f, pScene);
	pDirector->replaceScene(fade);
}

void MenuLayer::onAchievements(CCObject* sender)
{
    
}

void MenuLayer::onOptions(CCObject* sender)
{
	OptionsLayer* layer = OptionsLayer::create();
	this->addChild(layer, 100);
	layer->showLayer(false);
}

void MenuLayer::onStats(CCObject* sender)
{
    
}

void MenuLayer::onRobTop(CCObject* sender)
{
	CCApplication::sharedApplication()->openURL("http://www.robtopgames.com");
}

void MenuLayer::onFacebook(CCObject* sender)
{
	GameManager::sharedState()->likeFacebook();
    
}

void MenuLayer::onTwitter(CCObject* sender)
{
	GameManager::sharedState()->followTwitter();
}

void MenuLayer::onTrailer(CCObject* sender)
{
    PlatformToolbox::logEvent("gjl_trailer");
    if (!GameToolbox::doWeHaveInternet()) {
		CCApplication::sharedApplication()->openURL("https://www.youtube.com/watch?v=k90y6PIzIaE");
    }
}

void MenuLayer::onGameCenter(CCObject* sender)
{
	if (!GameManager::sharedState()->getGameCenterEnabled())
        showGCQuestion();

	GameManager::sharedState()->syncPlatformAchievements();
    PlatformToolbox::showAchievements();
}

void MenuLayer::onFullVersion(CCObject* sender)
{
	PlatformToolbox::logEvent("gjl_full");
	// PromoInterstitial::create()->show();
}

void MenuLayer::showGCQuestion()
{

}

void MenuLayer::onGooglePlayGames(CCObject* sender)
{
    if (!PlatformToolbox::isSignedInGooglePlay())
    {
		GameManager::sharedState()->syncPlatformAchievements();
        PlatformToolbox::showAchievements();
    }
    PlatformToolbox::signInGooglePlay();
}

void MenuLayer::willClose()
{
	GameManager::sharedState()->setMainMenuActive(false);
}

bool MenuLayer::init() {
    if (!CCLayer::init())
        return false;
    
	GameManager::sharedState()->fadeInMusic("menuLoop.mp3");
	GameManager::sharedState()->setMainMenuActive(true);
	GameManager::sharedState()->setLastScene(LastGameScene::unk0);
	this->setKeypadEnabled(true);
    
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

    MenuGameLayer* MGL = MenuGameLayer::create();
    this->addChild(MGL);
    
    // creates the logo
    CCSprite* logo = CCSprite::createWithSpriteFrameName("GJ_logo_001.png");
    this->addChild(logo, 2);
	logo->setPosition(CCPoint(winSize.width * 0.5f, CCDirector::sharedDirector()->getScreenTop() - 50.0f));
    
    CCMenu* mainMenu = CCMenu::create();
    
    // creates the play buttton
    CCSprite* playButton = CCSprite::createWithSpriteFrameName("GJ_playBtn_001.png");
    CCMenuItemSpriteExtra* playExtra = CCMenuItemSpriteExtra::create(playButton, NULL, this, menu_selector(MenuLayer::onPlay));
    mainMenu->addChild(playExtra);
    this->addChild(mainMenu);
    mainMenu->setPosition(CCPoint(winSize.width * 0.5f, (winSize.height * 0.5f) + 10.0f));
    
    // creates the garage button
    CCSprite* garageButton = CCSprite::createWithSpriteFrameName("GJ_garageBtn_001.png");
    CCMenuItemSpriteExtra* garageExtra = CCMenuItemSpriteExtra::create(garageButton, NULL, this, menu_selector(MenuLayer::onGarage));
    mainMenu->addChild(garageExtra);
    garageExtra->setPosition(playExtra->getPosition() + CCPoint(-110.0f, 0.0f));
    
	if (!GameManager::sharedState()->getClickedGarage())
    {
        CCSprite* chrSel = CCSprite::createWithSpriteFrameName("GJ_chrSel_001.png");
        this->addChild(chrSel);
        chrSel->setPosition(mainMenu->convertToWorldSpace(garageExtra->getPosition()) + CCPoint(-50.0f, -50.0f));
    }
    
    // creates the creator button
    CCSprite* creatorButton = CCSprite::createWithSpriteFrameName("GJ_creatorBtn_001.png");
    CCMenuItemSpriteExtra* creatorExtra = CCMenuItemSpriteExtra::create(creatorButton, NULL, this, menu_selector(MenuLayer::onCreator));
    mainMenu->addChild(creatorExtra);
    creatorExtra->setPosition(playExtra->getPosition() + CCPoint(110.0f, 0.0f));

	if (!GameManager::sharedState()->getClickedEditor())
    {
        CCSprite* lvlEdit = CCSprite::createWithSpriteFrameName("GJ_lvlEdit_001.png");
        this->addChild(lvlEdit);
        lvlEdit->setPosition(mainMenu->convertToWorldSpace(creatorExtra->getPosition()) + CCPoint(50.0f, -50.0f));
    }

	float buttonMenuY = CCDirector::sharedDirector()->getScreenBottom() + 45.0f;

    CCMenu* bottomMenu = CCMenu::create();
    this->addChild(bottomMenu);

    // todo: add functionality to all of these buttons
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		// GooglePlayManager::sharedState()->setDelegate(m_gpDelegate);
        
		m_platformSpr = CCSprite::createWithSpriteFrameName("GJ_gpBtn_001.png");
		CCMenuItemSpriteExtra* gplusExtra = CCMenuItemSpriteExtra::create(m_platformSpr, NULL, this, menu_selector(MenuLayer::onGooglePlayGames));
        bottomMenu->addChild(gplusExtra);
		this->googlePlaySignedIn();
	#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) // finally doesn't show game center on windows
		m_platformSpr = CCSprite::createWithSpriteFrameName("GJ_gkBtn_001.png");
		CCMenuItemSpriteExtra* gcExtra = CCMenuItemSpriteExtra::create(m_platformSpr, NULL, this, menu_selector(MenuLayer::onGameCenter));
        bottomMenu->addChild(gcExtra);
    #endif
    
    CCSprite* achievementsButton = CCSprite::createWithSpriteFrameName("GJ_achBtn_001.png");
    CCMenuItemSpriteExtra* achievementsExtra = CCMenuItemSpriteExtra::create(achievementsButton, NULL, this, menu_selector(MenuLayer::onAchievements));
    bottomMenu->addChild(achievementsExtra);
    
    CCSprite* optionsButton = CCSprite::createWithSpriteFrameName("GJ_optionsBtn_001.png");
    CCMenuItemSpriteExtra* optionsExtra = CCMenuItemSpriteExtra::create(optionsButton, NULL, this, menu_selector(MenuLayer::onOptions));
    bottomMenu->addChild(optionsExtra);
    
    CCSprite* statsButton = CCSprite::createWithSpriteFrameName("GJ_statsBtn_001.png");
    CCMenuItemSpriteExtra* statsExtra = CCMenuItemSpriteExtra::create(statsButton, NULL, this, menu_selector(MenuLayer::onStats));
    bottomMenu->addChild(statsExtra);
    
	bottomMenu->setPosition(ccp(winSize.width * 0.5f, buttonMenuY));
    bottomMenu->alignItemsHorizontallyWithPadding(5.0f);
    
	float robtopLogoPos = CCDirector::sharedDirector()->getScreenBottom() + 30.0f;

    CCSprite* robtopLogo = CCSprite::createWithSpriteFrameName("robtoplogo_small.png");
    robtopLogo->setScale(0.8f);
    CCMenuItemSpriteExtra* robtopExtra = CCMenuItemSpriteExtra::create(robtopLogo, NULL, this, menu_selector(MenuLayer::onRobTop));
    robtopExtra->setSizeMult(1.5f);
    
    CCMenu* socialsMenu = CCMenu::create(robtopExtra, NULL);
    this->addChild(socialsMenu, 2);
	socialsMenu->setPosition(CCPoint(CCDirector::sharedDirector()->getScreenLeft() + 50.0f, robtopLogoPos - 6.0f));
    
    CCSprite* facebookIcon = CCSprite::createWithSpriteFrameName("gj_fbIcon_001.png");
    CCMenuItemSpriteExtra* facebookExtra = CCMenuItemSpriteExtra::create(facebookIcon, NULL, this, menu_selector(MenuLayer::onFacebook));
    facebookExtra->setSizeMult(1.5f);
    socialsMenu->addChild(facebookExtra);
    
    CCSprite* twitterIcon = CCSprite::createWithSpriteFrameName("gj_twIcon_001.png");
    CCMenuItemSpriteExtra* twitterExtra = CCMenuItemSpriteExtra::create(twitterIcon, NULL, this, menu_selector(MenuLayer::onTwitter));
    twitterExtra->setSizeMult(1.5f);
    socialsMenu->addChild(twitterExtra);
    
	facebookExtra->setPosition(socialsMenu->convertToNodeSpace(ccp(CCDirector::sharedDirector()->getScreenLeft() + 30.0f, robtopLogoPos + 30.0f)));
    twitterExtra->setPosition(facebookExtra->getPosition() + ccp(40.0, 0.0f));
    
    CCSprite* moreGamesButton = CCSprite::createWithSpriteFrameName("GJ_moreGamesBtn_001.png");
	CCMenuItemSpriteExtra* moreGamesExtra = CCMenuItemSpriteExtra::create(moreGamesButton, NULL, this, menu_selector(MenuLayer::onMoreGames));

    CCMenu* extraMenu = CCMenu::create(moreGamesExtra, NULL);
    this->addChild(extraMenu, 2);
    
	extraMenu->setPosition(ccp(CCDirector::sharedDirector()->getScreenRight() - 43.0f, buttonMenuY));

	if (MoreGamesManager::sharedState()->getHasNewGames()) {
		CCSprite* exMark = CCSprite::createWithSpriteFrameName("exMark_001.png");
		moreGamesButton->addChild(exMark);
		exMark->setPosition(ccp(moreGamesButton->getTextureRect().size.width * 0.5f, moreGamesButton->getTextureRect().size.height + exMark->getTextureRect().size.height * 0.5f + 4));
	}

	GameManager::sharedState()->setFirstSetup(false);
    return true;
}

void MenuLayer::endGame()
{
	CCDirector::sharedDirector()->end();
}

void MenuLayer::syncPlatformAchievements(float dt) {
	CCNode::unschedule(schedule_selector(MenuLayer::syncPlatformAchievements));
	GameManager::sharedState()->syncPlatformAchievements();
}

void MenuLayer::googlePlaySignedIn()
{
	// todo
}