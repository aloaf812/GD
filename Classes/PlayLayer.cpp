#include "PlayLayer.h"
#include "SimpleAudioEngine.h"
#include "GameManager.h"
#include "AppDelegate.h"
#include "LevelTools.h"
#include "PauseLayer.h"
#include "ObjectToolbox.h"
using namespace CocosDenshion;
USING_NS_CC;

// to whoever finds this code, please don't try to fix it.
// forget about it, click off of the github page, and never look back.
// i have made the grave mistake of doing the opposite and continuing to dig myself deeper into this rabbit hole of decompilation.

// i am alone on this barren earth.

static CCArray* splitString(std::string input) // 0x0018c210 (for some reason doesn't have a debug symbol)
{
	CCArray* array = CCArray::create();

	size_t start = 0;
	size_t end = input.find(";");

	while (end != std::string::npos)
	{
		std::string token = input.substr(start, end - start);
		if (!token.empty()) {
			array->addObject(CCString::create(token.c_str()));
		}
		start = end + 1;
		end = input.find(";", start);
	}

	if (start < input.size())
	{
		std::string token = input.substr(start);
		if (!token.empty()) {
			array->addObject(CCString::create(token.c_str()));
		}
	}
	return array;
}

PlayLayer* PlayLayer::create(GJGameLevel* level)
{
    PlayLayer* pRet = new PlayLayer();
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

PlayLayer::PlayLayer()
{
    
}

void PlayLayer::onQuit()
{
    this->stopAllActions();
    this->unscheduleAllSelectors();
    SimpleAudioEngine* SAE = SimpleAudioEngine::sharedEngine();
    SAE->stopBackgroundMusic();
    GameManager* pGameManager = GameManager::sharedState();
    PlayLayer* playLayer = pGameManager->getPlayLayer();
    // (**(code **)(*playLayer + 0x238))();
    // pGameManager->returnToLastScene(m_level);
    pGameManager->fadeInMusic("menuLoop.mp3");
    return;
    
}

void PlayLayer::onExit()
{
	AppDelegate* AppDel = AppDelegate::get();
	if (!AppDel->getPaused())
		AppDel->setPaused(true);
		this->CCLayer::onExit();
}

void PlayLayer::onEnterTransitionDidFinish()
{
	AppDelegate::get()->setPaused(false);
	this->CCLayer::onEnterTransitionDidFinish();
	return;
}

CCScene* PlayLayer::scene(GJGameLevel* level)
{
    CCScene *scene = CCScene::create();
    AppDelegate* pApp = AppDelegate::get();
	pApp->setScenePointer(scene);
    PlayLayer* layer = PlayLayer::create(level);
    scene->addChild(layer);
    // scene->setObjType(5);
    return scene;
}

void PlayLayer::createObjectsFromSetup(std::string setup)
{

	CCArray* parts = splitString(setup);

	m_levelSettings =
		LevelSettingsObject::objectFromString(
		static_cast<CCString*>(parts->objectAtIndex(0))->getCString()
		);
	m_levelSettings->retain();


	/*m_levelSettings->updateColors(
		m_player->getGlowColor1(),
		m_player->getGlowColor2());*/

	m_tintObjectsUseBlend = m_levelSettings->getTintObjectsUseBlend();



	for (unsigned i = 1; i < parts->count(); ++i)
	{
		const char* objStr =
			static_cast<CCString*>(parts->objectAtIndex(i))->getCString();

		GameObject* obj = GameObject::objectFromString(objStr);
		
		if (obj)
		{
			// obj->setVisible(false);

			//if (!obj->getBlendAdditive())


			//obj->setObjectParent(m_batchNode);
			
			m_batchNode->addChild(obj);
			//this->addToSection(obj);

		}

	}
}

bool PlayLayer::init(GJGameLevel* level)
{
    if (!CCLayer::init())
        return false;
    // GameEffectsManager TODO
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	
	this->m_playbackMode = false;
	this->m_localLevel = level->getLevelType() == GJLevelType::LocalLevel;

	this->m_startPos = ccp(0.0f, 105.0f);

	this->m_attempts = 0;
	//this->field373_0x220 = 0;
	//this->field374_0x224 = 0;
	this->m_jumps = 0;
	this->m_endTriggered = false;
	this->m_isResetting = true;
	//this->field325_0x1c0 = 0.0;
	this->m_clkTimer = 0.0;

    GameManager* pGameManager = GameManager::sharedState();
    pGameManager->setEditMode(false);
    pGameManager->setPlayLayer(this);
    pGameManager->setWasHigh(false);
    
    m_level = level;
	level->retain();

    m_gameLayer = CCLayer::create();
	this->addChild(m_gameLayer);

	m_activeObjects = CCArray::create();

	m_stateObjects = CCArray::create();

	/*m_playerNode = CCNode::create();
	addChild(m_playerNode);*/

	CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("GJ_GameSheet.png");
    m_batchNode = CCSpriteBatchNode::createWithTexture(texture, 29);
	m_gameLayer->addChild(m_batchNode, 1);

	m_batchNodeAdd = CCSpriteBatchNode::createWithTexture(texture, 29);
	m_batchNodeAdd->setBlendFunc({ GL_SRC_ALPHA, GL_ONE});
	m_gameLayer->addChild(m_batchNodeAdd, 0);

	m_batchNodeBottom = CCSpriteBatchNode::createWithTexture(texture, 29);
	m_gameLayer->addChild(m_batchNodeBottom, -1);

	m_glitter = CCParticleSystemQuad::create("glitterEffect.plist");

    m_player = PlayerObject::create(pGameManager->getPlayerFrame(),
                                                pGameManager->getPlayerShip(),
												nullptr);
    this->addChild(m_player);

	this->createObjectsFromSetup(m_level->getLevelString());

	if (!m_levelSettings) {
		m_levelSettings = LevelSettingsObject::create();
		m_levelSettings->retain();
	}
	
	
	//m_background = CCSprite::create(pGameManager->getBGTexture(m_levelSettings->getBGIdx()));
	m_background = CCSprite::create(pGameManager->getBGTexture(1));
	m_background->setAnchorPoint({ 0, 0 });
	m_background->setScale(CCDirector::sharedDirector()->getScreenScaleFactorMax());
	m_background->setColor({ 0, 102, 255 });
	ccTexParams texParams = { GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT };
	m_background->getTexture()->setTexParameters(&texParams);
	m_background->setTextureRect(CCRectMake(0, 0, winSize.width * 2, m_background->getContentSize().height));
	m_gameLayer->addChild(m_background, -1);
	// m_bgWidth = winSize.width;

    //m_ground = GJGroundLayer::create(m_levelSettings->getGIdx());
	m_ground = GJGroundLayer::create(1);
	m_gameLayer->addChild(m_ground);
    
	m_uiLayer = UILayer::create();
	this->addChild(m_uiLayer);

    tintBackground(m_levelSettings->getStartBGColor(), 0.0f);
    tintGround(m_levelSettings->getStartGColor(), 0.0f);
    tintLine(m_levelSettings->getStartLineColor(), 0.0f);
    
    // i really need to come up with a good name for SAE variables
    SimpleAudioEngine* pAudioEngine = SimpleAudioEngine::sharedEngine();
	pAudioEngine->stopBackgroundMusic();
    
    m_attemptLabel = CCLabelBMFont::create("Attempt 1", "bigFont.fnt");
    m_gameLayer->addChild(m_attemptLabel, 3);

    runAction(CCSequence::create(
                CCDelayTime::create(1.0f),
                CCCallFunc::create(this, callfunc_selector(PlayLayer::startGame)), nullptr));
    
	this->m_cleanReset = true;

	updateVisibility();
    updateCamera(0.0f);
    // toggleAudioRain(false);
	toggleGlitter(false);
	GameManager::sharedState()->resetMusic();
    return true;
}

void PlayLayer::resetLevel()
{
	//i genuinely don't know these first 2 maybe i'll figure them out later
	/*this->field373_0x220 = 0;
	this->field374_0x224 = 0;*/
	m_resetQueued = false;
	m_isResetting = true;
	m_showingEndLayer = false;
	m_endTriggered = false;
	m_didAwardStars = false;
	m_didJump = false;

	/*FUN_003b1bb8(&this->field_0x214,&DAT_00401f12);
	*(undefined4 *)&this->field_0x20c = 0;*/

	// UILayer::enableMenu();

	// this->stopCameraShake();
	// this->field279_0x138 = 1;

	this->stopActionByTag(10);
	this->stopActionByTag(11);

	/*this->field315_0x1aa = false;
	this->field316_0x1ab = false;*/

	this->toggleGlitter(false);

	/*this->m_playerDead = false;
	this->field314_0x1a9 = this->m_cleanReset;
	this->clearPickedUpItems();*/

	// field277_0x130->removeAllObjects(); // this is a CCArray
	// field339_0x1e0->removeAllObjects(); // this is a CCDictionary

	this->m_flipValue = 0.0;
	/*this->field336_0x1d4 = 0.0;
	this->field_0x238 = 0;
	this->field337_0x1d8 = 1.0;*/
	this->stopActionByTag(14);

	this->m_cameraPortal = nullptr;
	//m_audioEffectsLayer->resetAudioVars();
	m_player->resetObject();
	//this->animateOutFlyGround(true);
	//this->animateOutRollGround(true);

	m_realPlayerPos = m_player->getPosition();
	//this->updateCamera();
	// this->updateVisibility();
    updateAttempts();
	m_isResetting = false;
}

void PlayLayer::fullReset()
{
	this->m_clkTimer = 0.0;
	/*this->field373_0x220 = 0;
	this->field374_0x224 = 0;
	this->field270_0x120 = true;*/
	this->m_cleanReset = true;
	this->m_attempts = 0;
	this->m_jumps = 0;

	if (!this->m_practiceMode)
		this->resetLevel();
	/*else
		this->togglePracticeMode(false);*/
}

void PlayLayer::startGame()
{
    scheduleUpdate();
	m_cleanReset = true;
	m_player->setVisible(true);
	this->resetLevel();
}

void PlayLayer::pauseGame()
{
	if (!m_endTriggered) {
		if (!AppDelegate::get()->getPaused()) {
			m_player->releaseButton(PlayerButton::Jump);
			SimpleAudioEngine* SAE = SimpleAudioEngine::sharedEngine();
			SAE->pauseAllEffects();
			SAE->pauseBackgroundMusic();
			auto pauseScreen = PauseLayer::create();
			this->getParent()->addChild(pauseScreen);
			this->onExit();
			pauseScreen->customSetup();
		}
	}
}

// updates
void PlayLayer::update(float dt)
{
	float step = dt * 60.0;

	if (!m_player->getIsLocked())
		//m_player->setPosition(m_realPlayerPos);

	m_player->setTouchedRing(nullptr);

	/*for (int i = 0; i > m_stateObjects->count(); ++i)
		static_cast<GameObject*>(m_stateObjects->objectAtIndex(i))->setStateVar(false);

	for (int i = 0; i > m_activeObjects->count(); ++i)
		m_activeObjects->objectAtIndex(i)->update(step);*/


	if (m_player->isFlying())
		m_player->updateShipRotation(step);


	// weird
	bool isUnlocked = m_player->getIsLocked();
	CCPoint newPlayerPos;
	if (!isUnlocked) {
		m_realPlayerPos = m_player->getPosition();
		float flipVal = m_flipValue;
		if ((flipVal != 0.0f) && (flipVal != 1.0f))
			if (flipVal == -1.0f)
				flipVal = 1.0f - flipVal;
		newPlayerPos = m_player->getPosition() + ccp(flipVal * 150.0f, 0.0f);
		isUnlocked = true;
	}
	else {
		isUnlocked = false;
	}

	updateCamera(step);
	updateVisibility();
	//checkSpawnObjects();
	m_clkTimer += dt;
	//m_audioEffectsLayer->audioStep(dt);
	//updateLevelColors();
	if (isUnlocked)
		m_player->setPosition(newPlayerPos);
	updateProgressbar();
	updateEffectPositions();
}


void PlayLayer::updateAttempts()
{
	// m_attemptLabel->setString(CCString::createWithFormat("Attempt %i", m_attempts)->getCString);
}


void PlayLayer::updateCamera(float dt)
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	float screenHeight = winSize.height;
	CCPoint camPos = m_cameraPos;	 
	CCPoint playerPos = m_player->getPosition();

	float targetY = camPos.y;

	if (playerPos.y > camPos.y + 120.0f) {
		targetY = playerPos.y - 120.0f;
	}

	if (playerPos.y < camPos.y + 90.0f) {
		targetY = playerPos.y - 90.0f;
	}

	camPos.y += (targetY - camPos.y) / (10.0f / dt);

	float maxY = 1740.0f - screenHeight;
	if (camPos.y < 0.0f) camPos.y = 0.0f;
	else if (camPos.y > maxY) camPos.y = 1740.0f;

	camPos.x = playerPos.x;

	m_cameraPos = camPos;

	CCCamera* camera = m_gameLayer->getCamera();
	camera->setCenterXYZ(camPos.x, camPos.y, 0.0f);
	camera->setEyeXYZ(camPos.x, camPos.y, camera->getZEye());
}

void PlayLayer::updateProgressbar()
{
    
}

void PlayLayer::updateEffectPositions()
{
    
}

void PlayLayer::tintBackground(ccColor3B color, float duration)
{
    m_background->setColor(color);
}

void PlayLayer::tintGround(ccColor3B color, float duration)
{
    m_ground->getGroundSprite()->setColor(color);
}

void PlayLayer::tintLine(ccColor3B color, float duration)
{
    m_ground->getLine()->setColor(color);
}

// toggles
void PlayLayer::toggleGlitter(bool visible)
{
	if (GameManager::sharedState()->getPerformanceMode())
		return;

	if (visible)
		m_glitter->resumeSystem();
	else
		m_glitter->stopSystem();
}

void PlayLayer::resume()
{

}

void PlayLayer::updateVisibility()
{

}

void PlayLayer::addToSection(GameObject* obj)
{

}