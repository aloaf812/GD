#ifndef __GeometryDash__LevelEditorLayer__
#define __GeometryDash__LevelEditorLayer__

#include "cocos2d.h"
#include "GJGameLevel.h"

// class LevelEditorLayer : public cocos2d::CCLayer : public LevelSettingsDelegate {
class LevelEditorLayer : public cocos2d::CCLayer {
public:
	static cocos2d::CCScene* scene(GJGameLevel* level);
	static LevelEditorLayer* create(GJGameLevel* level);
	bool init(GJGameLevel* level);

	CC_SYNTHESIZE_READONLY(GJGameLevel*, m_level, Level); // 0x130
	CC_SYNTHESIZE(int, m_objectCount, ObjectCount); // 0x124
};

#endif /* defined(__GeometryDash__LevelEditorLayer__) */
