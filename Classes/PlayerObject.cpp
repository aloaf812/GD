#include "PlayerObject.h"
#include "GameManager.h"
#include "PlayLayer.h"
USING_NS_CC;

// hi there, 
// this and PlayLayer are halfway there, with just hitboxes and other gamemodes being the main issues.
// hopefully they'll be done next month

PlayerObject::PlayerObject()
{
	m_vehicleSprite = nullptr;
	m_vehicleSpriteSecondary = nullptr;
	m_vehicleSpriteThird = nullptr;
	unk_0x2e4 = nullptr;
	m_flyMode = false;
	m_birdMode = false;
	m_rollMode = false;

	m_isLocked = false;

	m_gravityFlipped = false;

	m_canJump = false;
	unk_0x30e = false;

	unk_0x324 = 0.0f;
}

PlayerObject* PlayerObject::create(int player, int ship, CCLayer* layer)
{
    PlayerObject* pRet = new PlayerObject();
    if (pRet && pRet->init(player, ship, layer))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

bool PlayerObject::init(int player, int ship, CCLayer* layer) {
    
	int playerIdx = MAX(1, MIN(38, player));
	int shipIdx = MAX(1, MIN(14, ship));
    
    std::string frameFile = CCString::createWithFormat("player_%02d_001.png", playerIdx)->getCString();
	std::string frameFile2 = CCString::createWithFormat("player_%02d_2_001.png", playerIdx)->getCString();
    
	if (!GameObject::init(frameFile.c_str())) 
		return false;
	
	m_ghostType = GhostType::Disabled;
	m_timeMod = 0.9f;

	if (!layer)
		m_gameLayer = PLAY_LAYER->getGameLayer();
	else
		m_gameLayer = layer;

	m_isPlayLayer = layer == nullptr;

	this->setTextureRect(CCRectZero);

#pragma region Icon Frames
	m_iconSprite = CCSprite::createWithSpriteFrameName(frameFile.c_str());
	this->addChild(m_iconSprite, 1);
	m_iconSpriteSecondary = CCSprite::createWithSpriteFrameName(frameFile2.c_str());
	this->addChild(m_iconSpriteSecondary, -1);
	m_iconSpriteSecondary->setPosition(this->convertToNodeSpace(CCPointZero));
#pragma endregion

	std::string sFrameFile = CCString::createWithFormat("ship_%02d_001.png", shipIdx)->getCString();
	std::string sFrameFile2 = CCString::createWithFormat("ship_%02d_2_001.png", shipIdx)->getCString();

	m_vehicleSprite = CCSprite::createWithSpriteFrameName(sFrameFile.c_str());
	this->addChild(m_vehicleSprite, 2);
	m_vehicleSprite->setVisible(false);

	m_vehicleSpriteSecondary = CCSprite::createWithSpriteFrameName(sFrameFile2.c_str());
	m_vehicleSprite->addChild(m_vehicleSpriteSecondary, -1);
	m_vehicleSpriteSecondary->setPosition(m_vehicleSprite->convertToNodeSpace(CCPointZero));

	m_vehicleSpriteThird = CCSprite::createWithSpriteFrameName(sFrameFile.c_str());
	m_vehicleSprite->addChild(m_vehicleSpriteThird, -2);
	m_vehicleSpriteThird->setPosition(m_vehicleSprite->convertToNodeSpace(CCPointZero));
	m_vehicleSpriteThird->setVisible(false);

	m_isJumping = false;
	m_yVelocity = 0;
	m_canJump = false;
	m_onGround = false;
	m_isDead = false;
	m_playerScale = 1.0;
	this->updateTimeMod(0.9f);
	m_checkpointArray = nullptr;

#pragma region Particles
	m_dragParticle = CCParticleSystemQuad::create("dragEffect.plist");
	m_dragParticle->setPositionType(kCCPositionTypeFree);
	m_gameLayer->addChild(m_dragParticle, -1);
	m_dragParticle->stopSystem();
	m_pGroundActive = false;

	m_burstParticle = CCParticleSystemQuad::create("burstEffect.plist");
	m_burstParticle->setPositionType(kCCPositionTypeFree);
	m_gameLayer->addChild(m_burstParticle, -1);
	m_burstParticle->stopSystem();

	m_birdDragParticle = CCParticleSystemQuad::create("dragEffect.plist");
	m_birdDragParticle->setPositionType(kCCPositionTypeFree);
	m_gameLayer->addChild(m_birdDragParticle, -1);
	m_birdDragParticle->stopSystem();
	unk_0x308 = m_birdDragParticle->getLife();
	m_birdDragParticle->setPosVar(ccp(0.0f, 2.0f));

	m_dragParticle2 = CCParticleSystemQuad::create("dragEffect.plist");
	m_dragParticle2->setPositionType(kCCPositionTypeFree);
	m_gameLayer->addChild(m_dragParticle2, -1);
	m_dragParticle2->stopSystem();

	m_birdDragParticle->setSpeed(m_birdDragParticle->getSpeed() * 0.2f);
	m_birdDragParticle->setSpeedVar(m_birdDragParticle->getSpeedVar() * 0.2f);

	m_dragParticle2->setPosVar(ccp(0.0f, 2.0f));
	m_dragParticle2->setSpeed(m_dragParticle2->getSpeed() * 2);
	m_dragParticle->setSpeedVar(m_dragParticle2->getSpeedVar() * 2);
	m_dragParticle2->setAngleVar(m_dragParticle2->getAngleVar() * 2);
	m_dragParticle2->setStartSize(m_dragParticle2->getStartSize() * 1.5f);
	m_dragParticle2->setStartSizeVar(m_dragParticle2->getStartSizeVar() * 1.5f);

	m_pShipActive = false;

	m_birdDragParticle->setStartColor(ccc4f(0.0f, 1.0f, 1.0f, 1 / 2.55));
	m_birdDragParticle->setEndColor(ccc4f(0.0f, 0.0f, 1.0f, 1.0f));

	m_dragParticle2->setStartColor(ccc4f(0.0f, 1.0f, 1.0, 1.90 / 2.55));
	m_dragParticle2->setEndColor(ccc4f(0.0f, 0.0f, 1.0f, 1.0f));

	m_shipDragParticle = CCParticleSystemQuad::create("shipDragEffect.plist");
	m_shipDragParticle->setPositionType(kCCPositionTypeGrouped);
	m_gameLayer->addChild(m_shipDragParticle, 1);
	m_shipDragParticle->stopSystem();

	m_landParticle = CCParticleSystemQuad::create("landEffect.plist");
	m_landParticle->setPositionType(kCCPositionTypeGrouped);
	m_gameLayer->addChild(m_landParticle, 1);
	m_landParticle->stopSystem();
	unk_0x374 = m_landParticle->getAngle();
	unk_0x378 = m_landParticle->getGravity().y;

	m_landParticle2 = CCParticleSystemQuad::create("landEffect.plist");
	m_landParticle2->setPositionType(kCCPositionTypeGrouped);
	m_gameLayer->addChild(m_landParticle2, 1);
	m_landParticle2->stopSystem();
#pragma endregion Particles

	setupStreak();

	ccBlendFunc blendFunc = { GL_SRC_ALPHA, GL_ONE };
	unk_0x2e4 = CCSprite::createWithSpriteFrameName(frameFile.c_str());
	unk_0x2e4->setTextureRect(CCRectZero);
	unk_0x2e4->setBlendFunc(blendFunc);

	if (!m_isPlayLayer) 
		m_gameLayer->addChild(unk_0x2e4);
	else
		PLAY_LAYER->getBatchNodeAdd()->addChild(unk_0x2e4, 20);

	m_iconGlow = CCSprite::createWithSpriteFrameName(
		CCString::createWithFormat("player_%02d_glow_001.png", playerIdx)->getCString());
	m_iconGlow->setVisible(false);
	m_iconGlow->setBlendFunc(blendFunc);
	unk_0x2e4->addChild(m_iconGlow, 2);

	m_vehicleGlow = cocos2d::CCSprite::createWithSpriteFrameName(
		CCString::createWithFormat("ship_%02d_glow_001.png", shipIdx)->getCString());
	unk_0x2e4->addChild(m_vehicleGlow, -3);
	m_vehicleGlow->setVisible(false);
	m_vehicleGlow->setBlendFunc(blendFunc);
	updatePlayerGlow();

    return true;
}

void PlayerObject::releaseButton(PlayerButton button)
{
	if (button == PlayerButton::Jump) {
		if (m_isPlayLayer)
			PLAY_LAYER->recordAction(false);

		this->unk_0x30e = false;
		this->unk_0x312 = false;
	}
}

void PlayerObject::lockPlayer()
{
	m_isLocked = true;
	this->stopActionByTag(0);
	this->stopActionByTag(1);
	this->releaseButton(PlayerButton::Jump);
	this->deactivateParticle();
	m_onGround = false;
}

bool PlayerObject::isFlying()
{
	if (!m_flyMode)
		return m_birdMode;

	return true;
}

void PlayerObject::logValues()
{
	// hey robtop lowkey give us the gd source code :)
}

void PlayerObject::update(float dt)
{
	if (!m_isDead) {
		m_lastUpdatePos = getPosition();
		if (!m_isLocked) {
			this->updateJump(dt * 0.9f);
			this->setPosition(getPosition() + ccp(dt * m_speed * m_timeMod, dt * 0.9f * m_yVelocity));
		}
		if (isFlying()) {
			if (m_flyMode) {
				if (!unk_0x30e || levelFlipping()) {
					if (m_pShipActive)
						m_dragParticle2->stopSystem();
					
					m_pShipActive = false;
				}
				else {
					if (!m_pShipActive)
						m_dragParticle2->resumeSystem();

					m_pShipActive = true;
				}
			}
			if (!m_onGround || (m_yVelocity <= -1.0))
				m_shipDragParticle->stopSystem();
			else
				m_shipDragParticle->resumeSystem();
		}
		else if (!m_onGround || levelFlipping() || !m_isLocked) {
			this->touchedObject(nullptr);
			if (m_pGroundActive && this->getActionByTag(2) == 0) {
				CCDelayTime* delay = CCDelayTime::create(0.6f);
				CCCallFunc* uVar4 = CCCallFunc::create(this, callfunc_selector(PlayerObject::deactivateParticle));
				CCSequence* pCVar5 = CCSequence::create(delay, uVar4, nullptr);
				pCVar5->setTag(2);
				this->runAction(pCVar5);
			}
		}
		else {
			if (!m_pGroundActive)
				m_dragParticle->resumeSystem();

			m_pGroundActive = true;
			this->stopActionByTag(2);
		}

		if (isFlying() && (19 < ++unk_0x348)) {
			unk_0x348 = 0;
			this->tryPlaceCheckpoint();
		}
		
		/*if (unk_0x318 != 0.0 && (0.1 < FUN_0019d1c8() - unk_0x31c))
			unk_0x318 = 0.0;*/
	}
}

void PlayerObject::deactivateParticle()
{
	if (m_pGroundActive)
		m_dragParticle->stopSystem();

	m_pGroundActive = false;
}

void PlayerObject::activateStreak()
{
	if (!levelFlipping())
		m_playerStreak->resumeStroke();
}

void PlayerObject::deactivateStreak()
{
	m_playerStreak->stopStroke();
}

void PlayerObject::resetObject()
{
	unk_0x30c = true;
	deactivateStreak();
	removePendingCheckpoint();
	unk_0x318 = 0.0f;
	m_lastGroundPos = CCPointZero;
	m_portalObject = nullptr;
	m_isLocked = false;
	unk_0x340 = nullptr;
	unk_0x310 = false;
	setPosition(PLAY_LAYER->getStartPos());
	m_yVelocity = 0;
	flipGravity(false, false);
	toggleFlyMode(false);
	toggleRollMode(false);
	toggleBirdMode(false);
	togglePlayerScale(false);
	stopRotation();
	setRotation(0);
	m_isDead = false;
	stopActionByTag(3);
	setOpacity(255);
	toggleGhostEffect(GhostType::Disabled);
	updateTimeMod(0.9f);

	if (PLAY_LAYER && !PLAY_LAYER->getCleanReset()) {
		CCBlink* blink = CCBlink::create(0.4f, 4);
		CCSequence* seq1 = CCSequence::create(blink, CCShow::create(), nullptr);
		this->runAction(seq1);
		if (!GameManager::sharedState()->getPerformanceMode()) {
			int i = 0;
			do {
				CCCallFunc* callback = CCCallFunc::create(this, callfunc_selector(PlayerObject::spawnCircle));
				CCSequence* seq2 = CCSequence::create(CCDelayTime::create(i++ * 0.1f), callback, nullptr);
				this->runAction(seq2);
			} while (i != 4);
		}
	}

	resetStreak();
	levelFlipFinished();
	touchedObject(nullptr);
	unk_0x30c = false;
}

void PlayerObject::resetPlayerIcon()
{
	this->runRotateAction();
	
	m_iconSprite->setScale(1.0f);	
	m_iconSprite->setPosition(CCPointZero);
	m_vehicleSprite->setVisible(false);
	m_vehicleSpriteThird->setVisible(false);
	
	updatePlayerGlow();
	
	m_birdDragParticle->stopSystem();
	m_dragParticle2->stopSystem();
	m_shipDragParticle->stopSystem();
	
	// one divided by 2.55 i have NO idea why robtop did this
	m_birdDragParticle->setStartColor(ccc4f(0.0f, 1.0f, 1.0f, 1 / 2.55));
	m_birdDragParticle->setEndColor(ccc4f(0.0f, 0.0f, 1.0f, 1.0f));

	if (!unk_0x30c)
		this->spawnPortalCircle(ccc3(0, 255, 100), 50.0f);
	
	this->deactivateStreak();
	this->updatePlayerScale();
}

void PlayerObject::pushButton(PlayerButton button)
{
	if ((!m_isLocked) && (button == PlayerButton::Jump)) {
		if (m_isPlayLayer) {
			PLAY_LAYER->recordAction(true);
		}

		this->unk_0x30e = true;
		this->unk_0x312 = true;
		if (!m_rollMode) {
			if (m_touchedRing != nullptr) {
				this->ringJump();
				return;
			}
			if (isFlying()) {
				return;
			}

			if (!unk_0x30e) {
				return;
			}
		}
		else if (m_touchedRing != nullptr) {
			this->ringJump();
			return;
		}

		if (m_canJump != false) {
			this->updateJump(0.0f);
			return;
		}
	}
}

void PlayerObject::playerDestroyed()
{
	if (unk_0x318 != 0.0f) {
		// PLAY_LAYER->removeLastCheckpoint();
		unk_0x318 = 0.0f;
	}

	this->m_isDead = true;
	this->stopRotation();
	this->deactivateParticle();
	this->touchedObject(nullptr);

	m_birdDragParticle->stopSystem();
	m_dragParticle2->stopSystem();
	m_shipDragParticle->stopSystem();

	toggleGhostEffect(GhostType::Disabled);
}

void PlayerObject::playBurstEffect()
{
	if (!levelFlipping()) {
		m_burstParticle->resumeSystem();
		this->stopActionByTag(6);
		CCSequence* seq = CCSequence::create(CCDelayTime::create(0.12f),
			CCCallFunc::create(this, callfunc_selector(PlayerObject::stopBurstEffect)),
			nullptr);

		seq->setTag(6);
		runAction(seq);
	}
}

void PlayerObject::stopBurstEffect()
{
	m_burstParticle->stopSystem();
}

void PlayerObject::spawnCircle()
{

}

void PlayerObject::spawnPortalCircle(ccColor3B color, float size)
{

}

void PlayerObject::setColor(const ccColor3B& color)
{
	CCSprite::setColor(color);
	m_iconSprite->setColor(color);
	m_vehicleSprite->setColor(color);
}

void PlayerObject::setSecondColor(const ccColor3B& color)
{
	m_iconSpriteSecondary->setColor(color);
	m_vehicleSpriteSecondary->setColor(color);
}

void PlayerObject::setVisible(bool visible)
{
	GameObject::setVisible(visible);
	if (unk_0x2e4 != nullptr)
		unk_0x2e4->setVisible(visible);
}

void PlayerObject::setScale(float scale)
{
	GameObject::setScale(scale);
	if (unk_0x2e4 != nullptr)
		unk_0x2e4->setScale(scale);
}

void PlayerObject::setScaleX(float scale)
{
	GameObject::setScaleX(scale);
	if (unk_0x2e4 != nullptr)
		unk_0x2e4->setScaleX(scale);
}

void PlayerObject::setScaleY(float scale)
{
	GameObject::setScaleY(scale);
	if (unk_0x2e4 != nullptr)
		unk_0x2e4->setScaleY(scale);
}

void PlayerObject::setRotation(float rotation)
{
	GameObject::setRotation(rotation);
	if (unk_0x2e4 != nullptr)
		unk_0x2e4->setRotation(rotation);
}

void PlayerObject::setOpacity(GLubyte opacity)
{
	GameObject::setOpacity(opacity);
	m_iconSprite->setOpacity(opacity);
	m_iconSpriteSecondary->setOpacity(opacity);
	m_iconGlow->setOpacity(opacity);
	m_vehicleSprite->setOpacity(opacity);
	m_vehicleSpriteSecondary->setOpacity(opacity);
	m_vehicleSpriteThird->setOpacity(opacity);
	m_vehicleGlow->setOpacity(opacity);
}

void PlayerObject::setPosition(CCPoint const &position) {
	GameObject::setPosition(position);
	unk_0x2e4->setPosition(position);

	// this is WRONG like very very WRONG
	m_birdDragParticle->setPosition(position);
	m_dragParticle2->setPosition(position);
	m_burstParticle->setPosition(position);
	m_dragParticle->setPosition(position);
	m_shipDragParticle->setPosition(position);
}

void PlayerObject::setFlipX(bool flip)
{
	GameObject::setFlipX(flip);
	if (unk_0x2e4 != nullptr)
		unk_0x2e4->setFlipX(flip);
}

void PlayerObject::setFlipY(bool flip)
{
	GameObject::setFlipY(flip);
	if (unk_0x2e4 != nullptr)
		unk_0x2e4->setFlipY(flip);
}

void PlayerObject::updateShipRotation(float dt)
{

}

void PlayerObject::updateGlowColor()
{

}

void PlayerObject::updateJump(float dt)
{
	double gravity = this->m_gravity;
	double gravity2;
	if ((this->m_rollMode != false) || (isFlying()))
		gravity2 = 0.958199;
	else
		gravity2 = gravity;

	float pScale;
	bool isPlayerBig = this->m_playerScale == 1.0;
	if (isPlayerBig)
		pScale = 1.0f;
	else
		pScale = 0.8f;

	if (!isFlying())
	{
		float fVar5 = 0.6f;
		if (!this->m_rollMode) {
			fVar5 = 1.0f;
		}

		if ((unk_0x30e) && (m_canJump)) {
			this->m_isJumping = true;
			this->m_onGround = false;
			this->m_canJump = false;
			this->unk_0x312 = false;

			this->m_yVelocity = m_yStart * flipMod() * pScale;
			this->incrementJumps();
			if (this->m_rollMode != false) {
				/*flipGravity(this, (bool)(this->m_gravityFlipped ^ 1), true);
				dVar11 = (double)__muldf3(*(undefined4 *)pdVar8, *(undefined4 *)((int)&this->m_yVelocity + 4)
					, 0x40000000, 0x3fe33333);
				*pdVar8 = dVar11;*/
				unk_0x316 = 0;
				unk_0x30e = false;
				return;
			}
			runRotateAction();
			return;
		}

		if (this->m_isJumping) {
			this->m_yVelocity = m_yVelocity - gravity2 * dt * flipMod() * fVar5;

			if (!playerIsFalling())
				return;

			this->m_isJumping = false;
			this->unk_0x30f = true;
			this->m_onGround = false;
			return;
		}

		if (playerIsFalling()) {
			m_canJump = false;
		}

		m_yVelocity = m_yVelocity - gravity2 * dt * flipMod() * fVar5;

		if (!this->m_gravityFlipped) {
			if (m_yVelocity > 15.0)
				m_yVelocity = 15.0;
			else if (m_yVelocity < -15.0)
				m_yVelocity = -15.0;
		}

		if (!playerIsFalling())
			return;

		if ((!m_rollMode) && (!getActionByTag(0)))
			runRotateAction();

	}

	this->m_onGround = false;
}

void PlayerObject::updateTimeMod(float timeMod)
{
	if ((this->unk_0x30c == false) && (m_timeMod != timeMod))
		PLAY_LAYER->playSpeedParticle(timeMod);

	// temporary dummy values
	this->m_timeMod = timeMod;
	if (timeMod == 0.9f) {
		this->m_yStart = 11.180031776428223;
		this->m_gravity = 0.9581990242004395;
		this->m_speed = 5.7700018882751465;
	}
	else if (timeMod == 0.7f) {
		this->m_yStart = 10.620032;
		this->m_gravity = 0.940199;
		this->m_speed = 5.980002;
	}
	else if (timeMod == 1.1f) {
		this->m_yStart = 11.420032;
		this->m_gravity = 0.957199;
		this->m_speed = 5.870002;
	}
	else if (timeMod == 1.3f) {
		this->m_yStart = 11.230032;
		this->m_gravity = 0.961199;
		this->m_speed = 6.000002;
	}

	if (m_rollMode)
		this->runRotateAction();
}

void PlayerObject::updatePlayerGlow()
{

}

void PlayerObject::updatePlayerScale()
{

}

void PlayerObject::updatePlayerFrame(int frame)
{
	if (frame >= 38) frame = 38;
	if (frame <= 0) frame = 1;

	char const* spriteFrame1 = CCString::createWithFormat("player_%02d_001.png", frame)->getCString();
	char const* spriteFrame2 = CCString::createWithFormat("player_%02d_2_001.png", frame)->getCString();
	char const* spriteFrameGlow = CCString::createWithFormat("player_%02d_glow_001.png", frame)->getCString();

	m_iconSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(spriteFrame1));
	m_iconSpriteSecondary->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(spriteFrame2));
	m_iconGlow->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(spriteFrameGlow));
	CCSize iconSize = m_iconSprite->getContentSize();
	m_iconSpriteSecondary->setPosition(ccp(iconSize.width * 0.5f, iconSize.height * 0.5f));
}

