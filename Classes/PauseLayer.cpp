// decompiled by ItzZyann
// from GD 1.71 binary

#include "PauseLayer.h"
#include "GameManager.h"
#include "RT_COCOS/CCMenuItemSpriteExtra.h"
#include "RT_COCOS/CCMenuItemToggler.h"
#include "GameSoundManager.h"
#include "LevelEditorLayer.h"
#include "TutorialLayer.h"
#include "AdToolbox.h"

#include "cocos-ext.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace CocosDenshion;

void PauseLayer::customSetup()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	CCSize winSize = pDirector->getWinSize();

	CCScale9Sprite* background = CCScale9Sprite::create("square04_001.png", CCRect(0, 0, 80, 80));
	background->setColor({ 0, 0, 0 });
	background->setOpacity(175);

	float bgWidth = (pDirector->getScreenRight() - 20.0f) - pDirector->getScreenLeft();
	float bgHeight = (pDirector->getScreenTop() - 20.0f) - pDirector->getScreenBottom();

	background->setContentSize(CCSize(bgWidth, bgHeight));
	background->setPosition(ccp(winSize.width * 0.5f, winSize.height * 0.5f));
	this->addChild(background, -1);

	std::string levelName = PLAY_LAYER->getLevel()->getLevelName();
	CCLabelBMFont* levelLabel = CCLabelBMFont::create(levelName.c_str(), "bigFont.fnt");
	levelLabel->setPosition(ccp(winSize.width * 0.5f, (winSize.height * 0.5f + bgHeight * 0.5f) - 20.0f));
	this->addChild(levelLabel);

	setupProgressBars();

	CCMenu* mainButtonMenu = CCMenu::create();
	this->addChild(mainButtonMenu);

	CCSprite* menuBtn = CCSprite::createWithSpriteFrameName("GJ_menuBtn_001.png");

	if (PLAY_LAYER->getLevel()->getLevelType() == GJLevelType::LocalLevel) {
		CCSprite* editBtn = CCSprite::createWithSpriteFrameName("GJ_editBtn_001.png");
		editBtn->setScale(menuBtn->getContentSize().width / editBtn->getContentSize().height);
		CCMenuItemSpriteExtra* editExtra = CCMenuItemSpriteExtra::create(editBtn, NULL, this, menu_selector(PauseLayer::onEdit));
		mainButtonMenu->addChild(editExtra);
	}

	CCSprite* practiceBtn;
	SEL_MenuHandler practiceCallback;
	if (PLAY_LAYER->getPracticeMode()) {
		practiceBtn = CCSprite::createWithSpriteFrameName("GJ_normalBtn_001.png");
		practiceCallback = menu_selector(PauseLayer::onNormalMode);
	}
	else {
		practiceBtn = CCSprite::createWithSpriteFrameName("GJ_practiceBtn_001.png");
		practiceCallback = menu_selector(PauseLayer::onPracticeMode);
	}
	CCMenuItemSpriteExtra* practiceExtra = CCMenuItemSpriteExtra::create(practiceBtn, NULL, this, practiceCallback);
	mainButtonMenu->addChild(practiceExtra);

	CCSprite* resumeBtn = CCSprite::createWithSpriteFrameName("GJ_playBtn2_001.png");
	CCMenuItemSpriteExtra* resumeExtra = CCMenuItemSpriteExtra::create(resumeBtn, NULL, this, menu_selector(PauseLayer::onResume));
	mainButtonMenu->addChild(resumeExtra);

	CCMenuItemSpriteExtra* menuExtra = CCMenuItemSpriteExtra::create(menuBtn, NULL, this, menu_selector(PauseLayer::onQuit));
	mainButtonMenu->addChild(menuExtra);

	if (PLAY_LAYER->getLevel()->getLevelType() == GJLevelType::LocalLevel) {
		CCSprite* restartBtn = CCSprite::createWithSpriteFrameName("GJ_replayBtn_001.png");
		CCMenuItemSpriteExtra* restartExtra = CCMenuItemSpriteExtra::create(restartBtn, NULL, this, menu_selector(PauseLayer::onRestart));
		mainButtonMenu->addChild(restartExtra);
	}

	float spacing;
	if (PLAY_LAYER->getLevel()->getLevelType() == GJLevelType::LocalLevel)
		spacing = 15.0f;
	else
		spacing = 20.0f;

	mainButtonMenu->alignItemsHorizontallyWithPadding(spacing);

	CCPoint menuPos = mainButtonMenu->getPosition();
	mainButtonMenu->setPosition(ccp(menuPos.x, winSize.height * 0.5f - 30.0f));

	// practice mode banner
	if (!GameManager::sharedState()->getClickedPractice()) {
		if (PLAY_LAYER->getLevel()->getLevelType() != GJLevelType::LocalLevel) {
			CCSprite* practiceTxt = CCSprite::createWithSpriteFrameName("GJ_practiceTxt_001.png");
			this->addChild(practiceTxt);
			practiceTxt->setPosition(ccp(winSize.width * 0.5f - 165.0f, winSize.height * 0.5f - 12.0f));
		}
	}

	CCMenu* toggleMenu = CCMenu::create();
	this->addChild(toggleMenu);

	CCDirector* dir = CCDirector::sharedDirector();
	float screenBottom = dir->getScreenBottom();
	float centerX = winSize.width * 0.5f;

	GameManager* gm = GameManager::sharedState();

	createToggleButton("Music", menu_selector(PauseLayer::onMusic), false, toggleMenu, ccp(centerX - 185.0f, screenBottom + 65.0f));
	createToggleButton("SFX", menu_selector(PauseLayer::onFX), false, toggleMenu, ccp(centerX - 22.0f, screenBottom + 65.0f));
	createToggleButton("Auto-Retry", menu_selector(PauseLayer::onAutoRetry), false, toggleMenu, ccp(centerX + 84.0f, screenBottom + 65.0f));
	createToggleButton("Auto-Checkpoints", menu_selector(PauseLayer::onAutoCheckpoints), false, toggleMenu, ccp(centerX - 185.0f, screenBottom + 30.0f));
	createToggleButton("Progress Bar", menu_selector(PauseLayer::onProgressBar), true, toggleMenu, ccp(centerX - 22.0f, screenBottom + 30.0f));

	/*
	createToggleButton("Music", menu_selector(PauseLayer::onMusic), !gm->getBGMEnabled(), toggleMenu, ccp(centerX - 185.0f, screenBottom + 65.0f));
	createToggleButton("SFX", menu_selector(PauseLayer::onFX), !gm->getEffectsEnabled(), toggleMenu, ccp(centerX - 22.0f, screenBottom + 65.0f));
	createToggleButton("Auto-Retry", menu_selector(PauseLayer::onAutoRetry), !gm->getAutoRetry(), toggleMenu, ccp(centerX + 84.0f, screenBottom + 65.0f));
	createToggleButton("Auto-Checkpoints", menu_selector(PauseLayer::onAutoCheckpoints), !gm->getAutoCheckpoints(), toggleMenu, ccp(centerX - 185.0f, screenBottom + 30.0f));
	createToggleButton("Progress Bar", menu_selector(PauseLayer::onProgressBar), !gm->getShowProgressBar(), toggleMenu, ccp(centerX - 22.0f, screenBottom + 30.0f)); */
}

