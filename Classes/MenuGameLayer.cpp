#include "MenuGameLayer.h"
#include "GameManager.h"
USING_NS_CC;

MenuGameLayer* MenuGameLayer::create() {
    MenuGameLayer* ret = new MenuGameLayer();
    if (ret) {
        if (ret->init()) {
            ret->autorelease();
            return ret;
        }

        delete ret;
    }

    return NULL;
}

bool MenuGameLayer::init()
{
    if (!CCLayer::init())
        return false;
    
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCSize winSize = pDirector->getWinSize();
    GameManager* pGameManager = GameManager::sharedState();
   
    CCSprite* floorLine = CCSprite::createWithSpriteFrameName("floorLine_001.png");
    this->addChild(floorLine, 3);
    floorLine->setPosition(CCPoint(winSize.width * 0.5f, pDirector->getScreenBottom() + 75.0f));

    return true;
}