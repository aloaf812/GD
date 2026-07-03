#include "PlayLayer.h"
#include "SimpleAudioEngine.h"
#include "GameManager.h"
#include "AppDelegate.h"
#include "LevelTools.h"
#include "PauseLayer.h"
#include "ObjectToolbox.h"
#include "CheckpointObject.h"
#include "GameStatsManager.h"
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
	m_practiceMode = false;
	m_activeGColorAction = nullptr;
}

void PlayLayer::onQuit()
{
    this->stopAllActions();
    this->unscheduleAllSelectors();
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(false);
	GameManager::sharedState()->returnToLastScene(PLAY_LAYER->getLevel());
	GameManager::sharedState()->fadeInMusic("menuLoop.mp3");
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
	CCLayer::onEnterTransitionDidFinish();
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
			
			obj->customSetup();
			this->addToSection(obj);
			m_batchNode->addChild(obj);

		}

	}
}

bool PlayLayer::init(GJGameLevel* level)
{
    if (!CCLayer::init())
        return false;

	bool recordGP = GameManager::sharedState()->getRecordGameplay();
	m_testMode = false;

#pragma region Variables
	float screenRight = CCDirector::sharedDirector()->getScreenRight();
	float screenLeft = CCDirector::sharedDirector()->getScreenLeft();
	float screenTop = CCDirector::sharedDirector()->getScreenTop();
	float screenBottom = CCDirector::sharedDirector()->getScreenBottom();
	float screenMiddle = screenRight * 0.5f;

	m_playbackMode = false;
	m_localLevel = level->getLevelType() == GJLevelType::LocalLevel;
	m_activeEnterEffect = EnterEffect::unk1;
	m_startPos = ccp(0.0f, 105.0f);
	m_attempts = 0;  
	unk_0x220 = 0.0;
	m_jumps = 0;
	m_realLevelLength = 0.0f;
	m_clkTimer = 0.0f;
	m_endTriggered = false;
	m_isResetting = true;

	GameManager::sharedState()->setEditMode(false);
	GameManager::sharedState()->setPlayLayer(this);
	GameManager::sharedState()->setWasHigh(false);

	m_level = level;
	level->retain();

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	m_particlesDictionary = CCDictionary::create();
	m_particlesDictionary->retain();

	unk_0x1e0 = CCDictionary::create();
	unk_0x1e0->retain();

	m_gameLayer = CCLayer::create();
	this->addChild(m_gameLayer, 1);

	unk_0x184 = CCDictionary::create();
	unk_0x184->retain();

	m_checkpoints = CCArray::create();
	m_checkpoints->retain();

	unk_0x130 = CCArray::create();
	unk_0x130->retain();
	
	unk_0x134 = CCArray::create();
	unk_0x134->retain();

	m_effectObjects = CCArray::create();
	m_effectObjects->retain();

	m_hazardsArray = CCArray::create();
	m_hazardsArray->retain();

	m_activeObjects = CCArray::create();
	m_activeObjects->retain();

	unk_0x178 = CCArray::create();
	unk_0x178->retain();

	unk_0x170 = CCArray::create();
	unk_0x170->retain();

	this->m_stateObjects = CCArray::create();
	m_stateObjects->retain();

	this->m_bigActionContainer = CCArray::create();
	m_bigActionContainer->retain();

	this->field_0x1e4 = CCNode::create();
	this->addChild(field_0x1e4);
	field_0x1e4->setVisible(false);

	this->m_objColorRef = CCSprite::create();
	this->addChild(m_objColorRef);
	m_objColorRef->setVisible(false);

	this->field_0x1f4 = CCSprite::create();
	this->addChild(field_0x1f4);
	field_0x1f4->setVisible(false);

	this->field_0x1e8 = CCSprite::create();
	this->addChild(field_0x1e8);
	field_0x1e8->setVisible(false);

	this->m_gColorRef = CCSprite::create();
	this->addChild(m_gColorRef);
	m_gColorRef->setVisible(false);
#pragma endregion

	CCTextureCache* pTextureCache = CCTextureCache::sharedTextureCache();
	CCTexture2D* texture = pTextureCache->addImage("GJ_GameSheet.png");
	m_batchNode = CCSpriteBatchNode::createWithTexture(texture, 29);
	m_gameLayer->addChild(m_batchNode, 1);

	m_batchNodeAdd = CCSpriteBatchNode::createWithTexture(texture, 29);
	ccBlendFunc blendFunc = { GL_SRC_ALPHA, GL_ONE };
	m_batchNodeAdd->setBlendFunc(blendFunc);
	m_gameLayer->addChild(m_batchNodeAdd, 0);

	m_batchNodeBottom = CCSpriteBatchNode::createWithTexture(texture, 29);
	m_gameLayer->addChild(m_batchNodeBottom, -1);

	m_flyGroundTop = GJFlyGroundLayer::create();
	this->addChild(m_flyGroundTop, 5);
	m_flyGroundBottom = GJFlyGroundLayer::create();
	this->addChild(m_flyGroundBottom, 5);

	float randVal = rand();
	unk_0x1b8 = roundf((randVal / RAND_MAX) + (randVal / RAND_MAX)) + 1;
	
	m_glitter = CCParticleSystemQuad::create("glitterEffect.plist");
	m_glitter->setPositionType(tCCPositionType::kCCPositionTypeFree);
	m_gameLayer->addChild(m_glitter, 0);
	m_glitter->setPosVar(CCPoint((SCREEN_SCALE_F_W * 480.0f) / 1.8f, (SCREEN_SCALE_F_H * 320.0f) * 0.5f));
	m_glitter->stopSystem();

#pragma region Player

	m_player = PlayerObject::create(GameManager::sharedState()->getPlayerFrame(),
		GameManager::sharedState()->getPlayerShip(), nullptr);
	m_player->setColor(GameManager::sharedState()->colorForIdx(GameManager::sharedState()->getPlayerColor()));
	m_player->setSecondColor(GameManager::sharedState()->colorForIdx(GameManager::sharedState()->getPlayerColor2()));
	m_player->updateGlowColor();
	m_batchNode->addChild(m_player, 10);

#pragma endregion

	m_sections = CCArray::create();
	m_sections->retain();

	this->createObjectsFromSetup(m_level->getLevelString());

	if (!m_levelSettings) {
		this->m_levelSettings = LevelSettingsObject::create();
		m_levelSettings->retain();
	}

	char const* bgSpriteFile = GameManager::sharedState()->getBGTexture(m_levelSettings->getBGIdx());
	m_background = CCSprite::create(bgSpriteFile);
	ccTexParams texParams = { GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT };
	m_background->getTexture()->setTexParameters(&texParams);
	this->addChild(m_background, -1);

	m_background->setAnchorPoint(ccp(0, 0));
	m_background->setScale(CCDirector::sharedDirector()->getScreenScaleFactorMax());
	ccBlendFunc bgBlendFunc = { GL_ONE, GL_ZERO };
	m_background->setBlendFunc(bgBlendFunc);
	m_background->setColor(ccc3(40, 125, 255));
	unk_0x15c = m_background->getTextureRect().size.height * m_background->getScale();
	m_background->setTextureRect(m_background->getTextureRect());

	m_ground = GJGroundLayer::create(m_levelSettings->getGIdx());
	m_gameLayer->addChild(m_ground, 4);
	m_rollGroundTop = GJGroundLayer::create(m_levelSettings->getGIdx());
	m_gameLayer->addChild(m_rollGroundTop, 4);
	m_rollGroundBottom = GJGroundLayer::create(m_levelSettings->getGIdx());
	m_gameLayer->addChild(m_rollGroundBottom, 4);
	m_rollGroundBottom->setScaleY(-1.0f);
	
	unk_0x140 = CCSprite::createWithSpriteFrameName("whiteSquare60_001.png");
	unk_0x140->setAnchorPoint(ccp(1, 0));
	unk_0x140->setBlendFunc(bgBlendFunc);
	// unk_0x140->setScaleX((winSize.width + 20.0f) / m_progressBar->unk_0x138);
	/*fVar6 = ((local_124 - 320.0) * 0.5 + 10.0 + 20.0) / m_progressBar->0x13c);
	uVar28 = (**(code **)(*(int *)this->field287_0x140 + 0x48))(this->field287_0x140, fVar6);*/
	unk_0x140->setPosition(ccp(-10, 0));
	unk_0x140->setColor(ccc3(0, 102, 255));
	m_flyGroundTop->addChild(unk_0x140, 5);

	// missing code

	m_uiLayer = UILayer::create();
	this->addChild(m_uiLayer, 10);

	// add other missing code

	m_player->setPosition(m_startPos);

	SimpleAudioEngine* SAE = SimpleAudioEngine::sharedEngine();
	SAE->stopBackgroundMusic(false);
	int audioTrack = m_level->getAudioTrack();
	char const* audioFile = LevelTools::getAudioFileName(audioTrack);
	SAE->preloadBackgroundMusic(audioFile);
	// std::string audioStr = LevelTools::getAudioString(audioTrack);
	// this->m_audioEffectsLayer = AudioEffectsLayer::create(audioStr);
	// field_0x13c->addChild(m_audioEffectsLayer, 1);
	// m_audioEffectsLayer->setVisible(false);

	m_attemptLabel = CCLabelBMFont::create("Attempt 1", "bigFont.fnt");
	m_gameLayer->addChild(m_attemptLabel, 3);

	runAction(CCSequence::create(
		CCDelayTime::create(1.0f),
		CCCallFunc::create(this, callfunc_selector(PlayLayer::startGame)), nullptr));

	m_cleanReset = true;
	unk_0x1a9 = true;
	this->updateCamera(0.0f);
	m_attemptLabel->setPosition(ccp(m_cameraPos.x + winSize.width * 0.5f, m_cameraPos.y + (winSize.height * 0.5f) + 125.0f));
	
	this->m_progressBar = CCSprite::create("slidergroove2.png");
	this->addChild(m_progressBar, 10);
	this->m_progressFill = CCSprite::create("sliderBar2.png");
	unk_0x204 = 8.0f;
	// unk_0x200 = m_progressBar->isDirty() - 4.0f;
	ccTexParams texParams2 = { GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT };
	m_progressFill->getTexture()->setTexParameters(&texParams);
	m_progressFill->setColor(m_player->getGlowColor1());
	m_progressBar->addChild(m_progressFill, -1);

	m_progressFill->setAnchorPoint(ccp(0.0f, 0.0f));
	m_progressFill->setPosition(ccp(2.0f, 4.0f));
	m_progressBar->setPosition(ccp(winSize.width * 0.5, winSize.height - 8.0));

	updateProgressbar();
	toggleProgressbar();
	m_player->setVisible(m_testMode);

	tintBackground(m_levelSettings->getStartBGColor(), 0.0f);
	tintGround(m_levelSettings->getStartGColor(), 0.0f);
	tintLine(m_levelSettings->getStartLineColor(), 0.0f);
	tintObjects(m_levelSettings->getStartObjColor(), 0.0f);
	tintColorObjects(m_levelSettings->getStartTintObjColor(), 0.0f);

	updateLevelColors();
	animateOutFlyGround(true);
	animateOutRollGround(true);

	m_player->togglePlayerScale(m_levelSettings->getStartMiniMode());
	int startMode = m_levelSettings->getStartMode();

	if (startMode == 2)
		switchToRollMode(nullptr, true);
	else if (startMode == 3)
		switchToFlyMode(nullptr, true, true);
	/*else
		switchToFlyMode(nullptr, true, false);*/
		
	unk_0x120 = true;
	updateVisibility();
	updateCamera(0.0f);
	toggleAudioRain(false);
	toggleGlitter(false);
	GameManager::sharedState()->resetMusic();
    return true;
}

