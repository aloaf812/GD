#include "GameManager.h"

#include "AchievementManager.h"
#include "GameSoundManager.h"
#include "GameLevelManager.h"
#include "GameStatsManager.h"
#include "SimpleAudioEngine.h"
#include "GameToolbox.h"
#include "PlatformToolbox.h"
#include <stdio.h>

#include "CreatorLayer.h"
#include "MyLevelsLayer.h"
#include "MenuLayer.h"

USING_NS_CC;
using namespace CocosDenshion;

GameManager::GameManager()
{
	// todo
    m_didSyncAchievements = false;
    m_mainMenuActive = false;
    m_playerScoreValid = false;
    m_musicEnabled = false;
    m_fxEnabled = false;
    m_hasRatedGame = false;
	m_performanceMode = false;
	m_didLikeFacebook = false;
	m_didFollowTwitter = false;
    m_lastScene = LastGameScene::unk0;
    m_playerFrame = 0;
    m_playerShip = 0;
    m_playerBall = 0;
    m_playerBird = 0;
    m_playerColor = 0;
    m_playerColor2 = 0;
    m_playerStreak = 0;
    m_playerIconType = IconType::Cube;
    m_autoCheckpoints = false;
    m_showSongMarkers = false;
    m_showBPMMarkers = false;
    m_recordGameplay = false;
    m_autoRetryLevel = false;
    m_showProgressBar = false;
    m_performanceMode = false;
    m_commentSortRecent = false;
    m_showedPirate = false;
    m_clickedGarage = false;
    m_clickedEditor = false;
    m_clickedName = false;
    m_clickedPractice = false;
    m_showedEditorGuide = false;
    m_showedRateDiffDialog = false;
    m_showedRateStarDialog = false;
    m_showedLowDetailDialog = false;
    // m_gameRateDelegate = 0;
    m_lastLevelID = 0;
    m_loadedBGIdx = 0;
    m_loadedGIdx = 0;
    m_totalAttempts = 0;
    m_enableTutorial = false;
    m_editMode = false;
    m_wasHigh = false;
}

bool GameManager::init()
{
	m_saveFile = "CCGameManager.dat";
	unk_0xee = false;
    m_didSyncAchievements = false;
	unk_0xf8 = 0.0f;
	unk_0x100 = 0;
	unk_0x104 = "none";
	unk_0xef = false;
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
	if (this->m_didLikeFacebook != false) {
        GameManager* pGameManager = sharedState();
        pGameManager->reportAchievementWithID("geometry.ach.facebook", 100, false);
    }
    /* TODO: IMPLEMENT GameRateDelegate
    GameRateDelegate* rateDelegate = m_gameRateDelegate;
    if (rateDelegate != nullptr) {
        rateDelegate->updateRate();
    }*/
}

void GameManager::setup()
{
	unk_0xec = 1;
	GManager::load();
}

void GameManager::encodeDataTo(DS_Dictionary* dict)
{
	dict->setDictForKey("scoreKeeper", m_scoreKeeper);
	dict->setDictForKey("valueKeeper", m_valueKeeper);
	dict->setDictForKey("reportedAchievements", AchievementManager::sharedState()->getReportedAchievements());
	dict->setBoolForKey("gameCenterEnabled", m_gameCenterEnabled);
	dict->setBoolForKey("firstSetup", m_firstSetup);
	dict->setBoolForKey("showedFirstTutorial", m_showedFirstTutorial);
	dict->setBoolForKey("musicEnabled", m_musicEnabled);
	dict->setBoolForKey("fxEnabled", m_fxEnabled);
	dict->setStringForKey("playerUDID", m_playerUDID);
	dict->setStringForKey("playerName", m_playerName);
	dict->setIntegerForKey("playerUserID", m_playerUserID);
	dict->setIntegerForKey("playerFrame", m_playerFrame);
	dict->setIntegerForKey("playerShip", m_playerShip);
	dict->setIntegerForKey("playerBall", m_playerBall);
	dict->setIntegerForKey("playerBird", m_playerBird);
	dict->setIntegerForKey("playerColor", m_playerColor);
	dict->setIntegerForKey("playerColor2", m_playerColor2);
	dict->setIntegerForKey("playerIconType", (int)m_playerIconType);
	dict->setIntegerForKey("playerStreak", m_playerStreak);

	// MoreGamesManager::sharedState()->encodeDataTo(dict);
	// GameLevelManager::sharedState()->encodeDataTo(dict);
	GameStatsManager::sharedState()->encodeDataTo(dict);

	dict->setBoolForKey("autoCheckpoints", m_autoCheckpoints);
	dict->setBoolForKey("showSongMarkers", m_showSongMarkers);
	dict->setBoolForKey("showBPMMarkers", m_showBPMMarkers);
	dict->setBoolForKey("recordGameplay", m_recordGameplay);
	dict->setBoolForKey("autoRetryLevel", m_autoRetryLevel);
	dict->setBoolForKey("showProgressBar", m_showProgressBar);
	dict->setBoolForKey("commentSortRecent", m_commentSortRecent);
	dict->setBoolForKey("performanceMode", m_performanceMode);
	dict->setBoolForKey("clickedGarage", m_clickedGarage);
	dict->setBoolForKey("clickedEditor", m_clickedEditor);
	dict->setBoolForKey("clickedName", m_clickedName);
	dict->setBoolForKey("clickedPractice", m_clickedPractice);
	dict->setBoolForKey("showedEditorGuide", m_showedEditorGuide);
	dict->setBoolForKey("showedRateDiffDialog", m_showedRateDiffDialog);
	dict->setBoolForKey("showedRateStarDialog", m_showedRateStarDialog);
	dict->setBoolForKey("showedLowDetailDialog", m_showedLowDetailDialog);
	dict->setBoolForKey("kEnableTutorial", m_fullUnlocked);
	dict->setIntegerForKey("binaryVersion", 11);

	// dict->setIntegerForKey("timeCounter", getValidationNumber());
	dict->setBoolForKey("playerScoreValid", m_playerScoreValid);
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
    this->m_autoRetryLevel = dict->getBoolForKey("autoRetryLevel");
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

	GameLevelManager::sharedState()->dataLoaded(dict);

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
			bgStr = CCString::createWithFormat("game_bg_%02d_001.png", bgID);
			// pTextureCache->removeTextureForKey(bgStr->getCString);
		}
		bgStr = CCString::createWithFormat("game_bg_%02d_001.png", bgID);
		pTextureCache->addImage(bgStr->getCString());
		this->m_loadedBGIdx = bgID;
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
    if (groundID != this->m_loadedGIdx)
    {
        CCString* groundStr;
        CCTextureCache* pTextureCache = CCTextureCache::sharedTextureCache();
        if (this->m_loadedGIdx != 0)
        {
            groundStr = CCString::createWithFormat("groundSquare_%02d_001.png", groundID);
            // MISSING CC FUNCTION: pTextureCache->removeTextureForKey(groundStr->getCString);
        }
        groundStr = CCString::createWithFormat("groundSquare_%02d_001.png", groundID);
        pTextureCache->addImage(groundStr->getCString());
        this->m_loadedGIdx = groundID;
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
    if (true)
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
		this->m_didLikeFacebook = true;
    }
}

