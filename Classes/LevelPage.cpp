#include "LevelPage.h"
#include "RT_COCOS/CCMenuItemSpriteExtra.h"
#include "cocos-ext.h"
#include "GameManager.h"
#include "GameLevelManager.h"
#include "GameSoundManager.h"
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

// this function is genuinely written so bad it makes ObjectToolbox::init look good
bool LevelPage::init(GJGameLevel* level)
{
    if (!CCLayer::init())
        return false;
    
    m_level = level;
    m_level->retain();
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    auto menu = CCMenu::create();
    menu->setPosition(CCPointZero);
    this->addChild(menu, -1);
    
    CCScale9Sprite* button = CCScale9Sprite::create("square02_001.png", CCRect(0, 0, 80, 80));
    button->setColor(ccc3(125,125,125));
    button->setOpacity(125);
    button->setContentSize({340, 95});
    button->setPosition({winSize.width / 2, winSize.height / 2 + 50});
    this->addChild(button);
    
    auto buttonSpr = CCSprite::create();
    CCMenuItemSpriteExtra* playExtra = CCMenuItemSpriteExtra::create(buttonSpr, NULL, this, menu_selector(LevelPage::onPlay));
    playExtra->setScale(0.8f);
    playExtra->setPosition(button->getContentSize() / 2);
    menu->addChild(playExtra);
    
    auto buttonSpr2 = CCSprite::createWithSpriteFrameName("GJ_playBtn2_001.png");
    CCMenuItemSpriteExtra* playExtra2 = CCMenuItemSpriteExtra::create(buttonSpr2, NULL, this, menu_selector(LevelPage::onPlay));
    playExtra2->setScale(0.8f);
    playExtra2->setPosition(button->getContentSize() / 2);
    menu->addChild(playExtra2);
    
    if (true) {
        
        auto nameLabel = CCLabelBMFont::create(m_level->getLevelName().c_str(), "bigFont.fnt");
        nameLabel->setAnchorPoint({0, 0.5f});
        nameLabel->setPosition(ccp(65, 47.5f));
        button->addChild(nameLabel);
        
        if (nameLabel->getContentSize().width > 250.0f)
            nameLabel->setScale(250.0f / nameLabel->getContentSize().width);
		nameLabel->setScale((std::min)(nameLabel->getScale(), 1.0f));
        
        auto diffStr = CCString::createWithFormat("diffIcon_%02d_btn_001.png", m_level->getDifficulty());
        auto diffSpr = CCSprite::createWithSpriteFrameName(diffStr->getCString());
        diffSpr->setScale(1.1f);
        diffSpr->setPosition({35.75, 47.5f});
        button->addChild(diffSpr);
        
        if (m_level->getStars() > 0) {
            auto starIcon = CCSprite::createWithSpriteFrameName("GJ_starsIcon_001.png");
            starIcon->setScale(0.6f);
            starIcon->setPosition(ccp(325, 82));
            button->addChild(starIcon);
            
            auto starText = CCString::createWithFormat("%i", m_level->getStars());
            auto label = CCLabelBMFont::create(starText->getCString(), "bigFont.fnt");
            
            label->setAnchorPoint({1, 0.5f});
            label->setScale(0.5f);
            label->setPosition(starIcon->getPosition() + CCPoint(-12, 0));
            button->addChild(label);
        }
    } else {
        
    }
    
	CCSprite* normalBar = CCSprite::create("GJ_progressBar_001.png");
	normalBar->setColor(ccc3(0, 0, 0));
	normalBar->setOpacity(125);
	normalBar->setPosition(winSize / 2 + ccp(0.0f, -30.0f));
	this->addChild(normalBar, 3);

	auto normalFill = CCSprite::create("GJ_progressBar_001.png");
	normalFill->setScaleX(0.992f);
	normalFill->setScaleY(0.86f);
	normalFill->setPosition(ccp(normalBar->getContentSize().width - (normalFill->getContentSize().width * normalFill->getScaleX() / 2), normalBar->getContentSize().height / 2));
	normalFill->setAnchorPoint(ccp(0.0f, 0.5f));
	normalFill->setColor(ccGREEN);

	float fullWidth1 = normalFill->getContentSize().width * normalFill->getScaleX();
	// tmp percent idk if its right lol
	float actualWidth1 = fullWidth1 * (46 / 100.0f);
	normalFill->setTextureRect(CCRect(0, 0, actualWidth1, normalFill->getContentSize().height));
	normalBar->addChild(normalFill);

	CCSprite* practiceBar = CCSprite::create("GJ_progressBar_001.png");
	practiceBar->setColor(ccc3(0, 0, 0));
	practiceBar->setOpacity(125);
	practiceBar->setPosition(winSize / 2 + ccp(0.0f, -80.0f));
	this->addChild(practiceBar, 3);

	auto practiceFill = CCSprite::create("GJ_progressBar_001.png");
	practiceFill->setScaleX(0.992f);
	practiceFill->setScaleY(0.86f);
	practiceFill->setPosition(ccp(practiceBar->getContentSize().width - (practiceFill->getContentSize().width * practiceFill->getScaleX() / 2), practiceBar->getContentSize().height / 2));
	practiceFill->setAnchorPoint(ccp(0.0f, 0.5f));
	practiceFill->setColor(ccc3(0, 255, 255));

	float fullWidth2 = practiceFill->getContentSize().width * practiceFill->getScaleX();
	// tmp percent idk if its right lol
	float actualWidth2 = fullWidth2 * (56 / 100.0f);
	practiceFill->setTextureRect(CCRect(0, 0, actualWidth2, practiceFill->getContentSize().height));
	practiceBar->addChild(practiceFill);


	CCLabelBMFont* lbl1 = CCLabelBMFont::create(CCString::createWithFormat("%i%%", 43)->getCString(), "bigFont.fnt");
	lbl1->setScale(0.5f);
	lbl1->setPosition(normalBar->getPosition());
	this->addChild(lbl1, 4);

	CCLabelBMFont* lbl2 = CCLabelBMFont::create(CCString::createWithFormat("%i%%", 56)->getCString(), "bigFont.fnt");
	lbl2->setScale(0.5f);
	lbl2->setPosition(practiceBar->getPosition());
	this->addChild(lbl2, 4);
    
    auto normalLabel = CCLabelBMFont::create("Normal Mode", "bigFont.fnt");
    normalLabel->setScale(0.5f);
    normalLabel->setPosition(normalBar->getPosition() + CCPoint(0, 20));
    this->addChild(normalLabel, 4);
    
    auto practiceLabel = CCLabelBMFont::create("Practice Mode", "bigFont.fnt");
    practiceLabel->setScale(0.5f);
    practiceLabel->setPosition(practiceBar->getPosition() + CCPoint(0, 20));
    this->addChild(practiceLabel, 4);
    
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
    // implement
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
    CCScene* pScene = PlayLayer::scene(GameLevelManager::sharedState()->getMainLevel(2));
    CCTransitionFade* fade = CCTransitionFade::create(0.5f, pScene);
    pDirector->replaceScene(fade);
    return;
}