void PauseLayer::createToggleButton(std::string text, SEL_MenuHandler callback, bool toggled, CCMenu* menu, CCPoint position)
{
	CCSprite* onSprite = CCSprite::createWithSpriteFrameName("GJ_checkOn_001.png");
	CCSprite* offSprite = CCSprite::createWithSpriteFrameName("GJ_checkOff_001.png");

	onSprite->setScale(0.8f);
	offSprite->setScale(0.8f);

	CCMenuItemToggler* toggler = CCMenuItemToggler::create(onSprite, offSprite, this, callback);
	toggler->toggle(toggled);

	menu->addChild(toggler);
	toggler->setPosition(menu->convertToNodeSpace(position));
	toggler->setSizeMult(1.5f);

	CCLabelBMFont* label = CCLabelBMFont::create(text.c_str(), "bigFont.fnt");
	this->addChild(label);

	label->setAnchorPoint(ccp(0.0f, 0.5f));

	float checkHalfW = onSprite->getContentSize().width * 0.5f;
	label->setPosition(ccpAdd(position, ccp(checkHalfW * 0.8f + 6.0f, 0.0f)));

	if (label->getContentSize().width > 110.0f)
		label->setScale(110.0f / label->getContentSize().width);

	if (label->getScale() > 0.5f)
		label->setScale(0.5f);
}

