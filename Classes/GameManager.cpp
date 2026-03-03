#include "GameManager.h"

#include "AchievementManager.h"
#include "GameSoundManager.h"
#include "SimpleAudioEngine.h"
#include "GameToolbox.h"
#include "PlatformToolbox.h"
#include <stdio.h>

USING_NS_CC;
using namespace CocosDenshion;

GameManager::GameManager()
{
    this->offset_0x5 = false;                        
    this->m_didSyncAchievements = false;
    this->m_mainMenuActive = false;
    this->m_playerScoreValid = false;
    this->m_musicEnabled = false;
    this->m_fxEnabled = false;
    this->m_hasRatedGame = false;
	this->m_performanceMode = false;
    this->m_clickedFacebook = false;
    this->m_clickedTwitter = false;
    // this->m_lastScene = 0;
    this->m_playerFrame = 0;
    this->m_playerShip = 0;
    this->m_playerBall = 0;
    this->m_playerBird = 0;
    this->m_playerColor = 0;
    this->m_playerColor2 = 0;
    this->m_playerStreak = 0;
    // this->m_playerIconType = IconType::Cube;
    this->m_autoCheckpoints = false;
    this->m_showSongMarkers = false;
    this->m_showBPMMarkers = false;
    this->m_recordGameplay = false;
    this->m_autoRetry = false;
    this->m_showProgressBar = false;
    this->m_performanceMode = false;
    this->m_commentSortRecent = false;
    this->m_showedPirate = false;
    this->m_clickedGarage = false;
    this->m_clickedEditor = false;
    this->m_clickedName = false;
    this->m_clickedPractice = false;
    this->m_showedEditorGuide = false;
    this->m_showedRateDiffDialog = false;
    this->m_showedRateStarDialog = false;
    this->m_showedLowDetailDialog = false;
    // this->m_gameRateDelegate = 0;
    this->m_lastLevelID = 0;
    this->m_loadedBGIdx = 0;
    this->m_loadedGroundID = 0;
    this->m_totalAttempts = 0;
    this->m_enableTutorial = false;
    this->m_editMode = false;
    this->m_wasHigh = false;
}

bool GameManager::init()
{
    // FUN_003b19f8(&this->data,"CCGameManager.dat");
    this->offset_0x5 = false;
    this->m_didSyncAchievements = false;
    this->offset_0xf = false;
	// TEMPORARY FIX WHILE I DECOMP GMANAGER:
	this->firstLoad();
    // this->data).offset_0x13 = 0;
    // FUN_003b19f8(&(this->data).offset_0x17,&DAT_00403859);
    // (this->data).offset_0x6 = 0;
  return true;
}

void GameManager::applicationDidEnterBackground()
{

}

void GameManager::applicationWillEnterForeground()
{
    if (this->m_hasRatedGame != false) {
        GameManager* pGameManager = sharedState();
        pGameManager->reportAchievementWithID("geometry.ach.rate", 100, false);
    }
    CCLOG("clicked FB: %i", m_clickedFacebook);
    if (this->m_clickedFacebook != false) {
        GameManager* pGameManager = sharedState();
        pGameManager->reportAchievementWithID("geometry.ach.facebook", 100, false);
    }
    /* TODO: IMPLEMENT GameRateDelegate
    GameRateDelegate* rateDelegate = m_gameRateDelegate;
    if (rateDelegate != nullptr) {
        rateDelegate->updateRate();
    }*/
}

