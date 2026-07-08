#include "GJGarageLayer.h"

#include "cocos-ext.h"
#include "AppDelegate.h"
#include "RT_COCOS/CCMenuItemSpriteExtra.h"
#include "MenuLayer.h"
#include "GameManager.h"
#include "GameStatsManager.h"
#include "GaragePage.h"
USING_NS_CC;
USING_NS_CC_EXT;

CCScene* GJGarageLayer::scene()
{
    // 'scene' is an autorelease object
    CCScene* scene = CCScene::create();
    AppDelegate* pApp = AppDelegate::get();
    
    pApp->setScenePointer(scene);
    
    // 'layer' is an autorelease object
    GJGarageLayer* layer = GJGarageLayer::node();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool GJGarageLayer::init()
{
    if (!CCLayer::init())
        return false;
    
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

    GAME_MANAGER->setMainMenuActive(true);
	GAME_MANAGER->setLastScene(LastGameScene::unk0);
    
    this->setKeypadEnabled(true);
    
    CCSprite* bgSprite = CCSprite::create("GJ_gradientBG.png");
	bgSprite->setAnchorPoint(CCPoint(0.0f, 0.0f));
	this->addChild(bgSprite, -2);
	bgSprite->setScaleX((winSize.width + 10.0f) / bgSprite->getTextureRect().size.width);
	bgSprite->setScaleY((winSize.height + 10.0f) / bgSprite->getTextureRect().size.height);
	bgSprite->setPosition(CCPoint(-5.0f, -5.0f));
	bgSprite->setColor(ccc3(175, 175, 175));

    // looks matching enough
    CCSprite* sideArtLeft = CCSprite::createWithSpriteFrameName("GJ_sideArt_001.png");
    sideArtLeft->setAnchorPoint(CCPoint(0.0f, 0.0f));
	sideArtLeft->setPosition(CCPoint(CCDirector::sharedDirector()->getScreenLeft() - 1.0f, CCDirector::sharedDirector()->getScreenTop() - 71.0f));
    sideArtLeft->setFlipY(true);
    this->addChild(sideArtLeft, 1);
    
    CCSprite* sideArtRight = CCSprite::createWithSpriteFrameName("GJ_sideArt_001.png");
    sideArtRight->setAnchorPoint(CCPoint(1.0f, 0.0f));
	sideArtRight->setPosition(CCPoint(CCDirector::sharedDirector()->getScreenRight() + 1.0f, CCDirector::sharedDirector()->getScreenTop() - 71.0f));
    sideArtRight->setFlipY(true);
    sideArtRight->setFlipX(true);
    this->addChild(sideArtRight, 1);
    
    CCSprite* backBtnSprite = CCSprite::createWithSpriteFrameName("GJ_arrow_03_001.png");
    CCMenuItemSpriteExtra* backBtn = CCMenuItemSpriteExtra::create(backBtnSprite, NULL, this, menu_selector(GJGarageLayer::onBack));
    backBtn->setSizeMult(1.6f);
    CCMenu* backMenu = CCMenu::create(backBtn, NULL);
    this->addChild(backMenu, 1);
	backMenu->setPosition(CCPoint(CCDirector::sharedDirector()->getScreenLeft() + 25.0f, CCDirector::sharedDirector()->getScreenTop() - 22.0f));
    
    CCSprite* floorLine = CCSprite::createWithSpriteFrameName("floorLine_001.png");
    floorLine->setPosition(ccp(winSize.width * 0.5f, winSize.height * 0.5f + 50.0f));
    this->addChild(floorLine, 0);
    
    CCSprite* starIcon = CCSprite::createWithSpriteFrameName("GJ_starsIcon_001.png");
	starIcon->setPosition(CCPoint(CCDirector::sharedDirector()->getScreenRight() - 40.0f, CCDirector::sharedDirector()->getScreenTop() - 40.0f));
    this->addChild(starIcon);
    
    GameStatsManager* GSM = GameStatsManager::sharedState();
    int stars = GSM->getStat("6");
    CCLabelBMFont* starsLabel = CCLabelBMFont::create(CCString::createWithFormat("%i", stars)->getCString(), "bigFont.fnt");
    starsLabel->setAnchorPoint(ccp(1.0f, 0.5f));
    starsLabel->setPosition(starIcon->getPosition() + ccp(-18.0f, 0.0f));
    starsLabel->setScale(0.5f);
    this->addChild(starsLabel);
    
    
    CCSprite* coinIcon = CCSprite::createWithSpriteFrameName("GJ_coinsIcon_001.png");
    coinIcon->setPosition(starIcon->getPosition() + ccp(0.0f, -28.0f));
    this->addChild(coinIcon);
    
    int coins = GSM->getStat("8");
    CCLabelBMFont* coinsLabel = CCLabelBMFont::create(CCString::createWithFormat("%i", coins)->getCString(), "bigFont.fnt");
    coinsLabel->setAnchorPoint(ccp(1.0f, 0.5f));
    coinsLabel->setPosition(coinIcon->getPosition() + ccp(-18.0f, 0.0f));
    coinsLabel->setScale(0.5f);
    this->addChild(coinsLabel);
    
    /*CCSprite* editBarBG = CCSprite::create("edit_barBG_001.png");
    editBarBG->setAnchorPoint(CCPoint(0.0f, 0.0f));
    editBarBG->setPosition(CCPoint(pDirector->getScreenLeft(), pDirector->getScreenBottom()));
    this->addChild(editBarBG, 1);*/

	m_playerObject = SimplePlayer::create(GAME_MANAGER->getPlayerFrame());
	m_playerObject->setAnchorPoint(CCPoint(0.0f, 0.0f));
	this->addChild(m_playerObject, 1);
	m_playerObject->setScale(1.6f);
	m_playerObject->setPosition(floorLine->getPosition() + ccp(0.0f, 30.0f));
	this->updatePlayerColors();

	setupIconSelect();

    return true;
}

void GJGarageLayer::setupIconSelect()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	float baseYPos = (winSize.height * 0.5f) - 5;

	CCScale9Sprite* base = CCScale9Sprite::create("square02_001.png", CCRect(0, 0, 80, 80));
	base->setOpacity(75);
	base->setContentSize(CCSize(440, 100));
	this->addChild(base, -1);
	base->setPosition(ccp(winSize.width * 0.5f, baseYPos - 31.0f));

	CCSprite* unlockTxt = CCSprite::createWithSpriteFrameName("GJ_unlockTxt_001.png");
	this->addChild(unlockTxt);
	unlockTxt->setAnchorPoint(ccp(0.5, 0.5));
	unlockTxt->setPosition(base->getPosition() + ccp(120, (winSize.height * 0.5) + 12));

	CCMenu* buttonMenu = CCMenu::create();
	this->addChild(buttonMenu, 100);

	unk_0x13c = CCMenuItemToggler::create(
		CCSprite::createWithSpriteFrameName("gj_iconBtn_off_001.png"), 
		CCSprite::createWithSpriteFrameName("gj_iconBtn_on_001.png"), this, menu_selector(GJGarageLayer::onSelectTab));
	unk_0x13c->setSizeMult(1.2f);
	buttonMenu->addChild(unk_0x13c);
	unk_0x13c->setTag(0);

	unk_0x140 = CCMenuItemToggler::create(
		CCSprite::createWithSpriteFrameName("gj_shipBtn_off_001.png"),
		CCSprite::createWithSpriteFrameName("gj_shipBtn_on_001.png"), this, menu_selector(GJGarageLayer::onSelectTab));
	unk_0x140->setSizeMult(1.2f);
	buttonMenu->addChild(unk_0x140);
	unk_0x140->setTag(1);

	unk_0x144 = CCMenuItemToggler::create(
		CCSprite::createWithSpriteFrameName("gj_ballBtn_off_001.png"),
		CCSprite::createWithSpriteFrameName("gj_ballBtn_on_001.png"), this, menu_selector(GJGarageLayer::onSelectTab));
	unk_0x144->setSizeMult(1.2f);
	buttonMenu->addChild(unk_0x144);
	unk_0x144->setTag(2);

	unk_0x148 = CCMenuItemToggler::create(
		CCSprite::createWithSpriteFrameName("gj_birdBtn_off_001.png"),
		CCSprite::createWithSpriteFrameName("gj_birdBtn_on_001.png"), this, menu_selector(GJGarageLayer::onSelectTab));
	unk_0x148->setSizeMult(1.2f);
	buttonMenu->addChild(unk_0x148);
	unk_0x144->setTag(3);

	unk_0x14c = CCMenuItemToggler::create(
		CCSprite::createWithSpriteFrameName("gj_streakBtn_off_001.png"),
		CCSprite::createWithSpriteFrameName("gj_streakBtn_on_001.png"), this, menu_selector(GJGarageLayer::onSelectTab));
	unk_0x14c->setSizeMult(1.2f);
	buttonMenu->addChild(unk_0x14c);
	unk_0x144->setTag(99);
	
	buttonMenu->alignItemsHorizontallyWithPadding(0.0f);
	buttonMenu->setPosition(base->getPosition() + ccp(-125, (winSize.height * 0.5) + 18));

	unk_0x130 = CCArray::create();
	unk_0x130->retain();

	GaragePage* playerPage = GaragePage::create(IconType::Cube, this, menu_selector(GJGarageLayer::onPlayerIcon));
	this->addChild(playerPage, 100);
	unk_0x130->addObject(playerPage);

	GaragePage* shipPage = GaragePage::create(IconType::Ship, this, menu_selector(GJGarageLayer::onShipIcon));
	this->addChild(shipPage, 100);
	unk_0x130->addObject(shipPage);

	GaragePage* ballPage = GaragePage::create(IconType::Ball, this, menu_selector(GJGarageLayer::onBallIcon));
	this->addChild(ballPage, 100);
	unk_0x130->addObject(ballPage);

	GaragePage* birdPage = GaragePage::create(IconType::UFO, this, menu_selector(GJGarageLayer::onBirdIcon));
	this->addChild(birdPage, 100);
	unk_0x130->addObject(birdPage);

	GaragePage* specialPage = GaragePage::create(IconType::Special, this, menu_selector(GJGarageLayer::onSpecialIcon));
	this->addChild(specialPage, 100);
	unk_0x130->addObject(specialPage);

	selectPage(IconType::Cube);
}

void GJGarageLayer::updatePlayerColors()
{
	GameManager* pGameManager = GameManager::sharedState();
	m_playerObject->setColor(pGameManager->colorForIdx(pGameManager->getPlayerColor()));
	m_playerObject->setSecondColor(pGameManager->colorForIdx(pGameManager->getPlayerColor2()));
}

void GJGarageLayer::onBack(CCObject* sender)
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCScene* scene = MenuLayer::scene();
    CCTransitionFade* fade = CCTransitionFade::create(0.5f, scene);
    pDirector->replaceScene(fade);
}

void GJGarageLayer::onSelectTab(CCObject* sender)
{
	int senderTag = ((CCNode*)sender)->getTag();
	selectPage((IconType)senderTag);
}

void GJGarageLayer::onPlayerIcon(CCObject* sender)
{

}

void GJGarageLayer::onShipIcon(CCObject* sender)
{

}

void GJGarageLayer::onBallIcon(CCObject* sender)
{

}

void GJGarageLayer::onBirdIcon(CCObject* sender)
{

}

void GJGarageLayer::onSpecialIcon(CCObject* sender)
{

}

void GJGarageLayer::selectPage(IconType type)
{

}