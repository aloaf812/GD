#include "AppDelegate.h"
#include "RT_COCOS/CCMenuItemSpriteExtra.h"
#include "MenuLayer.h"
#include "GameLevelManager.h"
#include "LevelEditorLayer.h"
#include "GJSearchObject.h"

#include "CreatorLayer.h"
USING_NS_CC;

CreatorLayer::CreatorLayer()
{
    
}

CCScene* CreatorLayer::scene()
{
    // 'scene' is an autorelease object
    CCScene* scene = CCScene::create();
    
    AppDelegate* pApp = AppDelegate::get();
    pApp->setScenePointer(scene);
    
    // 'layer' is an autorelease object
    CreatorLayer* layer = CreatorLayer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

void CreatorLayer::onBack(CCObject* sender)
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCScene* scene = MenuLayer::scene();
    CCTransitionFade* fade = CCTransitionFade::create(0.5f, scene);
    pDirector->replaceScene(fade);
}

void CreatorLayer::onMyLevels(CCObject* sender)
{
	
	CCDirector* pDirector = CCDirector::sharedDirector();
	CCScene* scene = LevelEditorLayer::scene(GameLevelManager::sharedState()->getMainLevel(7));
	// CCScene* scene = LevelEditorLayer::scene(GJSearchObject::create(SearchType::MyLevels));
	CCTransitionFade* fade = CCTransitionFade::create(0.5f, scene);
	pDirector->replaceScene(fade);

}

void CreatorLayer::onSearch(CCObject* sender)
{
    GameLevelManager* GLM = GameLevelManager::sharedState();
    GLM->downloadLevel(108);
    /*CCDirector* pDirector = CCDirector::sharedDirector();
    CCScene* scene = LevelInfoLayer::scene();
    CCTransitionFade* fade = CCTransitionFade::create(0.5f, scene);
    pDirector->replaceScene(fade);*/
}

void CreatorLayer::onLeaderboards(cocos2d::CCObject *sender)
{
    GameLevelManager* GLM = GameLevelManager::sharedState();
    GLM->getLeaderboardScores("leaderboards_top");
}

