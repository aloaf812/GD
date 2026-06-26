// decompiled by ItzZyann
// from GD 1.71 binary

#include "AchievementBar.h"
#include "AchievementNotifier.h"
#include "GameManager.h"
#include "SimplePlayer.h"
#include "TextArea.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

AchievementBar::AchievementBar()
	: m_layerColor(nullptr)
	, m_targetScene(nullptr)
	, m_screenOffset(0.0f)
{
}

AchievementBar* AchievementBar::create(char const* title, char const* description, char const* icon)
{
	AchievementBar* pRet = new AchievementBar();
	if (pRet && pRet->init(title, description, icon))
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return nullptr;
}

bool AchievementBar::init(char const* title, char const* description, char const* icon)
{
	if (!CCNodeRGBA::init()) return false;

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	m_layerColor = CCLayerColor::create(ccc4(0, 0, 0, 0), winSize.width, 80.0f);
	this->addChild(m_layerColor);
	m_layerColor->setPosition(ccp(0.0f, CCDirector::sharedDirector()->getScreenTop() + 2.0f));

	CCScale9Sprite* bg = CCScale9Sprite::create("GJ_square01.png", CCRectMake(0, 0, 80, 80));
	bg->setContentSize(CCSize(300.0f, 70.0f));
	m_layerColor->addChild(bg, 1);
	bg->setPosition(ccp(winSize.width * 0.5f, 35.0f));

	CCSprite* measureSprite = CCSprite::createWithSpriteFrameName("playerSquare_001.png");

	CCNode* iconNode = nullptr;
	const char* unlockStr = nullptr;

	if (icon && strlen(icon) > 0)
	{
		CCArray* parts = CCArray::create();
		std::string iconStr(icon), seg;
		for (size_t i = 0; i <= iconStr.size(); ++i)
		{
			if (i == iconStr.size() || iconStr[i] == '_')
			{
				if (!seg.empty()) { parts->addObject(CCString::create(seg.c_str())); seg.clear(); }
			}
			else seg += iconStr[i];
		}

		if (parts->count() > 1)
		{
			const char* typeStr = static_cast<CCString*>(parts->objectAtIndex(0))->getCString();
			int idx = static_cast<CCString*>(parts->objectAtIndex(1))->intValue();

			bool isColor = (strcmp(typeStr, "color") == 0 || strcmp(typeStr, "color2") == 0);
			if (isColor)
			{
				unlockStr = "Unlocked new Color!";
				measureSprite->setColor(GameManager::sharedState()->colorForIdx(idx - 1));
				iconNode = measureSprite;
			}
			else
			{
				int playerType;
				if (strcmp(typeStr, "ship") == 0) { playerType = 1; unlockStr = CCString::createWithFormat("Unlocked new %s!", "Ship")->getCString(); }
				else if (strcmp(typeStr, "ball") == 0) { playerType = 2; unlockStr = CCString::createWithFormat("Unlocked new %s!", "Ball")->getCString(); }
				else if (strcmp(typeStr, "bird") == 0) { playerType = 3; unlockStr = CCString::createWithFormat("Unlocked new %s!", "UFO")->getCString(); }
				else { playerType = 0; unlockStr = CCString::createWithFormat("Unlocked new %s!", "Icon")->getCString(); }

				SimplePlayer* sp = SimplePlayer::create(1);
				sp->updatePlayerFrame(idx, static_cast<IconType>(playerType));
				sp->setColor(ccc3(0xAF, 0xAF, 0xAF));
				sp->setSecondColor(ccc3(0xFF, 0xFF, 0xFF));
				iconNode = sp;
			}
		}
		else goto use_fallback;
	}
	else
	{
	use_fallback:
		CCSprite* fallback = CCSprite::create("gk-icon.png");
		fallback->setColor(ccc3(0, 0, 0));
		fallback->setZOrder(100);
		iconNode = fallback;
	}

	iconNode->setPosition(ccp(40.0f, 35.0f));
	m_layerColor->addChild(iconNode, 3);

	CCNode* textNode = CCNode::create();
	m_layerColor->addChild(textNode, 2);

	CCLabelBMFont* titleLabel = CCLabelBMFont::create(title, "bigFont.fnt");
	textNode->addChild(titleLabel);
	titleLabel->setAnchorPoint(ccp(0.0f, 0.5f));
	titleLabel->setScale(0.7f);
	float titleW = titleLabel->getContentSize().width;
	if (titleW > 200.0f)
		titleLabel->setScale(200.0f / titleW);
	if (titleLabel->getScale() < 0.7f)
		titleLabel->setScale(0.7f);

	const char* descText = unlockStr ? unlockStr : description;

	// fok this textarea T-T
	// its soo buggy
	TextArea* descLabel = TextArea::create(descText, 200.0f, 0, ccp(0.0f, 1.0f), "chatFont.fnt");
	textNode->addChild(descLabel);
	descLabel->setAnchorPoint(ccp(0.0f, 0.5f));

	float titleH = titleLabel->getContentSize().height;
	float descH = descLabel->getContentSize().height + 17.0f;
	float midH = (titleH + descH) * 0.5f;
	titleLabel->setPosition(ccp(0.0f, (midH - titleH * 0.5f) + 2.0f));
	descLabel->setPosition(ccp(1.0f, 15.0f - (midH - descH * 0.5f) - 1.0f));

	measureSprite->setScale(1.0f);
	iconNode->setScale(1.0f);

	float squareW = measureSprite->getContentSize().width;
	float titleScaledW = titleLabel->getContentSize().width * titleLabel->getScaleX();
	float descW = descLabel->getContentSize().width;
	float textBlockW = ((titleScaledW >= descW) ? titleScaledW : descW) + 5.0f;

	float totalW = squareW * 0.5f + textBlockW + 30.0f;
	float iconX = (winSize.width * 0.5f) - (totalW * 0.5f) + (squareW * 0.5f);
	iconNode->setPosition(ccp(iconX, 35.0f));
	textNode->setPosition(ccp(iconNode->getPositionX() + 30.0f, 35.0f));

	m_screenOffset = 74.0f;

	return true;
}

void AchievementBar::show()
{
	CCMoveBy* moveIn = CCMoveBy::create(1.0f, ccp(0, -m_screenOffset));
	CCEaseInOut* easeIn = CCEaseInOut::create(moveIn, 2.0f);
	CCDelayTime* delay = CCDelayTime::create(2.0f);
	CCMoveBy* moveOut = CCMoveBy::create(1.0f, ccp(0, m_screenOffset));
	CCEaseInOut* easeOut = CCEaseInOut::create(moveOut, 2.0f);

	CCCallFunc* callback = CCCallFunc::create(
		AchievementNotifier::sharedState(),
		callfunc_selector(AchievementNotifier::achievementDisplayFinished));

	m_layerColor->runAction(CCSequence::create(easeIn, delay, easeOut, callback, nullptr));
}