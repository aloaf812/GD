#include "MenuGameLayer.h"
#include "GameManager.h"
#include "AppDelegate.h"
USING_NS_CC;

MenuGameLayer::MenuGameLayer() {
    float m_deltaCount = 0.f;
    bool m_isDestroyingPlayer = false;
    int m_initCount = 0;
    CCPoint m_unused1{};
    PlayerObject* m_playerObject = nullptr;
    CCSprite* m_backgroundSprite = nullptr;
    GJGroundLayer* m_groundLayer = nullptr;
    float m_backgroundSpeed = 0.0f;
}
    
MenuGameLayer* MenuGameLayer::create() {
    auto ret = new MenuGameLayer();
    if (ret->init()) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

bool MenuGameLayer::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    GameManager* pGameManager = GameManager::sharedState();
    
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCSize winSize = pDirector->getWinSize();
    
    const char* bgTextureName = pGameManager->getBGTexture(1);
    m_backgroundSprite = CCSprite::create(bgTextureName);
    this->addChild(m_backgroundSprite);
    
    m_backgroundSprite->setPosition(winSize * 0.5f);
    m_backgroundSprite->setScale(AppDelegate::get()->bgScale());
    ccColor3B bgColor = { 0, 102, 255 };
    m_backgroundSprite->setColor(bgColor);
    
    CCSprite* lineSprite = CCSprite::createWithSpriteFrameName("floorLine_001.png");
    this->addChild(lineSprite);
    
    lineSprite->setPosition(CCPoint(winSize.width * 0.5f, pDirector->getScreenBottom() + 90.0f));
    
    return true;
}

void MenuGameLayer::update(float delta)
{
    
}