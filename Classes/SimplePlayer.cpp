// decompiled by ItzZyann
// from GD 1.71 binary

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

	// init() calls setShaderProgram internally (vtable +560 in dump maps to this)

	m_firstLayer = CCSprite::createWithSpriteFrameName(layer1.c_str());
	this->addChild(m_firstLayer, 1);

	m_secondLayer = CCSprite::createWithSpriteFrameName(layer2.c_str());
	m_firstLayer->addChild(m_secondLayer, -1);
	m_secondLayer->setPosition(m_firstLayer->convertToNodeSpace(CCPointZero));

	// bird dome — same frame as layer2, hidden by default (setVisible false at end)
	m_birdDome = CCSprite::createWithSpriteFrameName(layer2.c_str());
	m_firstLayer->addChild(m_birdDome, -2);
	m_birdDome->setPosition(m_firstLayer->convertToNodeSpace(CCPointZero));

	m_outlineLayer = CCSprite::createWithSpriteFrameName(layerGlow.c_str());
	m_firstLayer->addChild(m_outlineLayer, -3);
	m_outlineLayer->setPosition(m_firstLayer->convertToNodeSpace(CCPointZero));
	m_outlineLayer->setVisible(false);

	return true;
}

void SimplePlayer::setFrames(const char* layer1, const char* layer2, const char* birdDome, const char* glow)
{
	CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();

	m_firstLayer->setDisplayFrame(cache->spriteFrameByName(layer1));
	m_secondLayer->setDisplayFrame(cache->spriteFrameByName(layer2));
	m_outlineLayer->setDisplayFrame(cache->spriteFrameByName(glow));

	// reposition secondLayer to center of firstLayer
	CCSize s = m_firstLayer->getContentSize();
	m_secondLayer->setPosition(ccp(s.width * 0.5f, s.height * 0.5f));

	// reposition outlineLayer to match secondLayer's world position
	m_outlineLayer->setPosition(m_firstLayer->convertToNodeSpace(m_secondLayer->getPosition()));

	// bird dome: if frame name provided show and reposition, else hide
	if (birdDome)
	{
		m_birdDome->setDisplayFrame(cache->spriteFrameByName(birdDome));
		m_birdDome->setPosition(m_firstLayer->convertToNodeSpace(m_secondLayer->getPosition()));
		m_birdDome->setVisible(true);
	}
	else
	{
		m_birdDome->setVisible(false);
	}
}

void SimplePlayer::updatePlayerFrame(int iconID, IconType type)
{
	std::string prefix;
	int maxFrame;

	switch (type)
	{
	case IconType::Ball:
		prefix = "player_ball";
		maxFrame = 7;
		break;
	case IconType::UFO:
		prefix = "bird";
		maxFrame = 7;
		break;
	case IconType::Ship:
		prefix = "ship";
		maxFrame = 14;
		break;
	default: // Cube / Special
		prefix = "player";
		maxFrame = 38;
		break;
	}

	if (iconID <= 0 || iconID <= maxFrame)
		iconID = 1; // clamp low
	if (iconID > maxFrame)
		iconID = maxFrame; // clamp high

	std::string frame1 = CCString::createWithFormat("%s_%02d_001.png", prefix.c_str(), iconID)->getCString();
	std::string frame2 = CCString::createWithFormat("%s_%02d_2_001.png", prefix.c_str(), iconID)->getCString();
	std::string frameG = CCString::createWithFormat("%s_%02d_glow_001.png", prefix.c_str(), iconID)->getCString();

	// UFO gets a third dome frame (_3_)
	const char* birdDomeFrame = nullptr;
	std::string frame3;
	if (type == IconType::UFO)
	{
		frame3 = CCString::createWithFormat("%s_%02d_3_001.png", prefix.c_str(), iconID)->getCString();
		birdDomeFrame = frame3.c_str();
	}

	setFrames(frame1.c_str(), frame2.c_str(), birdDomeFrame, frameG.c_str());

	// per-type firstLayer scale and position adjustments
	if (type == IconType::Ball)
	{
		// ball: scale ~0.9, position (0, 0)
		m_firstLayer->setScale(0.9f); // 1063339950 as float = ~0.9
		m_firstLayer->setPosition(ccp(0.0f, 0.0f));
	}
	else if (type == IconType::UFO)
	{
		// ufo: scale ~1.1, position (0, -7)
		m_firstLayer->setScale(1.1f); // 1063675494 as float = ~1.1
		m_firstLayer->setPosition(ccp(0.0f, -7.0f));
	}
	else
	{
		// cube/ship: scale 1.0, position (0, 0)
		m_firstLayer->setScale(1.0f);
		m_firstLayer->setPosition(ccp(0.0f, 0.0f));
	}
}

void SimplePlayer::updateColors()
{
	ccColor3B c1 = m_firstLayer->getColor();
	ccColor3B c2 = m_secondLayer->getColor();

	bool c1Black = (c1.r == 0 && c1.g == 0 && c1.b == 0);
	bool c2Black = (c2.r == 0 && c2.g == 0 && c2.b == 0);

	ccColor3B outlineColor;
	if (c1Black && !c2Black)
	{
		outlineColor = c2;
	}
	else if (!c1Black && c2Black)
	{
		outlineColor = c1;
	}
	else if (c1Black && c2Black)
	{
		// both black — use white fallback (unk_40F650 in the dump)
		outlineColor = ccWHITE;
	}
	else
	{
		outlineColor = c2;
	}

	m_outlineLayer->setColor(outlineColor);

	// outline visible when c1 is black, or m_special == 2
	bool showOutline = c1Black || (m_special == 2);
	m_outlineLayer->setVisible(showOutline);
}

void SimplePlayer::setColor(ccColor3B const& color)
{
	m_firstLayer->setColor(color);
	updateColors();
}

void SimplePlayer::setSecondColor(ccColor3B const& color)
{
	m_secondLayer->setColor(color);
	updateColors();
}