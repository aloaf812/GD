#ifndef __GeometryDash__PlayerObject__
#define __GeometryDash__PlayerObject__

#include "cocos2d.h"
#include "GameObject.h"

// i dont get this one :/
enum class PlayerButton {
	None = 0,
	Jump = 1
};

enum class GhostType {
	Disabled = 0,
	Enabled = 1,
};

class PlayerObject : public GameObject {
public:
	PlayerObject();
    static PlayerObject* create(int player, int ship, cocos2d::CCLayer* layer);
    bool init(int player, int ship, cocos2d::CCLayer* layer);

	
	void pushButton(PlayerButton button);
	// this was changed to a bool in modern gd
	void releaseButton(PlayerButton button);

	void lockPlayer();

	bool isFlying();

	void logValues();

	void playerDestroyed();

	// particles
	void playBurstEffect();
	void stopBurstEffect();

	void update(float dt);
	void updateJump(float dt);
	void updateShipRotation(float dt);
	void updateGlowColor();
	void updateTimeMod(float timeMod);

	void deactivateParticle();

	virtual void resetObject();

	bool levelFlipping();

	void setColor(cocos2d::ccColor3B color);
	void setSecondColor(cocos2d::ccColor3B color);
	// void setVisible(bool visible);
	virtual void setPosition(cocos2d::CCPoint const &position);

	float flipMod();

	void runRotateAction();
	void runNormalRotation();


	GhostType m_ghostType; // 0x2c0
	// GhostTrailEffect* m_ghostTrail; // 0x2c4
	
	cocos2d::CCSprite* m_iconSprite; // 0x2c8
	cocos2d::CCSprite* m_iconSpriteSecondary; // 0x2cc
	cocos2d::CCSprite* m_iconGlow; // 0x2d0
	cocos2d::CCSprite* m_vehicleSprite; // 0x2d4
	cocos2d::CCSprite* m_vehicleSpriteSecondary; // 0x2d8
	cocos2d::CCSprite* m_vehicleSpriteThird; // 0x2dc
	cocos2d::CCSprite* m_vehicleGlow; // 0x2e0
	cocos2d::CCSprite* field695_0x2e4; // 0x2e4
	cocos2d::CCMotionStreak* m_playerStreak; // 0x2e8

	double m_speed; // 0x2f0
	double m_yStart; // 0x2f8
	double m_gravity; // 0x300

	CC_SYNTHESIZE_READONLY(bool, m_isLocked, IsLocked); // 0x3a6
	CC_SYNTHESIZE_READONLY(cocos2d::CCPoint, m_lastGroundPos, LastGroundPos); // 0x3a8
	CC_SYNTHESIZE(GameObject*, m_touchedRing, TouchedRing); // 0x3b0
	CC_SYNTHESIZE(GameObject*, m_portalObject, PortalObject); // 0x3b4
	CC_SYNTHESIZE_READONLY(bool, m_hasJumped, HasJumped); // 0x3b8
	CC_SYNTHESIZE_READONLY(bool, m_hasRingJumped, HasRingJumped); // 0x3b9

	CC_SYNTHESIZE_READONLY(bool, m_flyMode, FlyMode); // 0x380
	CC_SYNTHESIZE_READONLY(bool, m_birdMode, BirdMode); // 0x381
	CC_SYNTHESIZE_READONLY(bool, m_rollMode, RollMode); // 0x382

	CC_SYNTHESIZE_READONLY(bool, m_gravityFlipped, GravityFlipped); // 0x383
	CC_SYNTHESIZE_READONLY(bool, m_isDead, IsDead); // 0x384
	CC_SYNTHESIZE_READONLY(float, m_playerScale, PlayerScale); // 0x388
	CC_SYNTHESIZE_READONLY(float, m_timeMod, TimeMod); // 0x38c
	CC_SYNTHESIZE(cocos2d::CCPoint, m_lastPos, LastP) // 0x390
	CC_SYNTHESIZE(cocos2d::CCPoint, m_portalPos, PortalP); // 0x398
	CC_SYNTHESIZE(bool, m_onGround, OnGround); // 0x3a4
	CC_SYNTHESIZE_READONLY(bool, m_isJumping, IsJumping); // 0x3a5	
	CC_SYNTHESIZE(cocos2d::CCLayer*, m_gameLayer, GameLayer); // 0x3a0
	CC_SYNTHESIZE_READONLY(cocos2d::ccColor3B, m_glowColor1, GlowColor1); // 0x3b8


	bool field772_0x30d; // 0x30d
	bool field773_0x30e; // 0x30e

	bool m_isPlayLayer; // 0x311

	bool m_pGroundActive; // 0x314
	bool m_pShipActive; // 0x315

	double m_yVelolcity; // 0x328


	cocos2d::CCPoint m_lastUpdatePos; // 0x34c

	// particles
	cocos2d::CCParticleSystemQuad* m_pGround; // 0x354
	cocos2d::CCParticleSystemQuad* m_pShipGround; // 0x360
	cocos2d::CCParticleSystemQuad* m_pBurstEffect; // 0x364
};

#endif /* defined(__GeometryDash__PlayerObject__) */
