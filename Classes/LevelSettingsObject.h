#ifndef __GeometryDash__LevelSettingsObject__
#define __GeometryDash__LevelSettingsObject__

#include "cocos2d.h"
#include "GJGameLevel.h"
#include <stdio.h>

class LevelSettingsObject : public cocos2d::CCNode {
public:
    LevelSettingsObject();
	CREATE_FUNC(LevelSettingsObject);
    static LevelSettingsObject* objectFromString(std::string str);
    virtual bool init();
    
	// colors
	CC_SYNTHESIZE(cocos2d::ccColor3B, m_startBGColor, StartBGColor); // 0xe8
	CC_SYNTHESIZE(cocos2d::ccColor3B, m_startGColor, StartGColor); // 0xeb
    CC_SYNTHESIZE(cocos2d::ccColor3B, m_startLineColor, StartLineColor); // 0xee
	CC_SYNTHESIZE(cocos2d::ccColor3B, m_startObjColor, StartObjColor); // 0xf1
	CC_SYNTHESIZE(cocos2d::ccColor3B, m_startTintObjColor, StartTintObjColor); // 0xf4

    CC_SYNTHESIZE(int, m_startMode, StartMode); // 0x10c
    CC_SYNTHESIZE(bool, m_startMiniMode, StartMiniMode); // 0x114
    CC_SYNTHESIZE(int, m_startSpeed, StartSpeed); // 0x110
    
	CC_SYNTHESIZE(int, m_audioTrack, AudioTrack); // 0x118
	CC_SYNTHESIZE(int, m_BGIdx, BGIdx); // 0x120
	CC_SYNTHESIZE(int, m_GIdx, GIdx); // 0x124
	CC_SYNTHESIZE(bool, m_tintObjectsUseBlend, TintObjectsUseBlend); // 0x11c
};

#endif /* defined(__GeometryDash__LevelSettingsObject__) */