void PlayerObject::updatePlayerShipFrame(int sFrame)
{
	if (sFrame >= 14) sFrame = 14;
	if (sFrame <= 0) sFrame = 1;

	char const* shipFrame1 = CCString::createWithFormat("ship_%02d_001.png", sFrame)->getCString();
	char const* shipFrame2 = CCString::createWithFormat("ship_%02d_2_001.png", sFrame)->getCString();
	char const* shipFrameGlow = CCString::createWithFormat("ship_%02d_glow_001.png", sFrame)->getCString();

	m_vehicleSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(shipFrame1));
	m_vehicleSpriteSecondary->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(shipFrame2));
	m_vehicleGlow->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(shipFrameGlow));
	CCSize iconSize = m_vehicleSprite->getContentSize();
	m_vehicleSpriteSecondary->setPosition(ccp(iconSize.width * 0.5f, iconSize.height * 0.5f));
}

void PlayerObject::updatePlayerRollFrame(int rFrame)
{
	if (rFrame >= 7) rFrame = 7;
	if (rFrame <= 0) rFrame = 1;

	char const* rollFrame1 = CCString::createWithFormat("player_ball_%02d_001.png", rFrame)->getCString();
	char const* rollFrame2 = CCString::createWithFormat("player_ball_%02d_2_001.png", rFrame)->getCString();
	char const* rollFrameGlow = CCString::createWithFormat("player_ball_%02d_glow_001.png", rFrame)->getCString();

	m_iconSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(rollFrame1));
	m_iconSpriteSecondary->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(rollFrame2));
	m_iconGlow->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(rollFrameGlow));
	CCSize iconSize = m_iconSprite->getContentSize();
	m_iconSpriteSecondary->setPosition(ccp(iconSize.width * 0.5f, iconSize.height * 0.5f));
}

