#include "LoadingLayer.h"
#include "GameManager.h"
#include "MenuLayer.h"
#include "LevelTools.h"
USING_NS_CC;

CCScene* LoadingLayer::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    LoadingLayer *layer = LoadingLayer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool LoadingLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return 1;
    }
    
    // why does it have to be this way
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    CCTextureCache *this_01 = CCTextureCache::sharedTextureCache();
    this_01->addImage("GJ_LaunchSheet.png");
    CCSpriteFrameCache *this_02 = CCSpriteFrameCache::sharedSpriteFrameCache();
    this_02->addSpriteFramesWithFile("GJ_LaunchSheet.plist");
    CCLOG("loaded GJ_LaunchSheet");
    GameManager *something = GameManager::sharedState();
    CCSprite* bgSprite = CCSprite::create(something->getBGTexture(1));
    bgSprite->createWithSpriteFrameName("GJ_logo_001.png");
    CCSprite* logoSprite = CCSprite::createWithSpriteFrameName("GJ_logo_001.png");
    logoSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(logoSprite, 0);
    // fix this you idiot CCLabelBMFont::create(LoadingLayer::getLoadingString(), "goldFont.fnt");
}

const char* LoadingLayer::getLoadingString(){
    
    char *loadingString;
    int stringNum = (rand() % 10 + 1);
    switch(stringNum) {
    case 1:
        loadingString = "Listen to the music to help time your jumps";
        break;
    case 2:
        loadingString = "Back for more are ya?";
        break;
    case 3:
        loadingString = "Use practice mode to learn the layout of a level";
        break;
    case 4:
        loadingString = "Build your own levels using the level editor";
        break;
    case 5:
        loadingString = "Go online to play other players levels!";
        break;
    case 6:
        loadingString = "If at first you don't succeed, try, try again...";
        break;
    case 7:
        loadingString = "Can you beat them all?";
        break;
    case 8:
        loadingString = "Customize your character's icon and color!";
        break;
    case 9:
        loadingString = "You can download all songs from the level select page!";
        break;
    default:
        loadingString = "Unlock new icons and colors by completing achievements!";    
    }
    /* ditch the CCLOG functions in order to aim for accuracy
    CCLOG("got loading string");
    CCLOG(loadingString);
    */
    return loadingString;
}

void LoadingLayer::loadingFinished(){
    MenuLayer::scene();
}