#ifndef __GeometryDash__GJGameLevel__
#define __GeometryDash__GJGameLevel__

#include "cocos2d.h"
#include <stdio.h>

enum class GJLevelType {
    Default = 0,
    MainLevel = 1,
    LocalLevel = 2,
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
	CC_SYNTHESIZE(int, m_password, Password); // 0x5b
    CC_SYNTHESIZE(int, m_levelID, LevelID); // 0x3b
	CC_SYNTHESIZE(GJLevelType, m_levelType, LevelType); // 0x6a
    CC_SYNTHESIZE(std::string, m_levelName, LevelName); // 0xf0
    CC_SYNTHESIZE(std::string, m_levelDesc, LevelDesc); // 0xf4
    CC_SYNTHESIZE(std::string, m_levelString, LevelString); // 0xf8
    //CC_PROPERTY(std::string, m_creatorName, CreatorName);
    //CC_PROPERTY(std::string, m_recordString, RecordString);
    CC_SYNTHESIZE(int, m_difficulty, Difficulty); // 0x44
    CC_SYNTHESIZE(int, m_normalPercent, NormalPercent); // 0x50
    CC_SYNTHESIZE(int, m_downloads, Downloads); // 0x48
    CC_SYNTHESIZE(int, m_stars, Stars); // 0x57
    CC_SYNTHESIZE(int, m_coins, Coins); // 0x164
    CC_SYNTHESIZE(int, m_audioTrack, AudioTrack); // 0x114
    CC_SYNTHESIZE(bool, m_autoLevel, AutoLevel); // 0x160
    
	CC_SYNTHESIZE(std::string, m_uploadDate, UploadDate); // 0x104
	CC_SYNTHESIZE(std::string, m_updateDate, UpdateDate); // 0x108
	CC_SYNTHESIZE(int, m_userID, UserID); // 0x43

    void setLevelVersion(int version);
    void setRatings(int ratings);
    void setRatingsSum(int ratingsSum);
    void setCompletes(int completes);
    void setGameVersion(int gameVersion);
    void setLikes(int likes);
    void setDemon(bool demon);
protected:
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
    int m_levelSize;
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
    int m_M_ID;
};

#endif /* defined(__GeometryDash__GJGameLevel__) */
