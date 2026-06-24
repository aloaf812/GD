#include "LevelPage.h"
#include "RT_COCOS/CCMenuItemSpriteExtra.h"
#include "cocos-ext.h"
#include "GameManager.h"
#include "GameLevelManager.h"
#include "GameSoundManager.h"
#include "FLAlertLayer.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
USING_NS_CC;
USING_NS_CC_EXT;

LevelPage* LevelPage::create(GJGameLevel* level)
{
    LevelPage* pRet = new LevelPage();
    if (pRet && pRet->init(level))
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

// the code situation has improved
bool LevelPage::init(GJGameLevel* level)
{
    if (!CCLayer::init())
        return false;
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();

    m_level = level;
    m_level->retain();
    
	// int userCoins = GameStatsManager::sharedState()->getStat("8");
	int reqCoins = m_level->getRequiredCoins();

	m_levelMenu = CCMenu::create();
	this->addChild(m_levelMenu, -1);
	m_levelMenu->setPosition(ccp(winSize.width * 0.5f, winSize.height * 0.5f + 60.0f));
    
    CCScale9Sprite* button = CCScale9Sprite::create("square02_001.png", CCRect(0, 0, 80, 80));
    button->setColor(ccc3(125,125,125));
    button->setOpacity(125);
    button->setContentSize(CCSize(340, 95));
    button->setPosition(ccp(winSize.width * 0.5f, winSize.height * 0.5f + 50.0f));
    
	CCSprite* buttonSpr = CCSprite::create();
	buttonSpr->addChild(button);
	buttonSpr->setContentSize(button->getContentSize());
	button->setPosition(ccp(button->getContentSize().width * 0.5f, button->getContentSize().height * 0.5f));

    CCMenuItemSpriteExtra* playExtra = CCMenuItemSpriteExtra::create(buttonSpr, NULL, this, menu_selector(LevelPage::onPlay));
    playExtra->setScaleVar(1.1f);
	m_levelMenu->addChild(playExtra);
    
    if (true) {
        
        auto nameLabel = CCLabelBMFont::create(m_level->getLevelName().c_str(), "bigFont.fnt");
        nameLabel->setAnchorPoint(ccp(0, 0.5f));
        nameLabel->setPosition(ccp(65, 47.5f));
        button->addChild(nameLabel);
        
        if (nameLabel->getContentSize().width > 250.0f)
            nameLabel->setScale(250.0f / nameLabel->getContentSize().width);
		nameLabel->setScale((std::min)(nameLabel->getScale(), 1.0f));
        
        auto diffStr = CCString::createWithFormat("diffIcon_%02d_btn_001.png", m_level->getDifficulty());
        auto diffSpr = CCSprite::createWithSpriteFrameName(diffStr->getCString());
        diffSpr->setScale(1.1f);
        diffSpr->setPosition(ccp(35.75, 47.5f));
        button->addChild(diffSpr);
        
        if (m_level->getStars() > 0) {
            auto starIcon = CCSprite::createWithSpriteFrameName("GJ_starsIcon_001.png");
            starIcon->setScale(0.6f);
            starIcon->setPosition(ccp(325, 82));
            button->addChild(starIcon);
            
            auto starText = CCString::createWithFormat("%i", m_level->getStars());
            auto label = CCLabelBMFont::create(starText->getCString(), "bigFont.fnt");
            
            label->setAnchorPoint(ccp(1, 0.5f));
            label->setScale(0.5f);
            label->setPosition(starIcon->getPosition() + CCPoint(-12, 0));
            button->addChild(label);
        }
    } else {
        
    }
    
	
	CCSprite* normalBar = CCSprite::create("GJ_progressBar_001.png");
	normalBar->setColor(ccBLACK);
	normalBar->setOpacity(125);
	normalBar->setScale(1.0f);
	this->addChild(normalBar, 3);
	normalBar->setPosition(ccp(winSize.width * 0.5f, (winSize.height * 0.5f) - 30.0f));
	
	CCSprite* normalFill = CCSprite::create("GJ_progressBar_001.png");
	normalFill->setScaleX(0.992f);
	normalFill->setScaleY(0.86f);
	normalFill->setColor(ccGREEN);
	normalBar->addChild(normalFill, 1);
	normalFill->setAnchorPoint(ccp(0.0f, 0.5f));
	CCSize nbContSize = normalBar->getContentSize();
	normalFill->setPosition(ccp((nbContSize.width - nbContSize.width * 0.992f) * 0.5f, nbContSize.height * 0.5f));


	CCSprite* practiceBar = CCSprite::create("GJ_progressBar_001.png");
	practiceBar->setColor(ccBLACK);
	practiceBar->setOpacity(125);
	practiceBar->setScale(1.0f);
	this->addChild(practiceBar, 3);
	practiceBar->setPosition(normalBar->getPosition() + ccp(0.0f, -50.0f));

	CCSprite* practiceFill = CCSprite::create("GJ_progressBar_001.png");
	practiceFill->setScaleX(0.992f);
	practiceFill->setScaleY(0.86f);
	practiceFill->setColor(ccc3(0, 255, 255));
	practiceBar->addChild(practiceFill, 1);
	practiceFill->setAnchorPoint(ccp(0.0f, 0.5f));
	practiceFill->setPosition(normalFill->getPosition());

	// some missing stuff that i need to add in
	
	CCLabelBMFont* normalPct = CCLabelBMFont::create(
		CCString::createWithFormat("%i%%", level->getNormalPercent())->getCString(),
		"bigFont.fnt");
	this->addChild(normalPct, 4);
	normalPct->setPosition(normalBar->getPosition());
	normalPct->setScale(0.5f);

	CCLabelBMFont* practicePct = CCLabelBMFont::create(
		CCString::createWithFormat("%i%%", level->getPracticePercent())->getCString(),
		"bigFont.fnt");
	this->addChild(practicePct, 4);
	practicePct->setPosition(practiceBar->getPosition());
	practicePct->setScale(0.5f);
	
	// missing the other one too

	CCLabelBMFont* normalLabel = CCLabelBMFont::create("Normal Mode", "bigFont.fnt");
	this->addChild(normalLabel, 4);
	normalLabel->setPosition(ccp(0.0f, 20.0f) + normalPct->getPosition());
	normalLabel->setScale(0.5f);

	CCLabelBMFont* practiceLabel = CCLabelBMFont::create("Practice Mode", "bigFont.fnt");
	this->addChild(practiceLabel, 4);
	practiceLabel->setPosition(ccp(0.0f, 20.0f) + practicePct->getPosition());
	practiceLabel->setScale(0.5f);
    
    int coinCount = m_level->getCoins();
    CCPoint basePos(324, 16);
    
    for (int i = 1; i <= coinCount; i++) {
        bool hasCoin = false;
        char const* icon = hasCoin ? "GJ_coinsIcon_001.png" : "GJ_coinsIcon_gray_001.png";
        auto coin = CCSprite::createWithSpriteFrameName(icon);
        coin->setPosition(basePos + CCPoint((coinCount - i) * -26.0f, 0));
        button->addChild(coin);
    }
    
    // collected star text: 255, 255, 50
    
    return true;
}

void LevelPage::onInfo(cocos2d::CCObject* sender)
{
    // WIP
	FLAlertLayer::create(nullptr, "Level Stats", "insert string here", "OK", nullptr, 300.0f)->show();
}

void LevelPage::onPlay(cocos2d::CCObject* sender)
{
    // GameStatsManager* GStatsM = GameStatsManager::GameStatsManager();
    SimpleAudioEngine* SAE = SimpleAudioEngine::sharedEngine();
    SAE->stopBackgroundMusic();
    
	GameSoundManager* GSoundM = GameSoundManager::sharedManager();
	GSoundM->playEffect("playSound_01.ogg", 1.0f, 0.0f, 0.3f);

    GameManager* pGameManager = GameManager::sharedState();
    pGameManager->setLastScene(LastGameScene::LevelSelect);
    
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCScene* pScene = PlayLayer::scene(m_level);
    CCTransitionFade* fade = CCTransitionFade::create(0.5f, pScene);
    pDirector->replaceScene(fade);
    return;
}