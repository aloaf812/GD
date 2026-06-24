#include "GameObject.h"
#include "ObjectToolbox.h"
#include "GameManager.h"

USING_NS_CC;

GameObject::GameObject() {
	this->unk_0x1b8 = 0;
	this->unk_0x1bc = 0;
	this->unk_0x1c0 = false;
	this->m_glowSprite = nullptr;
	this->unk_0x1c8 = false;
	this->unk_0x1c9 = false;
	this->m_myAction = nullptr;
	this->unk_0x1d0 = false;
	this->m_poweredOn = false;
	this->unk_0x1d4 = 0.0f;
	this->unk_0x1d8 = 0.0f;
	this->m_isActive = false;
	this->m_hasGlow = false;
	this->unk_0x1de = false;
	this->m_particleSystem = nullptr;
	this->m_particleString = "";
	this->m_particleAdded = false;
	this->unk_0x204 = false;
	this->unk_0x218 = false;
	this->m_hasColor = false;
	this->m_colorSprite = nullptr;
	this->m_ignoreScreenCheck = false;
	this->m_radius = 0.0f;
	this->m_isRotated = false;
	this->m_scaleModX = 1.0f;
	this->m_scaleModY = 1.0f;
	this->m_ID = 0;
	this->m_type = 0;
	this->m_sectionIdx = 0;
	this->m_shouldSpawn = false;
	this->m_touchTriggered = false;
	this->m_startPos = cocos2d::CCPointZero;
	this->m_blendAdditive = false;
	this->m_frame = "";
	this->m_usePlayerColor = false;
	this->m_usePlayerColor2 = false;
	this->m_isDisabled = false;
	this->m_useAudioScale = false;
	this->m_isSleeping = false;
	this->m_startRotation = 0.0f;
	this->m_startScaleX = 1.0f;
	this->m_startScaleY = 1.0f;
	this->m_shouldHide = false;
	this->m_spawnXPos = 0;
	this->m_isInvisible = false;
	this->m_enterAngle = 0.0f;
	this->m_enterEffect = 0;
	this->m_tintDuration = 0.0f;
	this->m_tintGround = false;
	this->m_objectKey = 0;
	this->m_dontTransform = false;
	this->m_dontFade = false;
	this->m_dontFadeTinted = false;
	this->m_isTintObject = false;
	this->m_hasBeenActivated = false;
	this->m_stateVar = false;
	this->m_objectZ = 0;
	this->m_objectParent = nullptr;
	this->m_customAudioScale = false;
	this->m_minAudioScale = 0.0f;
	this->m_maxAudioScale = 0.0f;
	this->m_uniqueID = 0;
	this->m_invisibleMode = false;
	this->m_glowUseBGColor = false;
	this->m_useBGColor = false;
	this->m_useSpecialLight = false;
	this->m_opacityMod = 1.0f;
	this->m_glowOpacityMod = 1.0f;
	this->m_dontShow = false;
	this->m_editorSelected = false;
	this->m_copyPlayerColor1 = false;
	this->m_copyPlayerColor2 = false;
	this->m_tintObjectsUseBlend = false;
}

bool GameObject::init(const char* spriteName) {
	if (spriteName && strlen(spriteName) > 0) {
		CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(spriteName);
		if (frame) {
			if (!CCSpritePlus::initWithSpriteFrame(frame)) {
				return false;
			}
		}
		else {
			if (!CCSpritePlus::initWithFile(spriteName)) {
				return false;
			}
		}
	}
	else {
		if (!CCSpritePlus::init()) {
			return false;
		}
	}

	this->m_tintDuration = 0.5f;
	this->setScale(1.0f);
	this->m_isActive = false;
	this->unk_0x1c0 = true;
	this->unk_0x1c8 = true;
	this->m_tintObjectsUseBlend = true;

	return true;
}

