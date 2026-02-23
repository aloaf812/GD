#ifndef __GeometryDash__GJGroundLayer__
#define __GeometryDash__GJGroundLayer__

#include "cocos2d.h"

class GJGroundLayer : public cocos2d::CCLayer {
public:
    GJGroundLayer();
    static GJGroundLayer* create(int gID);
    virtual bool init(int gID);
    void draw();

    void fadeInGround(float duration);
    void fadeInFinished();
    void fadeOutGround(float duration);

	void deactivateGround();

    // variables
	CC_SYNTHESIZE_READONLY(cocos2d::CCSprite*, m_groundSprite, GroundSprite); // 0x10c
	CC_SYNTHESIZE_READONLY(cocos2d::CCSprite*, m_line, Line);
	CC_SYNTHESIZE_READONLY(bool, m_isActive, IsActive);
	CC_SYNTHESIZE_READONLY(float, m_groundWidth, GroundWidth);
    float m_repeatWidth;
    int m_repeatCount;
    cocos2d::CCArray* m_tiles;
};

#endif