void GameManager::dataLoaded(DS_Dictionary* dict)
{   // robtop why

    // dicionaries
    // what?: this->m_valueKeeper =

    // bools
    /*this->m_gameCenterEnabled = dict->getBoolForKey("gameCenterEnabled");
    this->m_firstSetup = dict->getBoolForKey("firstSetup");
    this->m_showedFirstTutorial = dict->getBoolForKey("showedFirstTutorial");
    this->m_musicEnabled = dict->getBoolForKey("musicEnabled");
    this->m_fxEnabled = dict->getBoolForKey("fxEnabled");

    // intergers
    this->m_playerUserID = dict->getIntegerForKey("playerUserID");
    this->m_playerFrame = dict->getIntegerForKey("playerFrame");
    this->m_playerColor = dict->getIntegerForKey("playerColor");
    this->m_playerColor2 = dict->getIntegerForKey("playerColor2");

    // iVar9 = dict->getIntegerForKey("playerShip");

    // more bools
    this->m_autoCheckpoints = dict->getBoolForKey("autoCheckpoints");
    this->m_showSongMarkers = dict->getBoolForKey("showSongMarkers");
    this->m_showBPMMarkers = dict->getBoolForKey("showBPMMarkers");
    this->m_recordGameplay = dict->getBoolForKey("recordGameplay");
    this->m_autoRetry = dict->getBoolForKey("autoRetryLevel");
    this->m_showProgressBar = dict->getBoolForKey("showProgressBar");
    this->m_commentSortRecent = dict->getBoolForKey("commentSortRecent");
    this->m_performanceMode = dict->getBoolForKey("performanceMode");
    this->m_clickedEditor = dict->getBoolForKey("clickedEditor");
    this->m_clickedGarage = dict->getBoolForKey("clickedGarage");
    this->m_clickedName = dict->getBoolForKey("clickedName");
    this->m_clickedPractice = dict->getBoolForKey("clickedPractice");
    this->m_showedEditorGuide = dict->getBoolForKey("showedEditorGuide");
    this->m_playerScoreValid = dict->getBoolForKey("playerScoreValid");
    this->m_enableTutorial = dict->getBoolForKey("kEnableTutorial");
    this->m_showedRateDiffDialog = dict->getBoolForKey("showedRateDiffDialog");
    this->m_showedRateStarDialog = dict->getBoolForKey("showedRateStarDialog");
    this->m_showedLowDetailDialog = dict->getBoolForKey("showedLowDetailDialog");*/

}

void GameManager::loadBackground(int backID)
{
	int bgID = backID;
	if (3 < backID) {
        bgID = 4;
    }
	if (backID < 1) {
        bgID = 1;
    }
    if (bgID != m_loadedBGIdx) {
		CCString* bgStr;
		CCTextureCache* pTextureCache = CCTextureCache::sharedTextureCache();
		if (this->m_loadedBGIdx != 0)
		{
			bgStr = CCString::createWithFormat("groundSquare_%02d_001.png", bgID);
			// pTextureCache->removeTextureForKey(bgStr->getCString);
		}
		bgStr = CCString::createWithFormat("groundSquare_%02d_001.png", bgID);
		pTextureCache->addImage(bgStr->getCString());
		this->m_loadedGroundID = bgID;
    }
}

void GameManager::loadGround(int gID)
{
    int groundID = gID;
    if (3 < gID) {
        groundID = 4;
    }
    if (gID < 1) {
        groundID = 1;
    }
    if (groundID != this->m_loadedGroundID)
    {
        CCString* groundStr;
        CCTextureCache* pTextureCache = CCTextureCache::sharedTextureCache();
        if (this->m_loadedGroundID != 0)
        {
            groundStr = CCString::createWithFormat("groundSquare_%02d_001.png", groundID);
            // MISSING CC FUNCTION: pTextureCache->removeTextureForKey(groundStr->getCString);
        }
        groundStr = CCString::createWithFormat("groundSquare_%02d_001.png", groundID);
        pTextureCache->addImage(groundStr->getCString());
        this->m_loadedGroundID = groundID;
    }
}

// m_id in these 2 functions is a temporary variable used as a failsafe for overshooting on ground and background ids
char const* GameManager::getBGTexture(int bgID)
{
    int m_id = bgID;
    if (3 < bgID) {
        m_id = 4;
    }
    if (bgID < 1) {
        m_id = 1;
    }
	this->loadBackground(m_id);
	return CCString::createWithFormat("game_bg_%02d_001.png", m_id)->getCString();
}

