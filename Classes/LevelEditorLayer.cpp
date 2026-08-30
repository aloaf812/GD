#include "LevelEditorLayer.h"
#include "AppDelegate.h"
#include "GameManager.h"
#include "EditorUI.h"

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
USING_NS_CC;


LevelEditorLayer::LevelEditorLayer()
{
	m_bgSprite = nullptr;
	m_levelSettings = nullptr;
}

CCScene* LevelEditorLayer::scene(GJGameLevel* level)
{
	CCScene *scene = CCScene::create();
	AppDelegate* pApp = AppDelegate::get();
	pApp->setScenePointer(scene);
	LevelEditorLayer* layer = LevelEditorLayer::create(level);
	scene->addChild(layer);
	// scene->setObjType(5);
	return scene;
}

LevelEditorLayer* LevelEditorLayer::create(GJGameLevel* level)
{
	LevelEditorLayer* pRet = new LevelEditorLayer();
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

bool LevelEditorLayer::init(GJGameLevel* level)
{
	if (!CCLayer::init())
		return false;

	m_objectCount = 0;
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	GameManager::sharedState()->resetMusic();
	m_level = level;

	m_gameLayer = CCLayer::create();
	this->addChild(m_gameLayer, 1);
	this->addChild(EditorUI::create(this), 100);
	
	// missing code

	if (!m_levelSettings) {
		m_levelSettings = LevelSettingsObject::create();
		m_levelSettings->retain();
	}
	
	// m_gridLayer->setBlockTimeMarkers(false);
	// m_gridLayer->sortSpeedObjects();

	this->createBackground();

	return true;
}

void LevelEditorLayer::createBackground()
{
	if (m_bgSprite != nullptr) {
		this->removeBackground();
	}
	
	CCDirector* pDirector = CCDirector::sharedDirector();
	CCSize winSize = pDirector->getWinSize();
	CCSprite* bgSprite = CCSprite::create(GameManager::sharedState()->getBGTexture(
		m_levelSettings->getBGIdx()));
	bgSprite->setPosition(ccp(winSize.height * 0.5f, winSize.height * 0.5f));
	this->addChild(bgSprite, -1);
	bgSprite->setScale(pDirector->getScreenScaleFactorMax());
}

void LevelEditorLayer::removeBackground()
{
	if (m_bgSprite != nullptr) {
		m_bgSprite->removeFromParent();
		m_bgSprite = nullptr;
	}
}