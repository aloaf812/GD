#include "PlayLayer.h"
#include "SimpleAudioEngine.h"
#include "GameManager.h"
#include "AppDelegate.h"
#include "LevelTools.h"
#include "PauseLayer.h"
using namespace CocosDenshion;
USING_NS_CC;

// to whoever finds this code, please don't try to fix it.
// forget about it, click off of the github page, and never look back.
// i have made the grave mistake of doing the opposite and continuing to dig myself deeper into this rabbit hole of decompilation.

// i am alone on this barren earth.

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
    PlayLayer* layer = PlayLayer::create(level);
    scene->addChild(layer);
    // scene->setObjType(5);
    return scene;
}

void PlayLayer::createObjectsFromSetup(std::string setup)
{

}

bool PlayLayer::init(GJGameLevel* level)
{
    if (!CCLayer::init())
        return false;
    // GameEffectsManager TODO
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
	m_endTriggered = false;

    GameManager* pGameManager = GameManager::sharedState();
    pGameManager->setEditMode(false);
    pGameManager->setPlayLayer(this);
    pGameManager->setWasHigh(false);
    
    m_level = level;
    m_gameLayer = CCLayer::create();
	addChild(m_gameLayer);

	/*m_mainNode = CCNode::create();
	addChild(m_mainNode);*/

    CCTextureCache* pTextureCache = CCTextureCache::sharedTextureCache();
    m_batchNode = CCSpriteBatchNode::createWithTexture(pTextureCache->addImage("GJ_GameSheet.png"), 29);
	m_gameLayer->addChild(m_batchNode, 1);

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

	//m_backgroundSprite = CCSprite::create(pGameManager->getBGTexture(m_levelSettings->getBGIdx()));
	m_backgroundSprite = CCSprite::create(pGameManager->getBGTexture(1));
	m_backgroundSprite->setAnchorPoint({ 0, 0 });
	m_backgroundSprite->setScale(CCDirector::sharedDirector()->getScreenScaleFactorMax());
	m_backgroundSprite->setColor({ 0, 102, 255 });
	ccTexParams texParams = { GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT };
	m_backgroundSprite->getTexture()->setTexParameters(&texParams);
	m_backgroundSprite->setTextureRect(CCRectMake(0, 0, winSize.width * 2, m_backgroundSprite->getContentSize().height));
	m_gameLayer->addChild(m_backgroundSprite, -1);
	// m_bgWidth = winSize.width;

    //m_ground = GJGroundLayer::create(m_levelSettings->getGIdx());
	m_ground = GJGroundLayer::create(1);
	m_gameLayer->addChild(m_ground);
    
	m_uiLayer = UILayer::create();
	this->addChild(m_uiLayer);

    //tintBackground(m_levelSettings->getStartBGColor(), 0.0f);
    //tintGround(m_levelSettings->getStartGColor(), 0.0f);
    //tintLine(m_levelSettings->getStartLineColor(), 0.0f);
    
    // i really need to come up with a good name for SAE variables
    SimpleAudioEngine* pAudioEngine = SimpleAudioEngine::sharedEngine();
	pAudioEngine->stopBackgroundMusic();
    
    m_attemptLabel = CCLabelBMFont::create("Attempt 1", "bigFont.fnt");
    m_gameLayer->addChild(m_attemptLabel, 3);

    runAction(CCSequence::create(
                CCDelayTime::create(1.0f),
                CCCallFunc::create(this, callfunc_selector(PlayLayer::startGame)), nullptr));
    
    updateCamera(0.0f);
    
    return true;
}

UILayer* PlayLayer::getUILayer() { return m_uiLayer; }

PlayerObject* PlayLayer::getPlayer() { return m_player; }

GJGameLevel* PlayLayer::getLevel() { return m_level; }

CCPoint PlayLayer::getCameraPos() { return m_cameraPos; }

bool PlayLayer::getIsResetting() { return m_isResetting; }

void PlayLayer::setIsResetting(bool var) { m_isResetting = var; }

CCSpriteBatchNode* PlayLayer::getBatchNode() { return m_batchNode; }

CCSpriteBatchNode* PlayLayer::getBatchNodeBottom() { return m_batchNodeBottom; }

CCSpriteBatchNode* PlayLayer::getBatchNodeAdd() { return m_batchNodeAdd; }

CCLayer* PlayLayer::getGameLayer() { return m_gameLayer; }

bool PlayLayer::getCleanReset() { return m_cleanReset; }

int PlayLayer::getAttempts() { return m_attempts; }

int PlayLayer::getJumps() { return m_jumps; }

bool PlayLayer::getDidJump() { return m_didJump; }

bool PlayLayer::getShowingEndLayer() { return m_showingEndLayer; }

void PlayLayer::setShowingEndLayer(bool var) { m_showingEndLayer = var; }

bool PlayLayer::getEndTriggered() { return m_endTriggered; }

void PlayLayer::setEndTriggered(bool var) { m_endTriggered = var; }

bool PlayLayer::getResetQueued() { return m_resetQueued; }

void PlayLayer::setResetQueued(bool var) { m_resetQueued = var; }

bool PlayLayer::getDidAwardStars() { return m_didAwardStars; }

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

	/*this->field313_0x1a8 = false;
	this->field314_0x1a9 = this->m_cleanReset;
	this->clearPickedUpItems();*/

	// field277_0x130->removeAllObjects(); // this is a CCArray
	// field339_0x1e0->removeAllObjects(); // this is a CCDictionary

	/*this->field392_0x23c = 0.0;
	this->field336_0x1d4 = 0.0;
	this->field_0x238 = 0;
	this->field337_0x1d8 = 1.0;*/
	this->stopActionByTag(14);

	// this->updateVisibility();
    updateAttempts();
	m_isResetting = false;
}

void PlayLayer::startGame()
{
    scheduleUpdate();
	m_cleanReset = true;
	//SimpleAudioEngine::sharedEngine()->playBackgroundMusic(LevelTools::getAudioFileName(m_level->getAudioTrack()));
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
    float step = 2.0f + dt * 60.0f;
    
    updateCamera(step);
    updateProgressbar();
    updateEffectPositions();
}

void PlayLayer::updateAttempts()
{
    
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
    m_backgroundSprite->setColor(color);
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