void PauseLayer::setupProgressBars()
{
	GameManager* gm = GameManager::sharedState();
	CCDirector* pDirector = CCDirector::sharedDirector();
	CCSize winSize = pDirector->getWinSize();

	CCSprite* normalBarBG = CCSprite::create("GJ_progressBar_001.png");
	normalBarBG->setColor(ccBLACK);
	normalBarBG->setOpacity(125);
	normalBarBG->setScale(1.0f);
	this->addChild(normalBarBG, 3);
	normalBarBG->setPosition(ccp(winSize.width * 0.5f, winSize.height * 0.5f + 80.0f));

	CCSprite* normalBarFill = CCSprite::create("GJ_progressBar_001.png");
	normalBarFill->setColor(ccGREEN); // 0x64FF00 -> close to lime; actual RGB from floats: ~(0x64, 0xFF, 0x76) green tint
	normalBarFill->setAnchorPoint(ccp(0.0f, 0.5f));

	// fill width is clipped per normal-mode percent
	// positioned slightly inset from left edge
	float fillInset = normalBarBG->getContentSize().width - (normalBarBG->getContentSize().width * 0.992f);
	normalBarFill->setPosition(ccp(fillInset * 0.5f, normalBarBG->getContentSize().height * 0.5f));
	normalBarBG->addChild(normalBarFill, 1);

	// int normalPercent = level>getNormalPercent(); // vtable +620
	int normalPercent = 0;
	float normalBarW = normalBarFill->getContentSize().width;
	float normalFillW = normalBarW * (normalPercent / 100.0f);
	if (normalFillW < normalBarW)
		normalFillW = normalBarW * (normalPercent / 100.0f);
	normalBarFill->setTextureRect(CCRect(0, 0, normalFillW, normalBarFill->getContentSize().height));

	CCSprite* practiceBarBG = CCSprite::create("GJ_progressBar_001.png");
	practiceBarBG->setColor(ccBLACK);
	practiceBarBG->setOpacity(125);
	practiceBarBG->setScale(1.0f);
	this->addChild(practiceBarBG, 3);
	practiceBarBG->setPosition(ccpAdd(normalBarBG->getPosition(), ccp(0.0f, -50.0f)));

	CCSprite* practiceBarFill = CCSprite::create("GJ_progressBar_001.png");
	practiceBarFill->setColor(ccWHITE); // color {0, -1, -1} = {0x00, 0xFF, 0xFF} -> cyan
	practiceBarFill->setAnchorPoint(ccp(0.0f, 0.5f));
	practiceBarFill->setPosition(normalBarFill->getPosition()); // same local offset
	practiceBarBG->addChild(practiceBarFill, 1);

	// int practicePercent = level->getPracticePercent(); // vtable +628
	int practicePercent = 0;
	float practiceBarW = practiceBarFill->getContentSize().width;
	float practiceFillW = practiceBarW * (practicePercent / 100.0f);
	if (practiceFillW < practiceBarW)
		practiceFillW = practiceBarW * (practicePercent / 100.0f);
	practiceBarFill->setTextureRect(CCRect(0, 0, practiceFillW, practiceBarFill->getContentSize().height));

	CCLabelBMFont* normalPctLabel = CCLabelBMFont::create(
		CCString::createWithFormat("%i%%", normalPercent)->getCString(), "bigFont.fnt");
	this->addChild(normalPctLabel, 4);
	normalPctLabel->setPosition(normalBarBG->getPosition());
	normalPctLabel->setScale(0.5f);

	CCLabelBMFont* practicePctLabel = CCLabelBMFont::create(
		CCString::createWithFormat("%i%%", practicePercent)->getCString(), "bigFont.fnt");
	this->addChild(practicePctLabel, 4);
	practicePctLabel->setPosition(practiceBarBG->getPosition());
	practicePctLabel->setScale(0.5f);

	CCLabelBMFont* normalModeLabel = CCLabelBMFont::create("Normal Mode", "bigFont.fnt");
	this->addChild(normalModeLabel, 4);
	normalModeLabel->setPosition(ccpAdd(normalBarBG->getPosition(), ccp(0.0f, 20.0f)));
	normalModeLabel->setScale(0.5f);

	CCLabelBMFont* practiceModeLabel = CCLabelBMFont::create("Practice Mode", "bigFont.fnt");
	this->addChild(practiceModeLabel, 4);
	practiceModeLabel->setPosition(ccpAdd(practiceBarBG->getPosition(), ccp(0.0f, 20.0f)));
	practiceModeLabel->setScale(0.5f);
}

