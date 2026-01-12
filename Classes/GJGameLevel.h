#ifndef __GeometryDash__GJGameLevel__
#define __GeometryDash__GJGameLevel__

#include "cocos2d.h"
#include <stdio.h>

enum class GJLevelType {
    Default = 0,
    MainLevel = 1,
    EditorLevel = 2,
	SavedLevel = 3
};

class GJGameLevel : public cocos2d::CCNode {
public:
    GJGameLevel();
    static GJGameLevel* create();
    static GJGameLevel* create(cocos2d::CCDictionary* level);
    virtual bool init();

	// DS_Dictionary is extremely broken on windows phone (and win32 in general)
	// i would fix this but i'm lazy and tired rn
	// so this is a solution
    //void encodeWithCoder(DS_Dictionary* dict);
	void encodeWithCoder(cocos2d::CCDictionary* dict);
    // le CC_PROPERTY
    CC_PROPERTY(int, m_levelID, LevelID);
    CC_PROPERTY(std::string, m_levelName, LevelName);
    CC_PROPERTY(std::string, m_levelDesc, LevelDesc);
    CC_PROPERTY(std::string, m_levelString, LevelString);
    //CC_PROPERTY(std::string, m_creatorName, CreatorName);
    //CC_PROPERTY(std::string, m_recordString, RecordString);
    CC_PROPERTY(int, m_difficulty, Difficulty);
    CC_PROPERTY(int, m_normalPercent, NormalPercent);
    CC_PROPERTY(int, m_downloads, Downloads);
    CC_PROPERTY(int, m_stars, Stars);
    CC_PROPERTY(int, m_coins, Coins);
    CC_PROPERTY(int, m_audioTrack, AudioTrack);
    
    // set functions
    //void setLevelDesc(std::string desc);
    //void setLevelString(std::string string);
    void setLevelVersion(int version);
    void setUserID(int userID);
    void setRatings(int ratings);
    void setRatingsSum(int ratingsSum);
    void setCompletes(int completes);
    void setGameVersion(int gameVersion);
    void setLikes(int likes);
    void setDemon(bool demon);
    void setAutoLevel(bool autoLevel);
    void setLevelType(GJLevelType levelType);
protected:
    int m_userID;
    // ??? m_uploadDate;
    // ??? m_updateDate;
    int m_ratings;
    int m_ratingsSum;
    int m_completes;
    bool m_isEditable;
    bool m_isVerified;
    bool m_isUploaded;
    int m_levelVersion;
    int m_gameVersion;
    int m_attempts;
    int m_jumps;
    int m_practicePercent;
    int m_likes;
    int m_dislikes;
    int m_levelLength;
    int m_featured;
    bool m_demon;
    bool m_autoLevel;
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
