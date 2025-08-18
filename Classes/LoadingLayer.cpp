#include "LoadingLayer.h"
#include "AppDelegate.h"
#include "GameManager.h"
#include "GameSoundManager.h"
#include "MenuLayer.h"
#include "LevelTools.h"
#include "TextArea.h"
#include "PlatformToolbox.h"
#include <stdio.h>
USING_NS_CC;

CCScene* LoadingLayer::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    // create() should be renamed to node()
    LoadingLayer *layer = LoadingLayer::create();
    
    // add layer as a child to scene
    // the only line in this function that isn't accurate
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

LoadingLayer::LoadingLayer() {
    m_progressBarSize = CCSize(0.0f, 0.0f);
    m_loadStep = 0;
    m_caption = NULL;
    m_textArea = NULL;
    m_sliderBar = NULL;
}

bool LoadingLayer::init() {
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    timeval tv;
    gettimeofday(&tv, NULL);
    srand(tv.tv_sec * tv.tv_usec);
    
    GameManager* pGameManager = GameManager::sharedState();

    // GameSoundManager::GameSoundManager()->setup();

    CCTextureCache* pTextureCache = CCTextureCache::sharedTextureCache();
    pTextureCache->addImage("GJ_LaunchSheet.png");

    CCSpriteFrameCache* pSpriteFrameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
    pSpriteFrameCache->addSpriteFramesWithFile("GJ_LaunchSheet.plist");

    CCDirector* pDirector = CCDirector::sharedDirector();
    CCSize winSize = pDirector->getWinSize();

    const char* bgTextureName = pGameManager->getBGTexture(1);
    CCSprite* bgSprite = CCSprite::create(bgTextureName);
    this->addChild(bgSprite);
    
    bgSprite->setPosition(winSize * 0.5f);
    bgSprite->setScale(AppDelegate::get()->bgScale());
    ccColor3B bgColor = { 0, 102, 255 };
    bgSprite->setColor(bgColor);

    CCSprite* gjLogo = CCSprite::createWithSpriteFrameName("GJ_logo_001.png");
    this->addChild(gjLogo);
    gjLogo->setPosition(CCPoint(winSize.width * 0.5f, winSize.height * 0.5f + 26.0f));

    CCSprite* robTopLogo = CCSprite::createWithSpriteFrameName("RobTopLogoBig_001.png");
    this->addChild(robTopLogo);
    const CCPoint gjLogoPos = gjLogo->getPosition();
    const CCPoint logoPos2(0.0f, 80.0f);
    robTopLogo->setPosition(logoPos2 + gjLogoPos);
    
    // Loading Text
    m_caption = CCLabelBMFont::create(getLoadingString(), "goldFont.fnt");
    this->addChild(m_caption);
    const CCPoint loadingTextPos(winSize.width * 0.5f, winSize.height * 0.5f - 70.0f);
    m_caption->setPosition(loadingTextPos);
    m_caption->setScale(0.7f);
    m_caption->setVisible(true);

    m_textArea = TextArea::create(getLoadingString(), "goldFont.fnt", 1.0f, 440.0f, CCPoint(0.5f, 0.5f), 28.0f, false);
    this->addChild(m_textArea);
    m_textArea->setPosition(CCPoint(winSize.width * 0.5f, winSize.height * 0.5f - 100.0f));
    m_textArea->setScale(0.7f);
    
    if (300.0f < m_caption->getContentSize().width)
    {
        m_caption->setScale(300.0f / m_caption->getContentSize().width);
    }
    
    float textScale;
    if (m_caption->getScale() < 0.7f)
    {
        textScale = m_caption->getScale();
    } else
    {
        textScale = 0.7f;
    }
    
    m_caption->setScale(textScale);

    CCSprite* sliderGroove = CCSprite::create("slidergroove.png");
    this->addChild(sliderGroove, 3);
    
    m_sliderBar = CCSprite::create("sliderBar.png");
    m_progressBarSize = CCSize(sliderGroove->getTextureRect().size.width - 4.0f, 8.0f);
    
    CCTexture2D* tex = m_sliderBar->getTexture();
    ccTexParams params = { GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT };
    tex->setTexParameters(&params);
    
    sliderGroove->addChild(m_sliderBar, -1);
    m_sliderBar->setAnchorPoint(CCPoint(0.0f, 0.0f));
    m_sliderBar->setPosition(CCPoint(2.0f, 4.0f));
    
    sliderGroove->setPosition(CCPoint(m_caption->getPosition().x, m_textArea->getPosition().y + 40.0f));
    
    this->updateProgress(0);
    
    CCActionManager* pActionManager = pDirector->getActionManager();
    CCDelayTime* delayTime = CCDelayTime::create(0.0f);
    CCCallFunc* callFunc = CCCallFunc::create(this, callfunc_selector(LoadingLayer::loadAssets));
    CCSequence* sequence = CCSequence::create(delayTime, callFunc, NULL);
    pActionManager->addAction(sequence, this, false);

    /*
    if (false) {
        PlatformToolbox::activateGameCenter();
    }
    */

    return true;
}

