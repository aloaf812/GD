
#ifndef __GeometryDash__GameObject__
#define __GeometryDash__GameObject__

#include "cocos2d.h"
#include "RT_COCOS/CCSpritePlus.h"
#include <stdio.h>

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
/**
 @brief  Represents an object in a level
 */
class GameObject : public CCSpritePlus {
public:
    GameObject();
	static GameObject* objectFromString(std::string objString);
    static GameObject* create(const char* spriteName);
    bool init(const char* spriteName);
    
    // virtual void update(float dt);
    // virtual void setScaleX(float scaleX);
    // virtual void setScaleY(float scaleY);
    // virtual void setScale(float scale);
	virtual void setPosition(cocos2d::CCPoint const &position);
    // virtual void setVisible(bool visible);
    // virtual void setRotation(float rotation);
    // virtual void setOpacity(unsigned char opacity);
    
    void disableObject();
    const char* getBallFrame(int idx);
    // void addColorSprite();
    void activateObject();
    void powerOffObject();
    void powerOnObject();
    /*void removeGlow();
    void triggerActivated();*/

	void updateState();
	void customSetup();

    virtual void setFlipX(bool flipX);
    virtual void setFlipY(bool flipY);
    virtual void resetObject();
    // virtual void deactivateObject();
    virtual cocos2d::CCRect getObjectRect();
	virtual cocos2d::CCRect getObjectRect(float scaleModX, float scaleModY);
    virtual cocos2d::CCRect getObjectRect2(float scaleModX, float scaleModY);
    /*virtual cocos2d::CCRect getObjectTextureRect();
    virtual cocos2d::CCPoint getRealPosition();
    virtual void setStartPos(cocos2d::CCPoint position);
    virtual std::string getSaveString();*/

	void createAndAddParticle(int objType, char const* file, int zOrder, cocos2d::tCCPositionType positionType);
    
