#ifndef _GAME_LEVEL_MANAGER_H
#define _GAME_LEVEL_MANAGER_H

#include "cocos2d.h"
#include "HttpClient.h"

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
    static cocos2d::CCDictionary* responseToDict(std::string response, bool p0);
    CCObject* getMainLevel(int mainLevel);
};

#endif