#ifndef __CCCIRCLEWAVE_H__
#define __CCCIRCLEWAVE_H__

#include "cocos2d.h"

enum CircleMode {
	Filled = 0,
	Outline = 1
};

class CCCircleWaveDelegate {
public:
	virtual void onRemove(cocos2d::CCNode* sender) = 0;
};

class CCCircleWave : public cocos2d::CCNode {
public:
	CCCircleWave();
	virtual ~CCCircleWave();

	virtual void draw() override;

	static CCCircleWave* create(float startRadius, float endRadius, float duration, bool fadeInOut, bool easeOut);
	static CCCircleWave* create(float startRadius, float endRadius, float duration, bool fadeInOut);

	bool init(float startRadius, float endRadius, float duration, bool fadeInOut, bool easeOut);
	void baseSetup(float startRadius);

	void updatePosition(float dt);
	void updateTweenAction(float value, const char* key);
	void followObject(cocos2d::CCNode* target, bool manualUpdate);
	void removeMeAndCleanup();

	CC_SYNTHESIZE(float, m_width, Width);
	CC_SYNTHESIZE(float, m_radius, Radius);
	CC_SYNTHESIZE(float, m_opacity, Opacity);
	CC_SYNTHESIZE(cocos2d::ccColor3B, m_color, Color);
	CC_SYNTHESIZE(CircleMode, m_circleMode, CircleMode);
	CC_SYNTHESIZE(int, m_lineWidth, LineWidth);
	CC_SYNTHESIZE(float, m_opacityMod, OpacityMod);
	CC_SYNTHESIZE(bool, m_blendAdditive, BlendAdditive);
	CC_SYNTHESIZE(CCCircleWaveDelegate*, m_delegate, Delegate);
	CC_SYNTHESIZE_PASS_BY_REF(cocos2d::CCPoint, m_wavePosition, Position);

private:
	cocos2d::CCNode* m_followedObject;
};

#endif