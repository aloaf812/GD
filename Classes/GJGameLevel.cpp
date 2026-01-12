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
    this->m_levelID = 0;
    this->m_levelName = "";
    this->m_levelDesc = "";
    this->m_levelString = "";
    //this->m_creatorName = "";
    //this->m_recordString = "";
    this->m_userID = 0;
    this->m_difficulty = 0;
    this->m_audioTrack = 0;
    // this->m_uploadDate = &DAT_004cf368;
    // this->m_updateDate = &DAT_004cf368;
    this->m_ratings = 0;
    this->m_ratingsSum = 0;
    this->m_downloads = 0;
    this->m_completes = 0;
    this->m_isEditable = false;
    this->m_isVerified = false;
    this->m_isUploaded = false;
    this->m_levelVersion = 0;
    this->m_gameVersion = 0;
    this->m_attempts = 0;
    this->m_jumps = 0;
    this->m_normalPercent = 0;
    this->m_practicePercent = 0;
    this->m_likes = 0;
    this->m_dislikes = 0;
    this->m_levelLength = 0;
    this->m_featured = 0;
    this->m_demon = false;
    this->m_stars = 0;
    this->m_autoLevel = false;
    this->m_coins = 0;
    this->m_levelSize = 0;
    this->m_password = 0;
    this->m_failedPasswordAttempts = 0;
    this->m_starRatings = 0;
    this->m_starRatingsSum = 0;
    this->m_maxStarRatings = 0;
    this->m_minStarRatings = 0;
    this->m_demonVotes = 0;
    this->m_dontSave = false;
    this->m_isHidden = false;
    this->m_requiredCoins = 0;
    this->m_isUnlocked = false;
    // cocos2d::CCPoint::CCPoint((CCPoint *)&this->m_lastCameraPos);
    this->m_lastBuildTab = 0;
    this->m_lastEditorZoom = 0;
    this->m_lastBuildPage = 0;
    this->m_levelType = GJLevelType::LocalLevel;
    this->m_M_ID = 0;
}

bool GJGameLevel::init()
{
    m_levelType = GJLevelType::LocalLevel;
    m_attempts = 0;
    m_jumps = 0;
    m_coins = 0;
    m_stars = 0;
    m_demon = false;
    m_levelSize = 0;
    m_dontSave = false;
    m_isHidden = false;
    m_levelVersion = 1;
    CCDictionary* levelDict = CCDictionary::create();
    levelDict->retain();
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
    
    // on second thought i'm just stupid
    /* can't test this lol, originally used to store the creator's name. might make a gdps for this
    valStr = dict->valueForKey("7")->getCString();
    level->setUserName(valStr); */
    
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
    dict->setIntegerForKey("k1", this->m_levelID);
    dict->setStringForKey("k2", this->m_levelName);
    dict->setStringForKey("k3", this->m_levelDesc);
    if (((this->m_isHidden == false) && (this->m_dontSave == false)) && (this->m_levelType != GJLevelType::MainLevel)) {
        dict->setStringForKey("k4", this->m_levelString);
    }
    else {
        std::string(asStack_14,&DAT_00401d62,&pGStack_18);
        DS_Dictionary::setStringForKey(in_r1,"k4",asStack_14);
        FUN_003b16dc(asStack_14);
    //}
    //dict->setStringForKey("k5", this->m_creatorName);
    //dict->setStringForKey("k34", this->m_recordString);
    dict->setIntegerForKey("k6", this->m_userID);
    dict->setIntegerForKey("k7", this->m_difficulty);
    dict->setIntegerForKey("k8", this->m_audioTrack);
    dict->setIntegerForKey("k9", this->m_ratings);
    dict->setIntegerForKey("k10", this->m_ratingsSum);
    dict->setIntegerForKey("k11", this->m_downloads);
    dict->setIntegerForKey("k12", this->m_completes);
    dict->setBoolForKey("k13", this->m_isEditable);
    dict->setBoolForKey("k14", this->m_isVerified);
    dict->setBoolForKey("k15", this->m_isUploaded);*/
}

// get functions
std::string GJGameLevel::getLevelName()
{
     return m_levelName;
}

std::string GJGameLevel::getLevelDesc()
{
    return m_levelDesc;
}

std::string GJGameLevel::getLevelString()
{
    return m_levelString;
}

int GJGameLevel::getLevelID()
{
    return m_levelID;
}

int GJGameLevel::getAudioTrack() { return m_audioTrack; }

int GJGameLevel::getDifficulty() { return m_difficulty; }

int GJGameLevel::getNormalPercent() { return m_normalPercent; }

int GJGameLevel::getDownloads()
{
    return m_downloads;
}

int GJGameLevel::getStars()
{
    return m_stars;
}

int GJGameLevel::getCoins()
{
    return m_coins;
}

// set functions
void GJGameLevel::setLevelID(int ID)
{
    this->m_levelID = ID;
}

void GJGameLevel::setLevelName(std::string name)
{
    m_levelName = name;
}

void GJGameLevel::setLevelDesc(std::string desc)
{
    this->m_levelDesc = desc;
}

void GJGameLevel::setLevelString(std::string string)
{
    this->m_levelString = string;
}

void GJGameLevel::setLevelVersion(int version)
{
    this->m_levelVersion = version;
}

void GJGameLevel::setUserID(int userID)
{
    this->m_userID = userID;
}

void GJGameLevel::setRatings(int ratings)
{
    this->m_ratings = ratings;
}

void GJGameLevel::setRatingsSum(int ratingsSum)
{
    this->m_ratingsSum = ratingsSum;
}

void GJGameLevel::setDownloads(int downloads)
{
    this->m_downloads = downloads;
}

void GJGameLevel::setCompletes(int completes)
{
    this->m_completes = completes;
}

void GJGameLevel::setAudioTrack(int audioTrack)
{
    this->m_audioTrack = audioTrack;
}

void GJGameLevel::setGameVersion(int gameVersion)
{
    this->m_gameVersion = gameVersion;
}

void GJGameLevel::setLikes(int likes)
{
    this->m_likes = likes;
}

void GJGameLevel::setDemon(bool demon)
{
    this->m_demon = demon;
}

void GJGameLevel::setAutoLevel(bool autoLevel)
{
    this->m_autoLevel = autoLevel;
}

void GJGameLevel::setDifficulty(int difficulty)
{
    m_difficulty = difficulty;
}

void GJGameLevel::setStars(int stars)
{
    this->m_stars = stars;
}

void GJGameLevel::setLevelType(GJLevelType levelType)
{
    this->m_levelType = levelType;
}

void GJGameLevel::setCoins(int coins)
{
    this->m_coins = coins;
}

void GJGameLevel::setNormalPercent(int var)
{
    m_normalPercent = var;
}