void PlayerObject::updatePlayerBirdFrame(int bFrame)
{
	if (bFrame >= 7) bFrame = 7;
	if (bFrame <= 0) bFrame = 1;

	char const* birdFrame1 = CCString::createWithFormat("bird_%02d_001.png", bFrame)->getCString();
	char const* birdFrame2 = CCString::createWithFormat("bird_%02d_2_001.png", bFrame)->getCString();
	char const* birdFrame3 = CCString::createWithFormat("bird_%02d_3_001.png", bFrame)->getCString();
	char const* birdFrameGlow = CCString::createWithFormat("bird_%02d_glow_001.png", bFrame)->getCString();

	m_vehicleSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(birdFrame1));
	m_vehicleSpriteSecondary->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(birdFrame2));
	m_vehicleGlow->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(birdFrameGlow));
	m_vehicleSpriteThird->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(birdFrame2));
	CCSize iconSize = m_vehicleSprite->getContentSize();
	m_vehicleSpriteSecondary->setPosition(ccp(iconSize.width * 0.5f, iconSize.height * 0.5f));
	m_vehicleSpriteThird->setPosition(m_vehicleSpriteSecondary->getPosition());
}

bool PlayerObject::levelFlipping()
{
	if (m_isPlayLayer) {
		return PLAY_LAYER->isFlipping();
	}
	return false;
}