    int unk_0x1b8;
    int unk_0x1bc;
    bool unk_0x1c0;
    cocos2d::CCSprite* m_glowSprite; // 0x1c4
    bool unk_0x1c8;
    bool unk_0x1c9;
    cocos2d::CCAction* m_myAction; // 0x1cc
    bool unk_0x1d0;
    bool m_poweredOn; // 0x1d1
    float unk_0x1d4;
    float unk_0x1d8;
	CC_SYNTHESIZE_READONLY(bool, m_isActive, IsActive); // 0x1dc
    bool m_hasGlow; // 0x1dd
    bool unk_0x1de;
    cocos2d::CCParticleSystemQuad* m_particleSystem; // 0x1e0
	std::string m_particleString;
	bool m_particleAdded;
    cocos2d::CCPoint unk_0x1ec;
    cocos2d::CCRect unk_0x1f4;
    bool unk_0x204;
    cocos2d::CCRect unk_0x208;
    bool unk_0x218;
	CC_SYNTHESIZE_READONLY(bool, m_hasColor, HasColor); // 0x219
	CC_SYNTHESIZE_READONLY(cocos2d::CCSprite*, m_colorSprite, ColorSprite); // 0x21c
	CC_SYNTHESIZE(bool, m_ignoreScreenCheck, IgnoreScreenCheck); // 0x220
    CC_SYNTHESIZE(float, m_radius, Radius); // 0x224
    // CC_PROPERTY_READONLY(bool, m_isRotated, IsRotated); // 0x228
    CC_SYNTHESIZE(float, m_scaleModX, ScaleModX); // 0x22c
    CC_SYNTHESIZE(float, m_scaleModY, ScaleModY); // 0x230
	CC_SYNTHESIZE(int, m_ID, M_ID); // 0x234
    CC_SYNTHESIZE(GameObjectType, m_type, Type); // 0x238
	CC_SYNTHESIZE(int, m_sectionIdx, SectionIdx); // 0x23c
    CC_SYNTHESIZE_READONLY(bool, m_shouldSpawn, ShouldSpawn); // 0x240
    /*CC_PROPERTY(bool, m_touchTriggered, TouchTriggered); // 0x241
    cocos2d::CCPoint m_realPosition; // 0x244*/
    CC_SYNTHESIZE_READONLY(std::string, m_frame, Frame); // 0x24c
    CC_SYNTHESIZE_READONLY(bool, m_blendAdditive, BlendAdditive); // 0x250
	CC_SYNTHESIZE_READONLY(bool, m_usePlayerColor, UsePlayerColor); // 0x251
	CC_SYNTHESIZE_READONLY(bool, m_usePlayerColor2, UsePlayerColor2); // 0x252
	CC_SYNTHESIZE(bool, m_isDisabled, IsDisabled); // 0x253
    // CC_PROPERTY(bool, m_useAudioScale, UseAudioScale); // 0x254
    CC_SYNTHESIZE_READONLY(bool, m_isSleeping, IsSleeping); // 0x255
    CC_SYNTHESIZE(float, m_startRotation, StartRotation); // 0x258
    CC_SYNTHESIZE(float, m_startScaleX, StartScaleX); // 0x25c
    CC_SYNTHESIZE(float, m_startScaleY, StartScaleY); // 0x260
	CC_SYNTHESIZE(bool, m_shouldHide, ShouldHide); // 0x264
    CC_SYNTHESIZE_READONLY(float, m_spawnXPos, SpawnXPos); // 0x268
	CC_SYNTHESIZE_READONLY(bool, m_isInvisible, IsInvisible); // 0x26c
    CC_SYNTHESIZE(float, m_enterAngle, EnterAngle); // 0x270
    CC_SYNTHESIZE(int, m_enterEffect, EnterEffect); // 0x274
    CC_SYNTHESIZE(cocos2d::ccColor3B, m_tintColor, TintColor); // 0x278
	CC_SYNTHESIZE(float, m_tintDuration, TintDuration); // 0x27c
	CC_SYNTHESIZE(bool, m_tintGround, TintGround); // 0x280
    CC_SYNTHESIZE(int, m_objectKey, ObjectKey); // 0x284
    /*CC_PROPERTY(bool, m_dontTransform, DontTransform); // 0x288
    CC_PROPERTY(bool, m_dontFade, DontFade); // 0x289
    CC_PROPERTY(bool, m_dontFadeTinted, DontFadeTinted); // 0x28a
    CC_PROPERTY(bool, m_isTintObject, IsTintObject); // 0x28b*/
	CC_SYNTHESIZE_READONLY(bool, m_hasBeenActivated, HasBeenActivated);
    CC_SYNTHESIZE(bool, m_stateVar, StateVar); // 0x28d
    CC_SYNTHESIZE(int, m_objectZ, ObjectZ); // 0x290
    CC_SYNTHESIZE(cocos2d::CCNode*, m_objectParent, ObjectParent); // 0x294
    /*CC_PROPERTY_READONLY(bool, m_customAudioScale, CustomAudioScale); // 0x298
    CC_PROPERTY_READONLY(float, m_minAudioScale, MinAudioScale); // 0x29c
    CC_PROPERTY_READONLY(float, m_maxAudioScale, MaxAudioScale); // 0x2a0
    CC_PROPERTY(int, m_uniqueID, UniqueID); // 0x2a4
    CC_PROPERTY_READONLY(bool, m_invisibleMode, InvisibleMode); // 0x2a8
    CC_PROPERTY_READONLY(bool, m_glowUseBGColor, GlowUseBGColor); // 0x2a9
    CC_PROPERTY_READONLY(bool, m_useBGColor, UseBGColor); // 0x2aa
    CC_PROPERTY_READONLY(bool, m_useSpecialLight, UseSpecialLight); // 0x2ab*/
    CC_SYNTHESIZE(float, m_opacityMod, OpacityMod); // 0x2ac
    CC_SYNTHESIZE(float, m_glowOpacityMod, GlowOpacityMod); // 0x2b0
	CC_SYNTHESIZE(bool, m_dontShow, DontShow); // 0x2b4
    CC_SYNTHESIZE(bool, m_editorSelected, EditorSelected); // 0x2b5
    CC_SYNTHESIZE(bool, m_copyPlayerColor1, CopyPlayerColor1); // 0x2b6
    CC_SYNTHESIZE(bool, m_copyPlayerColor2, CopyPlayerColor2); // 0x2b7
    CC_SYNTHESIZE(bool, m_tintObjectsUseBlend, TintObjectsUseBlend); // 0x2b8
};

#endif
