#ifndef __GeometryDash__LevelSettingsObject__
#define __GeometryDash__LevelSettingsObject__

#include "cocos2d.h"
#include "GJGameLevel.h"
#include <stdio.h>

class LevelSettingsObject : public cocos2d::CCNode {
public:
    LevelSettingsObject();
    static LevelSettingsObject* create();
    static LevelSettingsObject* objectFromString(std::string str);
    virtual bool init();
    
    CC_PROPERTY(cocos2d::ccColor3B, m_startBGColor, StartBGColor);
    CC_PROPERTY(cocos2d::ccColor3B, m_startGColor, StartGColor);
    CC_PROPERTY(cocos2d::ccColor3B, m_startLineColor, StartLineColor);
    
    CC_PROPERTY(int, m_startMode, StartMode);
    CC_PROPERTY(bool, m_startMiniMode, StartMiniMode);
    CC_PROPERTY(int, m_startSpeed, StartSpeed);
    
    CC_PROPERTY(int, m_audioTrack, AudioTrack);
    CC_PROPERTY(int, m_BGIdx, BGIdx);
    CC_PROPERTY(int, m_GIdx, GIdx);
    
};

#endif /* defined(__GeometryDash__LevelSettingsObject__) */
