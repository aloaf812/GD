#include "AppDelegate.h"
#include "CCMenuItemSpriteExtra.h"
#include "MenuLayer.h"

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
    pApp->mMenuScene = scene;
    
    // 'layer' is an autorelease object
    CreatorLayer* layer = CreatorLayer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

CreatorLayer* CreatorLayer::create()
{
    CreatorLayer* pRet = new CreatorLayer();
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

void CreatorLayer::onBack(CCObject* sender)
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCScene* scene = MenuLayer::scene();
    CCTransitionFade* fade = CCTransitionFade::create(0.5f, scene);
    pDirector->replaceScene(fade);
}

bool CreatorLayer::init()
{
    if (!CCLayer::init())
        return false;
    
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCSize winSize = pDirector->getWinSize();
    
    cocos2d::CCSprite* m_backgroundSprite;
    
    m_backgroundSprite = CCSprite::create("GJ_gradientBG.png");
    m_backgroundSprite->setAnchorPoint(CCPoint(0.0f, 0.0f));
    this->addChild(m_backgroundSprite, -2);
    m_backgroundSprite->setScaleX((winSize.width + 10.0f) / m_backgroundSprite->getTextureRect().size.width);
    m_backgroundSprite->setScaleY((winSize.height + 10.0f) / m_backgroundSprite->getTextureRect().size.height);
    m_backgroundSprite->setPosition(CCPoint(-5.0f, -5.0f));
    // for some reason every time i want to set a ccColor3B i have to define it as a variable first lol
    ccColor3B c = {0, 102, 255};
    m_backgroundSprite->setColor(c);
    
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
    CCMenuItemSpriteExtra* createExtra = CCMenuItemSpriteExtra::create(createBtn, NULL, this, menu_selector(CreatorLayer::onBack));
    creatorMenu->addChild(createExtra);
    this->addChild(creatorMenu);
    creatorMenu->setPosition(CCPoint(winSize.width * 0.5f, (winSize.height * 0.5f) + 10.0f));
    createExtra->setPosition(m_backgroundSprite->getPosition() + CCPoint(-110.0f, 0.0f));
    
    CCSprite* savedBtn = CCSprite::createWithSpriteFrameName("GJ_savedBtn_001.png");
    CCMenuItemSpriteExtra* savedExtra = CCMenuItemSpriteExtra::create(savedBtn, NULL, this, menu_selector(CreatorLayer::onBack));
    creatorMenu->addChild(savedExtra);
    savedExtra->setPosition(m_backgroundSprite->getPosition() + CCPoint(0.0f, 0.0f));
    
    CCSprite* scoreBtn = CCSprite::createWithSpriteFrameName("GJ_highscoreBtn_001.png");
    CCMenuItemSpriteExtra* scoreExtra = CCMenuItemSpriteExtra::create(scoreBtn, NULL, this, menu_selector(CreatorLayer::onBack));
    creatorMenu->addChild(scoreExtra);
    scoreExtra->setPosition(m_backgroundSprite->getPosition() + CCPoint(110.0f, 0.0f));
    
    // this function uses something like the code below but i'm just too lazy to actually implement it
    // creatorMenu->setPosition(CCPoint(winSize.width * 0.5f, pDirector->getScreenBottom() + 45.0f));
    // creatorMenu->alignItemsHorizontallyWithPadding(5.0f);
    
    return true;
}