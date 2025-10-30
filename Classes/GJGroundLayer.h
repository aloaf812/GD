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

    // get functions
    cocos2d::CCSprite* getGroundSprite() const;
    cocos2d::CCSprite* getLine() const;
    float getGroundWidth() const;    
    bool getIsActive() const;

    // variables
    bool m_isActive;
    float m_groundWidth;
    float m_repeatWidth;
    int m_repeatCount;
    cocos2d::CCArray* m_tiles;
    cocos2d::CCSprite* m_groundSprite;
    cocos2d::CCSprite* m_line;
};

#endif