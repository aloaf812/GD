#include "AchievementBar.h"
#include "SimplePlayer.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

AchievementBar::AchievementBar()
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
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

bool AchievementBar::init(char const* title, char const* description, char const* icon)
{
	CCLOG("creating achievement bar for %s", title);
	CCDirector* pDirector = CCDirector::sharedDirector();
	CCSize winSize = pDirector->getWinSize();

	CCScale9Sprite* box = CCScale9Sprite::create("GJ_square01.png", CCRect(0, 0, 80, 80));
	box->setPosition({ winSize.width / 2, pDirector->getScreenTop() - 50 });
	box->setContentSize({ 300, 70 });
	this->addChild(box);

	CCSprite* playerSquare = CCSprite::createWithSpriteFrameName("playerSquare_001.png");
	if (icon)
	{
		char const* item = "color";
		if (true)
		{
			char const* descString = CCString::createWithFormat("Unlocked new %s!", item)->getCString();
			SimplePlayer* achIcon = SimplePlayer::create(1);
			achIcon->updatePlayerFrame(1, IconType::Cube);
			this->addChild(achIcon);
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
	titleText->setPosition({ winSize.width / 2, pDirector->getScreenTop() - 50 });
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

	return true;
}

void AchievementBar::show()
{
	CCNode* scene = CCDirector::sharedDirector()->getRunningScene();
	scene->addChild(this);
}

CCNode* AchievementBar::getTargetScene() { return m_targetScene; }

void AchievementBar::setTargetScene(CCNode* var) { m_targetScene = var; }