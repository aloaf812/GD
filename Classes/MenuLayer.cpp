// Partially decompiled by ProjectReversio: https://github.com/ProjectReversio/GeometryDash/blob/master/GeometryDash/Classes/MenuLayer.cpp
#include "MenuLayer.h"

#include "AppDelegate.h"
#include "CCMenuItemSpriteExtra.h"

// main button layers
#include "LevelSelectLayer.h"
#include "GJGarageLayer.h"
#include "CreatorLayer.h"

#include "PlatformToolbox.h"
#include "GameManager.h"
#include "GameToolbox.h"
USING_NS_CC;

CCScene* MenuLayer::scene(){
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    // create() should be renamed to node()
    AppDelegate* pApp = AppDelegate::get();
    pApp->mMenuScene = scene;
    
    // 'layer' is an autorelease object
    MenuLayer* layer = MenuLayer::node();
    
    // add layer as a child to scene
    scene->addChild(layer);
    // return the scene
    return scene;
}

MenuLayer* MenuLayer::node()
{
    MenuLayer* pRet = new MenuLayer();
    if (pRet && pRet->init())
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


void MenuLayer::onMoreGames(CCObject* sender)
{
    PlatformToolbox::isHD();
    GameManager* pGameManager = GameManager::sharedState();
    PlatformToolbox::logEvent("MoreGames");
    pGameManager->reportAchievementWithID("geometry.ach.moreGames", 100, false);
    return;
}

void MenuLayer::onPlay(CCObject* sender) {
    // for some reason this is called but never used
    // GameManager* pGameManager = GameManager::sharedState();
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCScene *pScene = LevelSelectLayer::scene(0);
    CCTransitionFade* fade = CCTransitionFade::create(0.5f, pScene);
    pDirector->replaceScene(fade);
    return;
}

void MenuLayer::onGarage(CCObject* sender)
{
    // for some reason this is called but never used
    // GameManager* pGameManager = GameManager::sharedState();
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCScene *pScene = GJGarageLayer::scene();
    CCTransitionFade* fade = CCTransitionFade::create(0.5f, pScene);
    pDirector->replaceScene(fade);
    return;

}

void MenuLayer::onCreator(CCObject* sender)
{
    // for some reason this is called but never used
    // GameManager* pGameManager = GameManager::sharedState();
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCScene *pScene = CreatorLayer::scene();
    CCTransitionFade* fade = CCTransitionFade::create(0.5f, pScene);
    pDirector->replaceScene(fade);
    return;
    
}

void MenuLayer::onAchievements(CCObject* sender)
{
    
}

void MenuLayer::onOptions(CCObject* sender)
{
    
}

void MenuLayer::onStats(CCObject* sender)
{
    
}

void MenuLayer::onRobTop(CCObject* sender)
{
    CCApplication* pApplication = CCApplication::sharedApplication();
    pApplication->openURL("http://www.robtopgames.com");
}

void MenuLayer::onFacebook(CCObject* sender)
{
    GameManager* pGameManager = GameManager::sharedState();
    pGameManager->likeFacebook();
    
}

void MenuLayer::onTwitter(CCObject* sender)
{
    GameManager* pGameManager = GameManager::sharedState();
    pGameManager->followTwitter();
}

void MenuLayer::onTrailer(CCObject* sender)
{
    PlatformToolbox::logEvent("gjl_trailer");
    if (!GameToolbox::doWeHaveInternet()) {
        CCApplication* pApplication = CCApplication::sharedApplication();
        pApplication->openURL("https://www.youtube.com/watch?v=k90y6PIzIaE");
    }
}

void MenuLayer::onGooglePlayGames(CCObject* sender)
{
    if (!PlatformToolbox::isSignedInGooglePlay())
    {
        GameManager* pGameManager = GameManager::sharedState();
        pGameManager->syncPlatformAchievements();
        PlatformToolbox::showAchievements();
    }
    PlatformToolbox::signInGooglePlay();
}

void MenuLayer::onGameCenter(CCObject *param_1)
{
    /*
     GameManager* pGameManager = GameManager::sharedState();
     // bro what is this :sob: int iVar2 = (**(code **)(*pGameManager + 0x1e4))();
     if (iVar2 == 0) {
     showGCQuestion();
     }*/
    GameManager* pGameManager = GameManager::sharedState();
    pGameManager->syncPlatformAchievements();
    PlatformToolbox::showAchievements();
}

bool MenuLayer::init() {
    if (!CCLayer::init())
        return false;
    
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCSize winSize = pDirector->getWinSize();
    GameManager* pGameManager = GameManager::sharedState();
    
    pGameManager->fadeInMusic("menuLoop.mp3");
    
    // creates the logo
    CCSprite* logo = CCSprite::createWithSpriteFrameName("GJ_logo_001.png");
    this->addChild(logo, 2);
    logo->setPosition(CCPoint(winSize.width * 0.5f, pDirector->getScreenTop() - 50.0f));
    
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
    
    if (!pGameManager->m_clickedGarage)
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
    
    if (!pGameManager->m_clickedEditor)
    {
        CCSprite* lvlEdit = CCSprite::createWithSpriteFrameName("GJ_lvlEdit_001.png");
        this->addChild(lvlEdit);
        lvlEdit->setPosition(mainMenu->convertToWorldSpace(creatorExtra->getPosition()) + CCPoint(50.0f, -50.0f));
    }
    
    CCMenu* bottomMenu = CCMenu::create();
    this->addChild(bottomMenu);
    
    // todo: add functionality to all of these buttons
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        CCSprite* gplusButton = CCSprite::createWithSpriteFrameName("GJ_gpBtn_001.png");
        gplusButton->setScale(1.0f);
        CCMenuItemSpriteExtra* gplusExtra = CCMenuItemSpriteExtra::create(gplusButton, NULL, this, menu_selector(MenuLayer::onAchievements));
        bottomMenu->addChild(gplusExtra);
    #else
        CCSprite* gcButton = CCSprite::createWithSpriteFrameName("GJ_gkBtn_001.png");
        gcButton->setScale(1.0f);
        CCMenuItemSpriteExtra* gcExtra = CCMenuItemSpriteExtra::create(gcButton, NULL, this, menu_selector(MenuLayer::onGameCenter));
        bottomMenu->addChild(gcExtra);
    #endif
    
    CCSprite* achievementsButton = CCSprite::createWithSpriteFrameName("GJ_achBtn_001.png");
    achievementsButton->setScale(1.0f);
    CCMenuItemSpriteExtra* achievementsExtra = CCMenuItemSpriteExtra::create(achievementsButton, NULL, this, menu_selector(MenuLayer::onAchievements));
    bottomMenu->addChild(achievementsExtra);
    
    CCSprite* optionsButton = CCSprite::createWithSpriteFrameName("GJ_optionsBtn_001.png");
    optionsButton->setScale(1.0f);
    CCMenuItemSpriteExtra* optionsExtra = CCMenuItemSpriteExtra::create(optionsButton, NULL, this, menu_selector(MenuLayer::onOptions));
    bottomMenu->addChild(optionsExtra);
    
    CCSprite* statsButton = CCSprite::createWithSpriteFrameName("GJ_statsBtn_001.png");
    statsButton->setScale(1.0f);
    CCMenuItemSpriteExtra* statsExtra = CCMenuItemSpriteExtra::create(statsButton, NULL, this, menu_selector(MenuLayer::onStats));
    bottomMenu->addChild(statsExtra);
    
    bottomMenu->setPosition(CCPoint(winSize.width * 0.5f, pDirector->getScreenBottom() + 45.0f));
    bottomMenu->alignItemsHorizontallyWithPadding(5.0f);
    
    CCSprite* robtopLogo = CCSprite::createWithSpriteFrameName("robtoplogo_small.png");
    robtopLogo->setScale(0.8f);
    CCMenuItemSpriteExtra* robtopExtra = CCMenuItemSpriteExtra::create(robtopLogo, NULL, this, menu_selector(MenuLayer::onRobTop));
    robtopExtra->setSizeMult(1.5f);
    
    CCMenu* socialsMenu = CCMenu::create(robtopExtra, NULL);
    this->addChild(socialsMenu, 2);
    socialsMenu->setPosition(CCPoint(pDirector->getScreenLeft() + 50.0f, pDirector->getScreenBottom() + 30.0f - 6.0f));
    
    CCSprite* facebookIcon = CCSprite::createWithSpriteFrameName("gj_fbIcon_001.png");
    facebookIcon->setScale(0.8f);
    CCMenuItemSpriteExtra* facebookExtra = CCMenuItemSpriteExtra::create(facebookIcon, NULL, this, menu_selector(MenuLayer::onFacebook));
    facebookExtra->setSizeMult(1.5f);
    socialsMenu->addChild(facebookExtra);
    
    CCSprite* twitterIcon = CCSprite::createWithSpriteFrameName("gj_twIcon_001.png");
    twitterIcon->setScale(0.8f);
    CCMenuItemSpriteExtra* twitterExtra = CCMenuItemSpriteExtra::create(twitterIcon, NULL, this, menu_selector(MenuLayer::onTwitter));
    twitterExtra->setSizeMult(1.5f);
    socialsMenu->addChild(twitterExtra);
    
    facebookExtra->setPosition(socialsMenu->convertToNodeSpace(CCPoint(pDirector->getScreenLeft() + 22.0f, pDirector->getScreenBottom() + 30.0f + 25.0f)));
    twitterExtra->setPosition(facebookExtra->getPosition() + CCPoint(30.0f, 0.0f));
    
    CCSprite* freeLevelsButton = CCSprite::createWithSpriteFrameName("GJ_moreGamesBtn_001.png");
    CCMenuItemSpriteExtra* freeLevelsExtra = CCMenuItemSpriteExtra::create(freeLevelsButton, NULL, this, menu_selector(MenuLayer::onMoreGames));
    
    CCMenu* extraMenu = CCMenu::create(freeLevelsExtra, NULL);
    this->addChild(extraMenu, 2);
    
    extraMenu->setPosition(CCPoint(pDirector->getScreenRight() - 43.0f, pDirector->getScreenBottom() + 45.0f));
    // add more code here

    return true;
}