float PlayerObject::flipMod()
{
	if (!m_gravityFlipped)
		return 1.0f;
	else
		return -1.0f;
}

void PlayerObject::incrementJumps()
{
	if (m_isPlayLayer) {
		PLAY_LAYER->incrementJumps();
		m_hasJumped = true;
	}
}


bool PlayerObject::playerIsFalling()
{
	double targetVel = m_gravity + m_gravity;
	if (m_gravityFlipped)
		return targetVel < m_yVelocity;
	else
		return m_yVelocity < targetVel;
}

bool PlayerObject::isSafeFlip()
{
	if (unk_0x324 == 0.0f)
		return false;

	return -15.0 <= m_yVelocity;
}

void PlayerObject::levelFlipFinished()
{

}

void PlayerObject::hitGround(bool notFlipped)
{
	m_yVelocity = 0;

	if ((!m_onGround && !notFlipped) && !levelFlipping()) {
		CCParticleSystemQuad* landParticle;
		if (unk_0x368)
			landParticle = m_landParticle;
		else
			landParticle = m_landParticle2;

		this->unk_0x368 = unk_0x368 ^ 1;
		landParticle->setAngle(unk_0x374 * flipMod());
		landParticle->setGravity(ccp(m_landParticle->getGravity().x, unk_0x378 * flipMod()));
		landParticle->setPosition(this->getPosition() + ccp(0.0f, (-12 * flipMod()) * m_playerScale));
		landParticle->resetSystem();
	}

	m_onGround = true;
	m_canJump = true;
	unk_0x316 = true;

	if (!m_rollMode && getActionByTag(0))
		this->stopRotation();

	if (m_rollMode && !getActionByTag(0))
		this->runRotateAction();

	m_lastGroundPos = this->getPosition();
	if (!isFlying()) {
		this->deactivateStreak();
		this->tryPlaceCheckpoint();
	}
	unk_0x310 = false;
}

