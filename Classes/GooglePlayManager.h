#ifndef _GOOGLE_PLAY_MANAGER_H_
#define _GOOGLE_PLAY_MANAGER_H_
#include "cocos2d.h"

class GooglePlayDelegate;

class GooglePlayManager : public cocos2d::CCNodeRGBA {
public:
	static GooglePlayManager* sharedState();
	bool init();

	CC_SYNTHESIZE(GooglePlayDelegate*, m_delegate, Delegate); // 0xe8
	CC_SYNTHESIZE(GooglePlayDelegate*, m_delegate2, Delegate2); // 0xec
};

#endif