void PlayLayer::resetLevel()
{
	unk_0x220 = 0;
	m_resetQueued = false;
	m_isResetting = true;
	m_showingEndLayer = false;
	m_endTriggered = false;
	m_didAwardStars = false;
	m_didJump = false;

	unk_0x214 = "";
	unk_0x20c = 0;

	m_uiLayer->enableMenu();

	// this->stopCameraShake();
	m_activeEnterEffect = EnterEffect::unk1;

	this->stopActionByTag(10);
	this->stopActionByTag(11);

	m_cameraMovingX = false;
	m_cameraMovingY = false;

	this->toggleGlitter(false);

	m_playerDead = false;
	unk_0x1a9 = m_cleanReset;
	// this->clearPickedUpItems();

	unk_0x130->removeAllObjects(); // this is a CCArray
	unk_0x1e0->removeAllObjects(); // this is a CCDictionary

	// unk_0x178 is unused so far so this will be unused for now
	/*for (int i = 0; i < unk_0x178->count(); i++) {
		piVar12 = unk_0x178->objectAtIndex(i);
		piVar12->resetObject();
		piVar12->setEnterEffect(EnterEffect::unk1);
	}*/

	this->m_flipValue = 0.0;
	// this->field336_0x1d4 = 0.0;
	this->m_isFlipped = false;
	//this->field337_0x1d8 = 1.0;
	this->stopActionByTag(14);

	this->m_cameraPortal = nullptr;
	//m_audioEffectsLayer->resetAudioVars();
	m_player->resetObject();
	this->animateOutFlyGround(true);
	this->animateOutRollGround(true);

	m_realPlayerPos = m_player->getPosition();
	this->updateCamera(0.0f);
	this->updateVisibility();
    updateAttempts();
	m_isResetting = false;
}

