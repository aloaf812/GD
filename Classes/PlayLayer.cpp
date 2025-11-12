#include "PlayLayer.h"
#include "SimpleAudioEngine.h"
#include "GameManager.h"
#include "AppDelegate.h"
using namespace CocosDenshion;
USING_NS_CC;

void PlayLayer::onQuit()
{
    // CCNode::stopAllActions((CCNode *)this);
    // CCNode::unscheduleAllSelectors((CCNode *)this);
    SimpleAudioEngine* SAE = SimpleAudioEngine::sharedEngine();
    SAE->stopBackgroundMusic();
    GameManager* pGameManager = GameManager::sharedState();
    // piVar3 = (int *)(**(code **)(*piVar3 + 0x1c4))();
    // (**(code **)(*piVar3 + 0x238))();
    // pGameManager->returnToLastScene();
    pGameManager->fadeInMusic("menuLoop.mp3");
    return;
    
}

CCScene* PlayLayer::scene(GJGameLevel* level)
{
    CCScene *scene = CCScene::create();
    AppDelegate* pApp = AppDelegate::get();
    PlayLayer* layer = PlayLayer::create(level);
    scene->addChild(layer);
    // scene->setObjType(5);
    return scene;
}

PlayLayer* PlayLayer::create(GJGameLevel* level)
{
    PlayLayer* pRet = new PlayLayer();
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

PlayLayer::PlayLayer()
{
    
}

// bool PlayLayer::init(GJGameLevel* level)
// {
//     if (!CCLayer::init())
//         return false;
//     // GameEffectsManager TODO

//     GameManager* pGameManager = GameManager::sharedState();
//     pGameManager->setEditMode(false);
//     // pGameManager->setPlayLayer(this);
//     pGameManager->setWasHigh(false);

//     CCTextureCache* pTextureCache = CCTextureCache::sharedTextureCache();
//     CCSpriteBatchNode::createWithTexture(pTextureCache->addImage("GJ_GameSheet.png"), 29);
    
//     return true;
// }

bool PlayLayer::init(GJGameLevel* level) {
    if (!CCLayer::init())
        return false;

    GameManager* pGameManager = GameManager::sharedState();
}