void PauseLayer::onResume(CCObject* sender)
{
	PLAY_LAYER->resume();
	CCNode::removeMeAndCleanup();
}

void PauseLayer::onQuit(CCObject* sender)
{
	this->unscheduleAllSelectors();
	PLAY_LAYER->resume();
	PLAY_LAYER->onQuit();
	GameSoundManager::sharedManager()->playEffect("quitSound_01.ogg", 1.0f, 0.0f, 0.7f);
}

void PauseLayer::onEdit(CCObject* sender)
{
	PLAY_LAYER->resume();
	PLAY_LAYER->stopAllActions();
	PLAY_LAYER->unscheduleAllSelectors();

	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(false);

	CCScene* scene = LevelEditorLayer::scene(PLAY_LAYER->getLevel());
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f, scene));
}

void PauseLayer::onRestart(CCObject* sender)
{
	PLAY_LAYER->resumeAndRestart();
	CCNode::removeMeAndCleanup();
}

void PauseLayer::onNormalMode(CCObject* sender)
{
	PLAY_LAYER->togglePracticeMode(false);
	this->onResume(nullptr);
}

void PauseLayer::onPracticeMode(CCObject* sender)
{
	GameManager::sharedState()->setClickedPractice(true);
	PLAY_LAYER->togglePracticeMode(true);
	this->onResume(nullptr);
}

void PauseLayer::onAutoRetry(CCObject* sender)
{
	GameManager* gm = GameManager::sharedState();
	// gm->setAutoRetry(!gm->getAutoRetry());
}

void PauseLayer::onAutoCheckpoints(CCObject* sender)
{
	GameManager* gm = GameManager::sharedState();
	gm->setAutoCheckpoints(!gm->getAutoCheckpoints());
}

void PauseLayer::onProgressBar(CCObject* sender)
{
	GameManager* gm = GameManager::sharedState();
	gm->setShowProgressBar(!gm->getShowProgressBar());
	PLAY_LAYER->toggleProgressbar();
}

void PauseLayer::onRecordReplays(CCObject* sender)
{
	GameManager* gm = GameManager::sharedState();
	// gm->setRecordReplays(!gm->getRecordReplays());
	// reads back the value after setting — likely a valueChanged notify side effect
	// gm->getRecordReplays();
}

void PauseLayer::onFX(CCObject* sender)
{
	GameManager::sharedState()->toggleFX();
}

void PauseLayer::onMusic(CCObject* sender)
{
	GameManager::sharedState()->toggleMusic();
}

void PauseLayer::onHelp(CCObject* sender)
{
	TutorialLayer::create()->show();
}

void PauseLayer::tryShowBanner(float dt)
{
	// AdToolbox::enableBanner(this);
	this->unschedule(schedule_selector(PauseLayer::tryShowBanner));
}

void PauseLayer::keyBackClicked()
{
	this->onQuit(nullptr);
}