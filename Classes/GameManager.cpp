#include "GameManager.h"

#include "GameSoundManager.h"
#include "SimpleAudioEngine.h"
#include "GameToolbox.h"
#include "PlatformToolbox.h"
#include <stdio.h>

USING_NS_CC;
using namespace CocosDenshion;


bool GameManager::init(){
    // just list variables here as their initial state until a proper save system has been implemented
    m_clickedEditor = false;
    m_clickedGarage = false;
    m_clickedName = false;
    // weird function here
    // creates "CCGameManager.dat" file
    return true;
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
    return;
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
	return cocos2d::CCString::createWithFormat("game_bg_%02d_001.png", bgID)->getCString();
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
        // changes some value in save file: (this->data).offset_0x4b = 1;
    }
}

void GameManager::followTwitter()
{
    if (GameToolbox::doWeHaveInternet()) {
        CCApplication* pApplication = CCApplication::sharedApplication();
        pApplication->openURL("https://twitter.com/robtopgames");
        // changes some value in save file: (this->data).offset_0x4c = 1;
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
    /*CCObject *pCVar1;
     GameSoundManager *pGVar2;
     SimpleAudioEngine *this_00;
     GameLevelManager *this_01;
     GameStatsManager *pGVar3;
     float extraout_s0;
     float extraout_s0_00;
     undefined1 auStack_14 [4];
     
     pCVar1 = (CCObject *)cocos2d::CCDictionary::create();
     (this->data).offset_0x7 = pCVar1;
     cocos2d::CCObject::retain(pCVar1);
     pCVar1 = (CCObject *)cocos2d::CCDictionary::create();
     (this->data).offset_0xb = pCVar1;
     cocos2d::CCObject::retain(pCVar1);
     PlatformToolbox::getUniqueUserID();
     FUN_003b28d4(&(this->data).offset_0x3b,auStack_14);
     FUN_003b16dc(auStack_14);
     pGVar2 = (GameSoundManager *)FUN_003b19f8(&(this->data).offset_0x3f,"Player");
     (this->data).offset_0x43 = 0;
     (this->data).offset_0x6f = 3;
     (this->data).offset_0x37 = 0;
     (this->data).offset_0x38 = 1;
     (this->data).offset_0x39 = 0;
     (this->data).offset_0x6b = 0;
     (this->data).offset_0x5b = 1;
     (this->data).offset_0x5f = 1;
     (this->data).offset_0x63 = 1;
     (this->data).offset_0x67 = 1;
     (this->data).offset_0x73 = 1;
     (this->data).offset_0x77 = 0;
     (this->data).offset_0x48 = 1;
     (this->data).offset_0x49 = 1;
     pGVar2 = GameSoundManager::GameSoundManager(pGVar2);
     GameSoundManager::setBGMusicVolume(pGVar2,extraout_s0);
     this_00 = (SimpleAudioEngine *)CocosDenshion::SimpleAudioEngine::sharedEngine();
     CocosDenshion::SimpleAudioEngine::setEffectsVolume(this_00,extraout_s0_00);
     this_01 = (GameLevelManager *)GameLevelManager::sharedState();
     pGVar3 = (GameStatsManager *)GameLevelManager::firstSetup(this_01);
     pGVar3 = GameStatsManager::GameStatsManager(pGVar3);
     GameStatsManager::firstSetup(pGVar3);
     (this->data).offset_0x7b = 1;
     (this->data).offset_0x7c = 1;
     (this->data).offset_0x7d = 0;
     (this->data).offset_0x7f = 1;
     (this->data).offset_0x80 = 0;
     (this->data).offset_0x82 = 0;
     (this->data).offset_0x81 = 0;
     (this->data).offset_0xa7 = 0;
     (this->data).offset_0x6 = 1;
     (this->data).offset_0x89 = 0;
     (this->data).offset_0x8a = 0;
     (this->data).offset_0x8b = 0;
     (this->data).offset_0x7e = 0;
     (this->data).offset_0x47 = 0;*/
}