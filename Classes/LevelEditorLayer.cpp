#include "LevelEditorLayer.h"
#include "AppDelegate.h"
#include "GameManager.h"
#include "EditorUI.h"

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
USING_NS_CC;

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

	this->m_objectCount = 0;
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	GameManager::sharedState()->resetMusic();
	this->m_level = level;

	m_gameLayer = CCLayer::create();
	this->addChild(m_gameLayer, 1);
	this->addChild(EditorUI::create(this), 100);
	
	// missing code

	this->createBackground();

}

void LevelEditorLayer::createBackground()
{
	// todo: implement
}