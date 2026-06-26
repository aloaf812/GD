// decompiled by ItzZyann and Aloaf
// from GD 1.71 binary

#include "LevelSelectLayer.h"

#include "AppDelegate.h"
#include "RT_COCOS/CCMenuItemSpriteExtra.h"
#include "MenuLayer.h"
#include "GameManager.h"
#include <cmath>
#include "BoomScrollLayer.h"
#include "GameLevelManager.h"
#include "LevelPage.h"
#include "LevelTools.h"
#include "SongsLayer.h"
#include "ExtendedLayer.h"
USING_NS_CC;

LevelSelectLayer::LevelSelectLayer()
{
	m_bslDelegate = NULL;
	m_winWidth = 0.0f;
	m_background = NULL;
	m_ground = NULL;
	m_scrollLayer = NULL;
}

CCScene* LevelSelectLayer::scene(int page)
{
	CCScene* scene = CCScene::create();

	AppDelegate* pApp = AppDelegate::get();
	pApp->setScenePointer(scene);

	LevelSelectLayer* layer = LevelSelectLayer::create(page);
	scene->addChild(layer);

	return scene;
}

LevelSelectLayer* LevelSelectLayer::create(int page)
{
	LevelSelectLayer* pRet = new LevelSelectLayer();
	if (pRet && pRet->init(page))
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

bool LevelSelectLayer::init(int page)
{
	if (!CCLayer::init())
		return false;

	this->setKeypadEnabled(true);

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	// ((float*)this + 68) = v158  →  store winWidth for scrollLayerMoved
	m_winWidth = winSize.width;

	m_background = CCSprite::create("GJ_gradientBG.png");
	m_background->setAnchorPoint(CCPoint(0.0f, 0.0f));
	this->addChild(m_background, -2);
	m_background->setScaleX((winSize.width + 10.0f) / m_background->getTextureRect().size.width);
	m_background->setScaleY((winSize.height + 10.0f) / m_background->getTextureRect().size.height);
	m_background->setPosition(CCPoint(-5.0f, -5.0f));
	m_background->setColor(ccc3(40, 125, 255));

	CCLayer* groundLayer = CCLayer::create();
	this->addChild(groundLayer, 0);

	m_ground = CCSprite::create(
		GameManager::sharedState()->getGTexture(
		GameManager::sharedState()->getLoadedGIdx()));

	ccTexParams texParams = { GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT };
	m_ground->getTexture()->setTexParameters(&texParams);
	groundLayer->addChild(m_ground, 2);

	m_ground->setAnchorPoint(ccp(0.0f, 1.0f));
	m_ground->setScale(CCDirector::sharedDirector()->getScreenScaleFactorMax());
	m_ground->setColor(ccc3(0, 102, 255));

	float refYPos = (winSize.height * 0.5f) - 110.0f;
	float groundH = m_ground->getContentSize().height;
	if (refYPos > groundH)
		refYPos = groundH;

	CCRect groundRect = m_ground->getTextureRect();
	float cols = ceilf(winSize.width / groundRect.size.width) + 1.0f;
	groundRect.size.width = groundRect.size.width * cols;
	m_ground->setTextureRect(groundRect);
	m_ground->setPosition(ccp(0.0f, refYPos));

	CCSprite* lineSprite = CCSprite::createWithSpriteFrameName("floorLine_001.png");
	groundLayer->addChild(lineSprite, 3);
	lineSprite->setPosition(CCPoint(winSize.width * 0.5f, refYPos));
	ccBlendFunc lineBlendFunc = { GL_SRC_ALPHA, GL_ONE };
	lineSprite->setBlendFunc(lineBlendFunc);
	lineSprite->setOpacity(200);

	CCSprite* leftShadow = CCSprite::createWithSpriteFrameName("groundSquareShadow_001.png");
	leftShadow->setAnchorPoint(ccp(0.0f, 1.0f));
	leftShadow->setPosition(ccp(CCDirector::sharedDirector()->getScreenLeft() - 1.0f, refYPos));
	groundLayer->addChild(leftShadow, 3);

	CCSprite* rightShadow = CCSprite::createWithSpriteFrameName("groundSquareShadow_001.png");
	rightShadow->setAnchorPoint(ccp(1.0f, 1.0f));
	rightShadow->setPosition(ccp(CCDirector::sharedDirector()->getScreenRight() + 1.0f, refYPos));
	groundLayer->addChild(rightShadow, 3);
	rightShadow->setFlipX(true);

	leftShadow->setOpacity(100);
	rightShadow->setOpacity(100);

	// setScaleX with float bits 0x3F800000 = 1.0f, not 0.7f
	leftShadow->setScaleX(1.0f);
	rightShadow->setScaleX(1.0f);

	ccBlendFunc shadowBlendFunc = { GL_DST_COLOR, GL_ONE_MINUS_SRC_ALPHA }; // 774, 771
	leftShadow->setBlendFunc(shadowBlendFunc);   // FIX: both get it
	rightShadow->setBlendFunc(shadowBlendFunc);

	CCSprite* topBar = CCSprite::createWithSpriteFrameName("GJ_topBar_001.png");
	topBar->setAnchorPoint(CCPoint(0.5f, 1.0f));
	topBar->setPosition(CCPoint(winSize.width * 0.5f,
		CCDirector::sharedDirector()->getScreenTop() + 1.0f));
	this->addChild(topBar, 1);

	CCSprite* sideArtLeft = CCSprite::createWithSpriteFrameName("GJ_sideArt_001.png");
	sideArtLeft->setAnchorPoint(CCPoint(0.0f, 0.0f));
	sideArtLeft->setPosition(CCPoint(CCDirector::sharedDirector()->getScreenLeft() - 1.0f,
		CCDirector::sharedDirector()->getScreenBottom() - 1.0f));
	this->addChild(sideArtLeft, 1);

	CCSprite* sideArtRight = CCSprite::createWithSpriteFrameName("GJ_sideArt_001.png");
	sideArtRight->setAnchorPoint(CCPoint(1.0f, 0.0f));
	sideArtRight->setPosition(CCPoint(CCDirector::sharedDirector()->getScreenRight() + 1.0f,
		CCDirector::sharedDirector()->getScreenBottom() - 1.0f));
	sideArtRight->setFlipX(true);
	this->addChild(sideArtRight, 1);

	CCArray* pages = CCArray::create();
	int i = 1;
	do {
		GJGameLevel* level = GameLevelManager::sharedState()->getMainLevel(i);
		++i;
		LevelPage* levelPage = LevelPage::create(level);
		pages->addObject(levelPage);
	} while (i != 16);

	// Coming soon page
	CCLayer* csLayer = CCLayer::create();
	CCLabelBMFont* csLabel = CCLabelBMFont::create("Coming Soon!", "bigFont.fnt");
	csLabel->setPosition(ccp(winSize.width * 0.5f, winSize.height * 0.5f + 50.0f));
	csLayer->addChild(csLabel);
	pages->addObject(csLayer);

	// this part is pain in ass
	// no wonder why it wouldn't work
	// its just because of boomscrolllayer not
	// fully decompiled T-T

	bool showDots = pages->count() > 3;
	m_scrollLayer = BoomScrollLayer::create(pages, 0, showDots);
	this->addChild(m_scrollLayer);
	m_scrollLayer->setPagesIndicatorPosition(
		ccp(winSize.width * 0.5f,
		CCDirector::sharedDirector()->getScreenBottom() + 15.0f));
	m_scrollLayer->getInternalLayer()->setDelegate(m_bslDelegate);

	// page == 15 -> instantMoveToPage(14) THEN instantMoveToPage(15)
	// this is intentional in the original, it snaps to 14 first then to 15
	// (the "Coming Soon" slide), so we preserve it exactly as assembled.
	if (page == 0) {
		this->scrollLayerMoved(CCPointZero);
	}
	else {
		if (page == 15) {
			m_scrollLayer->instantMoveToPage(14);
		}
		m_scrollLayer->instantMoveToPage(page);
	}

	CCLabelBMFont* downloadTxt = CCLabelBMFont::create("Download the soundtracks", "bigFont.fnt");
	downloadTxt->setScale(0.5f);
	CCMenuItemSpriteExtra* downloadExtra = CCMenuItemSpriteExtra::create(
		downloadTxt, NULL, this, menu_selector(LevelSelectLayer::onDownload));
	downloadExtra->setSizeMult(2.0f);

	CCMenu* downloadMenu = CCMenu::create(downloadExtra, NULL);
	this->addChild(downloadMenu);
	downloadMenu->setPosition(CCPoint(winSize.width * 0.5f,
		CCDirector::sharedDirector()->getScreenBottom() + 35.0f));

	CCMenu* arrowsMenu = CCMenu::create();
	this->addChild(arrowsMenu, 5);

	CCSprite* leftBtnSprite = CCSprite::createWithSpriteFrameName("navArrowBtn_001.png");
	leftBtnSprite->setFlipX(true);
	CCMenuItemSpriteExtra* leftBtn = CCMenuItemSpriteExtra::create(
		leftBtnSprite, NULL, this, menu_selector(LevelSelectLayer::onPrev));
	arrowsMenu->addChild(leftBtn);
	leftBtn->setSizeMult(2.0f);
	leftBtn->setPosition(arrowsMenu->convertToNodeSpace(
		CCPoint(CCDirector::sharedDirector()->getScreenLeft() + 25.0f,
		winSize.height * 0.5f)));

	CCSprite* rightBtnSprite = CCSprite::createWithSpriteFrameName("navArrowBtn_001.png");
	CCMenuItemSpriteExtra* rightBtn = CCMenuItemSpriteExtra::create(
		rightBtnSprite, NULL, this, menu_selector(LevelSelectLayer::onNext));
	arrowsMenu->addChild(rightBtn);
	rightBtn->setSizeMult(2.0f);
	rightBtn->setPosition(arrowsMenu->convertToNodeSpace(
		CCPoint(CCDirector::sharedDirector()->getScreenRight() - 25.0f,
		winSize.height * 0.5f)));

	// its should setSizeMult(2.0f), the decompiled source had 1.6f which was wrong
	CCSprite* backBtnSprite = CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png");
	CCMenuItemSpriteExtra* backBtn = CCMenuItemSpriteExtra::create(
		backBtnSprite, NULL, this, menu_selector(LevelSelectLayer::onBack));
	backBtn->setSizeMult(2.0f);
	CCMenu* backMenu = CCMenu::create(backBtn, NULL);
	this->addChild(backMenu, 1);
	backMenu->setPosition(CCPoint(CCDirector::sharedDirector()->getScreenLeft() + 25.0f,
		CCDirector::sharedDirector()->getScreenTop() - 22.0f));

	CCMenu* infoMenu = CCMenu::create();
	this->addChild(infoMenu);

	CCSprite* infoBtnSprite = CCSprite::createWithSpriteFrameName("GJ_infoIcon_001.png");
	CCMenuItemSpriteExtra* infoBtn = CCMenuItemSpriteExtra::create(
		infoBtnSprite, NULL, this, menu_selector(LevelSelectLayer::onInfo));
	infoBtn->setSizeMult(2.0f);
	infoMenu->addChild(infoBtn);
	infoMenu->setPosition(CCPoint(CCDirector::sharedDirector()->getScreenRight() - 20.0f,
		CCDirector::sharedDirector()->getScreenTop() - 20.0f));

	this->scheduleUpdate();

	return true;
}

void LevelSelectLayer::keyBackClicked()
{
	this->onBack(NULL);
}

void LevelSelectLayer::onDownload(CCObject* sender)
{
	SongsLayer* layer = SongsLayer::create();
	getParent()->addChild(layer, 100);
	layer->showLayer(false);
}

void LevelSelectLayer::onBack(CCObject* sender)
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	CCScene* scene = MenuLayer::scene();
	CCTransitionFade* fade = CCTransitionFade::create(0.5f, scene);
	pDirector->replaceScene(fade);
}

