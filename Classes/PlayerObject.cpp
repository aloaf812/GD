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

	// FIX: these were left uninitialized until later in init(), but
	// PlayerObject::setPosition() can be invoked virtually (e.g. via
	// setTextureRect -> setPosition) before init() reaches the lines that
	// actually create these objects. Zero them here so any early call
	// is a safe no-op instead of dereferencing uninitialized heap memory
	// (the 0xCDCDCDCD MSVC debug-heap pattern seen in the crash dump).
	m_dragParticle = nullptr;
	m_birdDragParticle = nullptr;
	m_dragParticle2 = nullptr;
	m_shipDragParticle = nullptr;
	m_burstParticle = nullptr;
	m_landParticle = nullptr;
	m_landParticle2 = nullptr;
}

PlayerObject* PlayerObject::create(int player, int ship, cocos2d::CCLayer *layer)
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

bool PlayerObject::init(int player, int ship, cocos2d::CCLayer *layer) {
	int playerIdx;
	int shipIdx;

	playerIdx = player;
	if (player <= 0) playerIdx = 1;
	if (player >= 38) playerIdx = 38;

	shipIdx = ship;
	if (ship >= 14) shipIdx = 14;
	if (ship <= 0) shipIdx = 1;

	char const* frameFile = CCString::createWithFormat("player_%02d_001.png", playerIdx)->getCString();
	char const* frameFile2 = CCString::createWithFormat("player_%02d_2_001.png", playerIdx)->getCString();

	if (!GameObject::init(frameFile)) return false;

	m_ghostType = GhostType::Disabled;
	m_timeMod = 0.9f;

	if (!layer)
		m_gameLayer = PLAY_LAYER->getGameLayer();
	else
		m_gameLayer = layer;


	this->m_isPlayLayer = layer == nullptr;

	this->setTextureRect(CCRect(0.f, 0.f, 0.f, 0.f));

#pragma region Icon Frames
	m_iconSprite = CCSprite::createWithSpriteFrameName(frameFile);
	if (!m_iconSprite) {
		CCLOG("PlayerObject::init - missing sprite frame: %s", frameFile);
		return false;
	}
	this->addChild(m_iconSprite, 1);

	m_iconSpriteSecondary = CCSprite::createWithSpriteFrameName(frameFile2);
	if (!m_iconSpriteSecondary) {
		CCLOG("PlayerObject::init - missing sprite frame: %s", frameFile2);
		return false;
	}
	this->addChild(m_iconSpriteSecondary);
	m_iconSpriteSecondary->setPosition(this->convertToNodeSpace(m_iconSprite->getPosition()));
#pragma endregion

	char const* sFrameFile = CCString::createWithFormat("ship_%02d_001.png", shipIdx)->getCString();
	char const* sFrameFile2 = CCString::createWithFormat("ship_%02d_2_001.png", shipIdx)->getCString();

	m_vehicleSprite = CCSprite::createWithSpriteFrameName(sFrameFile);
	this->addChild(m_vehicleSprite, 2);
	m_vehicleSprite->setVisible(false);

	m_vehicleSpriteSecondary = CCSprite::createWithSpriteFrameName(sFrameFile2);
	m_vehicleSprite->addChild(m_vehicleSpriteSecondary, -1);
	m_vehicleSpriteSecondary->setPosition(m_vehicleSprite->convertToNodeSpace(m_vehicleSprite->getPosition()));

	m_vehicleSpriteThird = CCSprite::createWithSpriteFrameName(sFrameFile);
	m_vehicleSprite->addChild(m_vehicleSpriteThird, -2);
	m_vehicleSpriteThird->setPosition(m_vehicleSprite->convertToNodeSpace(m_vehicleSprite->getPosition()));
	m_vehicleSpriteThird->setVisible(false);

	this->m_isJumping = false;
	this->m_yVelocity = 0;
	this->m_canJump = false;
	this->m_onGround = false;
	this->m_isDead = false;
	this->m_playerScale = 1.0;
	this->updateTimeMod(0.9f);
	//this->field758_0x344 = 0;

#pragma region Particles
	this->m_dragParticle = CCParticleSystemQuad::create("dragEffect.plist");
	m_dragParticle->setPositionType(kCCPositionTypeFree);
	m_gameLayer->addChild(m_dragParticle, -1);
	m_dragParticle->stopSystem();
	this->m_pGroundActive = false;

	this->m_burstParticle = CCParticleSystemQuad::create("burstEffect.plist");
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
	m_birdDragParticle->setSpeedVar(m_birdDragParticle->getSpeedVar() * 0.2);

	m_dragParticle2->setPosVar(ccp(0.0f, 2.0f));

	int tmpVar = m_dragParticle2->getSpeed();
	m_dragParticle2->setSpeed(tmpVar + tmpVar);

	tmpVar = m_dragParticle2->getSpeedVar();
	m_dragParticle->setSpeedVar(tmpVar + tmpVar);

	tmpVar = m_dragParticle2->getAngleVar();
	m_dragParticle2->setAngleVar(tmpVar + tmpVar);

	m_dragParticle2->setStartSize(m_dragParticle2->getStartSize() * 1.5f);
	m_dragParticle2->setStartSizeVar(m_dragParticle2->getStartSizeVar() * 1.5f);

	m_pShipActive = false;

	m_birdDragParticle->setStartColor(ccc4f(0.0f, 1.0f, 1.0f, 100));
	m_birdDragParticle->setEndColor(ccc4f(0.0f, 0.0f, 1.0f, 1.0f));

	m_dragParticle2->setStartColor(ccc4f(0.0f, 1.0f, 1.0, 190));
	m_dragParticle2->setEndColor(ccc4f(0.0f, 0.0f, 1.0f, 1.0f));

	m_shipDragParticle = CCParticleSystemQuad::create("shipDragEffect.plist");
	m_shipDragParticle->setPositionType(kCCPositionTypeGrouped);
	m_gameLayer->addChild(m_shipDragParticle, 1);
	m_shipDragParticle->stopSystem();

	this->m_landParticle = CCParticleSystemQuad::create("landEffect.plist");
	m_landParticle->setPositionType(kCCPositionTypeGrouped);
	m_gameLayer->addChild(m_landParticle, 1);
	m_landParticle->stopSystem();
	unk_0x374 = m_landParticle->getAngle();
	/*iVar3 = (**(code **)(*(int *)this->m_landParticle + 0x1f8))();
	*(undefined4 *)&this->field_0x378 = *(undefined4 *)(iVar3 + 4);*/

	this->m_landParticle2 = CCParticleSystemQuad::create("landEffect.plist");
	m_landParticle2->setPositionType(kCCPositionTypeGrouped);
	m_gameLayer->addChild(m_landParticle2, 1);
	m_landParticle2->stopSystem();
#pragma endregion Particles

	setupStreak();

	ccBlendFunc blendFunc = { GL_SRC_ALPHA, GL_ONE };
	unk_0x2e4 = CCSprite::createWithSpriteFrameName(frameFile);
	// unk_0x2e4->setTextureRect
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
		if (m_isPlayLayer) {
			PLAY_LAYER->recordAction(false);
		}
		this->unk_0x30e = false;
		this->unk_0x312 = false;
	}
}

