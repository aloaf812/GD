#include "EndLevelLayer.h"
#include "GameManager.h"
#include "GameSoundManager.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;

char const* EndLevelLayer::getEndText()
{
    int idx = rand() % 7;
    switch(idx) {
    case 2: return "Good Job!"; break;
    case 3: return "Well Done!"; break;
    case 4: return "Impressive!"; break;
    case 5: return "Amazing!"; break;
    case 6: return "Incredible!"; break;
    case 7: return "Skillful!"; break;
    default: return "Awesome!";
    }
}

void EndLevelLayer::onMenu(CCObject* sender)
{
	PLAY_LAYER->onQuit();
	this->exitLayer(false);
	GameSoundManager::sharedManager()->playEffect("quitSound_01.ogg", 1.0f, 0.0f, 0.7f);
}

void EndLevelLayer::onReplay(CCObject* sender)
{
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(false);
	GameSoundManager::sharedManager()->playEffect("playSound_01.ogg", 1.0f, 0.0f, 0.3f);
	this->exitLayer(false);
	
	PLAY_LAYER->runAction(CCSequence::create(CCDelayTime::create(0.5f), CCCallFunc::create(PLAY_LAYER, callfunc_selector(PlayLayer::fullReset)), nullptr));
}


void EndLevelLayer::onEveryplay(CCObject* sender) {}