GameObject* GameObject::create(const char* spriteName) {
	GameObject* pRet = new GameObject();
	if (pRet && pRet->init(spriteName)) {
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return nullptr;
}

void GameObject::setPosition(cocos2d::CCPoint const &position) {
	CCSpritePlus::setPosition(position);
}

void GameObject::setFlipX(bool flipX) {
	CCSpritePlus::setFlipX(flipX);
}

void GameObject::setFlipY(bool flipY) {
	CCSpritePlus::setFlipY(flipY);
}

void GameObject::triggerObject() {
}

void GameObject::activateObject() {
}

void GameObject::deactivateObject() {
	if (this->m_shouldHide) {
		if (this->m_isActive) {
			this->m_isActive = false;

			GameManager* gm = GameManager::sharedState();
			if (this->unk_0x1c9 && gm) {
				void* layer = gm->getPlayLayer();
				if (layer && reinterpret_cast<uintptr_t>(layer) != 0xCDCDCDCD) {
				}
			}

			this->setVisible(false);
			if (this->m_glowSprite && reinterpret_cast<uintptr_t>(this->m_glowSprite) != 0xCDCDCDCD) this->m_glowSprite->setVisible(false);
			if (this->m_colorSprite && reinterpret_cast<uintptr_t>(this->m_colorSprite) != 0xCDCDCDCD) this->m_colorSprite->setVisible(false);
		}
	}
}

GameObject* GameObject::objectFromString(std::string objString) {
	return nullptr;
}

void GameObject::updateState() {
	if (!this->m_stateVar) {
		this->deactivateObject();
	}
}

void GameObject::customSetup() {
}

void GameObject::resetObject() {
	this->m_hasBeenActivated = false;
	this->m_isSleeping = false;
	this->unk_0x1de = false;
}

void GameObject::update(float dt) {
}

cocos2d::CCRect GameObject::getObjectRect() {
	return this->getObjectRect(this->m_scaleModX, this->m_scaleModY);
}

void GameObject::calculateSpawnXPos() {
	this->m_spawnXPos = this->m_startPos.x;
}

void GameObject::triggerActivated() {
	this->m_hasBeenActivated = true;
}

void GameObject::powerOnObject() {
	bool activated = this->m_poweredOn;
	this->m_stateVar = true;
	if (!activated) {
		this->m_poweredOn = true;
	}
}

void GameObject::powerOffObject() {
	if (this->m_poweredOn) {
		this->m_poweredOn = false;
	}
}

cocos2d::CCRect GameObject::getObjectRect(float scaleX, float scaleY) {
	cocos2d::CCSize size = cocos2d::CCSizeMake(this->unk_0x1d4, this->unk_0x1d8);
	float width = size.width * scaleX;
	float height = size.height * scaleY;

	if (this->m_isRotated) {
		float temp = width;
		width = height;
		height = temp;
	}

	cocos2d::CCPoint pos = this->getPosition();
	return cocos2d::CCRectMake(pos.x - width / 2.0f, pos.y - height / 2.0f, width, height);
}

void GameObject::setOpacity(unsigned char opacity) {
	unsigned int finalOpacity = opacity;
	if (!this->m_isSleeping) {
		finalOpacity = static_cast<unsigned int>(opacity * this->m_opacityMod);
	}

	cocos2d::CCSprite::setOpacity(finalOpacity);
	this->setGlowOpacity(finalOpacity);

	if (this->m_hasColor && this->m_colorSprite && reinterpret_cast<uintptr_t>(this->m_colorSprite) != 0xCDCDCDCD) {
		this->m_colorSprite->setOpacity(finalOpacity);
	}
}

void GameObject::setGlowOpacity(unsigned char opacity) {
	if (this->m_glowSprite && reinterpret_cast<uintptr_t>(this->m_glowSprite) != 0xCDCDCDCD) {
		unsigned char scaledOpacity = static_cast<unsigned char>(opacity * this->m_glowOpacityMod);
		this->m_glowSprite->setOpacity(scaledOpacity);
	}
}

void GameObject::setChildColor(cocos2d::_ccColor3B color) {
	if (this->m_hasColor && this->m_colorSprite && reinterpret_cast<uintptr_t>(this->m_colorSprite) != 0xCDCDCDCD) {
		this->m_colorSprite->setColor(color);
	}
}