char const* GameManager::getGTexture(int gID)
{
    int m_id = gID;
    if (3 < gID) {
        m_id = 4;
    }
    if (gID < 1) {
        m_id = 1;
    }
    this->loadGround(m_id);
    return CCString::createWithFormat("groundSquare_%02d_001.png", m_id)->getCString();
}

/* char const* GameManager::iconKey(int id, IconType type){
    switch (type) {
        case IconType::Cube:
        default:
            return cocos2d::CCString::createWithFormat("i_%i", id)->getCString();
        case IconType::Ship:
            return cocos2d::CCString::createWithFormat("ship_%i", id)->getCString();
        case IconType::Ball:
            return cocos2d::CCString::createWithFormat("ball_%i", id)->getCString();
        case IconType::Ufo:
            return cocos2d::CCString::createWithFormat("bird_%i", id)->getCString();
        case IconType::Special:
            return cocos2d::CCString::createWithFormat("special_%i", id)->getCString();
        }
    }
}
*/

void GameManager::fadeInMusic(char const *fileName){
    // shhh: GameSoundManager* GSM = GameSoundManager::sharedManager();
    if (false)
    {
        // todo: implement actual fading
        SimpleAudioEngine* SAE = SimpleAudioEngine::sharedEngine();
        SAE->setBackgroundMusicVolume(100.0f);
        SAE->playBackgroundMusic(fileName, true);
    }
    return;
}

void GameManager::syncPlatformAchievements()
{
    
}

GameManager* GameManager::sharedState()
{
    static GameManager* gGameManager = NULL;
    if (!gGameManager)
    {
        gGameManager = new GameManager();
        gGameManager->init();
    }
    
    return gGameManager;
}

void GameManager::reportAchievementWithID(char const* ach_ID, int percentage, bool param_3)
{
    AchievementManager* achMan = AchievementManager::sharedState();
    if (!achMan->isAchievementEarned(ach_ID)) {
        // literally no point in this: achMan = nullptr;
        if (99 < percentage) {
            this->completedAchievement(ach_ID);
        }
        achMan->reportAchievementWithID(ach_ID, percentage, param_3);
    }
}

void GameManager::completedAchievement(char const* ach_ID)
{

}

void GameManager::likeFacebook()
{
    if (GameToolbox::doWeHaveInternet()) {
        CCApplication* pApplication = CCApplication::sharedApplication();
        pApplication->openURL("https://www.facebook.com/geometrydash");
        this->m_clickedFacebook = true;
    }
}

void GameManager::followTwitter()
{
    if (GameToolbox::doWeHaveInternet()) {
        CCApplication* pApplication = CCApplication::sharedApplication();
        pApplication->openURL("https://twitter.com/robtopgames");
        this->m_clickedTwitter = true;
    }
}

void GameManager::toggleFX()
{
    SimpleAudioEngine* SAE = SimpleAudioEngine::sharedEngine();
    float volume;
    
    if (!(m_fxEnabled ^ 1)) { volume = 1.0f; }
    else { volume = 0.0f; }
    SAE->setEffectsVolume(volume);
}

void GameManager::toggleMusic()
{
	GameSoundManager* GSM = GameSoundManager::sharedManager();
    float volume;
    
    if (!(m_musicEnabled ^ 1)) { volume = 1.0f; }
    else { volume = 0.0f; }
    GSM->setBGMusicVolume(volume);
}

std::string GameManager::colorKey(int param_1, bool param_2)
{
    return CCString::createWithFormat("c%i_%d", param_1, param_2)->getCString();
}

int GameManager::colorForPos(int color)

