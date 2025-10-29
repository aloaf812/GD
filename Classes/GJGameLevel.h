#ifndef __GeometryDash__GJGameLevel__
#define __GeometryDash__GJGameLevel__

#include "cocos2d.h"
#include <stdio.h>

enum class GJLevelType {
    MainLevel = 1,
    // i may be wrong with these two
    OnlineLevel = 2,
    LocalLevel = 0
};

class GJGameLevel : public cocos2d::CCNode {
public:
    GJGameLevel();
    static GJGameLevel* create();
    static GJGameLevel* create(cocos2d::CCDictionary* level);
    virtual bool init();

    void encodeWithCoder(DS_Dictionary* dict);
    // get functions
    static std::string getLevelName();
    // set functions
    void setLevelID(int ID);
    void setLevelName(std::string name);
    void setLevelDesc(std::string desc);
    void setLevelString(std::string string);
    void setLevelVersion(int version);
    void setUserID(int userID);
    void setRatings(int ratings);
    void setRatingsSum(int ratingsSum);
    void setDownloads(int downloads);
    void setCompletes(int completes);
    void setAudioTrack(int audioTrack);
    void setGameVersion(int gameVersion);
    void setLikes(int likes);
    void setDemon(bool demon);
    void setAutoLevel(bool autoLevel);
    void setDifficulty(int difficulty);
    void setStars(int stars);
    void setLevelType(GJLevelType levelType);
    void setCoins(int coins);
// protected:
    int m_levelID;
    std::string m_levelName;
    std::string m_levelDesc;
    std::string m_levelString;
    std::string m_creatorName;
    std::string m_recordString;
    int m_userID;
    int m_difficulty;
    int m_audioTrack;
    // ??? m_uploadDate;
    // ??? m_updateDate;
    int m_ratings;
    int m_ratingsSum;
    int m_downloads;
    int m_completes;
    bool m_isEditable;
    bool m_isVerified;
    bool m_isUploaded;
    int m_levelVersion;
    int m_gameVersion;
    int m_attempts;
    int m_jumps;
    int m_normalPercent;
    int m_practicePercent;
    int m_likes;
    int m_dislikes;
    int m_levelLength;
    int m_featured;
    bool m_demon;
    int m_stars;
    bool m_autoLevel;
    int m_coins;
    int m_levelSize;
    int m_password;
    int m_failedPasswordAttempts;
    int m_starRatings;
    int m_starRatingsSum;
    int m_maxStarRatings;
    int m_minStarRatings;
    int m_demonVotes;
    bool m_dontSave;
    bool m_isHidden;
    int m_requiredCoins;
    bool m_isUnlocked;
    cocos2d::CCPoint* m_lastCameraPos;
    int m_lastBuildTab;
    int m_lastEditorZoom;
    int m_lastBuildPage;
    GJLevelType m_levelType;
    int m_M_ID;
};

#endif /* defined(__GeometryDash__GJGameLevel__) */
