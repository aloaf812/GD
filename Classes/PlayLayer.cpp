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
	m_practiceMode = false;
	m_activeGColorAction = nullptr;
}

void PlayLayer::onQuit()
{
    this->stopAllActions();
    this->unscheduleAllSelectors();
    SimpleAudioEngine* SAE = SimpleAudioEngine::sharedEngine();
    SAE->stopBackgroundMusic();
    GameManager* pGameManager = GameManager::sharedState();
	// pGameManager->returnToLastScene(PLAY_LAYER->getLevel());
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
	
	GameManager* pGameManager = GameManager::sharedState();
	CCDirector* pDirector = CCDirector::sharedDirector();
	CCSize winSize = pDirector->getWinSize();

	// add missing code

	m_startPos = ccp(0.0f, 105.0f);

	// missing code

	pGameManager->setEditMode(false);
	pGameManager->setPlayLayer(this);
	pGameManager->setWasHigh(false);

#pragma region Variables
	m_level = level;
	level->retain();

	/*this->field_0x1dc = CCDictionary::create();
	field_0x1dc->retain();

	this->field_0x1e0 = CCDictionary::create();
	field_0x1e0->retain();*/

	this->m_gameLayer = CCLayer::create();
	this->addChild(m_gameLayer, 1);

	/*this->field_0x184 = CCDictionary::create();
	field_0x184->retain();

	this->field_0x12c = CCArray::create();
	field_0x12c->retain();

	this->field_0x130 = CCArray::create();
	field_0x130->retain();

	this->field_0x134 = CCArray::create();
	field_0x134->retain();

	this->field_0x188 = CCArray::create()
	field_0x188->retain();

	this->field_0x168 = CCArray::create();
	field_0x168->retain();*/

	this->m_activeObjects = CCArray::create();
	m_activeObjects->retain();

	/*this->field_0x178 = CCArray::create();
	field_0x178->retain();

	this->field_0x170 = CCArray::create();
	field_0x170->retain();*/

	this->m_stateObjects = CCArray::create();
	m_stateObjects->retain();

	this->m_bigActionContainer = CCArray::create();
	m_bigActionContainer->retain();

	this->field_0x1e4 = CCNode::create();
	this->addChild(field_0x1e4);
	field_0x1e4->setVisible(false);

	this->field_0x1ec = CCSprite::create();
	this->addChild(field_0x1ec);
	field_0x1ec->setVisible(false);

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
	this->m_batchNode = CCSpriteBatchNode::createWithTexture(texture, 29);
	m_gameLayer->addChild(m_batchNode, 1);

	// quite some more missing code

	
	this->m_glitter = CCParticleSystemQuad::create("glitterEffect.plist");
	m_glitter->setPositionType(tCCPositionType::kCCPositionTypeFree);
	m_gameLayer->addChild(m_glitter, 0);
	float scaleFactorW = pDirector->getScreenScaleFactorW();
	float scaleFactorH = pDirector->getScreenScaleFactorH();
	CCPoint glitterPos = CCPoint((scaleFactorW * 480.0) / 1.8, (scaleFactorH * 320.0) * 0.5);
	m_glitter->setPosVar(glitterPos);
	m_glitter->stopSystem();

#pragma region Player

	int pFrame = pGameManager->getPlayerFrame();
	int pShip = pGameManager->getPlayerShip();
	this->m_player = PlayerObject::create(pFrame, pShip, nullptr);

	int pColor = pGameManager->getPlayerColor();
	ccColor3B primaryColor = pGameManager->colorForIdx(pColor);
	m_player->setColor(primaryColor);

	int pColor2 = pGameManager->getPlayerColor2();
	ccColor3B secondColor = pGameManager->colorForIdx(pColor2);
	m_player->setSecondColor(secondColor);
	m_player->updateGlowColor();

	m_batchNode->addChild(m_player, 10);

#pragma endregion

	this->m_sections = CCArray::create();
	m_sections->retain();

	std::string levelString = m_level->getLevelString();
	this->createObjectsFromSetup(levelString);

	if (!m_levelSettings) {
		this->m_levelSettings = LevelSettingsObject::create();
		m_levelSettings->retain();
	}

	pGameManager = GameManager::sharedState();
	char const* bgSpriteFile = pGameManager->getBGTexture(m_levelSettings->getBGIdx());
	this->m_background = CCSprite::create(bgSpriteFile);
	ccTexParams texParams = { GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT };
	m_background->getTexture()->setTexParameters(&texParams);
	this->addChild(this->m_background, -1);

	m_background->setAnchorPoint(ccp(0.0f, 0.0f));
	m_background->setScale(pDirector->getScreenScaleFactorMax());
	m_background->setBlendFunc({ GL_SRC_ALPHA, GL_ONE });
	m_background->setColor(ccc3(40, 255, 125));
	// some weird math goes on in the midde of this...
	// m_background->setTextureRect(m_background->getUserData());
	
	/*this->m_ground = GJGroundLayer::create(m_levelSettings->getGIdx());
	this->addChild(m_ground, 4);
	this->m_ground2 = GJGroundLayer::create(m_levelSettings->getGIdx());
	this->addChild(m_ground2, 4);
	this->m_ground3 = GJGroundLayer::create(m_levelSettings->getGIdx());
	this->addChild(m_ground3, 4);
	this->m_ground3->setScaleY(1.0f);*/


	// temporary fix
	this->m_ground = GJGroundLayer::create(m_levelSettings->getGIdx());
	m_gameLayer->addChild(m_ground, 4);
	this->m_ground2 = GJGroundLayer::create(m_levelSettings->getGIdx());
	m_gameLayer->addChild(m_ground2, 4);
	this->m_ground3 = GJGroundLayer::create(m_levelSettings->getGIdx());
	m_gameLayer->addChild(m_ground3, 4);
	this->m_ground3->setScaleY(1.0f);

	// missing code

	this->m_uiLayer = UILayer::create();
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

	this->m_attemptLabel = CCLabelBMFont::create("Attempt 1", "bigFont.fnt");
	m_gameLayer->addChild(m_attemptLabel, 3);

	runAction(CCSequence::create(
		CCDelayTime::create(1.0f),
		CCCallFunc::create(this, callfunc_selector(PlayLayer::startGame)), nullptr));

	m_cleanReset = true;
	field383_0x1a9 = true;
	this->updateCamera(0.0f);
	m_attemptLabel->setPosition(ccp(winSize.width * 0.5f, (winSize.height * 0.5f) + 125.0f));
	
	this->m_progressBar = CCSprite::create("slidergroove2.png");
	this->addChild(m_progressBar, 10);
	this->m_progressFill = CCSprite::create("sliderBar2.png");
	this->field453_0x204 = 8.0f;
	// this->field449_0x200 = m_progressBar->getUserObject() - 4.0f;
	ccTexParams texParams2 = { GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT };
	m_progressFill->getTexture()->setTexParameters(&texParams2);
	m_progressFill->setColor(m_player->getGlowColor1());
	m_progressBar->addChild(m_progressFill, -1);

	m_progressFill->setPosition(ccp(0.0f, 0.0f));
	m_progressFill->setPosition(ccp(2.0f, 4.0f));
	m_progressBar->setPosition(ccp(winSize.width * 0.5, winSize.height - 8.0));

	this->updateProgressbar();
	this->toggleProgressbar();
	m_player->setVisible(this->m_testMode != false);

	this->tintBackground(m_levelSettings->getStartBGColor(), 0.0f);
	this->tintGround(m_levelSettings->getStartGColor(), 0.0f);
	this->tintLine(m_levelSettings->getStartLineColor(), 0.0f);
	this->tintObjects(m_levelSettings->getStartObjColor(), 0.0f);
	this->tintColorObjects(m_levelSettings->getStartTintObjColor(), 0.0f);

	this->updateLevelColors();
	//this->animateOutFlyGround(true);
	this->animateOutRollGround(true);

	//m_player->togglePlayerScale(m_levelSettings->getStartMiniMode());
	int startMode = m_levelSettings->getStartMode();
	if (startMode == 2) {
		//this->switchToRollMode(nullptr, true);
	}
	else if (startMode == 3) {
		//this->switchToFlyMode(nullptr, true, true);
	}

	this->field279_0x120 = true;
	this->updateVisibility();
	this->updateCamera(0.0f);
	//this->toggleAudioRain(false);
	this->toggleGlitter(false);
	pGameManager->resetMusic();
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

	m_uiLayer->enableMenu();

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
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
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
	CCPoint newPostion = ccp(this->getAnchorPointInPoints().x + winSize.width * 0.5f, (this->getAnchorPointInPoints().y + winSize.height) + 125.0f);
	m_attemptLabel->setPosition(newPostion);
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
	m_player->update(step);
	this->checkCollisions(step / 4);

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
	updateLevelColors();
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
	if (this->m_practiceMode == practice) {
		return;
	}
	this->m_practiceMode = practice;
	//m_uiLayer->toggleCheckpointsMenu(practice);
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
	// TODO
}

