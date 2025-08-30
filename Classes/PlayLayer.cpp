#include "PlayLayer.h"
#include "SimpleAudioEngine.h"
#include "GameManager.h"
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