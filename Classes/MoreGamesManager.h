#ifndef __MORE_GAMES_MANAGER_H__
#define __MORE_GAMES_MANAGER_H__

#include "cocos2d.h"
#include <string>

class MoreGamesManager : public cocos2d::CCNode {
public:
	static MoreGamesManager* sharedState();
	bool init();
	void firstLoad();

	int m_lastMonth; // 0xe8
	int m_lastDay; // 0xec
	CC_SYNTHESIZE(std::string, m_moreGamesString, MoreGamesString); // 0xf0
	CC_SYNTHESIZE(bool, m_hasNewGames, HasNewGames); // 0xf4
};

#endif /* defined(__MORE_GAMES_MANAGER_H__) */