void PlayLayer::fullReset()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	this->m_clkTimer = 0.0;
	this->unk_0x220 = 0.0;
	this->unk_0x120 = true;
	this->m_cleanReset = true;
	this->m_attempts = 0;
	this->m_jumps = 0;

	if (m_practiceMode)
		togglePracticeMode(false);
	else
		resetLevel();

	m_attemptLabel->setPosition(ccp(m_cameraPos.x + winSize.width * 0.5f, (m_cameraPos.y + winSize.height * 0.5f) + 125.0f));
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
	if (!m_endTriggered && !AppDelegate::get()->getPaused()) {	
		m_player->releaseButton(PlayerButton::Jump);
		SimpleAudioEngine::sharedEngine()->pauseAllEffects();
		SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
		PauseLayer* pauseScreen = PauseLayer::create();
		this->getParent()->addChild(pauseScreen, 10);
		this->onExit();
		pauseScreen->customSetup();
	}
}

// updates
void PlayLayer::update(float dt)
{
	float step = dt * 60.0;

	if (!m_player->getIsLocked())
		m_player->setPosition(m_realPlayerPos);

		m_player->setTouchedRing(nullptr);

	for (int i = 0; i > m_stateObjects->count(); ++i)
		((GameObject*)(m_stateObjects->objectAtIndex(i)))->setStateVar(false);

	for (int i = 0; i > m_activeObjects->count(); ++i)
		m_activeObjects->objectAtIndex(i)->update(step);
	
	m_player->update(step);
	this->checkCollisions(step / 4);

	if (m_player->isFlying())
		m_player->updateShipRotation(step);

	for (int i = 0; 0 < m_stateObjects->count(); i = i + 1) {
		((GameObject *)m_stateObjects->objectAtIndex(i))->updateState();
	}

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
	updateLevelColors();
	if (isUnlocked)
		m_player->setPosition(newPlayerPos);
	updateProgressbar();
	updateEffectPositions();
}


