#ifndef __GeometryDash__PlayerObject__
#define __GeometryDash__PlayerObject__

#include "cocos2d.h"
#include "GameObject.h"
#include "CheckpointObject.h"

enum class PlayerButton {
	None = 0,
	Jump = 1
};

enum class GhostType {
	Disabled = 0,
	Enabled = 1,
};

class GhostTrailEffect; // tmp while i decompile it

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

	void spawnPortalCircle(cocos2d::ccColor3B color, float size);

	void update(float dt);
	void updateJump(float dt);
	void updateShipRotation(float dt);
	void updateGlowColor();
	void updateTimeMod(float timeMod);

	void updatePlayerGlow();
	void updatePlayerScale();

	void updatePlayerShipFrame(int sFrame);

	void deactivateParticle();

	void activateStreak();
	void deactivateStreak();

	virtual void resetObject();
	void resetPlayerIcon();

	bool levelFlipping();

	void setColor(cocos2d::ccColor3B color);
	void setSecondColor(cocos2d::ccColor3B color);
	void setVisible(bool visible);
	void setScale(float scale);
	void setScaleX(float scale);
	void setScaleY(float scale);
	void setRotation(float rotation);
	void setOpacity(GLubyte opacity);
	void setPosition(cocos2d::CCPoint const &position);
	void setFlipX(bool flip);
	void setFlipY(bool flip);

	float flipMod();
	void incrementJumps();
	bool playerIsFalling();
	bool isSafeFlip();
	void hitGround(bool notFlipped);
	void ringJump();
	void setupStreak();

	void collidedWithObject(float dt, GameObject* obj);

	void runRotateAction();
	void runNormalRotation();
	void runBallRotation();
	void stopRotation();

	void toggleFlyMode(bool enable);
	void toggleRollMode(bool enable);
	void toggleBirdMode(bool enable);

	void toggleGhostEffect(GhostType type);

	void touchedObject(GameObject* obj);

	void saveToCheckpoint(CheckpointObject* check);
	void removePendingCheckpoint();

	GhostType m_ghostType; // 0x2c0
	GhostTrailEffect* m_ghostTrail; // 0x2c4

	cocos2d::CCSprite* m_iconSprite; // 0x2c8
	cocos2d::CCSprite* m_iconSpriteSecondary; // 0x2cc
	cocos2d::CCSprite* m_iconGlow; // 0x2d0
	cocos2d::CCSprite* m_vehicleSprite; // 0x2d4
	cocos2d::CCSprite* m_vehicleSpriteSecondary; // 0x2d8
	cocos2d::CCSprite* m_vehicleSpriteThird; // 0x2dc
	cocos2d::CCSprite* m_vehicleGlow; // 0x2e0
	cocos2d::CCSprite* unk_0x2e4; // 0x2e4
	cocos2d::CCMotionStreak* m_playerStreak; // 0x2e8

	double m_speed; // 0x2f0
	double m_yStart; // 0x2f8
	double m_gravity; // 0x300
	float unk_0x308; // 0x308

	bool unk_0x30c; // 0x30c
	bool m_canJump; // 0x30d
	bool unk_0x30e; // 0x30e
	bool unk_0x30f; // 0x30f

	bool unk_0x310; // 0x310
	bool m_isPlayLayer; // 0x311
	bool unk_0x312; // 0x312
	bool unk_0x313; // 0x313; this one is quite odd since it goes completely unused, maybe there's a chance it's used in an older/newer gd version.
	bool m_pGroundActive; // 0x314
	bool m_pShipActive; // 0x315
	bool unk_0x316; // 0x316

	float unk_0x318; // 0x318

	float unk_0x324; // 0x324
	double m_yVelocity; // 0x328

	cocos2d::CCPoint m_lastUpdatePos; // 0x34c

	// particles
	cocos2d::CCParticleSystemQuad* m_dragParticle; // 0x354
	cocos2d::CCParticleSystemQuad* m_birdDragParticle; // 0x358
	cocos2d::CCParticleSystemQuad* m_dragParticle2; // 0x35c
	cocos2d::CCParticleSystemQuad* m_shipDragParticle; // 0x360
	cocos2d::CCParticleSystemQuad* m_burstParticle; // 0x364

	bool field_0x368; // 0x368

	cocos2d::CCParticleSystemQuad* m_landParticle; // 0x36c
	cocos2d::CCParticleSystemQuad* m_landParticle2; // 0x370
	float unk_0x374; // 0x374

	CC_SYNTHESIZE_READONLY(bool, m_flyMode, FlyMode); // 0x380
	CC_SYNTHESIZE_READONLY(bool, m_birdMode, BirdMode); // 0x381
	CC_SYNTHESIZE_READONLY(bool, m_rollMode, RollMode); // 0x382
	CC_SYNTHESIZE_READONLY(bool, m_gravityFlipped, GravityFlipped); // 0x383
	CC_SYNTHESIZE_READONLY(bool, m_isDead, IsDead); // 0x384
	CC_SYNTHESIZE_READONLY(float, m_playerScale, PlayerScale); // 0x388
	CC_SYNTHESIZE_READONLY(float, m_timeMod, TimeMod); // 0x38c
	CC_SYNTHESIZE(cocos2d::CCPoint, m_lastPos, LastP) // 0x390
		CC_SYNTHESIZE(cocos2d::CCPoint, m_portalPos, PortalP); // 0x398
	CC_SYNTHESIZE(cocos2d::CCLayer*, m_gameLayer, GameLayer); // 0x3a0
	CC_SYNTHESIZE(bool, m_onGround, OnGround); // 0x3a4
	CC_SYNTHESIZE_READONLY(bool, m_isJumping, IsJumping); // 0x3a5	

	CC_SYNTHESIZE_READONLY(bool, m_isLocked, IsLocked); // 0x3a6
	CC_SYNTHESIZE_READONLY(cocos2d::CCPoint, m_lastGroundPos, LastGroundPos); // 0x3a8
	CC_SYNTHESIZE(GameObject*, m_touchedRing, TouchedRing); // 0x3b0
	CC_SYNTHESIZE(GameObject*, m_portalObject, PortalObject); // 0x3b4
	CC_SYNTHESIZE_READONLY(bool, m_hasJumped, HasJumped); // 0x3b8
	CC_SYNTHESIZE_READONLY(bool, m_hasRingJumped, HasRingJumped); // 0x3b9

	CC_SYNTHESIZE_READONLY(cocos2d::ccColor3B, m_glowColor1, GlowColor1); // 0x3ba
	CC_SYNTHESIZE_READONLY(cocos2d::ccColor3B, m_glowColor2, GlowColor2); // 0x3bd

	void updatePlayerFrame(int frame);
	void updatePlayerRollFrame(int frame);
	void updatePlayerBirdFrame(int frame);
	bool canJump() { return true; }
};

#endif /* defined(__GeometryDash__PlayerObject__) */