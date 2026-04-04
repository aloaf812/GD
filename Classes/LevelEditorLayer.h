#ifndef __GeometryDash__LevelEditorLayer__
#define __GeometryDash__LevelEditorLayer__

#include "cocos2d.h"
#include "GJGameLevel.h"
#include "LevelSettingsObject.h"

// class LevelEditorLayer : public cocos2d::CCLayer : public LevelSettingsDelegate {
class LevelEditorLayer : public cocos2d::CCLayer {
public:
	LevelEditorLayer();
	static cocos2d::CCScene* scene(GJGameLevel* level);
	static LevelEditorLayer* create(GJGameLevel* level);
	bool init(GJGameLevel* level);
	void createBackground();
	void removeBackground();

	cocos2d::CCSprite* m_bgSprite; // 0x110

	CC_SYNTHESIZE(int, m_objectCount, ObjectCount); // 0x124
	//CC_SYNTHESIZE_READONLY(DrawGridLayer*, m_gridLayer, GridLayer); // 0x128
	CC_SYNTHESIZE_READONLY(cocos2d::CCLayer*, m_gameLayer, GameLayer); // 0x12c
	CC_SYNTHESIZE_READONLY(GJGameLevel*, m_level, Level); // 0x130
	CC_SYNTHESIZE_READONLY(LevelSettingsObject*, m_levelSettings, LevelSettings); // 0x134
};

#endif /* defined(__GeometryDash__LevelEditorLayer__) */