bool CreatorLayer::init()
{
    if (!CCLayer::init())
        return false;
    
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCSize winSize = pDirector->getWinSize();
    
    CCSprite* m_backgroundSprite;
    
    m_backgroundSprite = CCSprite::create("GJ_gradientBG.png");
    m_backgroundSprite->setAnchorPoint(CCPoint(0.0f, 0.0f));
    this->addChild(m_backgroundSprite, -2);
    m_backgroundSprite->setScaleX((winSize.width + 10.0f) / m_backgroundSprite->getTextureRect().size.width);
    m_backgroundSprite->setScaleY((winSize.height + 10.0f) / m_backgroundSprite->getTextureRect().size.height);
    m_backgroundSprite->setPosition(CCPoint(-5.0f, -5.0f));
    m_backgroundSprite->setColor({0, 102, 255});
    
    CCSprite* sideArtTL = CCSprite::createWithSpriteFrameName("GJ_sideArt_001.png");
    sideArtTL->setAnchorPoint(CCPoint(0.0f, 0.0f));
    sideArtTL->setPosition(CCPoint(pDirector->getScreenLeft() - 1.0f, pDirector->getScreenTop() - 71.0f));
    sideArtTL->setFlipY(true);
    this->addChild(sideArtTL, 1);
    
    CCSprite* sideArtTR = CCSprite::createWithSpriteFrameName("GJ_sideArt_001.png");
    sideArtTR->setAnchorPoint(CCPoint(1.0f, 0.0f));
    sideArtTR->setPosition(CCPoint(pDirector->getScreenRight() + 1.0f, pDirector->getScreenTop() - 71.0f));
    sideArtTR->setFlipY(true);
    sideArtTR->setFlipX(true);
    this->addChild(sideArtTR, 1);
    
    CCSprite* sideArtBL = CCSprite::createWithSpriteFrameName("GJ_sideArt_001.png");
    sideArtBL->setAnchorPoint(CCPoint(0.0f, 0.0f));
    sideArtBL->setPosition(CCPoint(pDirector->getScreenLeft() - 1.0f, pDirector->getScreenBottom() - 1.0f));
    this->addChild(sideArtBL, 1);
    
    CCSprite* sideArtBR = CCSprite::createWithSpriteFrameName("GJ_sideArt_001.png");
    sideArtBR->setAnchorPoint(CCPoint(1.0f, 0.0f));
    sideArtBR->setPosition(CCPoint(pDirector->getScreenRight() + 1.0f, pDirector->getScreenBottom() - 1.0f));
    sideArtBR->setFlipX(true);
    this->addChild(sideArtBR, 1);
    
    CCSprite* backBtnSprite = CCSprite::createWithSpriteFrameName("GJ_arrow_03_001.png");
    CCMenuItemSpriteExtra* backBtn = CCMenuItemSpriteExtra::create(backBtnSprite, NULL, this, menu_selector(CreatorLayer::onBack));
    backBtn->setSizeMult(1.6f);
    CCMenu* backMenu = CCMenu::create(backBtn, NULL);
    this->addChild(backMenu, 1);
    backMenu->setPosition(CCPoint(pDirector->getScreenLeft() + 25.0f, pDirector->getScreenTop() - 22.0f));
    
    CCMenu* creatorMenu = CCMenu::create();
    
    
    CCSprite* createBtn = CCSprite::createWithSpriteFrameName("GJ_createBtn_001.png");
	CCMenuItemSpriteExtra* createExtra = CCMenuItemSpriteExtra::create(createBtn, NULL, this, menu_selector(CreatorLayer::onMyLevels));
    creatorMenu->addChild(createExtra);
    this->addChild(creatorMenu);
    creatorMenu->setPosition(CCPoint(winSize.width * 0.5f, (winSize.height * 0.5f) + 10.0f));
    createExtra->setPosition(m_backgroundSprite->getPosition() + CCPoint(-110.0f, 55.0f));
    
    CCSprite* savedBtn = CCSprite::createWithSpriteFrameName("GJ_savedBtn_001.png");
    CCMenuItemSpriteExtra* savedExtra = CCMenuItemSpriteExtra::create(savedBtn, NULL, this, menu_selector(CreatorLayer::onBack));
    creatorMenu->addChild(savedExtra);
    savedExtra->setPosition(m_backgroundSprite->getPosition() + CCPoint(0.0f, 55.0f));
    
    CCSprite* scoreBtn = CCSprite::createWithSpriteFrameName("GJ_highscoreBtn_001.png");
    CCMenuItemSpriteExtra* scoreExtra = CCMenuItemSpriteExtra::create(scoreBtn, NULL, this, menu_selector(CreatorLayer::onLeaderboards));
    creatorMenu->addChild(scoreExtra);
    scoreExtra->setPosition(m_backgroundSprite->getPosition() + CCPoint(110.0f, 55.0f));
    
    CCSprite* featuredBtn = CCSprite::createWithSpriteFrameName("GJ_featuredBtn_001.png");
    CCMenuItemSpriteExtra* featuredExtra = CCMenuItemSpriteExtra::create(featuredBtn, NULL, this, menu_selector(CreatorLayer::onBack));
    creatorMenu->addChild(featuredExtra);
    featuredExtra->setPosition(m_backgroundSprite->getPosition() + CCPoint(-110.0f, -55.0f));
    
    CCSprite* mapPacksBtn = CCSprite::createWithSpriteFrameName("GJ_mapPacksBtn_001.png");
    CCMenuItemSpriteExtra* mapPacksExtra = CCMenuItemSpriteExtra::create(mapPacksBtn, NULL, this, menu_selector(CreatorLayer::onBack));
    creatorMenu->addChild(mapPacksExtra);
    mapPacksExtra->setPosition(m_backgroundSprite->getPosition() + CCPoint(0.0f, -55.0f));
    
    CCSprite* searchBtn = CCSprite::createWithSpriteFrameName("GJ_searchBtn_001.png");
    CCMenuItemSpriteExtra* searchExtra = CCMenuItemSpriteExtra::create(searchBtn, NULL, this, menu_selector(CreatorLayer::onSearch));
    creatorMenu->addChild(searchExtra);
    searchExtra->setPosition(m_backgroundSprite->getPosition() + CCPoint(110.0f, -55.0f));
    
    return true;
}