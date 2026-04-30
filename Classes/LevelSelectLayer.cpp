// Partially decompiled by ProjectReversio: https://github.com/ProjectReversio/GeometryDash/blob/master/GeometryDash/Classes/LevelSelectLayer.cpp
#include "LevelSelectLayer.h"

#include "AppDelegate.h"
#include "RT_COCOS/CCMenuItemSpriteExtra.h"
#include "MenuLayer.h"
#include "GameManager.h"
#include <cmath>
#include "BoomScrollLayer.h"
#include "GameLevelManager.h"
#include "LevelPage.h"
#include "LevelTools.h"
#include "SongsLayer.h"
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
    pApp->setScenePointer(scene);
    
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
    
    GameLevelManager* pGLM = GameLevelManager::sharedState();
    GameManager* pGameManager = GameManager::sharedState();
    
    m_backgroundSprite = CCSprite::create("GJ_gradientBG.png");
    m_backgroundSprite->setAnchorPoint(CCPoint(0.0f, 0.0f));
    this->addChild(m_backgroundSprite, -4);
    m_backgroundSprite->setScaleX((winSize.width + 10.0f) / m_backgroundSprite->getTextureRect().size.width);
    m_backgroundSprite->setScaleY((winSize.height + 10.0f) / m_backgroundSprite->getTextureRect().size.height);
    m_backgroundSprite->setPosition(CCPoint(-5.0f, -5.0f));
    m_backgroundSprite->setColor(ccc3(40, 125, 255));
    
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
    
    CCArray* pages = CCArray::create();
    for (int i = 1; i <= 15; ++i) {
        GJGameLevel* level = pGLM->getMainLevel(i);
        LevelPage* page = LevelPage::create(level);
        pages->addObject(page);
    }
    
    // coming soon!
    CCLayer* csLayer = CCLayer::create();
    CCLabelBMFont* csLabel = CCLabelBMFont::create("Coming Soon!", "bigFont.fnt");
    csLabel->setPosition(ccp(winSize.width / 2, winSize.height / 2 + 50));
    csLayer->addChild(csLabel);
    pages->addObject(csLayer);
    
	// the third param is for looping
    bool showDots = pages->count() > 3;
    BoomScrollLayer* scrollLayer = BoomScrollLayer::create(pages, 0, showDots);
    m_scrollLayer = scrollLayer;
    this->addChild(scrollLayer);
    
    
    CCLabelBMFont* downloadTxt = CCLabelBMFont::create("Download the soundtracks", "bigFont.fnt");
    downloadTxt->setScale(0.5f);
    CCMenuItemSpriteExtra* downloadExtra = CCMenuItemSpriteExtra::create(downloadTxt, NULL, this, menu_selector(LevelSelectLayer::onDownload));
    downloadExtra->setSizeMult(2.0f);
    
    CCMenu* downloadMenu = CCMenu::create(downloadExtra, NULL);
    this->addChild(downloadMenu, 5);
    downloadMenu->setPosition(CCPoint(winSize.width * 0.5f, pDirector->getScreenBottom() + 35.0f));
    
    CCMenu* arrowsMenu = CCMenu::create();
    this->addChild(arrowsMenu, 5);
    
    CCSprite* leftBtnSprite = CCSprite::createWithSpriteFrameName("navArrowBtn_001.png");
    leftBtnSprite->setFlipX(true);
    CCMenuItemSpriteExtra* leftBtn = CCMenuItemSpriteExtra::create(leftBtnSprite, NULL, this, menu_selector(LevelSelectLayer::onPrev));
    arrowsMenu->addChild(leftBtn);
    leftBtn->setSizeMult(2.0f);
    leftBtn->setPosition(arrowsMenu->convertToNodeSpace(CCPoint(pDirector->getScreenLeft() + 25.0f, winSize.height * 0.5f)));
    
    CCSprite* rightBtnSprite = CCSprite::createWithSpriteFrameName("navArrowBtn_001.png");
    CCMenuItemSpriteExtra* rightBtn = CCMenuItemSpriteExtra::create(rightBtnSprite, NULL, this, menu_selector(LevelSelectLayer::onNext));
    arrowsMenu->addChild(rightBtn);
    rightBtn->setSizeMult(2.0f);
    rightBtn->setPosition(arrowsMenu->convertToNodeSpace(CCPoint(pDirector->getScreenRight() - 25.0f, winSize.height * 0.5f)));
    
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

    // ground
    CCLayer* groundLayer = CCLayer::create();
    this->addChild(groundLayer, 0);
    
	m_ground = CCSprite::create(pGameManager->getGTexture(1));
    ccTexParams texParams = {GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT};
	m_ground->getTexture()->setTexParameters(&texParams);
	groundLayer->addChild(m_ground, 2);
	m_ground->setAnchorPoint(ccp(0, 1));
	m_ground->setColor(ccc3(0, 102, 255));
	m_ground->setPosition(ccp(0.0f, 60.0f));
	m_ground->setTextureRect(CCRectMake(0, 0, winSize.width, m_ground->getContentSize().height));
	
    CCSprite* leftShadow = CCSprite::createWithSpriteFrameName("groundSquareShadow_001.png");
    leftShadow->setAnchorPoint(ccp(0.0f, 1.0f));
	leftShadow->setPosition(ccp(pDirector->getScreenLeft() - 1.0f, m_ground->getPositionY()));
    groundLayer->addChild(leftShadow, -2);
    leftShadow->setOpacity(100);
    leftShadow->setColor(ccc3(150, 150, 150));
    leftShadow->setBlendFunc({GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA});
    leftShadow->setTag(0);
    
    CCSprite* rightShadow = CCSprite::createWithSpriteFrameName("groundSquareShadow_001.png");
    rightShadow->setAnchorPoint(ccp(1.0f, 1.0f));
    rightShadow->setPosition(ccp(pDirector->getScreenRight() + 1.0f, m_ground->getPositionY()));
    rightShadow->setFlipX(true);
    groundLayer->addChild(rightShadow, -2);
    rightShadow->setOpacity(100);
    rightShadow->setColor(ccc3(150, 150, 150));
    rightShadow->setBlendFunc({GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA});
    rightShadow->setTag(0);
    
    CCSprite* lineSprite = CCSprite::createWithSpriteFrameName("floorLine_001.png");
    groundLayer->addChild(lineSprite, 3);
	lineSprite->setPosition(CCPoint(winSize.width * 0.5f, m_ground->getPositionY()));
    
    return true;
}

void LevelSelectLayer::onDownload(CCObject* sender)
{
	SongsLayer* layer = SongsLayer::create();
	getParent()->addChild(layer, 100);
	layer->showLayer(false);
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

}

void LevelSelectLayer::onPrev(CCObject* sender)
{
    m_scrollLayer->quickUpdate();
    
    int currentPage = m_scrollLayer->getCurrentScreen();
    m_scrollLayer->moveToPage(currentPage - 1);
}

void LevelSelectLayer::onNext(CCObject* sender)
{
    m_scrollLayer->quickUpdate();
    
    int currentPage = m_scrollLayer->getCurrentScreen();
    m_scrollLayer->moveToPage(currentPage + 1);
}