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
        nameLabel->setPosition({65, 47.5f});
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
            starIcon->setPosition({325, 82});
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
    
    
    auto createProgBar = [&](int percent, CCPoint center, CCPoint offsetY, bool practice) -> CCSprite* {
        auto bg = CCSprite::create("GJ_progressBar_001.png");
        bg->setColor({0, 0, 0});
        bg->setOpacity(125);
        bg->setPosition(center + offsetY);
        this->addChild(bg, 3);
        
        auto fill = CCSprite::create("GJ_progressBar_001.png");
        fill->setScaleX(0.992f);
        fill->setScaleY(0.86f);
        float temp = (bg->getContentSize().width - (fill->getContentSize().width * fill->getScaleX() / 2));
        fill->setPosition({temp, bg->getContentSize().height / 2});
        fill->setAnchorPoint({0.0f, 0.5f});
        
        if (!practice) fill->setColor(ccGREEN);
        else fill->setColor({0, 255, 255});
        
        float fullWidth = fill->getContentSize().width * fill->getScaleX();
        float actualWidth = fullWidth * (percent / 100.0f);
        fill->setTextureRect(CCRect(0, 0, actualWidth, fill->getContentSize().height));
        bg->addChild(fill);

        return bg;
    };
    
    auto normalBar = createProgBar(10, winSize / 2, {0, -30}, false);
    auto practiceBar = createProgBar(56, winSize / 2, {0, -80}, true);
    
    auto createProgText = [&](char const* text, CCNode* target) {
        auto lbl = CCLabelBMFont::create(text, "bigFont.fnt");
        lbl->setScale(0.5f);
        lbl->setPosition(target->getPosition());
        this->addChild(lbl, 4);
    
    };
    
    createProgText(CCString::createWithFormat("%i%%", 43)->getCString(), normalBar);
    createProgText(CCString::createWithFormat("%i%%", 56)->getCString(), practiceBar);
    
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
    CCLOG("play");
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