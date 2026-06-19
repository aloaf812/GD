#ifndef _GAME_LEVEL_MANAGER_H
#define _GAME_LEVEL_MANAGER_H

#include "cocos2d.h"
#include "cocos-ext.h"
#include "GJGameLevel.h"
#include "GJSearchObject.h"

class GameLevelManager : public cocos2d::CCNode {
public:
    static GameLevelManager* sharedState();
    bool init();
	void downloadLevel(int level_id);
    void getLeaderboardScores(char const* leaderboardType);
    void getOnlineLevels();
	char const* getLevelKey(int level);
	bool isDLActive(char const* key);
	void addDLToActive(char const* key);
	bool hasDownloadedLevel(int level);
    void onDownloadLevelComplete(cocos2d::extension::CCHttpClient* client, cocos2d::extension::CCHttpResponse* response);
    void onGetLeaderboardScoresCompleted(cocos2d::extension::CCHttpClient* client, cocos2d::extension::CCHttpResponse* response);
    // void storeUserNames(std::string usernameString);
    static cocos2d::CCDictionary* responseToDict(std::string response, bool p0);
    GJGameLevel* getMainLevel(int mainLevel);
	void dataLoaded(DS_Dictionary* dict);
	void limitSavedLevels();

	cocos2d::CCDictionary* unk_0xe8; // 0xe8
	cocos2d::CCDictionary* unk_0xec; // 0xec
	cocos2d::CCDictionary* unk_0xf0; // 0xf0
	cocos2d::CCDictionary* unk_0xf4; // 0xf4
	cocos2d::CCDictionary* unk_0xf8; // 0xf8
	cocos2d::CCDictionary* unk_0xfc; // 0xfc
	cocos2d::CCDictionary* unk_0x100; // 0x100
	cocos2d::CCDictionary* unk_0x104; // 0x104
	cocos2d::CCDictionary* unk_0x108; // 0x108
	cocos2d::CCDictionary* unk_0x10c; // 0x10c
	cocos2d::CCDictionary* unk_0x110; // 0x110

	CC_SYNTHESIZE_READONLY(cocos2d::CCArray*, m_localLevels, LocalLevels); // 0x114
	CC_SYNTHESIZE(int, m_lastLeaderboard, LastLeaderboard); // 0x120
	CC_SYNTHESIZE(bool, m_createdNewLevel, CreatedNewLevel); // 0x124
	CC_SYNTHESIZE(SearchType, m_lastSearchType, LastSearchType); // 0x148
};

#endif