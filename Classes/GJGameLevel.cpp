#include "GJGameLevel.h"
#include "LevelTools.h"
USING_NS_CC;

GJGameLevel* GJGameLevel::create()
{
    static GJGameLevel* gGJGameLevel = NULL;
    if (!gGJGameLevel)
    {
        gGJGameLevel = new GJGameLevel();
        gGJGameLevel->init();
    }
    
    return gGJGameLevel;
}

GJGameLevel::GJGameLevel()
{
    m_levelID = 0;
    m_levelName = "";
    m_levelDesc = "";
    m_levelString = "";
    m_recordString = "";
    m_userID = 0;
    m_difficulty = 0;
    m_audioTrack = 0;
    // m_uploadDate = &DAT_004cf368;
    // m_updateDate = &DAT_004cf368;
    m_ratings = 0;
    m_ratingsSum = 0;
    m_downloads = 0;
    m_completes = 0;
    // m_isEditable = false;
    m_isVerified = false;
    // m_isUploaded = false;
    m_levelVersion = 0;
    m_gameVersion = 0;
    m_attempts = 0;
    m_jumps = 0;
    m_normalPercent = 0;
    m_practicePercent = 0;
    m_likes = 0;
    /*m_dislikes = 0;
    m_levelLength = 0;
    m_featured = 0;*/
    m_demon = false;
    m_stars = 0;
    m_autoLevel = false;
    m_coins = 0;
    m_levelSize = 0;
    m_password = 0;
    /*m_failedPasswordAttempts = 0;
    m_starRatings = 0;
    m_starRatingsSum = 0;
    m_maxStarRatings = 0;
    m_minStarRatings = 0;
    m_demonVotes = 0;*/
    m_dontSave = false;
    m_isHidden = false;
    m_requiredCoins = 0;
    m_isUnlocked = false;
    // cocos2d::CCPoint::CCPoint((CCPoint *)&m_lastCameraPos);
    /*m_lastBuildTab = 0;
    m_lastEditorZoom = 0;
    m_lastBuildPage = 0;*/
    m_levelType = GJLevelType::Default;
    // m_M_ID = 0;
}

bool GJGameLevel::init()
{
    m_levelName = "";
    m_levelDesc = "";
    m_levelString = "";
    m_levelType = GJLevelType::Default;
    m_attempts = 0;
    m_jumps = 0;
    m_coins = 0;
    m_stars = 0;
    m_demon = false;
    m_levelSize = 0;
    m_dontSave = false;
    m_isHidden = false;
    m_M_ID = 0;
    m_levelVersion = 1;
    this->setLastBuildSave(CCDictionary::create());
    return true;
}

GJGameLevel* GJGameLevel::create(CCDictionary* dict)
{
    GJGameLevel* level = GJGameLevel::create();
    
    int valInt = dict->valueForKey("1")->intValue();
    level->setLevelID(valInt);
    
    std::string valStr = dict->valueForKey("2")->getCString();
    level->setLevelName(valStr);
    
    valStr = dict->valueForKey("3")->getCString();
    level->setLevelDesc(valStr);
    
    valStr = dict->valueForKey("4")->getCString();
    level->setLevelString(valStr);
    
    valInt = dict->valueForKey("5")->intValue();
    level->setLevelVersion(valInt);
    
    valInt = dict->valueForKey("6")->intValue();
    level->setUserID(valInt);
    
    valInt = dict->valueForKey("8")->intValue();
    level->setRatings(valInt);
    
    valInt = dict->valueForKey("9")->intValue();
    level->setRatingsSum(valInt);
    
    valInt = dict->valueForKey("10")->intValue();
    level->setDownloads(valInt);
    
    valInt = dict->valueForKey("11")->intValue();
    level->setCompletes(valInt);
    
    valInt = dict->valueForKey("12")->intValue();
    level->setAudioTrack(valInt);
    
    valInt = dict->valueForKey("13")->intValue();
    level->setGameVersion(valInt);
    
    // likes used to be calculated locally, but now it's server-side
    valInt = dict->valueForKey("14")->intValue();
    level->setLikes(valInt);
    
    bool valBool = dict->valueForKey("17")->boolValue();
    level->setDemon(valBool);
    
    valBool = dict->valueForKey("25")->boolValue();
    level->setAutoLevel(valBool);
    
    return level;
}

// yep. you know the drill.
// void GJGameLevel::encodeWithCoder(DS_Dictionary* dict)
void GJGameLevel::encodeWithCoder(CCDictionary* dict)
{
    /*dict->setIntegerForKey("kCEK", 4);
    dict->setIntegerForKey("k1", m_levelID);
    dict->setStringForKey("k2", m_levelName);
    dict->setStringForKey("k3", m_levelDesc);
    if (((m_isHidden == false) && (m_dontSave == false)) && (m_levelType != GJLevelType::MainLevel)) {
        dict->setStringForKey("k4", m_levelString);
    }
    else {
        std::string(asStack_14,&DAT_00401d62,&pGStack_18);
        DS_Dictionary::setStringForKey(in_r1,"k4",asStack_14);
        FUN_003b16dc(asStack_14);
    //}
    //dict->setStringForKey("k5", m_creatorName);
    //dict->setStringForKey("k34", m_recordString);
    dict->setIntegerForKey("k6", m_userID);
    dict->setIntegerForKey("k7", m_difficulty);
    dict->setIntegerForKey("k8", m_audioTrack);
    dict->setIntegerForKey("k9", m_ratings);
    dict->setIntegerForKey("k10", m_ratingsSum);
    dict->setIntegerForKey("k11", m_downloads);
    dict->setIntegerForKey("k12", m_completes);
    dict->setBoolForKey("k13", m_isEditable);
    dict->setBoolForKey("k14", m_isVerified);
    dict->setBoolForKey("k15", m_isUploaded);*/
}

char const* GJGameLevel::getCoinKey(int coinNumber)
{
	return CCString::createWithFormat("%i_%i", m_levelID, coinNumber)->getCString();
}

void GJGameLevel::savePercentage(int percent, bool practiceMode)
{
	// todo
}