#include "LoadingLayer.h"
#include "GameManager.h"
#include "GameSoundManager.h"
#include "MenuLayer.h"
#include "LevelTools.h"
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

bool LoadingLayer::init() {
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    GameSoundManager::GameSoundManager()->setup();

    CCTextureCache *this_01 = CCTextureCache::sharedTextureCache();
    this_01->addImage("GJ_LaunchSheet.png");

    CCSpriteFrameCache *this_02 = CCSpriteFrameCache::sharedSpriteFrameCache();
    this_02->addSpriteFramesWithFile("GJ_LaunchSheet.plist");

    GameManager *something = GameManager::sharedState();
    CCSprite* bgSprite = CCSprite::create(something->getBGTexture(1));
    bgSprite->createWithSpriteFrameName("GJ_logo_001.png");

    // renders the geometry dash logo to the middle of the screen
    CCSprite* logoSprite = CCSprite::createWithSpriteFrameName("GJ_logo_001.png");
    logoSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(logoSprite, 0);

    // this is a custom function: CCDirector::sharedDirector->getScreenScaleFactorMax();
    return true;
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

void LoadingLayer::loadingFinished() {
    CCScene *pScene = MenuLayer::scene();
    CCDirector::sharedDirector()->replaceScene(pScene);
    return;
}

void LoadingLayer::loadAssets() {
    return;
}
