#include "AchievementBar.h"
#include "AchievementNotifier.h"
#include "SimplePlayer.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

AchievementBar::AchievementBar()
{
	m_targetScene = nullptr;
}

AchievementBar* AchievementBar::create(char const* title, char const* description, char const* icon)
{
    AchievementBar* pRet = new AchievementBar();
    if (pRet && pRet->init(title, description, icon))
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

// gonna have to redecompile this entire function again...
bool AchievementBar::init(char const* title, char const* description, char const* icon)
{
	CCLOG("creating achievement bar for %s", title);
	CCDirector* pDirector = CCDirector::sharedDirector();
	CCSize winSize = pDirector->getWinSize();

	this->m_layerColor = CCLayerColor::create(ccc4(0, 0, 0, 0));
	this->addChild(m_layerColor);

	CCScale9Sprite* box = CCScale9Sprite::create("GJ_square01.png", CCRect(0, 0, 80, 80));
	box->setPosition(ccp(winSize.width / 2, pDirector->getScreenTop() - 50));
	box->setContentSize(CCSize(300, 70));
	m_layerColor->addChild(box);

	CCSprite* playerSquare = CCSprite::createWithSpriteFrameName("playerSquare_001.png");
	if (icon)
	{
		char const* item = "color";
		if (true)
		{
			char const* descString = CCString::createWithFormat("Unlocked new %s!", item)->getCString();
			SimplePlayer* achIcon = SimplePlayer::create(1);
			achIcon->updatePlayerFrame(1, IconType::Cube);
			m_layerColor->addChild(achIcon);
			/*local_11c = 175;
			local_11b = 175;
			local_11a = 175;
			(**(code **)(*(int *)pSVar10 + 0x1cc))(pSVar10, &local_11c);*/
			achIcon->setSecondColor(ccc3(255, 255, 255));
		}
		else 
		{

		}
	}

	// CCSprite* gkIcon = CCSprite::create("gk-icon.png");  this is literally just a checkmark and idk when it is shown

	CCLabelBMFont* titleText = CCLabelBMFont::create(title, "bigFont.fnt");
	titleText->setPosition(ccp(winSize.width / 2, pDirector->getScreenTop() - 50));
	this->addChild(titleText);

	if (200.0f < titleText->getContentSize().width)
	{
		titleText->setScale(200.0f / titleText->getContentSize().width);
	}

	float textScale;
	if (titleText->getScale() <= 0.7f)
	{
		textScale = titleText->getScale();
	}
	else
	{
		textScale = 0.7f;
	}

	titleText->setScale(textScale);

	m_screenOffset = 74.0f;

	return true;
}

void AchievementBar::show()
{
	CCNode* scene = CCDirector::sharedDirector()->getRunningScene();
	
	if (m_targetScene != nullptr)
		scene = m_targetScene;

	scene->addChild(this, 105);

	// the animation
	CCMoveBy* moveIn = CCMoveBy::create(1.0f, ccp(0.0f, -m_screenOffset));
	CCEaseInOut* easeIn = CCEaseInOut::create(moveIn, 2.0f);
	CCDelayTime* delay = CCDelayTime::create(1.5f);
	CCMoveBy* moveOut = CCMoveBy::create(1.0f, ccp(0.0f, m_screenOffset));
	CCEaseInOut* easeOut = CCEaseInOut::create(moveOut, 2.0f);
	CCCallFunc* callback = CCCallFunc::create(AchievementNotifier::sharedState(), callfunc_selector(AchievementNotifier::achievementDisplayFinished));
	m_layerColor->runAction(CCSequence::create(easeIn, delay, easeOut, nullptr));
}