void PlayerObject::lockPlayer()
{
	this->m_isLocked = true;
	this->stopActionByTag(0);
	this->stopActionByTag(1);
	this->releaseButton(PlayerButton::Jump);
	this->deactivateParticle();
	this->m_onGround = false;
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
	if (!this->m_isDead)
	{
		m_lastUpdatePos = this->getPosition();
		if (!this->m_isLocked)
		{
			this->updateJump(dt * 0.9f);
			float addXPos = dt * m_speed * m_timeMod;
			float addYPos = dt * 0.9f * m_yVelocity;
			this->setPosition(this->getPosition() + ccp(addXPos, addYPos));
		}

		if (this->isFlying())
		{
			if (m_flyMode)
			{
				if (m_pShipActive)
				{ // m_pShipLift->stopSystem(); 
				}
				else { // m_pShipLift->resumeSystem(); 
				}
			}

			//if (!m_onGround)
		}
		else {
			if (this->m_pGroundActive == false)
				m_dragParticle->resumeSystem();

			this->m_pGroundActive = true;
			this->stopActionByTag(2);
		}
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
	this->unk_0x30c = true;
	this->deactivateStreak();
	this->removePendingCheckpoint();
	unk_0x318 = 0.0f;
	m_lastGroundPos = CCPointZero;
	m_portalObject = nullptr;
	m_isLocked = false;
	// *(undefined4 *)&this->field_0x340 = 0;
	unk_0x310 = false;
	this->setPosition(PLAY_LAYER->getStartPos());
	// this->flipGravity(false, false);
	toggleFlyMode(false);
	toggleRollMode(false);
	toggleBirdMode(false);
	// togglePlayerScale(false);
	setRotation(0.0f);
	// FIX: this used to unconditionally call setVisible(false) here, which
	// re-hid the player every time resetObject() ran - including right after
	// PlayLayer::startGame() set it visible (startGame calls resetLevel(),
	// which calls this). Nothing else in the current code re-shows the
	// player afterward, so the icon would flash once at load and then stay
	// invisible for the rest of the attempt/level. Visibility is already
	// handled by startGame() and (eventually) the death/respawn flash, so
	// it doesn't belong here.
	m_isDead = false;
	stopActionByTag(3);
	setOpacity(255);

	// resetStreak();
	// levelFlipFinished();
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

void PlayerObject::spawnPortalCircle(ccColor3B color, float size)
{

}

void PlayerObject::setColor(ccColor3B color)
{
	CCSprite::setColor(color);
	m_iconSprite->setColor(color);
	m_vehicleSprite->setColor(color);
}

void PlayerObject::setSecondColor(ccColor3B color)
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

	// FIX: unk_0x2e4 and m_dragParticle are not created until partway
	// through init(). This override can be invoked virtually before
	// then (e.g. init() calls setTextureRect(...) early on, which
	// internally triggers setPosition()). Without these null checks,
	// the first call dereferences uninitialized/garbage pointers and
	// crashes with an access violation (matches the 0xCDCDCDCD debug-heap
	// pattern seen in the crash dump).
	if (unk_0x2e4 != nullptr)
		unk_0x2e4->setPosition(position);

	if (m_dragParticle != nullptr)
		m_dragParticle->setPosition(position);
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
	CCPoint delta = this->getPosition() - m_lastPos;

	float distSq = (delta.x * delta.x) + (delta.y * delta.y);
	if (distSq >= 1.2f)
	{
		double targetAngle = atan2(-delta.y, delta.x);
		float currentRotation = this->getRotation();

		double turnAngle = targetAngle;
		float turnRate;
		if (m_birdMode)
		{
			turnAngle = targetAngle * -0.4;
			turnRate = 0.07f;
			if (turnAngle <= -0.08)
				turnAngle = -0.08;
		}
		else
		{
			turnRate = 0.15f;
		}

		float t = turnRate * dt;
		if (t >= 1.0f)
			t = 1.0f;

		float currentRad = currentRotation * 0.017453f; // degrees -> radians
		float newRad = currentRad + (float)((turnAngle - currentRad) * t); // simple lerp toward target angle (slerp2D approximation)
		this->setRotation(newRad * 57.296f); // radians -> degrees
	}
}

void PlayerObject::updateGlowColor()
{
	ccColor3B iconColor = m_iconSprite->getColor();
	ccColor3B vehicleColor = m_vehicleSprite->getColor();

	bool iconIsBlack = (iconColor.r == 0 && iconColor.g == 0 && iconColor.b == 0);
	bool vehicleIsBlack = (vehicleColor.r == 0 && vehicleColor.g == 0 && vehicleColor.b == 0);

	ccColor3B glow1 = iconIsBlack ? ccc3(255, 255, 255) : iconColor;
	ccColor3B glow2 = vehicleIsBlack ? ccc3(255, 255, 255) : vehicleColor;

	m_glowColor1 = glow1;
	m_glowColor2 = glow2;

	if (m_iconGlow) m_iconGlow->setColor(glow2);
	if (m_vehicleGlow) m_vehicleGlow->setColor(glow2);
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
	// Decompiled (simplified) from PlayerObject::updatePlayerGlow @ 0x18F6E0.
	// The icon glow is shown whenever the icon color is pure black (the
	// "default, needs an outline to read against dark backgrounds" case),
	// and follows the icon sprite's position/scale. The vehicle glow
	// mirrors the vehicle sprite's visibility.
	ccColor3B iconColor = m_iconSprite->getColor();
	bool iconIsBlack = (iconColor.r == 0 && iconColor.g == 0 && iconColor.b == 0);

	m_iconGlow->setScale(m_iconSprite->getScale());
	m_iconGlow->setPosition(m_iconSprite->getPosition());

	m_iconGlow->setVisible(iconIsBlack);

	bool vehicleVisible = m_vehicleSprite->isVisible();
	m_vehicleGlow->setVisible(vehicleVisible);
	m_vehicleGlow->setScale(m_vehicleSprite->getScale());
	m_vehicleGlow->setPosition(m_vehicleSprite->getPosition());
}

void PlayerObject::updatePlayerScale()
{
	this->stopActionByTag(5);
	this->setScale(m_playerScale);

	if (this->isFlying() && m_gravityFlipped)
		this->setScaleY(-m_playerScale);
	else
		this->setScaleY(m_playerScale);
}

void PlayerObject::updatePlayerShipFrame(int sFrame)
{
	int shipIdx = sFrame;
	if (shipIdx >= 14) shipIdx = 14;
	if (shipIdx <= 0) shipIdx = 1;

	const char* frame1 = CCString::createWithFormat("ship_%02d_001.png", shipIdx)->getCString();
	const char* frame2 = CCString::createWithFormat("ship_%02d_2_001.png", shipIdx)->getCString();
	const char* frameGlow = CCString::createWithFormat("ship_%02d_glow_001.png", shipIdx)->getCString();

	CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	m_vehicleSprite->setDisplayFrame(cache->spriteFrameByName(frame1));
	m_vehicleSpriteSecondary->setDisplayFrame(cache->spriteFrameByName(frame2));
	m_vehicleGlow->setDisplayFrame(cache->spriteFrameByName(frameGlow));

	CCSize size = m_vehicleSprite->getContentSize();
	m_vehicleSpriteSecondary->setPosition(ccp(size.width * 0.5f, size.height * 0.5f));
}

void PlayerObject::updatePlayerFrame(int frame)
{
	int playerIdx = frame;
	if (playerIdx >= 38) playerIdx = 38;
	if (playerIdx <= 0) playerIdx = 1;

	const char* frame1 = CCString::createWithFormat("player_%02d_001.png", playerIdx)->getCString();
	const char* frame2 = CCString::createWithFormat("player_%02d_2_001.png", playerIdx)->getCString();
	const char* frameGlow = CCString::createWithFormat("player_%02d_glow_001.png", playerIdx)->getCString();

	CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	m_iconSprite->setDisplayFrame(cache->spriteFrameByName(frame1));
	m_iconSpriteSecondary->setDisplayFrame(cache->spriteFrameByName(frame2));
	m_iconGlow->setDisplayFrame(cache->spriteFrameByName(frameGlow));

	CCSize size = m_iconSprite->getContentSize();
	m_iconSpriteSecondary->setPosition(ccp(size.width * 0.5f, size.height * 0.5f));
}

void PlayerObject::updatePlayerRollFrame(int frame)
{
	int ballIdx = frame;
	if (ballIdx >= 7) ballIdx = 7;
	if (ballIdx <= 0) ballIdx = 0;

	const char* frame1 = CCString::createWithFormat("player_ball_%02d_001.png", ballIdx)->getCString();
	const char* frame2 = CCString::createWithFormat("player_ball_%02d_2_001.png", ballIdx)->getCString();
	const char* frameGlow = CCString::createWithFormat("player_ball_%02d_glow_001.png", ballIdx)->getCString();

	CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	m_iconSprite->setDisplayFrame(cache->spriteFrameByName(frame1));
	m_iconSpriteSecondary->setDisplayFrame(cache->spriteFrameByName(frame2));
	m_iconGlow->setDisplayFrame(cache->spriteFrameByName(frameGlow));

	CCSize size = m_iconSprite->getContentSize();
	m_iconSpriteSecondary->setPosition(ccp(size.width * 0.5f, size.height * 0.5f));
}

void PlayerObject::updatePlayerBirdFrame(int frame)
{
	int birdIdx = frame;
	if (birdIdx >= 7) birdIdx = 7;
	if (birdIdx <= 0) birdIdx = 1;

	const char* frame1 = CCString::createWithFormat("bird_%02d_001.png", birdIdx)->getCString();
	const char* frame2 = CCString::createWithFormat("bird_%02d_2_001.png", birdIdx)->getCString();
	const char* frame3 = CCString::createWithFormat("bird_%02d_3_001.png", birdIdx)->getCString();
	const char* frameGlow = CCString::createWithFormat("bird_%02d_glow_001.png", birdIdx)->getCString();

	CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	m_iconSprite->setDisplayFrame(cache->spriteFrameByName(frame1));
	m_iconSpriteSecondary->setDisplayFrame(cache->spriteFrameByName(frame2));
	m_vehicleSpriteThird->setDisplayFrame(cache->spriteFrameByName(frame3));
	m_iconGlow->setDisplayFrame(cache->spriteFrameByName(frameGlow));

	CCSize size = m_iconSprite->getContentSize();
	m_iconSpriteSecondary->setPosition(ccp(size.width * 0.5f, size.height * 0.5f));
	m_vehicleSpriteThird->setPosition(m_iconSpriteSecondary->getPosition());
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
	if (!this->m_gravityFlipped)
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

	return m_yVelocity < targetVel;
}

bool PlayerObject::isSafeFlip()
{
	if (unk_0x324 == 0.0f)
		return false;

	return -15.0 <= m_yVelocity;
}

void PlayerObject::hitGround(bool notFlipped)
{
	m_yVelocity = 0;

	if ((!m_onGround && !notFlipped) && !levelFlipping()) {

		CCParticleSystemQuad* landParticle;
		if (!field_0x368)
			landParticle = m_landParticle2;
		else
			landParticle = m_landParticle;

		this->field_0x368 = field_0x368 ^ 1;

		// orients and repositions the landing-dust particle so it faces
		// the correct direction when gravity is flipped, then fires it
		// at the player's current ground position.
		landParticle->setAngle(unk_0x374 * flipMod());
		CCPoint posVar = landParticle->getPosVar();
		landParticle->setPosVar(ccp(posVar.x, posVar.y * flipMod()));
		CCPoint particlePos = this->getPosition() + ccp(0.0f, (-15.0f * flipMod()) * m_playerScale);
		landParticle->setPosition(particlePos);

		landParticle->resetSystem();
	}


	m_onGround = true;
	m_canJump = true;
	unk_0x316 = true;

	if ((!m_rollMode) && (getActionByTag(0)))
		this->stopRotation();

	// more stuff
	m_lastGroundPos = this->getPosition();
	if (!isFlying()) {
		this->deactivateStreak();
		// this->tryPlaceCheckpoint();
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

	// currently used as a placeholder since this is a pretty big function
	if (true) {
		if (this->getObjectRect(0.3f, 0.3f).intersectsRect(obj->getObjectRect())) {
			if ((true) && (isSafeFlip())) {
				CCPoint moveToPos;
				if (!m_gravityFlipped) {
					moveToPos = ccp(getPosition().x, getPosition().y - objRect.getMinY());
				}
				else {
					// moveToPos = ccp(getPosition().x, (float)((ulonglong)uVar11 >> 0x20));
				}
				this->setPosition(moveToPos);
				this->hitGround(true);
				m_onGround = false;
			}
			else {
				if (obj->getType() == GameObjectType::unknown22) {
					// obj->destroyObject();
				}
				else {
					if (!PLAY_LAYER->getPlaybackMode()) {
						PLAY_LAYER->destroyPlayer();
					}
				}
			}
		}
	}

}

// this whole project is spaghetti code and educated guesses lol
void PlayerObject::runRotateAction()
{
	if (m_isLocked)
		return;

	this->stopRotation();

	if (!m_rollMode) {
		this->runNormalRotation();
		return;
	}

	this->runBallRotation();
}

void PlayerObject::runNormalRotation()
{
	if (isFlying()) {
		return;
	}

	float rotateValue;
	if (m_playerScale == 1.0)
		rotateValue = 0.43333334f;
	else
		rotateValue = 0.33333334f;

	CCRotateBy* rotateAction = CCRotateBy::create(rotateValue, (180 * flipMod()));
	rotateAction->setTag(0);
	this->runAction(rotateAction);
	return;
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

		if (!m_flyMode)
			this->resetPlayerIcon();
		else {
			this->updatePlayerShipFrame(GameManager::sharedState()->getPlayerShip());
			m_iconSprite->setScale(0.55f);
			m_iconSprite->setPosition(ccp(0.0f, 5.0f));

			m_vehicleSprite->setVisible(true);
			m_vehicleSprite->setPosition(ccp(0.0f, -5.0f));
			this->updatePlayerGlow();

			m_birdDragParticle->resetSystem();
			m_dragParticle2->resetSystem();
			m_dragParticle2->stopSystem();

			this->m_pShipActive = false;
			this->deactivateParticle();
			this->spawnPortalCircle(ccc3(255, 0, 255), 50.0f);
			this->activateStreak();
			this->updatePlayerScale();
		}
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

		if (m_rollMode) {
			int ballFrame = (m_playerScale == 1.0f) ? GameManager::sharedState()->getPlayerBall() : 0;
			this->updatePlayerRollFrame(ballFrame);
			this->spawnPortalCircle(ccc3(0xFF, 0x32, 0xFF), 50.0f);
		}
		else {
			if (!unk_0x30c)
				this->spawnPortalCircle(ccc3(0xFF, 0x9F, 0x63), 100.0f);

			int cubeFrame = (m_playerScale == 1.0f) ? GameManager::sharedState()->getPlayerFrame() : 0;
			this->updatePlayerFrame(cubeFrame);
		}

		this->stopRotation();
	}
}

void PlayerObject::toggleBirdMode(bool enable)
{
	if (m_birdMode != enable) {
		m_birdMode = enable;

		if (enable) {
			this->toggleRollMode(false);
			this->toggleFlyMode(false);
		}

		this->stopRotation();
		m_yVelocity = m_yVelocity * 0.5;
		setRotation(0.0f);
		m_onGround = false;
		unk_0x30f = false;
		unk_0x312 = false;
		this->removePendingCheckpoint();

		if (m_birdMode) {
			this->updatePlayerBirdFrame(GameManager::sharedState()->getPlayerBird());

			m_iconSprite->setScale(0.55f);
			m_iconSprite->setPosition(ccp(0.0f, 5.0f));
			m_vehicleSpriteThird->setVisible(true);
			m_vehicleSpriteThird->setPosition(ccp(0.0f, -7.0f));

			this->updatePlayerGlow();

			m_birdDragParticle->resetSystem();
			this->deactivateParticle();
			this->spawnPortalCircle(ccc3(0xFF, 0xC8, 0xC8), 200.0f);
			this->activateStreak();
			this->updatePlayerScale();
			m_vehicleSprite->setVisible(true);
		}
		else {
			this->resetPlayerIcon();
		}
	}
}

void PlayerObject::toggleGhostEffect(GhostType type)
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

void PlayerObject::removePendingCheckpoint()
{

}

void PlayerObject::setupStreak()
{

}