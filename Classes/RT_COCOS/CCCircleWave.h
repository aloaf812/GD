#ifndef __CCCIRCLEWAVE_H__
#define __CCCIRCLEWAVE_H__

#include "cocos2d.h"

enum class CircleMode {
	Filled = 0,
	Outline = 1
};

class CCCircleWaveDelegate {
public:
	virtual void circleWaveWillBeRemoved(class CCCircleWave* wave) = 0;
};

class CCCircleWave : public cocos2d::CCNode {
public:
	CCCircleWave();
	virtual ~CCCircleWave();

	static CCCircleWave* create(float radius, float duration, float speed, bool fadeOut, bool easeOut);
	static CCCircleWave* create(float radius, float duration, float speed, bool fadeOut);

	bool init(float radius, float duration, float speed, bool fadeOut, bool easeOut);
	void baseSetup(float radius);

	virtual void draw() override;
	void updatePosition(float dt);
	void updateTweenAction(float value, const char* key);
	void removeMeAndCleanup();

	int followObject(cocos2d::CCNode* target, bool snapToPosition);

	CC_SYNTHESIZE(float, m_width, Width); // offset +236
	CC_SYNTHESIZE(float, m_radius, Radius); // offset +240
	CC_SYNTHESIZE(float, m_opacity, Opacity); // offset +244
	CC_SYNTHESIZE(cocos2d::ccColor3B, m_color, Color); // offset +248
	CC_SYNTHESIZE(CircleMode, m_circleMode, CircleMode); // offset +260
	CC_SYNTHESIZE(int, m_lineWidth, LineWidth); // offset +264
	CC_SYNTHESIZE(float, m_opacityMod, OpacityMod); // offset +268
	CC_SYNTHESIZE(bool, m_blendAdditive, BlendAdditive); // offset +272
	CC_SYNTHESIZE(CCCircleWaveDelegate*, m_delegate, Delegate); // offset +276
	
	virtual const cocos2d::CCPoint& getPosition() override { return m_positionInternal; }
	virtual void setPosition(const cocos2d::CCPoint& position) override { m_positionInternal = position; }

protected:
	cocos2d::CCNode* m_targetNode; // offset +232
	cocos2d::CCPoint m_positionInternal; // offset +252 (X) and +256 (Y)
};

#endif // __CCCIRCLEWAVE_H__