#ifndef __GeometryDash__GameObject__
#define __GeometryDash__GameObject__

#include "cocos2d.h"
#include "RT_COCOS/CCSpritePlus.h"
#include <stdio.h>
#include <string>

enum GameObjectType : int32_t {
	None = 0,
	Hazard = 2,
	InvertGravityPortal = 3,
	NormalGravityPortal = 4,
	ShipPortal = 5,
	CubePortal = 6,
	Decoration = 7,
	YellowPad = 9,
	GravityPad = 10,
	YellowOrb = 11,
	BlueOrb = 12,
	MirrorPortal = 13,
	CounterMirrorPortal = 14,
	BallPortal = 15,
	unknown22 = 22,
	SecretCoin = 23
};

class GameObject : public CCSpritePlus {
public:
	GameObject();
	static GameObject* objectFromString(std::string objString);
	static GameObject* create(const char* spriteName);
	bool init(const char* spriteName);

	virtual void setPosition(cocos2d::CCPoint const &position) override;
	void setFlipX(bool flipX);
	void setFlipY(bool flipY);
	virtual void setOpacity(unsigned char opacity) override;
	virtual void resetObject();
	virtual void triggerObject();
	virtual void activateObject();
	virtual void deactivateObject();

	void disableObject();
	const char* getBallFrame(int idx);
	void updateState();
	void customSetup();
	void update(float dt);
	cocos2d::CCRect getObjectRect();
	cocos2d::CCRect getObjectRect(float scaleX, float scaleY);
	void calculateSpawnXPos();
	void triggerActivated();
	void powerOnObject();
	void powerOffObject();
	void setGlowOpacity(unsigned char opacity);
	void setChildColor(cocos2d::_ccColor3B color);

	CC_SYNTHESIZE_READONLY(bool, m_isActive, IsActive);
	CC_SYNTHESIZE_READONLY(bool, m_hasColor, HasColor);
	CC_SYNTHESIZE_READONLY(cocos2d::CCSprite*, m_colorSprite, ColorSprite);
	CC_SYNTHESIZE(bool, m_ignoreScreenCheck, IgnoreScreenCheck);
	CC_SYNTHESIZE_READONLY(float, m_radius, Radius);
	CC_SYNTHESIZE_READONLY(bool, m_isRotated, IsRotated);
	CC_SYNTHESIZE(float, m_scaleModX, ScaleModX);
	CC_SYNTHESIZE(float, m_scaleModY, ScaleModY);
	CC_SYNTHESIZE(int, m_ID, M_ID);
	CC_SYNTHESIZE(int, m_type, Type);
	CC_SYNTHESIZE(int, m_sectionIdx, SectionIdx);
	CC_SYNTHESIZE_READONLY(bool, m_shouldSpawn, ShouldSpawn);
	CC_SYNTHESIZE(bool, m_touchTriggered, TouchTriggered);
	CC_SYNTHESIZE_READONLY(bool, m_blendAdditive, BlendAdditive);
	CC_SYNTHESIZE_READONLY(bool, m_usePlayerColor, UsePlayerColor);
	CC_SYNTHESIZE_READONLY(bool, m_usePlayerColor2, UsePlayerColor2);
	CC_SYNTHESIZE(bool, m_isDisabled, IsDisabled);
	CC_SYNTHESIZE(bool, m_useAudioScale, UseAudioScale);
	CC_SYNTHESIZE_READONLY(bool, m_isSleeping, IsSleeping);
	CC_SYNTHESIZE(float, m_startRotation, StartRotation);
	CC_SYNTHESIZE(float, m_startScaleX, StartScaleX);
	CC_SYNTHESIZE(float, m_startScaleY, StartScaleY);
	CC_SYNTHESIZE(bool, m_shouldHide, ShouldHide);
	CC_SYNTHESIZE_READONLY(int, m_spawnXPos, SpawnXPos);
	CC_SYNTHESIZE_READONLY(bool, m_isInvisible, IsInvisible);
	CC_SYNTHESIZE(float, m_enterAngle, EnterAngle);
	CC_SYNTHESIZE(int, m_enterEffect, EnterEffect);
	CC_SYNTHESIZE(cocos2d::_ccColor3B, m_tintColor, TintColor);
	CC_SYNTHESIZE(float, m_tintDuration, TintDuration);
	CC_SYNTHESIZE(bool, m_tintGround, TintGround);
	CC_SYNTHESIZE(int, m_objectKey, ObjectKey);
	CC_SYNTHESIZE(bool, m_dontTransform, DontTransform);
	CC_SYNTHESIZE(bool, m_dontFade, DontFade);
	CC_SYNTHESIZE(bool, m_dontFadeTinted, DontFadeTinted);
	CC_SYNTHESIZE(bool, m_isTintObject, IsTintObject);
	CC_SYNTHESIZE_READONLY(bool, m_hasBeenActivated, HasBeenActivated);
	CC_SYNTHESIZE(bool, m_stateVar, StateVar);
	CC_SYNTHESIZE(int, m_objectZ, ObjectZ);
	CC_SYNTHESIZE(cocos2d::CCNode*, m_objectParent, ObjectParent);
	CC_SYNTHESIZE_READONLY(bool, m_customAudioScale, CustomAudioScale);
	CC_SYNTHESIZE_READONLY(float, m_minAudioScale, MinAudioScale);
	CC_SYNTHESIZE_READONLY(float, m_maxAudioScale, MaxAudioScale);
	CC_SYNTHESIZE(int, m_uniqueID, UniqueID);
	CC_SYNTHESIZE_READONLY(bool, m_invisibleMode, InvisibleMode);
	CC_SYNTHESIZE_READONLY(bool, m_glowUseBGColor, GlowUseBGColor);
	CC_SYNTHESIZE_READONLY(bool, m_useBGColor, UseBGColor);
	CC_SYNTHESIZE_READONLY(bool, m_useSpecialLight, UseSpecialLight);
	CC_SYNTHESIZE(float, m_opacityMod, OpacityMod);
	CC_SYNTHESIZE(float, m_glowOpacityMod, GlowOpacityMod);
	CC_SYNTHESIZE(bool, m_dontShow, DontShow);
	CC_SYNTHESIZE(bool, m_editorSelected, EditorSelected);
	CC_SYNTHESIZE(bool, m_copyPlayerColor1, CopyPlayerColor1);
	CC_SYNTHESIZE(bool, m_copyPlayerColor2, CopyPlayerColor2);
	CC_SYNTHESIZE(bool, m_tintObjectsUseBlend, TintObjectsUseBlend);
	CC_SYNTHESIZE_READONLY(cocos2d::CCPoint, m_startPos, StartPos);
	CC_SYNTHESIZE(std::string, m_frame, Frame);

private:
	int unk_0x1b8;
	int unk_0x1bc;
	bool unk_0x1c0;
	cocos2d::CCSprite* m_glowSprite;
	bool unk_0x1c8;
	bool unk_0x1c9;
	cocos2d::CCAction* m_myAction;
	bool unk_0x1d0;
	bool m_poweredOn;
	float unk_0x1d4;
	float unk_0x1d8;
	bool m_hasGlow;
	bool unk_0x1de;
	cocos2d::CCParticleSystem* m_particleSystem;
	std::string m_particleString;
	bool m_particleAdded;
	bool unk_0x204;
	bool unk_0x218;
};

#endif