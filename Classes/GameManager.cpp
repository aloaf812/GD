#include "GameManager.h"

#include "GameSoundManager.h"
#include "SimpleAudioEngine.h"
#include "GameToolbox.h"
#include "PlatformToolbox.h"
#include <stdio.h>
// 186 FUNCTIONS WHAT THE friendly BRO

// 65 variables aren't that insane for a class that manages save files
USING_NS_CC;
using namespace CocosDenshion;

GameManager::GameManager()
{
    this->offset_0x5 = false;                        
    this->m_didSyncAchievements = false;
    this->m_playerScoreValid = false;
    this->m_musicEnabled = false;
    this->m_fxEnabled = false;
    this->m_hasRatedGame = false;
    this->m_clickedFacebook = false;
    this->m_clickedTwitter = false;
    this->m_playerFrame = 0;
    this->m_playerShip = 0;
    this->m_playerBall = 0;
    this->m_playerBird = 0;
    this->m_playerColor = 0;
    this->m_playerColor2 = 0;
    this->m_playerStreak = 0;
    this->m_playerIconType = 0;
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
    this->m_gameRateDelegate = 0;
    this->m_lastLevelID = 0;
    this->m_loadedBgID = 0;
    this->m_loadedGroundID = 0;
    this->m_totalAttempts = 0;
    this->m_enableTutorial = false;
}

bool GameManager::init()
{
    // FUN_003b19f8(&this->data,"CCGameManager.dat");
    this->offset_0x5 = false;
    this->m_didSyncAchievements = false;
    this->offset_0xf = false;
    // this->data).offset_0x13 = 0;
    // FUN_003b19f8(&(this->data).offset_0x17,&DAT_00403859);
    // (this->data).offset_0x6 = 0;
  return true;
}

void GameManager::dataLoaded(DS_Dictionary* param_1)
{   // robtop why

    // dicionaries
    this->m_valueKeeper = 

    // bools
    this->m_gameCenterEnabled = DS_Dictionary::getBoolForKey("gameCenterEnabled");
    this->m_firstSetup = DS_Dictionary::getBoolForKey("firstSetup");
    this->m_showedFirstTutorial = DS_Dictionary::getBoolForKey("showedFirstTutorial");
    this->m_musicEnabled = DS_Dictionary::getBoolForKey("musicEnabled");
    // broken? m_fxEnabled = DS_Dictionary::getBoolForKey("fxEnabled");

    // intergers
    this->m_playerUserID = DS_Dictionary::getIntegerForKey("playerUserID");
    this->m_playerFrame = DS_Dictionary::getIntegerForKey("playerFrame");
    this->m_playerColor = DS_Dictionary::getIntegerForKey("playerColor");
    this->m_playerColor2 = DS_Dictionary::getIntegerForKey("playerColor2");

    // iVar9 = DS_Dictionary::getIntegerForKey("playerShip");

    // more bools
    this->m_autoCheckpoints = DS_Dictionary::getBoolForKey("autoCheckpoints");
    this->m_showSongMarkers = DS_Dictionary::getBoolForKey("showSongMarkers");
    this->m_showBPMMarkers = DS_Dictionary::getBoolForKey("showBPMMarkers");
    this->m_recordGameplay = DS_Dictionary::getBoolForKey("recordGameplay");
    this->m_autoRetry = DS_Dictionary::getBoolForKey("autoRetryLevel");
    this->m_showProgressBar = DS_Dictionary::getBoolForKey("showProgressBar");
    this->m_commentSortRecent = DS_Dictionary::getBoolForKey("commentSortRecent");
    this->m_performanceMode = DS_Dictionary::getBoolForKey("performanceMode");
    this->m_clickedEditor = DS_Dictionary::getBoolForKey("clickedEditor");
    this->m_clickedGarage = DS_Dictionary::getBoolForKey("clickedGarage");
    this->m_clickedName = DS_Dictionary::getBoolForKey("clickedName");
    this->m_clickedPractice = DS_Dictionary::getBoolForKey("clickedPractice");
    this->m_showedEditorGuide = DS_Dictionary::getBoolForKey("showedEditorGuide");
    this->m_playerScoreValid = DS_Dictionary::getBoolForKey("playerScoreValid");
    this->m_enableTutorial = DS_Dictionary::getBoolForKey("kEnableTutorial");
    this->m_showedRateDiffDialog = DS_Dictionary::getBoolForKey("showedRateDiffDialog");
    this->m_showedRateStarDialog = DS_Dictionary::getBoolForKey("showedRateStarDialog");
    this->m_showedLowDetailDialog = DS_Dictionary::getBoolForKey("showedLowDetailDialog");

}

void GameManager::loadBackground(int param_1)
{
    int bgID = param_1;
    if (3 < param_1) {
        bgID = 4;
    }
    if (param_1 < 1) {
        bgID = 1;
    }
    if (bgID != m_loadedBgID)
}

char const* GameManager::getBGTexture(int id)
{
    int bgID = id;
    if (3 < id) {
        bgID = 4;
    }
    if (id < 1) {
        bgID = 1;
    }
	this->loadBackground(bgID);
	return CCString::createWithFormat("game_bg_%02d_001.png", bgID)->getCString();
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
    // GameSoundManager* GSM = GameSoundManager::sharedState();
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
    // todo: implement achievements
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

std::string GameManager::colorKey(int param_1, UnlockType param_2)
{
    return CCString::createWithFormat("c%i_%i", param_1, param_2)->getCString();
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

void GameManager::rateGame()
{
    if (!GameToolbox::doWeHaveInternet()) {
        PlatformToolbox::openAppPage();
        // changes bool to true and unlocks the "supporter" achievement: (this->data).offset_0x4a = 1;
    }
}

void GameManager::firstLoad()
{
    // TODO: give proper names to these values, define in header file

    // this->m_scoreKeeper = CCDictionary::create()->retain;
    this->m_valueKeeper = CCDictionary::create()->retain;
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
    this->m_playerIconType = 0;
    this->m_musicEnabled = true;
    this->m_fxEnabled = true;
    /* pGVar2 = GameSoundManager::GameSoundManager(pGVar2);
     GameSoundManager::setBGMusicVolume(pGVar2,extraout_s0);
     this_00 = (SimpleAudioEngine *)CocosDenshion::SimpleAudioEngine::sharedEngine();
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