void PlayerObject::ringJump()
{
	// todo
}

void PlayerObject::collidedWithObject(float dt, GameObject* obj)
{
	CCRect playerRect = this->getObjectRect();
	CCRect objRect = obj->getObjectRect();

	float objMaxY = objRect.getMaxY();
	float objMinY = objRect.getMinY();

	// currently used as a placeholder since this is a pretty big function
	if (false) {
		if (this->getObjectRect(0.3f, 0.3f).intersectsRect(obj->getObjectRect())) {
			if ((true) && (isSafeFlip())) {
				CCPoint moveToPos;
				if (!m_gravityFlipped)
					moveToPos = ccp(getPosition().x, getPosition().y - objMinY);
				else
					// moveToPos = ccp(getPosition().x, (float)((ulonglong)uVar11 >> 0x20));
				this->setPosition(moveToPos);
				this->hitGround(true);
				m_onGround = false;
			}
			else {
				if (obj->getType() == GameObjectType::unknown22) {
					// obj->destroyObject();
				}
				else {
					if (!PLAY_LAYER->getPlaybackMode())
						PLAY_LAYER->destroyPlayer();
				}
			}
		}
	}

}

// the saxophones are getting louder.
void PlayerObject::runRotateAction()
{
	if (!m_isLocked) {
		this->stopRotation();
		if (m_rollMode)
			this->runBallRotation();
		else
			this->runNormalRotation();
	}
}

