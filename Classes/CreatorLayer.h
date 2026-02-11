#ifndef __GeometryDash__CreatorLayer__
#define __GeometryDash__CreatorLayer__

#include "cocos2d.h"

class CreatorLayer : public cocos2d::CCLayer
{
public:
    CreatorLayer();
    static cocos2d::CCScene* scene();
	CREATE_FUNC(CreatorLayer);
    bool init();
    void onBack(cocos2d::CCObject* sender);
	void onSearch(cocos2d::CCObject* sender);
	void onMyLevels(cocos2d::CCObject* sender);
    void onLeaderboards(cocos2d::CCObject* sender);
};

#endif /* defined(__GeometryDash__CreatorLayer__) */