void PlayLayer::updateAttempts()
{
	m_attempts++;
	GAME_MANAGER->setTotalAttempts(GAME_MANAGER->getTotalAttempts() + 1);
	char const* attemptString = CCString::createWithFormat("Attempt %i", m_attempts)->getCString();
	m_attemptLabel->setString(attemptString);

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	if (m_attempts != 1)
		m_attemptLabel->setPosition(ccp(m_cameraPos.x + (winSize.width * 0.5f) + 50.0f, m_cameraPos.y + (winSize.height * 0.5f) + 125.0f));
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

	camPos.x = playerPos.x - 125.0f;

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

void PlayLayer::updateLevelColors()
{
	// todo: finish
	m_ground->getGroundSprite()->setColor(m_gColorRef->getColor());

}



void PlayLayer::tintBackground(ccColor3B color, float duration)
{
    m_background->setColor(color);
}

void PlayLayer::tintGround(ccColor3B color, float duration)
{
	m_gColorRef->stopAllActions();
	ColorAction* cAction = ColorAction::create(this->getGColor(), color, duration, m_clkTimer);
	this->setActiveGColorAction(cAction);

	if (duration <= 0.0f)
		m_gColorRef->setColor(color);
	else {
		CCTintTo* tintAction = CCTintTo::create(duration, color.r, color.g, color.b);
		m_gColorRef->runAction(tintAction);
	}
}

void PlayLayer::tintLine(ccColor3B color, float duration)
{
    m_ground->getLine()->setColor(color);
}

void PlayLayer::tintObjects(ccColor3B color, float duration)
{

}

void PlayLayer::tintColorObjects(ccColor3B color, float duration)
{

}

ccColor3B PlayLayer::getLineColor()
{
	return m_ground->getLine()->getColor();
}

ccColor3B PlayLayer::getGColor()
{
	return m_ground->getGroundSprite()->getColor();
}


void PlayLayer::setActiveGColorAction(ColorAction* action)
{
	if (this->m_activeGColorAction != action) {
		if (action != nullptr)
			action->retain();

		if (this->m_activeGColorAction != nullptr)
			m_activeGColorAction->release();

			this->m_activeGColorAction = action;
	}
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

void PlayLayer::togglePracticeMode(bool practice)
{
	if (m_practiceMode == practice)
		return;

	m_practiceMode = practice;
	m_uiLayer->toggleCheckpointsMenu(practice);
	if (practice) {
		SimpleAudioEngine* SAE = SimpleAudioEngine::sharedEngine();
		SAE->pauseBackgroundMusic();
		SAE->playBackgroundMusic("StayInsideMe.mp3", true);
		return;
	}
	//while (int idx = m_checkpoints->count(), idx != 0) {
		// removeLastCheckpoint();
	//}
	this->m_cleanReset = true;
	resetLevel();
}

void PlayLayer::toggleProgressbar()
{
	m_progressBar->setVisible(GameManager::sharedState()->getShowProgressBar());
}

void PlayLayer::toggleAudioRain(bool toggle)
{
	// m_audioEffectsLayer->setRainActive(toggle);
}

void PlayLayer::registerStateObject(GameObject* obj)
{
	if (m_stateObjects->containsObject(obj)) {
		m_stateObjects->addObject(obj);
	}
}

void PlayLayer::resume()
{
	AppDelegate* pApp = AppDelegate::get();
	GameManager* pGameManager = GameManager::sharedState();
	SimpleAudioEngine* SAE = SimpleAudioEngine::sharedEngine();

	if (!pApp->getPaused()) {
		return;
	}

	pApp->setPaused(false);
	this->onEnter();
	SAE->resumeAllEffects();
	if (((pGameManager->getRecordGameplay() != false) && (!m_practiceMode)) && (!m_testMode)) {
		//this->tryStartRecord();
	}
	if (!m_practiceMode) {
		if (m_player->getPosition().x <= 0.0f) {
			return;
		}
		if (!SAE->isBackgroundMusicPlaying()) {
			char const* audioFile = LevelTools::getAudioFileName(m_level->getAudioTrack());
			SAE->playBackgroundMusic(audioFile, false);
		}
		//SAE->setBackgroundMusicTime(timeForXPos(m_player->getPosition().x, false));
	}
	SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	return;
}

void PlayLayer::resumeAndRestart()
{
	AppDelegate* pApp = AppDelegate::get();
	if (pApp->getPaused()) {
		pApp->setPaused(false);
		this->onEnter();
		this->resetLevel();
	}
}

void PlayLayer::updateVisibility()
{

}

void PlayLayer::addToSection(GameObject* obj)
{
	unsigned int targetSection = sectionForPos(obj->getPosition());
	if (m_sections->count() < targetSection + 1) {
		while (m_sections->count() < targetSection + 1) {
			m_sections->addObject(CCArray::create());
		}
	}
	CCArray* section = (CCArray*)m_sections->objectAtIndex(targetSection);
	section->addObject(obj);
	obj->setSectionIdx(targetSection);
}

void PlayLayer::switchToFlyMode(GameObject* obj, bool param_1, bool param_2)
{
	this->exitRollMode();

	if (obj) {
		m_player->setPortalP(obj->getPosition());
		m_player->setPortalObject(obj);
		m_cameraPortal = obj;
	}

	/*if (param_2)
		m_player->toggleBirdMode(true);
	else
		m_player->toggleFlyMode(true);*/

	this->toggleGlitter(true);

	// incomplete
}

void PlayLayer::switchToRollMode(GameObject* obj, bool)
{

}

void PlayLayer::exitAirMode()
{
	this->toggleGlitter(false);
	this->animateOutFlyGround(false);
	m_cameraMovingY = true;
}

void PlayLayer::exitBirdMode()
{
	m_player->toggleBirdMode(false);
	this->exitAirMode();
}

void PlayLayer::exitFlyMode()
{
	m_player->toggleFlyMode(false);
	this->exitAirMode();
}

void PlayLayer::exitRollMode()
{
	m_player->toggleRollMode(false);
	this->animateOutRollGround(false);
}

void PlayLayer::animateInFlyGround(bool instant)
{
	if (!m_flyGroundActive) {
		m_flyGroundActive = true;
		m_flyGroundTop->deactivateGround();
		m_flyGroundBottom->deactivateGround();
		m_flyGroundTop->setVisible(true);
		m_flyGroundBottom->setVisible(true);

		if (!instant) {
			CCMoveTo* moveAction = CCMoveTo::create(0.5f, ccp(0.0f, unk_0x1a0));
			CCEaseInOut* easeMove = CCEaseInOut::create(moveAction, 2.0f);

			CCMoveTo* moveAction2 = CCMoveTo::create(0.5f, ccp(0.0f, unk_0x1a4));
			CCEaseInOut* easeMove2 = CCEaseInOut::create(moveAction2, 2.0f);

			m_flyGroundTop->runAction(easeMove);
			m_flyGroundBottom->runAction(easeMove2);

			m_flyGroundTop->fadeOutGround(0.5f);
			m_flyGroundBottom->fadeOutGround(0.5f);
		}
		else {
			m_flyGroundTop->setPosition(ccp(0.0f, unk_0x1a0));
			m_flyGroundBottom->setPosition(ccp(0.0f, unk_0x1a4));
			m_flyGroundTop->showGround();
			m_flyGroundBottom->showGround();
		}
	}
}

void PlayLayer::animateOutFlyGround(bool instant)
{
	/*m_flyGroundActive = false;
	CCPoint groundTopPos = ccp(0.0f, CCDirector::sharedDirector()->getScreenBottom() - 2.0f);
	CCPoint groundBottomPos = ccp(0.0f, CCDirector::sharedDirector()->getScreenTop() + 2.0f);
	m_flyGroundTop->deactivateGround();
	m_flyGroundBottom->deactivateGround();

	if (instant) {
		animateOutFlyGroundFinished();
		m_flyGroundTop->setPosition(groundTopPos);
		m_flyGroundBottom->setPosition(groundBottomPos);
	}
	else {
		CCMoveTo* moveAction = CCMoveTo::create(0.4f, groundBottomPos);
		CCEaseInOut* easeMove = CCEaseInOut::create(moveAction, 1.5f);

		CCMoveTo* moveAction2 = CCMoveTo::create(0.4f, groundBottomPos);
		CCEaseInOut* easeMove2 = CCEaseInOut::create(moveAction2, 1.5f);

		CCDelayTime* delay = CCDelayTime::create(0.6f);
		CCSequence* doneSequence = CCSequence::create(delay, CCCallFunc::create(this, callfunc_selector(PlayLayer::animateOutFlyGroundFinished)), nullptr);

		m_flyGroundTop->runAction(easeMove);
		m_flyGroundBottom->runAction(easeMove2);
		m_flyGroundBottom->runAction(doneSequence);

		m_flyGroundTop->fadeOutGround(0.4f);
		m_flyGroundBottom->fadeOutGround(0.4f);
	}*/
}

void PlayLayer::animateOutFlyGroundFinished()
{
	m_flyGroundTop->setVisible(false);
	m_flyGroundBottom->setVisible(false);
}

void PlayLayer::animateInRollGround(bool instant)
{
	if (!m_rollGroundActive) {
		m_rollGroundActive = true;
		m_rollGroundTop->setVisible(true);
		m_rollGroundBottom->setVisible(true);
		m_rollGroundTop->deactivateGround();
		m_rollGroundBottom->deactivateGround();

		if (!instant) {
			CCMoveTo* moveAction = CCMoveTo::create(0.5f, ccp(0.0f, unk_0x190));
			CCEaseInOut* easeMove = CCEaseInOut::create(moveAction, 2.0f);

			CCMoveTo* moveAction2 = CCMoveTo::create(0.5f, ccp(0.0f, unk_0x194));
			CCEaseInOut* easeMove2 = CCEaseInOut::create(moveAction2, 2.0f);

			m_rollGroundTop->runAction(easeMove);
			m_rollGroundBottom->runAction(easeMove2);

			m_rollGroundTop->fadeOutGround(0.5f);
			m_rollGroundBottom->fadeOutGround(0.5f);
		}
		else {
			m_rollGroundTop->setPosition(ccp(0.0f, unk_0x190));
			m_rollGroundBottom->setPosition(ccp(0.0f, unk_0x194));
			m_rollGroundTop->showGround();
			m_rollGroundBottom->showGround();
		}
	}
}

void PlayLayer::animateOutRollGround(bool instant)
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	m_rollGroundActive = false;
	float groundYPos = m_rollGroundTop->getGroundSprite()->getPosition().y;
	CCPoint groundTopPos = ccp(0.0f, (CCDirector::sharedDirector()->getScreenBottom() - 2.0f) - groundYPos);
	CCPoint groundBottomPos = ccp(0.0f, (CCDirector::sharedDirector()->getScreenTop() + 2.0f) - (winSize.height - groundYPos));
	m_rollGroundTop->deactivateGround();
	m_rollGroundBottom->deactivateGround();

	if (instant) {
		animateOutRollGroundFinished();
		m_rollGroundTop->setPosition(groundTopPos);
		m_rollGroundBottom->setPosition(groundBottomPos);
	}
	else {
		CCMoveTo* moveAction = CCMoveTo::create(0.4f, groundTopPos);
		CCEaseInOut* easeMove = CCEaseInOut::create(moveAction, 1.5f);

		CCMoveTo* moveAction2 = CCMoveTo::create(0.4f, groundTopPos);
		CCEaseInOut* easeMove2 = CCEaseInOut::create(moveAction2, 1.5f);

		CCDelayTime* delay = CCDelayTime::create(0.6f);
		CCSequence* doneSequence = CCSequence::create(delay, CCCallFunc::create(this, callfunc_selector(PlayLayer::animateOutRollGroundFinished)), nullptr);
		
		m_rollGroundTop->runAction(easeMove);
		m_rollGroundBottom->runAction(easeMove2);
		m_rollGroundBottom->runAction(doneSequence);

		m_rollGroundTop->fadeOutGround(0.4f);
		m_rollGroundBottom->fadeOutGround(0.4f);
	}
}

void PlayLayer::animateOutRollGroundFinished()
{
	m_rollGroundTop->setVisible(false);
	m_rollGroundBottom->setVisible(false);
}

void PlayLayer::checkCollisions(float dt)
{
	float playerScale = m_player->getPlayerScale();
	if (playerScale != 1.0f)
		playerScale = 1.0f - playerScale;

	float balancer;
	if (playerScale == 1.0f)
		balancer = 0.0f;
	else
		balancer = (playerScale * 30.0f) * 0.5f;

	if (m_player->getPosition().y > (105.0f - balancer) || m_player->isFlying()) {
		if (m_player->getPosition().y > (balancer + 1890.0f)) {
			this->destroyPlayer();
			return;
		}
	}
	else {
		if (m_player->getGravityFlipped()) {
			if (m_player->isSafeFlip()) {
				// missing stuff
				m_player->hitGround(true);
				return;
			}
			this->destroyPlayer();
			return;
		}

		if (!m_player->getIsJumping()) {
			m_player->setPosition(ccp(m_player->getPosition().x, 105.0f - balancer));
			m_player->hitGround(false);
		}
	}

	// welcome to the worst switch statement i've had to write so far
	int currentSection = this->sectionForPos(m_player->getPosition());
	int idx;
	GameObject* currentObject;
	for (idx = currentSection - 1; idx <= currentSection + 1; idx = idx + 1) {
		if ((-1 < idx) && (idx < m_sections->count()))
		{
			CCArray* this_00 = (CCArray *)m_sections->objectAtIndex(idx);
			for (int objIdx = 0; objIdx < this_00->count(); objIdx = objIdx + 1
				) {
				currentObject = (GameObject *)this_00->objectAtIndex(objIdx);
				if (currentObject->getIsSleeping())
					return;

				if (currentObject->getType() == Hazard) {
					m_hazardsArray->addObject(currentObject);
					goto LAB_0018ffd8;
				}

				if ((currentObject->getIsDisabled()) || (currentObject->getHasBeenActivated()))
					return;

				if (!(m_player->getObjectRect().intersectsRect(currentObject->getObjectRect()))) 
					return;
					// || ((0.0f < currentObject->getRadius() && (!(objectIntersectsCircle(m_player, currentObject))))

				switch (currentObject->getType()) {
				case InvertGravityPortal:
					if (!m_player->getGravityFlipped()) {
						// this->playGravityEffect(true);
					}
					m_player->setPortalP(currentObject->getPosition());
					m_player->setPortalObject(currentObject);
					// m_player->flipGravity(true, false);
					break;
				case NormalGravityPortal:
					if (m_player->getGravityFlipped()) {
						// this->playGravityEffect(false);
					}
					m_player->setPortalP(currentObject->getPosition());
					m_player->setPortalObject(currentObject);
					// m_player->flipGravity(false, false);
					break;
				case ShipPortal:
					this->switchToFlyMode(currentObject, false, false);
					break;
				case CubePortal:
					m_player->setPortalP(currentObject->getPosition());
					m_player->setPortalObject(currentObject);
					this->exitFlyMode();
					this->exitBirdMode();
					this->exitRollMode();
					break;
				default:
					m_player->collidedWithObject(dt, currentObject);
					return;
					// skip some more
				case YellowPad:
				case GravityPad:
					m_player->setPortalP(currentObject->getPosition());
					currentObject->triggerActivated();
					if (((currentObject->getType() == GravityPad) && !m_player->getFlyMode()) && !m_player->getBirdMode())
						m_player->getRollMode();

					m_player->setPortalObject(currentObject);
					this->switchToFlyMode(currentObject, false, false);
					// m_player->propellPlayer(fVar3);
					// goto LAB_0018ffd8;
					break;
				}
			}
		}
	}

LAB_0018ffd8:

	unsigned int haIdx = 0;
	while (true) {
		if (m_hazardsArray->count() <= haIdx) {
			m_hazardsArray->removeAllObjects();
			return;
		}

		currentObject = (GameObject*)m_hazardsArray->objectAtIndex(haIdx);
		// doesnt work for some reason
		if ((m_player->getObjectRect().intersectsRect(currentObject->getObjectRect())) && (currentObject->getRadius() <= 0.0f)) // || (objectIntersectsCircle(m_player, currentObject)) && (!m_playbackMode))))
			break;

		haIdx = haIdx + 1;
	}
	this->destroyPlayer();
}

int PlayLayer::sectionForPos(CCPoint point)
{
	return floorf(point.x);
}

void PlayLayer::recordAction(bool pressed)
{
	if (m_localLevel != false) {
		if (pressed) {
			field391_0x211 = true;
			return;
		}
		field392_0x212 = true;
	}
}

bool PlayLayer::isFlipping()
{
	if (m_flipValue == 0.0) {
		return false;
	}
	return m_flipValue != 1.0;
}

void PlayLayer::destroyPlayer()
{
	if (!m_player->getIsLocked() && !m_playerDead) {
		if (!m_showingHint && (m_level->getLevelID() == 1) && !m_player->getHasJumped() && m_attempts > 1)
			this->showHint();

		if (!m_showingHint && (m_level->getLevelID() == 3) && !m_player->getHasRingJumped() && m_attempts > 1)
			this->showHint();
		
		// bVar1 = true;
		m_playerDead = true;
		m_player->playerDestroyed();
		
		// more left to implement
	}
}

void PlayLayer::showHint()
{
	this->m_showingHint = true;
	CCDirector* pDirector = CCDirector::sharedDirector();
	CCSize winSize = pDirector->getWinSize();

	float delayTime;
	float scale;
	char const* string;

	if (m_level->getLevelID() == 1) {
		delayTime = 3.0f;
		scale = 0.7f;
		string = "Tap to jump over the spikes";
	}
	else {
		delayTime = 4.0f;
		scale = 0.6f;
		string = "Tap while touching a ring to jump mid air";
	}

	CCLabelBMFont* hintLabel = CCLabelBMFont::create(string, "bigFont.fnt");
	hintLabel->setScale(scale);
	this->addChild(hintLabel, 3);
	hintLabel->setPosition(ccp(winSize.width * 0.5f, (winSize.height * 0.5f) + 60.0f));
	hintLabel->setOpacity(0);

	hintLabel->runAction(CCSequence::create(
		CCFadeIn::create(0.5f),
		CCDelayTime::create(delayTime),
		CCFadeOut::create(0.5f),
		CCCallFunc::create(hintLabel, callfunc_selector(CCNode::removeMeAndCleanup))));
}

std::string PlayLayer::getParticleKey(int objType, char const* file, int zOrder, cocos2d::tCCPositionType positionType)
{
	return CCString::createWithFormat("%i%s%i%i", objType, file, zOrder, positionType)->getCString();
}

/*std::string PlayLayer::getParticleKey2(std::string pKey)
{
	return CCString::createWithFormat("%s%s", pKey, )->getCString();
}*/

void PlayLayer::createParticle(int objType, char const* file, int zOrder, cocos2d::tCCPositionType positionType)
{
	GameManager* pGameManager = GameManager::sharedState();

	if (!pGameManager->getPerformanceMode()) {
		std::string particleKey = this->getParticleKey(objType, file, zOrder, positionType);
		if (!m_particlesDictionary->objectForKey(particleKey)) {
			// TODO: add better names to these variables
			CCArray* pCVar3 = CCArray::create();
			CCArray* pCVar4 = CCArray::create();
			m_particlesDictionary->setObject(pCVar3, particleKey);
			// m_particlesDictionary->setObject(pCVar4, this->getParticleKey2(particleKey));
		}
	}
}

void PlayLayer::playSpeedParticle(float timeMod)
{
	// todo
}

void PlayLayer::moveCameraToPos(cocos2d::CCPoint pos)
{
	cameraMoveX(pos.y, 1.2f, 1.8f);
	cameraMoveY(pos.x, 1.2f, 1.8f);
}

void PlayLayer::cameraMoveX(float value, float duration, float rate)
{
	this->stopActionByTag(10);
	// field_0x1aa = true;
	CCEaseInOut* ease = CCEaseInOut::create(
		CCActionTween::create(duration, "cTX", m_cameraPos.x, value),
		rate);
	ease->setTag(10);
	this->runAction(ease);
}

void PlayLayer::cameraMoveY(float value, float duration, float rate)
{
	this->stopActionByTag(11);
	m_cameraMovingY = true;
	CCEaseInOut* ease = CCEaseInOut::create(
		CCActionTween::create(duration, "cTY", m_cameraPos.y, value),
		rate);
	ease->setTag(11);
	this->runAction(ease);
}

CheckpointObject* PlayLayer::createCheckpoint()
{
	CheckpointObject* check = CheckpointObject::create();
	m_player->saveToCheckpoint(check);
	check->setTimeStamp(m_clkTimer);

	// todo

	return check;
}


void PlayLayer::storeCheckpoint(CheckpointObject* check)
{
	m_checkpoints->addObject(check);
	addToSection(check->getObject());
}

void PlayLayer::markCheckpoint()
{
	if (!m_player->getIsDead()) {
		CheckpointObject* check = createCheckpoint();
		storeCheckpoint(check);
		check->getObject()->activateObject();
	}
}

bool PlayLayer::hasUniqueCoin(GameObject* obj)
{
	char const* key = m_level->getCoinKey(obj->getUniqueID());
	return GameStatsManager::sharedState()->hasUniqueItem(key);
}

void PlayLayer::incrementJumps()
{ 
	m_didJump = true;
	GameStatsManager::sharedState()->incrementStat("1");
	m_jumps++;
	m_level->setJumps(m_level->getJumps() + 1);
}