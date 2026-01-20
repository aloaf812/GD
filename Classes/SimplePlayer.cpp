#include "SimplePlayer.h"
USING_NS_CC;

SimplePlayer::SimplePlayer()
{
    
}

SimplePlayer* SimplePlayer::create(int iconID)
{
	auto pRet = new SimplePlayer;

	if (pRet && pRet->init(iconID))
	{
		pRet->autorelease();
		return pRet;
	}

	CC_SAFE_DELETE(pRet);
	return nullptr;
}

// basically "borrowed" from WylieMaster: https://github.com/Wyliemaster/GD-Decompiled/blob/main/GD/code/src/SimplePlayer.cpp#L31
bool SimplePlayer::init(int iconID)
{
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
    int id = std::min(iconID, 38) <= 0 ? 1 : std::min(iconID, 38);
#else
	int id = (std::min)(iconID, 38) <= 0 ? 1 : (std::min)(iconID, 38);
#endif
    std::string layer1 = CCString::createWithFormat("player_%02d_001.png", id)->getCString();
    std::string layer2 = CCString::createWithFormat("player_%02d_2_001.png", id)->getCString();
    std::string layerGlow = CCString::createWithFormat("player_%02d_glow_001.png", id)->getCString();
    
	if (!CCSprite::init())
		return false;
    
	m_firstLayer = CCSprite::createWithSpriteFrameName(layer1.c_str());
	this->addChild(m_firstLayer, 1);
	m_secondLayer = CCSprite::createWithSpriteFrameName(layer2.c_str());
	m_firstLayer->addChild(m_secondLayer, -1);
	m_secondLayer->setPosition(m_firstLayer->getContentSize() / 2);
    
	/*CCSprite* m_pPlayerSpriteBirdDome = cocos2d::CCSprite::createWithSpriteFrameName(layer2.c_str());
    m_pPlayerSpriteLayer1->addChild(m_pPlayerSpriteBirdDome, -2);
    // m_pPlayerSpriteBirdDome->setPosition(m_pPlayerSpriteLayer1->convertToNodeSpace(g_obUnknownGlobal));
    
	//m_outlineLayer = cocos2d::CCSprite::createWithSpriteFrameName(layerGlow.c_str());
	//m_firstLayer->addChild(m_outlineLayer, -3);
    // m_outlineLayer->setPosition(m_firstLayer->convertToNodeSpace(g_obUnknownGlobal));
	//m_outlineLayer->setVisible(false);
    
    m_pPlayerSpriteDetail = cocos2d::CCSprite::createWithSpriteFrameName(layerGlow.c_str());
    m_firstLayer->addChild(m_pPlayerSpriteDetail, 1);
    // m_pPlayerSpriteDetail->setPosition(m_pPlayerSpriteLayer1->convertToNodeSpace(g_obUnknownGlobal));*/
    return true;
}

void SimplePlayer::updatePlayerFrame(int iconID, IconType type)
{

}

void SimplePlayer::setSecondColor(ccColor3B const& color)
{

}