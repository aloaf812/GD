#include "LevelInfoLayer.h"
#include "AppDelegate.h"
#include "CCMenuItemSpriteExtra.h"
#include "PlayLayer.h"
#include "GameManager.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
USING_NS_CC;

CCScene* LevelInfoLayer::scene(GJGameLevel* level)
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    AppDelegate* pApp = AppDelegate::get();
    // pApp->mMenuScene = scene;
    
    // 'layer' is an autorelease object
    LevelInfoLayer* layer = LevelInfoLayer::create(level);
    
    // add layer as a child to scene
    scene->addChild(layer);
    // return the scene
    return scene;
}

LevelInfoLayer::LevelInfoLayer()
{
    
}

LevelInfoLayer* LevelInfoLayer::create(GJGameLevel *level)
{
    LevelInfoLayer* pRet = new LevelInfoLayer();
    if (pRet && pRet->init(level))
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

void LevelInfoLayer::onBack(cocos2d::CCObject *sender)
{
    
}

void LevelInfoLayer::onPlay(CCObject* sender)
{
    // GameManager* pGameManager = GameManager::sharedState();
    SimpleAudioEngine* SAE = SimpleAudioEngine::sharedEngine();
    SAE->stopBackgroundMusic();
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCScene *pScene = PlayLayer::scene(m_level);
    CCTransitionFade* fade = CCTransitionFade::create(0.5f, pScene);
    pDirector->replaceScene(fade);
    return;
}

bool LevelInfoLayer::init(GJGameLevel* level)
{
    if (!CCLayer::init())
        return false;
    
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCSize winSize = pDirector->getWinSize();
    
    CCSprite* m_backgroundSprite;
    
    m_level = level;
    m_backgroundSprite = CCSprite::create("GJ_gradientBG.png");
    m_backgroundSprite->setAnchorPoint(CCPoint(0.0f, 0.0f));
    this->addChild(m_backgroundSprite, -2);
    m_backgroundSprite->setScaleX((winSize.width + 10.0f) / m_backgroundSprite->getTextureRect().size.width);
    m_backgroundSprite->setScaleY((winSize.height + 10.0f) / m_backgroundSprite->getTextureRect().size.height);
    m_backgroundSprite->setPosition(CCPoint(-5.0f, -5.0f));
    // for some reason every time i want to set a ccColor3B i have to define it as a variable first lol
    ccColor3B c = {0, 102, 255};
    m_backgroundSprite->setColor(c);
    
    CCSprite* sideArtL = CCSprite::createWithSpriteFrameName("GJ_sideArt_001.png");
    sideArtL->setAnchorPoint(CCPoint(0.0f, 0.0f));
    sideArtL->setPosition(CCPoint(pDirector->getScreenLeft() - 1.0f, pDirector->getScreenBottom() - 1.0f));
    this->addChild(sideArtL, 1);
    
    CCSprite* sideArtR = CCSprite::createWithSpriteFrameName("GJ_sideArt_001.png");
    sideArtR->setAnchorPoint(CCPoint(1.0f, 0.0f));
    sideArtR->setPosition(CCPoint(pDirector->getScreenRight() + 1.0f, pDirector->getScreenBottom() - 1.0f));
    sideArtR->setFlipX(true);
    this->addChild(sideArtR, 1);
    
    CCSprite* backBtnSprite = CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png");
    CCMenuItemSpriteExtra* backBtn = CCMenuItemSpriteExtra::create(backBtnSprite, NULL, this, menu_selector(LevelInfoLayer::onBack));
    backBtn->setSizeMult(1.6f);
    CCMenu* backMenu = CCMenu::create(backBtn, NULL);
    this->addChild(backMenu, 1);
    backMenu->setPosition(CCPoint(pDirector->getScreenLeft() + 25.0f, pDirector->getScreenTop() - 22.0f));
    
    // this is being held together by hopes and dreams and it works perfectly
    CCLabelBMFont* m_levelCaption = CCLabelBMFont::create(level->m_levelName.c_str(), "bigFont.fnt");
    this->addChild(m_levelCaption);
    const CCPoint levelTextPos(winSize.width * 0.5f, pDirector->getScreenTop() - 30.0f);
    m_levelCaption->setPosition(levelTextPos);
    m_levelCaption->setScale(0.8f);
    m_levelCaption->setVisible(true);
    
    CCLabelBMFont* m_creatorCaption = CCLabelBMFont::create(CCString::createWithFormat("by %s", "YEAH")->getCString()
, "goldFont.fnt");
    this->addChild(m_creatorCaption);
    const CCPoint creatorTextPos(m_levelCaption->getPosition() - CCPoint(0.0f, 20.0f));
    m_creatorCaption->setPosition(creatorTextPos);
    m_creatorCaption->setScale(0.8f);
    m_creatorCaption->setVisible(true);
    
    CCMenu* playMenu = CCMenu::create();
    
    CCSprite* playButton = CCSprite::createWithSpriteFrameName("GJ_playBtn2_001.png");
    CCMenuItemSpriteExtra* playExtra = CCMenuItemSpriteExtra::create(playButton, NULL, this, menu_selector(LevelInfoLayer::onPlay));
    playMenu->addChild(playExtra);
    this->addChild(playMenu);
    playMenu->setPosition(CCPoint(winSize.width * 0.5f, (winSize.height * 0.5f) + 40.0f));
   
    CCSprite* downloadsSpr = CCSprite::createWithSpriteFrameName("GJ_downloadsIcon_001.png");
    this->addChild(downloadsSpr, 1);
    downloadsSpr->setPosition(playMenu->getPosition() + CCPoint(60.0f, 35.0f));
    
    CCLabelBMFont* m_downloadCaption = CCLabelBMFont::create("102", "bigFont.fnt");
    this->addChild(m_downloadCaption);
    const CCPoint downloadTextPos(downloadsSpr->getPosition() + CCPoint(50.0f, 0.0f));
    m_downloadCaption->setPosition(downloadTextPos);
    m_downloadCaption->setScale(0.8f);
    m_downloadCaption->setVisible(true);

    CCSprite* likeSpr = CCSprite::createWithSpriteFrameName("GJ_likesIcon_001.png");
    this->addChild(likeSpr, 1);
    likeSpr->setPosition(playMenu->getPosition() + CCPoint(60.0f, 0.0f));
    
    CCLabelBMFont* m_likesCaption = CCLabelBMFont::create("49", "bigFont.fnt");
    this->addChild(m_likesCaption);
    const CCPoint likesTextPos(likeSpr->getPosition() + CCPoint(50.0f, 0.0f));
    m_likesCaption->setPosition(likesTextPos);
    m_likesCaption->setScale(0.8f);
    m_likesCaption->setVisible(true);

    CCSprite* lengthSpr = CCSprite::createWithSpriteFrameName("GJ_timeIcon_001.png");
    this->addChild(lengthSpr, 1);
    lengthSpr->setPosition(playMenu->getPosition() + CCPoint(60.0f, -35.0f));
    
    CCLabelBMFont* m_lengthCaption = CCLabelBMFont::create("Tiny", "bigFont.fnt");
    this->addChild(m_lengthCaption);
    const CCPoint lengthTextPos(lengthSpr->getPosition() + CCPoint(50.0f, 0.0f));
    m_lengthCaption->setPosition(lengthTextPos);
    m_lengthCaption->setScale(0.8f);
    m_lengthCaption->setVisible(true);
    
    CCMenu* sideMenu = CCMenu::create();
    
    CCSprite* deleteBtn = CCSprite::createWithSpriteFrameName("GJ_deleteBtn_001.png");
    CCMenuItemSpriteExtra* deleteExtra = CCMenuItemSpriteExtra::create(deleteBtn, NULL, this, menu_selector(LevelInfoLayer::init));
    sideMenu->addChild(deleteExtra);
    this->addChild(sideMenu, 2);
    
    CCSprite* updateBtn = CCSprite::createWithSpriteFrameName("GJ_updateBtn_001.png");
    CCMenuItemSpriteExtra* updateExtra = CCMenuItemSpriteExtra::create(updateBtn, NULL, this, menu_selector(LevelInfoLayer::init));
    sideMenu->addChild(updateExtra);
    
    CCSprite* infoBtn = CCSprite::createWithSpriteFrameName("GJ_infoBtn_001.png");
    CCMenuItemSpriteExtra* infoExtra = CCMenuItemSpriteExtra::create(infoBtn, NULL, this, menu_selector(LevelInfoLayer::init));
    sideMenu->addChild(infoExtra);
    
    CCSprite* rateDiffBtn = CCSprite::createWithSpriteFrameName("GJ_rateDiffBtn_001.png");
    CCMenuItemSpriteExtra* rateDiffExtra = CCMenuItemSpriteExtra::create(rateDiffBtn, NULL, this, menu_selector(LevelInfoLayer::init));
    sideMenu->addChild(rateDiffExtra);
    
    CCSprite* likeBtn = CCSprite::createWithSpriteFrameName("GJ_like2Btn_001.png");
    CCMenuItemSpriteExtra* likeExtra = CCMenuItemSpriteExtra::create(likeBtn, NULL, this, menu_selector(LevelInfoLayer::init));
    sideMenu->addChild(likeExtra);
    
    CCSprite* starBtn = CCSprite::createWithSpriteFrameName("GJ_starBtn_001.png");
    CCMenuItemSpriteExtra* starExtra = CCMenuItemSpriteExtra::create(starBtn, NULL, this, menu_selector(LevelInfoLayer::init));
    sideMenu->addChild(starExtra);
    
    deleteExtra->setPosition(sideMenu->convertToNodeSpace(CCPoint(pDirector->getScreenRight() - 35.0f, pDirector->getScreenTop() - 30.0f)));
    updateExtra->setPosition(deleteExtra->getPosition() - CCPoint(0.0, 50.0f));
    infoExtra->setPosition(updateExtra->getPosition() - CCPoint(0.0, 50.0f));
    rateDiffExtra->setPosition(infoExtra->getPosition() - CCPoint(0.0, 50.0f));
    likeExtra->setPosition(rateDiffExtra->getPosition() - CCPoint(0.0, 50.0f));
    starExtra->setPosition(likeExtra->getPosition() - CCPoint(0.0, 50.0f));
    
    CCMenu* lvlInfoMenu = CCMenu::create();
    
    CCSprite* lvlInfoBtn = CCSprite::createWithSpriteFrameName("GJ_infoIcon_001.png");
    CCMenuItemSpriteExtra* lvlInfoExtra = CCMenuItemSpriteExtra::create(lvlInfoBtn, NULL, this, menu_selector(LevelInfoLayer::init));
    lvlInfoMenu->addChild(lvlInfoExtra);
    this->addChild(lvlInfoMenu);
    lvlInfoExtra->setPosition(sideArtL->getPosition());
    
    return true;
}
