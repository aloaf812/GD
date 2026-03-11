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
	void downloadLevel(int level_ID);
    void getLeaderboardScores(char const* leaderboardType);
    void getOnlineLevels();
	// char getLevelKey(int level);
    void onDownloadLevelComplete(cocos2d::extension::CCHttpClient* client, cocos2d::extension::CCHttpResponse* response);
    void onGetLeaderboardScoresCompleted(cocos2d::extension::CCHttpClient* client, cocos2d::extension::CCHttpResponse* response);
    // void storeUserNames(std::string usernameString);
    static cocos2d::CCDictionary* responseToDict(std::string response, bool p0);
    GJGameLevel* getMainLevel(int mainLevel);

	CC_SYNTHESIZE_READONLY(cocos2d::CCArray*, m_localLevels, LocalLevels); // 0x114
	CC_SYNTHESIZE(SearchType, m_lastSearchType, LastSearchType); // 0x148
};

#endif