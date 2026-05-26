#ifndef _CHECKPOINT_OBJECT_H_
#define _CHECKPOINT_OBJECT_H_
#include "cocos2d.h"
#include "GameObject.h"

class CheckpointObject : public cocos2d::CCNode {
public:
	CREATE_FUNC(CheckpointObject);

	bool init();

	CC_PROPERTY(GameObject*, m_object, Object); // 0xe8

	CC_SYNTHESIZE(cocos2d::CCPoint, m_playerPos, PlayerPos); // 0xec
	CC_SYNTHESIZE(float, m_playerYVel, PlayerYVel); // 0xf4
	CC_SYNTHESIZE(bool, m_flipGravity, FlipGravity); // 0xf8
	CC_SYNTHESIZE(bool, m_flyMode, FlyMode); // 0xf9
	CC_SYNTHESIZE(bool, m_rollMode, RollMode); // 0xfa
	CC_SYNTHESIZE(bool, m_birdMode, BirdMode); // 0xfb
	CC_SYNTHESIZE(bool, m_canJump, CanJump); // 0xfc
	CC_SYNTHESIZE(int, m_ghostType, GhostType); // 0x100
	CC_SYNTHESIZE(bool, m_isFlipped, IsFlipped); // 0x104
	CC_SYNTHESIZE(bool, m_isScaled, IsScaled); // 0x105
	CC_SYNTHESIZE(float, m_timeMod, TimeMod); // 0x108
	CC_SYNTHESIZE(cocos2d::CCPoint, m_cameraPos, CameraPos); // 0x10c
	CC_SYNTHESIZE(GameObject*, m_portalObject, PortalObject); // 0x12c
	CC_SYNTHESIZE(double, m_timeStamp, TimeStamp); // 0x130
};

#endif // _CHECKPOINT_OBJECT_H_