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
	this->addChild(m_iconSprite, 1);
	m_iconSpriteSecondary = CCSprite::createWithSpriteFrameName(frameFile2);
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
	m_shipDragParticle	->setPositionType(kCCPositionTypeGrouped);
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
	m_birdDragParticle->setStartColor(ccc4f(0.0f, 1.0f, 1.0f, 1/2.55));
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

void PlayerObject::updatePlayerShipFrame(int sFrame)
{

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

void PlayerObject::levelFlipFinished()
{

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
		/*fVar6 = this->field793_0x374;
		pcVar4 = *(code **)(*(int *)landParticle + 0x1ec);
		iVar2 = flipMod(this);
		(*pcVar4)(this_00, fVar6 * (float)(longlong)iVar2);
		pcVar4 = *(code **)(*(int *)landParticle + 0x1fc);
		(**(code **)(*(int *)this->m_landParticle + 0x1f8))();
		uVar5 = flipMod(this);
		cocos2d::CCPoint::CCPoint(aCStack_38, (float)uVar5, (float)((ulonglong)uVar5 >> 0x20));
		(*pcVar4)(this_00, aCStack_38);
		pcVar4 = *(code **)(*(int *)landParticle + 0x5c);
		pCVar3 = (CCPoint *)(**(code **)(*(int *)this + 0x60))(this);
		uVar5 = flipMod(this);
		cocos2d::CCPoint::CCPoint(aCStack_30, (float)uVar5, (float)((ulonglong)uVar5 >> 0x20));
		cocos2d::CCPoint::operator+(aCStack_28, pCVar3);
		(*pcVar4)(this_00, aCStack_28);*/
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

	float objMaxY = objRect.getMaxY();
	float objMinY = objRect.getMinY();

	// currently used as a placeholder since this is a pretty big function
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

}

void PlayerObject::toggleBirdMode(bool enable)
{

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

void PlayerObject::removePendingCheckpoint()
{

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