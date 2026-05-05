#include "PlayerObject.h"
#include "GameManager.h"
#include "PlayLayer.h"
USING_NS_CC;

// hi there, 
// this and PlayLayer are halfway there, with just hitboxes and other gamemodes being the main issues.
// hopefully they'll be done next month

PlayerObject::PlayerObject()
{
	this->m_flyMode = false;
	this->m_birdMode = false;
	this->m_rollMode = false;

	this->m_isLocked = false;

	this->m_gravityFlipped = false;

	this->field772_0x30d = false;
	this->field773_0x30e = false;

	this->field747_0x324 = 0.0f;
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

	m_vehicleSprite = CCSprite::createWithSpriteFrameName(frameFile);
	this->addChild(m_vehicleSprite, 2);
	m_vehicleSprite->setVisible(false);

	this->m_isJumping = false;
	this->m_yVelocity = 0;
	//this->field737_0x32c = 0;
	this->field772_0x30d = false;
	this->m_onGround = false;
	this->m_isDead = false;
	this->m_playerScale = 1.0;
	this->updateTimeMod(0.9f);
	//this->field758_0x344 = 0;

#pragma region Particles
	this->m_pGround = CCParticleSystemQuad::create("dragEffect.plist");
	m_pGround->setPositionType(tCCPositionType::kCCPositionTypeFree);
	m_gameLayer->addChild(m_pGround, -1);
	m_pGround->stopSystem();
	this->m_pGroundActive = false;

	this->m_pBurstEffect = CCParticleSystemQuad::create("burstEffect.plist");
	m_pBurstEffect->setPositionType(tCCPositionType::kCCPositionTypeFree);
	m_gameLayer->addChild(m_pBurstEffect, -1);
	m_pBurstEffect->stopSystem();
#pragma endregion Particles

	/*field695_0x2e4 = CCSprite::createWithSpriteFrameName(frameFile);
	// field695_0x2e4->setTextureRect
	field695_0x2e4->setBlendFunc({ GL_SRC_ALPHA, GL_ONE });

	if (!m_isPlayLayer) 
		m_gameLayer->addChild(field695_0x2e4);
	else
		PLAY_LAYER->getBatchNodeAdd()->addChild(field695_0x2e4, 20);*/

    return true;
}

void PlayerObject::releaseButton(PlayerButton button)
{
	if (button == PlayerButton::Jump) {
		if (m_isPlayLayer != false) {
			PLAY_LAYER->recordAction(false);
		}
		this->field773_0x30e = false;
		this->field729_0x312 = false;
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
	if (this->m_flyMode == false) {
		return this->m_birdMode;
	}
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
				m_pGround->resumeSystem();

			this->m_pGroundActive = true;
			this->stopActionByTag(2);
		}
	}
}

void PlayerObject::deactivateParticle()
{
	if (this->m_pGroundActive != false)
		m_pGround->stopSystem();

	this->m_pGroundActive = false;
}

void PlayerObject::deactivateStreak()
{
	// m_playerStreak->stopStroke();
}

void PlayerObject::resetObject()
{
	/*this->field708_0x30c = true;
	this->deactivateStreak();
	this->removePendingCheckpoint();
	*(undefined4 *)&this->field_0x318 = 0;
	cocos2d::CCPoint::operator=(&this[1].m_lastGroundPos,(CCPoint *)&DAT_004c6e48);
	iVar5 = *(int *)this;*/
	m_portalObject = nullptr;
	m_isLocked = false;
	// *(undefined4 *)&this->field_0x340 = 0;
	// this->field_0x310 = 0;
	this->setPosition(PLAY_LAYER->getStartPos());
	/*this->flipGravity(false, false);
	this->toggleFlyMode(false);
	this->toggleRollMode(false);
	this->toggleBirdMode(false);
	this->togglePlayerScale(false);*/
	this->setRotation(0.0f);
	this->m_isDead = false;
	this->stopActionByTag(3);
	this->setOpacity(255);
}

void PlayerObject::pushButton(PlayerButton button)
{
	if ((m_isLocked == false) && (button == PlayerButton::Jump)) {
		if (m_isPlayLayer != false) {
			PLAY_LAYER->recordAction(true);
		}

		this->field773_0x30e = true;
		this->field729_0x312 = true;
		if (m_rollMode == false) {
			if (m_touchedRing != nullptr) {
				//this->ringJump();
				return;
			}
			if (isFlying()) {
				return;
			}

			if (field773_0x30e == false) {
				return;
			}
		}
		else if (m_touchedRing != nullptr) {
			//this->ringJump();
			return;
		}

		if (field772_0x30d != false) {
			this->updateJump(0.0f);
			return;
		}
	}
}