void PlayLayer::updateVisibility()
{

}

void PlayLayer::addToSection(GameObject* obj)
{

}

void PlayLayer::animateOutRollGround(bool instant)
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	CCSize winSize = pDirector->getWinSize();
	this->m_rollGroundActive = false;
	float groundYPos = m_ground2->getGroundSprite()->getPosition().y;
	CCPoint ground2Pos = ccp(0.0f, (pDirector->getScreenBottom() - 2.0f) - groundYPos);
	CCPoint ground3Pos = ccp(0.0f, (pDirector->getScreenTop() + 2.0f) - (winSize.height - groundYPos));
	m_ground2->deactivateGround();
	m_ground3->deactivateGround();
	if (!instant) {
		CCMoveTo* moveAction = CCMoveTo::create(0.4f, ground2Pos);
		CCEaseInOut* easeMove = CCEaseInOut::create(moveAction, 1.5f);

		CCMoveTo* moveAction2 = CCMoveTo::create(0.4f, ground3Pos);
		CCEaseInOut* easeMove2 = CCEaseInOut::create(moveAction2, 1.5f);

		CCSequence* doneSequence = CCSequence::create(CCDelayTime::create(0.6f), CCCallFunc::create(this, callfunc_selector(PlayLayer::animateOutRollGroundFinished)), nullptr);
		m_ground2->runAction(easeMove);
		m_ground3->runAction(easeMove2);
		m_ground3->runAction(doneSequence);
		m_ground2->fadeOutGround(0.4f);
		m_ground3->fadeOutGround(0.4f);
	}
	else {
		this->animateOutRollGroundFinished();
		m_ground2->setPosition(ground2Pos);
		m_ground3->setPosition(ground3Pos);
	}
}

void PlayLayer::animateOutRollGroundFinished()
{
	m_ground2->setVisible(false);
	m_ground3->setVisible(false);
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
	// field_0x1ab = true;
	CCEaseInOut* ease = CCEaseInOut::create(
		CCActionTween::create(duration, "cTY", m_cameraPos.y, value),
		rate);
	ease->setTag(11);
	this->runAction(ease);
}