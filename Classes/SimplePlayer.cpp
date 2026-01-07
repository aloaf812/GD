#include "SimplePlayer.h"
USING_NS_CC;

SimplePlayer::SimplePlayer()
{
    
}

SimplePlayer* SimplePlayer::create(int iconID)
{
    SimplePlayer* pRet = new SimplePlayer();
    if (pRet && pRet->init(iconID))
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

// basically "borrowed" from WylieMaster: https://github.com/Wyliemaster/GD-Decompiled/blob/main/GD/code/src/SimplePlayer.cpp#L31
bool SimplePlayer::init(int iconID)
{
    if (!CCSprite::init())
        return false;
    
    int id = std::min(iconID, 38) <= 0 ? 1 : std::min(iconID, 38);
    
    std::string layer1 = cocos2d::CCString::createWithFormat("player_%02d_001.png", id)->m_sString;
    std::string layer2 = cocos2d::CCString::createWithFormat("player_%02d_2_001.png", id)->m_sString;
    std::string layerGlow = cocos2d::CCString::createWithFormat("player_%02d_glow_001.png", id)->m_sString;
    
    // setTextureRect(g_UnkRect);
    
    CCSprite* m_pPlayerSpriteLayer1 = cocos2d::CCSprite::createWithSpriteFrameName(layer1.c_str());
    CCSprite* m_pPlayerSpriteLayer2 = cocos2d::CCSprite::createWithSpriteFrameName(layer2.c_str());
    
    m_pPlayerSpriteLayer1->addChild(m_pPlayerSpriteLayer2, -1);
    m_pPlayerSpriteLayer2->setPosition(CCPoint(0.0f, 0.0f));
    // m_pPlayerSpriteLayer2->setPosition(m_pPlayerSpriteLayer1->convertToNodeSpace(g_obUnknownGlobal));
    
    CCSprite* m_pPlayerSpriteBirdDome = cocos2d::CCSprite::createWithSpriteFrameName(layer2.c_str());
    m_pPlayerSpriteLayer1->addChild(m_pPlayerSpriteBirdDome, -2);
    // m_pPlayerSpriteBirdDome->setPosition(m_pPlayerSpriteLayer1->convertToNodeSpace(g_obUnknownGlobal));
    
    CCSprite* m_pPlayerSpriteGlow = cocos2d::CCSprite::createWithSpriteFrameName(layerGlow.c_str());
    m_pPlayerSpriteLayer1->addChild(m_pPlayerSpriteGlow, -3);
    // m_pPlayerSpriteGlow->setPosition(m_pPlayerSpriteLayer1->convertToNodeSpace(g_obUnknownGlobal));
    m_pPlayerSpriteGlow->setVisible(false);
    
    CCSprite* m_pPlayerSpriteDetail = cocos2d::CCSprite::createWithSpriteFrameName(layerGlow.c_str());
    m_pPlayerSpriteLayer1->addChild(m_pPlayerSpriteDetail, 1);
    // m_pPlayerSpriteDetail->setPosition(m_pPlayerSpriteLayer1->convertToNodeSpace(g_obUnknownGlobal));
    // updatePlayerFrame(id, 0);
    return true;
}