void GameManager::followTwitter()
{
    if (GameToolbox::doWeHaveInternet()) {
        CCApplication* pApplication = CCApplication::sharedApplication();
        pApplication->openURL("https://twitter.com/robtopgames");
		this->m_didFollowTwitter = true;
    }
}

void GameManager::toggleFX()
{   
	m_fxEnabled ^= 1;
	if (m_fxEnabled)
		SimpleAudioEngine::sharedEngine()->setEffectsVolume(1.0f);
    else
		SimpleAudioEngine::sharedEngine()->setEffectsVolume(0.0f);
}

void GameManager::toggleMusic()
{
	m_musicEnabled ^= 1;
    if (m_musicEnabled)
		GameSoundManager::sharedManager()->setBGMusicVolume(1.0f);
	else
		GameSoundManager::sharedManager()->setBGMusicVolume(0.0f);
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
    if (GameToolbox::doWeHaveInternet()) {
        PlatformToolbox::openAppPage();
        m_hasRatedGame = true;
    }
}

void GameManager::firstLoad()
{
	m_scoreKeeper = CCDictionary::create(); 
	m_scoreKeeper->retain();
	
	m_valueKeeper = CCDictionary::create(); 
	m_valueKeeper->retain();

	m_playerUDID = PlatformToolbox::getUniqueUserID();
	m_playerName = "Player";
	m_playerUserID = 0;
	m_playerColor2 = 3;
	m_gameCenterEnabled = false;
	m_firstSetup = true;
	m_showedFirstTutorial = false;
	m_playerColor = 0;
	m_playerFrame = 1;
	m_playerShip = 1;
	m_playerBall = 1;
	m_playerBird = 1;
	m_playerStreak = 1;
	m_playerIconType = IconType::Cube;
	m_musicEnabled = true;
	m_fxEnabled = true;

    GameSoundManager::sharedManager()->setBGMusicVolume(1.0f);
    SimpleAudioEngine::sharedEngine()->setEffectsVolume(1.0f);

    GameLevelManager::sharedState()->firstSetup();
	GameStatsManager::sharedState()->firstSetup();

	m_autoCheckpoints = true;
	m_showSongMarkers = true;
	m_showBPMMarkers = false;
	m_autoRetryLevel = true;
	m_showProgressBar = false;
	m_commentSortRecent = false;
	m_performanceMode = false;
	m_fullUnlocked = false;
	unk_0xef = true;
	m_showedRateDiffDialog = false;
	m_showedRateStarDialog = false;
	m_showedLowDetailDialog = false;
	m_recordGameplay = false;
	m_playerScoreValid = false;
}

void GameManager::resetMusic()
{

}

void GameManager::returnToLastScene(GJGameLevel* level)
{
	CCDirector* pDirector = CCDirector::sharedDirector();

	CCScene* targetScene;
	switch (m_lastScene) {
	case LastGameScene::SearchScene:
		targetScene = CreatorLayer::scene();
		break;
	case LastGameScene::EditorLevels:
		// targetScene = MyLevelsLayer::scene();
		break;
	case LastGameScene::unk3:
		// i dont think this is necessary yet
	default:
		targetScene = MenuLayer::scene();
		break;
	// skip a few
	case LastGameScene::LevelSelect:
		int currentLevel = 0;
		if (level) {
			currentLevel = 0;
			if (1 < level->getLevelID()) {
				currentLevel = level->getLevelID();
				currentLevel = currentLevel + -1;
			}
		}
		targetScene = LevelSelectLayer::scene(currentLevel);
	}

	pDirector->replaceScene(CCTransitionFade::create(0.5f, targetScene));
	sharedState()->fadeInMusic("menuLoop.mp3");
}