// todo: hd textures
void LoadingLayer::loadAssets() {
    AppDelegate* pApp = AppDelegate::get();
    CCDirector* pDirector = CCDirector::sharedDirector();
    GameManager* pGameManager = GameManager::sharedState();
    CCTextureCache* pTextureCache = CCTextureCache::sharedTextureCache();
    CCSpriteFrameCache* pSpriteFrameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
    
    switch (m_loadStep)
    {
        case 0:
        default:
        {
            // CCLOG("step 1");
            pTextureCache->addImage("GJ_GameSheet.png");
            pSpriteFrameCache->addSpriteFramesWithFile("GJ_GameSheet.plist");
            break;
        }
        case 1:
        {
            // CCLOG("step 2");
            pTextureCache->addImage("GJ_GameSheet02.png");
            pSpriteFrameCache->addSpriteFramesWithFile("GJ_GameSheet02.plist");
            break;
        }
        case 2:
        {
            // CCLOG("step 3");
            pTextureCache->addImage("CCControlColourPickerSpriteSheet.png");
            pSpriteFrameCache->addSpriteFramesWithFile("CCControlColourPickerSpriteSheet.plist");
            
            pTextureCache->addImage("GJ_gradientBG.png");
            pTextureCache->addImage("edit_barBG_001.png");
            pTextureCache->addImage("GJ_button_01.png");
            pTextureCache->addImage("GJ_square01.png");
            pTextureCache->addImage("slidergroove2.png");
            pTextureCache->addImage("sliderBar2.png");
            break;
        }
        case 3:
        {
            // CCLOG("step 4");
            pTextureCache->addImage("goldFont.png");
            pTextureCache->addImage("bigFont.png");
            
            // i'm not sure why the game does this but it does it nonetheless
            CCLabelBMFont::create(" ", "goldFont.fnt");
            CCLabelBMFont::create(" ", "bigFont.fnt");
            break;
        }
        case 4:
        {
            // i'm pretty sure this one is matching
            
            // CCLOG("loading finished");
            pApp->loadingIsFinished();
            pGameManager->fadeInMusic("menuLoop.mp3");
            pGameManager->syncPlatformAchievements();
            loadingFinished();
            return;
        }
    }
    m_loadStep++;
    updateProgress(m_loadStep * 25	);
    CCActionManager* pActionManager = pDirector->getActionManager();
    CCDelayTime* delayTime = CCDelayTime::create(0.01f);
    CCCallFunc* callFunc = CCCallFunc::create(this, callfunc_selector(LoadingLayer::loadAssets));
    CCSequence* sequence = CCSequence::create(delayTime, callFunc, NULL);
    pActionManager->addAction(sequence, this, false);
}

void LoadingLayer::updateProgress(int progress)
{
    float width = m_progressBarSize.width;
    if (width > (width * static_cast<float>(progress) / 100.0f))
        width = width * static_cast<float>(progress) / 100.0f;

    m_sliderBar->setTextureRect(CCRect(0.0f, 0.0f, width, m_progressBarSize.height));
}

void LoadingLayer::loadingFinished() {
    CCScene *pScene = MenuLayer::scene();
    CCDirector::sharedDirector()->replaceScene(pScene);
    return;
}

const char* LoadingLayer::getLoadingString() {
    
    int stringNum = (rand() % 10 + 1);
    switch(stringNum) {
    case 1:
        return "Listen to the music to help time your jumps";
        break;
    case 2:
        return "Back for more are ya?";
        break;
    case 3:
        return "Use practice mode to learn the layout of a level";
        break;
    case 4:
        return "Build your own levels using the level editor";
        break;
    case 5:
        return "Go online to play other players levels!";
        break;
    case 6:
        return "If at first you don't succeed, try, try again...";
        break;
    case 7:
        return "Can you beat them all?";
        break;
    case 8:
        return "Customize your character's icon and color!";
        break;
    case 9:
        return "You can download all songs from the level select page!";
        break;
    default:
        return "Unlock new icons and colors by completing achievements!";    
    }
}

