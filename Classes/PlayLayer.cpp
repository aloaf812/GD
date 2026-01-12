#include "PlayLayer.h"
#include "SimpleAudioEngine.h"
#include "GameManager.h"
#include "AppDelegate.h"
#include "LevelTools.h"
using namespace CocosDenshion;
USING_NS_CC;

// to whoever finds this code, please don't try to fix it.
// forget about it, click off of the github page, and never look back.
// i have made the grave mistake of doing the opposite and continuing to dig myself deeper into this rabbit hole of decompilation.

// i am alone on this barren earth.

void PlayLayer::onQuit()
{
    // CCNode::stopAllActions((CCNode *)this);
    // CCNode::unscheduleAllSelectors((CCNode *)this);
    SimpleAudioEngine* SAE = SimpleAudioEngine::sharedEngine();
    SAE->stopBackgroundMusic();
    GameManager* pGameManager = GameManager::sharedState();
    // piVar3 = (int *)(**(code **)(*piVar3 + 0x1c4))();
    // (**(code **)(*piVar3 + 0x238))();
    // pGameManager->returnToLastScene();
    pGameManager->fadeInMusic("menuLoop.mp3");
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

bool PlayLayer::init(GJGameLevel* level)
{
    if (!CCLayer::init())
        return false;
    // GameEffectsManager TODO
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    GameManager* pGameManager = GameManager::sharedState();
    pGameManager->setEditMode(false);
    pGameManager->setPlayLayer(this);
    pGameManager->setWasHigh(false);
    
    m_level = level;
    m_mainLayer = CCLayer::create();
    addChild(m_mainLayer);
    
    CCTextureCache* pTextureCache = CCTextureCache::sharedTextureCache();
    CCSpriteBatchNode::createWithTexture(pTextureCache->addImage("GJ_GameSheet.png"), 29);
    
    m_player = PlayerObject::create(pGameManager->getPlayerFrame(),
                                                pGameManager->getPlayerShip(),
                                                nullptr);
    this->addChild(m_player);
    
    m_levelSettings = LevelSettingsObject::objectFromString("kS1,255,kS2,4,kS3,181,kS4,226,kS5,0,kS6,138,kA1,1");
    
    m_backgroundSprite = CCSprite::create(pGameManager->getBGTexture(m_levelSettings->getBGIdx()));
    m_backgroundSprite->setAnchorPoint({0, 0});
    m_backgroundSprite->setScale(CCDirector::sharedDirector()->getScreenScaleFactorMax());
    m_backgroundSprite->setColor({ 0, 102, 255 });
    ccTexParams texParams = {GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT};
    m_backgroundSprite->getTexture()->setTexParameters(&texParams);
    m_backgroundSprite->setTextureRect(CCRectMake(0, 0, winSize.width * 2, m_backgroundSprite->getContentSize().height));
    m_mainLayer->addChild(m_backgroundSprite, -1);
    // m_bgWidth = winSize.width;
    
    m_ground = GJGroundLayer::create(m_levelSettings->getGIdx());
    m_mainLayer->addChild(m_ground);
    
    tintBackground(m_levelSettings->getStartBGColor(), 0.0f);
    tintGround(m_levelSettings->getStartGColor(), 0.0f);
    //tintLine(m_levelSettings->getStartLineColor(), 0.0f);
    
    // i really need to come up with a good name for SAE variables
    SimpleAudioEngine* pAudioEngine = SimpleAudioEngine::sharedEngine();
    pAudioEngine->stopBackgroundMusic();
    
    pAudioEngine->playBackgroundMusic(LevelTools::getAudioFileName(m_level->getAudioTrack()));
    
    m_attemptLabel = CCLabelBMFont::create("Attempt 1", "bigFont.fnt");
    m_mainLayer->addChild(m_attemptLabel, 3);
    
    runAction(CCSequence::create(
                CCDelayTime::create(1.0f),
                CCCallFunc::create(this, callfunc_selector(PlayLayer::startGame)), nullptr));
    
    updateCamera(0.0f);
    
    return true;
}

GJGameLevel* PlayLayer::getLevel() { return m_level; }

PlayerObject* PlayLayer::getPlayer() { return m_player; }

int PlayLayer::getAttempts() { return m_attempts; }

int PlayLayer::getJumps() { return m_jumps; }

CCPoint PlayLayer::getCameraPos() { return m_cameraPos; }

void PlayLayer::startGame()
{
    CCLOG("started");
    scheduleUpdate();
}

void PlayLayer::resetLevel()
{
    updateAttempts();
}

// updates
void PlayLayer::update(float dt)
{
    // ehh i'll decompile it later
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
    
    CCCamera* camera = m_mainLayer->getCamera();
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