#include "EditorUI.h"
USING_NS_CC;


EditorUI* EditorUI::create(LevelEditorLayer* editorLayer)
{
	EditorUI* ret = new EditorUI();
	if (ret) {
		if (ret->init(editorLayer)) {
			ret->autorelease();
			return ret;
		}

		delete ret;
	}

	return NULL;
}

bool EditorUI::init(LevelEditorLayer* editorLayer)
{

	if (!CCLayer::init())
		return false;

	CCDirector* pDirector = CCDirector::sharedDirector();


	this->setTouchEnabled(true);
	this->setKeypadEnabled(true);

	CCSprite* bgSprite = CCSprite::create("edit_barBG_001.png");
	bgSprite->setPosition(ccp(0.0f, 0.0f));

	CCMenu* buttonMenu = CCMenu::create();
	this->addChild(buttonMenu, 2);
	
	// robtop why unordered i confusd
	CCMenuItemSpriteExtra* modeBtn;
	modeBtn = getModeBtn("edit_buildBtn_001.png", 2);
	this->m_buildBtn = modeBtn;
	buttonMenu->addChild(modeBtn);

	modeBtn = getModeBtn("edit_editBtn_001.png", 3);
	this->m_editBtn = modeBtn;
	buttonMenu->addChild(modeBtn);
	
	modeBtn = getModeBtn("edit_deleteBtn_001.png", 1);
	this->m_deleteBtn = modeBtn;
	buttonMenu->addChild(modeBtn);

	m_buildBtn->setPosition(ccp(pDirector->getScreenLeft() + 42.0f, pDirector->getScreenBottom() + 75.0f));
	m_editBtn->setPosition(m_buildBtn->getPosition() + ccp(0.0f, -29.0f));
	m_deleteBtn->setPosition(m_editBtn->getPosition() + ccp(0.0f, -29.0f));
	buttonMenu->setPosition(ccp(pDirector->getScreenLeft() + 85.0f, pDirector->getScreenBottom() + 75.0f));


	CCSprite* vLine = CCSprite::createWithSpriteFrameName("edit_vLine_001.png");
	this->addChild(vLine, 2);
	vLine->setPosition(ccp(pDirector->getScreenLeft() + 85.0f, pDirector->getScreenBottom() + 75.0f));

	// this->setupDeleteMenu();
	this->setupCreateMenu();
	// this->setupEditMenu();
	this->resetUI();
	
	//CCSprite* pauseSpr = CCSprite::createWithSpriteFrameName("GJ_pauseBtn_001.png");
	//CCMenuItemSpriteExtra* pauseExtra = CCMenuItemSpriteExtra::create(pauseSpr, NULL, this, menu_selector(EditorUI::onPause));


    return true;
}

void EditorUI::setupCreateMenu()
{
    
}

CCMenuItemSpriteExtra* EditorUI::getModeBtn(char const* sprite, int tag)
{
	CCSprite* tmpSpr = CCSprite::createWithSpriteFrameName(sprite);
	CCMenuItemSpriteExtra* finalSprite = CCMenuItemSpriteExtra::create(tmpSpr, nullptr, this, menu_selector(EditorUI::toggleMode));
	finalSprite->setTag(tag);
	return finalSprite;
}

void EditorUI::toggleMode(cocos2d::CCObject* sender)
{
	CCLOG("toggling");
}

void EditorUI::resetUI()
{
	CCSprite* normalFrame;
	CCSpriteFrame* frame;

	normalFrame = (CCSprite*)m_deleteBtn->getNormalImage();
	frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("edit_deleteBtn_001.png");
	normalFrame->setDisplayFrame(frame);

	normalFrame = (CCSprite*)m_buildBtn->getNormalImage();
	frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("edit_buildBtn_001.png");
	normalFrame->setDisplayFrame(frame);

	normalFrame = (CCSprite*)m_editBtn->getNormalImage();
	frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("edit_editBtn_001.png");
	normalFrame->setDisplayFrame(frame);

	//updateDeleteMenu();
	//this->updateCreateMenu(false);
	//updateEditMenu();
}