void PlayerObject::runNormalRotation()
{
	if (!isFlying()) {
		float rotateValue;
		if (m_playerScale == 1.0)
			rotateValue = 0.43333334f;
		else
			rotateValue = 0.33333334f;

		CCRotateBy* rotateAction = CCRotateBy::create(rotateValue, (180 * flipMod()));
		rotateAction->setTag(0);
		this->runAction(rotateAction);
	}
}

void PlayerObject::runBallRotation()
{
	// todo
}

void PlayerObject::stopRotation()
{
	this->stopActionByTag(0);
	this->stopActionByTag(1);

	if ((getRotation() != 0.0f) && (!m_rollMode)) {
		float rotInterval;
		if (flipMod() == 1.0f)
			rotInterval = 90.0f * (roundf(getRotation() / 90.0f));
		else
			rotInterval = -90.0f * (roundf(getRotation() / -90.0f));

		this->setRotation(rotInterval);
	}
}

void PlayerObject::toggleFlyMode(bool enable)
{
	if (m_flyMode != enable) {
		m_flyMode = enable;

		if (enable) {
			this->toggleRollMode(false);
			this->toggleBirdMode(false);
		}

		this->stopRotation();
		m_yVelocity = m_yVelocity * 0.5;
		this->setVisible(false);
		m_onGround = false;
		m_canJump = false;
		unk_0x310 = false;
		this->removePendingCheckpoint();

		if (m_flyMode) {
			this->updatePlayerShipFrame(GameManager::sharedState()->getPlayerShip());
			m_iconSprite->setScale(0.55f);
			m_iconSprite->setPosition(ccp(0.0f, 5.0f));

			m_vehicleSprite->setVisible(true);
			m_vehicleSprite->setPosition(ccp(0.0f, -5.0f));
			this->updatePlayerGlow();

			m_birdDragParticle->resetSystem();
			m_dragParticle2->resetSystem();
			m_dragParticle2->stopSystem();

			m_pShipActive = false;
			this->deactivateParticle();
			this->spawnPortalCircle(ccc3(255, 0, 255), 50.0f);
			this->activateStreak();
			this->updatePlayerScale();
		}
		else
			this->resetPlayerIcon();
	}
}