void LevelSelectLayer::onInfo(CCObject* sender)
{
	int pageNum = m_scrollLayer->getRelativePageForNum(m_scrollLayer->getCurrentScreen());
	if (pageNum != m_scrollLayer->getTotalPages() - 1)
		((LevelPage*)m_scrollLayer->getPage(pageNum))->onInfo(nullptr);
}

void LevelSelectLayer::onPrev(CCObject* sender)
{
	m_scrollLayer->quickUpdate();
	m_scrollLayer->moveToPage(m_scrollLayer->getCurrentScreen() - 1);
}

void LevelSelectLayer::onNext(CCObject* sender)
{
	m_scrollLayer->quickUpdate();
	m_scrollLayer->moveToPage(m_scrollLayer->getCurrentScreen() + 1);
}

cocos2d::ccColor3B LevelSelectLayer::colorForPage(int page)
{
	static const int colorIndices[] = { 5, 7, 8, 9, 10, 11, 1, 3, 4 };

	if (page >= 9)
		return this->colorForPage(page % 9);

	int colorIdx = colorIndices[page];
	return GameManager::sharedState()->colorForIdx(colorIdx);
}

cocos2d::ccColor3B LevelSelectLayer::getColorValue(int pageA, int pageB, float t)
{
	float v = (t / 0.66667f) - 0.2f;
	if (v < 0.0f) v = 0.0f;
	else if (v > 1.0f) v = 1.0f;

	ccColor3B ca = colorForPage(pageA);
	ccColor3B cb = colorForPage(pageB);

	ccColor3B out;
	out.r = (GLubyte)((float)cb.r * v + (float)ca.r * (1.0f - v));
	out.g = (GLubyte)((float)cb.g * v + (float)ca.g * (1.0f - v));
	out.b = (GLubyte)((float)cb.b * v + (float)ca.b * (1.0f - v));
	return out;
}

void LevelSelectLayer::scrollLayerMoved(CCPoint pos)
{
	float i = -pos.x / m_winWidth;
	while (i < 0.0f)
		i += 16.0f;

	int   pageFloor = (int)floorf(i);
	float frac = i - (float)pageFloor;

	int curPage = pageFloor % 16;
	int nextPage = (curPage == 15) ? 0 : curPage + 1; // if (v4%16 == 0xF) v6=0

	ccColor3B bgColor = getColorValue(curPage, nextPage, frac);

	m_background->setColor(bgColor);

	ccColor3B gndColor;
	gndColor.r = (GLubyte)((float)bgColor.r * 0.8f);
	gndColor.g = (GLubyte)((float)bgColor.g * 0.8f);
	gndColor.b = (GLubyte)((float)bgColor.b * 0.8f);
	m_ground->setColor(gndColor);
}

void LevelSelectLayer::update(float dt) {
	if (m_scrollLayer && m_scrollLayer->getInternalLayer()) {
		CCPoint pos = m_scrollLayer->getInternalLayer()->getPosition();
		this->scrollLayerMoved(pos);
	}
}