void PlayerObject::playerDestroyed()
{
	/*if (this->field720_0x318 != 0.0) {
		PLAY_LAYER->removeLastCheckpoint();
		this->field720_0x318 = 0.0;
	}*/

	this->m_isDead = true;
	// this->stopRotation();
	this->deactivateParticle();
	// this->touchedObject(this);
}

void PlayerObject::playBurstEffect()
{
	if (!levelFlipping()) {
		m_pBurstEffect->resumeSystem();
		this->stopActionByTag(6);
		// *(undefined4 *)(pCVar4 + 0x20) = 6;
		runAction(CCSequence::create(CCDelayTime::create(0.12f),
			CCCallFunc::create(this, callfunc_selector(PlayerObject::stopBurstEffect)),
			nullptr));
	}
}

void PlayerObject::stopBurstEffect()
{
	m_pBurstEffect->stopSystem();
}

void PlayerObject::setColor(cocos2d::ccColor3B color)
{
	CCSprite::setColor(color);
	m_iconSprite->setColor(color);
	m_vehicleSprite->setColor(color);
}

void PlayerObject::setSecondColor(cocos2d::ccColor3B color)
{
	m_iconSpriteSecondary->setColor(color);
	//m_vehicleSpriteSecondary->setColor(color);
}

void PlayerObject::setPosition(CCPoint const &position) {
	GameObject::setPosition(position);
	//field695_0x2e4->setPosition(position);


	m_pGround->setPosition(position);
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

		if ((field773_0x30e) && (field772_0x30d)) {
			this->m_isJumping = true;
			this->m_onGround = false;
			this->field772_0x30d = false;
			this->field729_0x312 = false;

			this->m_yVelocity = m_yStart * flipMod() * pScale;
			this->incrementJumps();
			if (this->m_rollMode != false) {
				/*flipGravity(this, (bool)(this->m_gravityFlipped ^ 1), true);
				dVar11 = (double)__muldf3(*(undefined4 *)pdVar8, *(undefined4 *)((int)&this->m_yVelocity + 4)
					, 0x40000000, 0x3fe33333);
				*pdVar8 = dVar11;
				this->field_0x316 = 0;
				this->field765_0x30e = false;*/
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
			// this->field_0x30f = true;
			this->m_onGround = false;
			return;
		}

		if (playerIsFalling()) {
			field772_0x30d = false;
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
	if ((this->field771_0x30c == false) && (m_timeMod != timeMod))
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
	if (this->m_isPlayLayer != false) {
		// PLAY_LAYER->incrementJumps();
		this->m_hasJumped = true;
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
	// if (field747_0x324 == 0.0f)
		// return false;

	return -15.0 <= m_yVelocity;
}

void PlayerObject::hitGround(bool notFlipped)
{
	m_yVelocity = 0;
	// stuff
	m_onGround = true;
	field772_0x30d = true;
	field733_0x316 = true;

	if ((!m_rollMode) && (getActionByTag(0)))
		this->stopRotation();

	// more stuff
	m_lastGroundPos = this->getPosition();
	if (!isFlying()) {
		this->deactivateStreak();
		// this->tryPlaceCheckpoint();
	}
	field727_0x310 = false;
}

void PlayerObject::collidedWithObject(float dt, GameObject* obj)
{
	CCRect playerRect = this->getObjectRect();
	CCRect objRect = obj->getObjectRect();

	// currently used as a placeholder since this is a pretty big function
	if (true) {
		// if (this->getObjectRect(0.3f, 0.3f).intersectsRect(obj->getObjectRect())) {
		if (true) {
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
		field772_0x30d = false;
		field727_0x310 = false;
		// this->removePendingCheckpoint();

		// if (!m_flyMode)
			// this->resetPlayerIcon();
		}
	else {
		// this->updatePlayerShipFrame(GameManager::sharedState()->getPlayerShip());
		m_iconSprite->setScale(0.55f);
		m_iconSprite->setPosition(ccp(0.0f, 5.0f));

		m_vehicleSprite->setVisible(true);
		m_vehicleSprite->setPosition(ccp(0.0f, -5.0f));
		this->updatePlayerGlow();

		// m_birdDragParticle->resetSystem();
		// m_dragParticle2->resetSystem();
		// m_dragParticle2->stopSystem();
		
		// this->field732_0x315 = false;
		this->deactivateParticle();
		// this->spawnPortalCircle(ccc3(255, 0, 255), 50.0f);
		// this->activateStreak();
		// this->updatePlayerScale();
	}
}

void PlayerObject::toggleRollMode(bool enable)
{

}

void PlayerObject::toggleBirdMode(bool enable)
{

}