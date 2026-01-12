#include "PlayerObject.h"
#include "GameManager.h"
USING_NS_CC;

PlayerObject* PlayerObject::create(int player, int ship, cocos2d::CCLayer *layer)
{
    PlayerObject* pRet = new PlayerObject();
    if (pRet && pRet->init(player, ship, layer))
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

bool PlayerObject::init(int player, int ship, cocos2d::CCLayer *layer) {
    int playerIdx;
    int shipIdx;
    
    if (player >= 38) playerIdx = 38;
    else playerIdx = player;
    if (player <=0) playerIdx = 1;
    
    if (ship >= 14) shipIdx = 14;
    else shipIdx = ship;
    if (ship <=0) shipIdx = 1;
    
    std::string frameFile = CCString::createWithFormat("player_%02d_001.png", playerIdx)->getCString();
    std::string frameFile2 = CCString::createWithFormat("player_%02d_2_001.png", playerIdx)->getCString();
    
	if (!GameObject::init(frameFile.c_str())) return false;
	
	m_ghostType = GhostType::Disabled;
	// field800_0x38c = 0.9;  i suppose this might be m_timeMod, but it isn't listed in the geode docs

	if (!layer)
		m_layer = PLAY_LAYER;

    this->setPosition({100, 100});
    
    return true;
}