#include "LevelSelectLayer.h"

#include "AppDelegate.h"
#include "CCMenuItemSpriteExtra.h"
#include "MenuLayer.h"
USING_NS_CC;

LevelSelectLayer::LevelSelectLayer()
{
    // mUnknown1 = 0.0f;
    m_backgroundSprite = NULL;
    // mGroundLayer = NULL;
}

CCScene* LevelSelectLayer::scene(int page)
{
    // 'scene' is an autorelease object
    CCScene* scene = CCScene::create();
    
    AppDelegate* pApp = AppDelegate::get();
    pApp->mMenuScene = scene;
    
    // 'layer' is an autorelease object
    LevelSelectLayer* layer = LevelSelectLayer::create(page);
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

LevelSelectLayer* LevelSelectLayer::create(int page)
{
    LevelSelectLayer* pRet = new LevelSelectLayer();
    if (pRet && pRet->init(page))
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

bool LevelSelectLayer::init(int page)
{
    if (!CCLayer::init())
        return false;
    
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCSize winSize = pDirector->getWinSize();
    
    m_backgroundSprite = CCSprite::create("GJ_gradientBG.png");
    CCLOG("hi");
    m_backgroundSprite->setAnchorPoint(CCPoint(0.0f, 0.0f));
    this->addChild(m_backgroundSprite, -2);
    m_backgroundSprite->setScaleX((winSize.width + 10.0f) / m_backgroundSprite->getTextureRect().size.width);
    m_backgroundSprite->setScaleY((winSize.height + 10.0f) / m_backgroundSprite->getTextureRect().size.height);
    m_backgroundSprite->setPosition(CCPoint(-5.0f, -5.0f));
    // for some reason every time i want to set a ccColor3B i have to define it as a variable first lol
    ccColor3B c = {40, 125, 255};
    m_backgroundSprite->setColor(c);
    
    CCSprite* topBar = CCSprite::createWithSpriteFrameName("GJ_topBar_001.png");
    topBar->setAnchorPoint(CCPoint(0.5f, 1.0f));
    topBar->setPosition(CCPoint(winSize.width * 0.5f, pDirector->getScreenTop() + 1.0f));
    this->addChild(topBar, 1);
    
    CCSprite* sideArtLeft = CCSprite::createWithSpriteFrameName("GJ_sideArt_001.png");
    sideArtLeft->setAnchorPoint(CCPoint(0.0f, 0.0f));
    sideArtLeft->setPosition(CCPoint(pDirector->getScreenLeft() - 1.0f, pDirector->getScreenBottom() - 1.0f));
    this->addChild(sideArtLeft, 1);
    
    CCSprite* sideArtRight = CCSprite::createWithSpriteFrameName("GJ_sideArt_001.png");
    sideArtRight->setAnchorPoint(CCPoint(1.0f, 0.0f));
    sideArtRight->setPosition(CCPoint(pDirector->getScreenRight() + 1.0f, pDirector->getScreenBottom() - 1.0f));
    sideArtRight->setFlipX(true);
    this->addChild(sideArtRight, 1);
    
    CCLabelBMFont* downloadTxt = CCLabelBMFont::create("Download the soundtracks", "bigFont.fnt");
    downloadTxt->setScale(0.5f);
    CCMenuItemSpriteExtra* downloadExtra = CCMenuItemSpriteExtra::create(downloadTxt, NULL, this, menu_selector(LevelSelectLayer::onDownload));
    downloadExtra->setSizeMult(2.0f);
    
    CCMenu* downloadMenu = CCMenu::create(downloadExtra, NULL);
    this->addChild(downloadMenu);
    downloadMenu->setPosition(CCPoint(winSize.width * 0.5f, pDirector->getScreenBottom() + 35.0f));
    
    CCMenu* navigationMenu = CCMenu::create();
    this->addChild(navigationMenu, 5);
    
    const char* leftBtnImg;
    leftBtnImg = "navArrowBtn_001.png";
    CCSprite* leftBtnSprite = CCSprite::createWithSpriteFrameName(leftBtnImg);
    leftBtnSprite->setFlipX(true);
    
    CCMenuItemSpriteExtra* leftBtn = CCMenuItemSpriteExtra::create(leftBtnSprite, NULL, this, menu_selector(LevelSelectLayer::onBack));
    navigationMenu->addChild(leftBtn);
    leftBtn->setSizeMult(2.0f);
    leftBtn->setPosition(navigationMenu->convertToNodeSpace(CCPoint(pDirector->getScreenLeft() + 25.0f, winSize.height * 0.5f)));
    
    CCSprite* backBtnSprite = CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png");
    CCMenuItemSpriteExtra* backBtn = CCMenuItemSpriteExtra::create(backBtnSprite, NULL, this, menu_selector(LevelSelectLayer::onBack));
    backBtn->setSizeMult(1.6f);
    CCMenu* backMenu = CCMenu::create(backBtn, NULL);
    this->addChild(backMenu, 1);
    backMenu->setPosition(CCPoint(pDirector->getScreenLeft() + 25.0f, pDirector->getScreenTop() - 22.0f));

    CCMenu* infoMenu = CCMenu::create();
    this->addChild(infoMenu);
    
    CCSprite* infoBtnSprite = CCSprite::createWithSpriteFrameName("GJ_infoIcon_001.png");
    CCMenuItemSpriteExtra* infoBtn = CCMenuItemSpriteExtra::create(infoBtnSprite, NULL, this, menu_selector(LevelSelectLayer::onInfo));
    infoBtn->setSizeMult(2.0f);
    infoMenu->addChild(infoBtn);
    
    infoMenu->setPosition(CCPoint(pDirector->getScreenRight() - 20.0f, pDirector->getScreenTop() - 20.0f));

    return true;
}

void LevelSelectLayer::onDownload(CCObject* sender)
{
    CCLOG("clicked the download thing");
}

void LevelSelectLayer::onBack(CCObject* sender)
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCScene* scene = MenuLayer::scene();
    CCTransitionFade* fade = CCTransitionFade::create(0.5f, scene);
    pDirector->replaceScene(fade);
}

void LevelSelectLayer::onInfo(CCObject* sender)
{
    CCLOG("INFO");
}