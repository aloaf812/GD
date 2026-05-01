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
    // le wall of CC_SYNTHESIZE
	CC_SYNTHESIZE(cocos2d::CCDictionary*, m_lastBuildSave, LastBuildSave); // 0xe8
    CC_SYNTHESIZE(int, m_levelID, LevelID); // 0xec
    CC_SYNTHESIZE(std::string, m_levelName, LevelName); // 0xf0
    CC_SYNTHESIZE(std::string, m_levelDesc, LevelDesc); // 0xf4
    CC_SYNTHESIZE(std::string, m_levelString, LevelString); // 0xf8
	CC_SYNTHESIZE(std::string, m_recordString, RecordString); // 0x100
	CC_SYNTHESIZE(std::string, m_uploadDate, UploadDate); // 0x104
	CC_SYNTHESIZE(std::string, m_updateDate, UpdateDate); // 0x108
	CC_SYNTHESIZE(int, m_userID, UserID); // 0x10c
    CC_SYNTHESIZE(int, m_difficulty, Difficulty); // 0x110
    CC_SYNTHESIZE(int, m_audioTrack, AudioTrack); // 0x114
	CC_SYNTHESIZE(int, m_ratings, Ratings); // 0x118
	CC_SYNTHESIZE(int, m_ratingsSum, RatingsSum); // 0x11c
    CC_SYNTHESIZE(int, m_downloads, Downloads); // 0x120
	CC_SYNTHESIZE(int, m_completes, Completes); // 0x124
	CC_SYNTHESIZE(bool, m_isVerified, IsVerified); // 0x129
	CC_SYNTHESIZE(int, m_levelVersion, LevelVersion); // 0x12c
	CC_SYNTHESIZE(int, m_gameVersion, GameVersion); // 0x130
	CC_SYNTHESIZE(int, m_buildVersion, BuildVersion); // 0x134
	CC_SYNTHESIZE(int, m_attempts, Attempts); // 0x138
	CC_SYNTHESIZE(int, m_jumps, Jumps); // 0x13c
    CC_SYNTHESIZE(int, m_normalPercent, NormalPercent); // 0x140
	CC_SYNTHESIZE(int, m_practicePercent, PracticePercent); // 0x144
	CC_SYNTHESIZE(int, m_likes, Likes); // 0x148
	CC_SYNTHESIZE(bool, m_demon, Demon); // 0x158
    CC_SYNTHESIZE(int, m_stars, Stars); // 0x15c
    CC_SYNTHESIZE(bool, m_autoLevel, AutoLevel); // 0x160
    CC_SYNTHESIZE(int, m_coins, Coins); // 0x164
	CC_SYNTHESIZE(int, m_levelSize, LevelSize); // 0x168
	CC_SYNTHESIZE(int, m_password, Password); // 0x16c
	CC_SYNTHESIZE(bool, m_dontSave, DontSave); // 0x188
	CC_SYNTHESIZE(bool, m_isHidden, IsHidden); // 0x189
	CC_SYNTHESIZE(int, m_requiredCoins, RequiredCoins); // 0x18c
	CC_SYNTHESIZE(bool, m_isUnlocked, IsUnlocked); // 0x190
	CC_SYNTHESIZE(GJLevelType, m_levelType, LevelType); // 0x1a8
	CC_SYNTHESIZE(int, m_M_ID, M_ID); // 0x1ac
    

};

#endif /* defined(__GeometryDash__GJGameLevel__) */