{
    switch(color) {
        case 4: color = 16; break;
        case 5: color = 4; break;
        case 6: color = 5; break;
        case 7: color = 6; break;
        case 8: color = 13; break;
        case 9: color = 7; break;
        case 10: color = 8; break;
        case 11: color = 9; break;
        case 12: color = 10; break;
        case 13: color = 14; break;
        case 14: color = 11; break;
        case 15: color = 12; break;
        case 16: color = 17; break;
        case 17: color = 15;
    }
    return color;
}

ccColor3B GameManager::colorForIdx(int col)
{
    switch (col) {
        case 0: return ccc3(125, 255, 0);
        case 1: return ccc3(0, 255, 0);
        case 2: return ccc3(0, 255, 128);
        case 3: return ccc3(0, 255, 255);
        case 4: return ccc3(0, 200, 255);
        case 5: return ccc3(0, 125, 255);
        case 6: return ccc3(0, 0, 255);
        case 7: return ccc3(125, 0, 255);
        case 8: return ccc3(185, 0, 255);
        case 9: return ccc3(255, 0, 255);
        case 10: return ccc3(255, 0, 125);
        case 11: return ccc3(255, 0, 0);
        case 12: return ccc3(255, 125, 125);
        case 13: return ccc3(255, 125, 0);
        case 14: return ccc3(255, 185, 0);
		case 15: return ccc3(255, 255, 0);
		case 16: return ccc3(240, 211, 247);
        case 17: return ccc3(255, 255, 255);
        case 18: return ccc3(125, 225, 0);
        default: return ccc3(255, 225, 255);
    }
}

void GameManager::rateGame()
{
    if (!GameToolbox::doWeHaveInternet()) {
        PlatformToolbox::openAppPage();
        this->m_hasRatedGame = true;
    }
}

void GameManager::firstLoad()
{
    // TODO: give proper names to these values, define in header file

    // this->m_scoreKeeper = CCDictionary::create()->retain();
    // this->m_valueKeeper = CCDictionary::create()->retain();
    /* PlatformToolbox::getUniqueUserID();
     FUN_003b28d4(&(this->data).offset_0x3b,auStack_14);
     FUN_003b16dc(auStack_14);
     pGVar2 = (GameSoundManager *)FUN_003b19f8(&(this->data).offset_0x3f,"Player");*/
    this->m_playerUserID = 0;
    this->m_playerColor2 = 3;
    this->m_gameCenterEnabled = false;
    this->m_firstSetup = true;
    this->m_showedFirstTutorial = false;
    this->m_playerColor = 0;
    this->m_playerFrame = 1;
    this->m_playerShip = 1;
    this->m_playerBall = 1;
    this->m_playerBird = 1;
    this->m_playerStreak = 1;
    // this->m_playerIconType = IconType::Cube;
    this->m_musicEnabled = true;
    this->m_fxEnabled = true;
    GameSoundManager::sharedManager()->setBGMusicVolume(100.0f);
    /*this_00 = (SimpleAudioEngine *)CocosDenshion::SimpleAudioEngine::sharedEngine();
     CocosDenshion::SimpleAudioEngine::setEffectsVolume(this_00,extraout_s0_00);
     this_01 = (GameLevelManager *)GameLevelManager::sharedState();
     pGVar3 = (GameStatsManager *)GameLevelManager::firstSetup(this_01);
     pGVar3 = GameStatsManager::GameStatsManager(pGVar3);
     GameStatsManager::firstSetup(pGVar3);*/
    this->m_autoCheckpoints = true;
    this->m_showSongMarkers = true;
    this->m_showBPMMarkers = false;
    this->m_autoRetry = true;
    this->m_showProgressBar = false;
    this->m_commentSortRecent = false;
    this->m_performanceMode = false;
    this->m_enableTutorial = false;
    // (this->data).offset_0x6 = 1;
    this->m_showedRateDiffDialog = false;
    this->m_showedRateStarDialog = false;
    this->m_showedLowDetailDialog = false;
    this->m_recordGameplay = false;
    this->m_playerScoreValid = false;
}

void GameManager::resetMusic()
{

}