void PlayerObject::toggleRollMode(bool enable)
{
	if (m_rollMode != enable) {
		m_rollMode = enable;
		
		if (enable) {
			this->toggleFlyMode(false);
			this->toggleBirdMode(false);
		}

		if (!m_rollMode) {
			if (!unk_0x30c)
				this->spawnPortalCircle(ccc3(0, 255, 100), 50.0f);

			if (m_playerScale == 1.0)
				this->updatePlayerFrame(GameManager::sharedState()->getPlayerFrame());
			else
				this->updatePlayerFrame(0);
		}
		else {
			if (m_playerScale == 1.0)
				this->updatePlayerRollFrame(GameManager::sharedState()->getPlayerBall());
			else
				this->updatePlayerRollFrame(0);

			this->spawnPortalCircle(ccc3(255, 50, 50), 50.0f);
		}
		this->stopRotation();
	}
}

void PlayerObject::toggleBirdMode(bool enable)
{
	// uses FUN_0019cdac, which is in fact unimplemented.
}

void PlayerObject::toggleGhostEffect(GhostType type)
{

}

void PlayerObject::togglePlayerScale(bool scaled)
{

}

void PlayerObject::touchedObject(GameObject* obj)
{

}

// HelloWorld("print")
void PlayerObject::saveToCheckpoint(CheckpointObject* check)
{
	CCPoint playerPos;
	if (PLAY_LAYER->isFlipping())
		playerPos = this->getPosition();
	else
		playerPos = PLAY_LAYER->getRealPlayerPos();

	check->setPlayerPos(playerPos);
	check->setPlayerYVel(m_yVelocity);
	check->setFlipGravity(m_gravityFlipped);
	check->setFlyMode(m_flyMode);
	check->setRollMode(m_rollMode);
	check->setBirdMode(m_birdMode);
	check->setCanJump(m_canJump);
	check->setGhostType((int)m_ghostType);
	check->setIsScaled(m_playerScale != 1.0f);
	check->setTimeMod(m_timeMod);

	if (isFlying() || m_rollMode) {
		if (PLAY_LAYER->getCameraPortal()) {
			check->setPortalObject(PLAY_LAYER->getCameraPortal());
		}	
	}
}

void PlayerObject::tryPlaceCheckpoint()
{

}

void PlayerObject::removePendingCheckpoint()
{
	if (m_checkpointArray) {
		GameObject* check = m_checkpointArray->getObject();
		PLAY_LAYER->removeObjectFromSection(check);
		check->removeGlow();
		check->removeMeAndCleanup();
		m_checkpointArray->release();
		m_checkpointArray = nullptr;
	}
}

void PlayerObject::resetStreak()
{

}

void PlayerObject::setupStreak()
{

}

void PlayerObject::flipGravity(bool, bool)
{

}