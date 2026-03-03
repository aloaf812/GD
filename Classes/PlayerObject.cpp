#include "PlayerObject.h"
#include "GameManager.h"
#include "PlayLayer.h"
USING_NS_CC;

// hi there, 
// this and PlayLayer are both incredibly incomplete and i do not recommend using them as a reference for physics just yet
// give it like a week or 2 and the physics will be ready trust

PlayerObject::PlayerObject()
{
	this->m_flyMode = false;
	this->m_birdMode = false;
	this->m_rollMode = false;

	this->m_isLocked = false;

	this->m_gravityFlipped = false;

	this->field772_0x30d = false;
	this->field773_0x30e = false;
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
    
    if (player >= 38) playerIdx = 38;
    else playerIdx = player;
    if (player <=0) playerIdx = 1;
    
    if (ship >= 14) shipIdx = 14;
    else shipIdx = ship;
    if (ship <=0) shipIdx = 1;
    
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

	this->m_isJumping = false;
	this->field736_0x328 = 0; // possibly yvelocity
	//this->field737_0x32c = 0;
	//this->field709_0x30d = false;
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
	// THIS IS NOT HOW IT ACTUALLY WORKS
	// just some "swizzle magic"

	this->field772_0x30d = false;
	this->field773_0x30e = false;


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
			float addYPos = dt * 0.9f * field736_0x328;
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
	// unfinished...

	this->field772_0x30d = true;
	this->field773_0x30e = true;
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
	//m_vehicleSprite->setColor(color);
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
	if ((this->m_rollMode != false) || (isFlying())) {
		gravity2 = 0.958199;
	}
	else {
		gravity2 = gravity;
	}
	//fVar7 = 0.8f;
	float fVar7;
	bool isPlayerBig = this->m_playerScale == 1.0;
	if (isPlayerBig) {
		fVar7 = 1.0f;
	}
	if (!isPlayerBig) {
		fVar7 = 0.8f;
	}
	if (isFlying()) {
		/*if (this->m_playerScale != 1.0) {
		fVar7 = 0.85;
		}
		if (this->m_flyMode == false) {
		if ((this->field777_0x312 != false) && (this->field773_0x30e != false)) {
		this->field777_0x312 = false;
		fVar5 = 8.0;
		if (this->m_playerScale == 1.0) {
		fVar5 = 7.0;
		}
		iVar3 = flipMod(this);
		*(double *)&this->field_0x328 = (double)(fVar5 * (float)(longlong)iVar3 * fVar7);
		playBurstEffect(this);
		}
		iVar3 = playerIsFalling(this);
		dVar6 = *(double *)&this->field_0x328;
		fVar5 = 1.2;
		if (iVar3 != 0) {
		fVar5 = 0.8;
		}
		iVar3 = flipMod(this);
		fVar5 = fVar8 * in_r1 * (float)(longlong)iVar3 * fVar5 * 0.5;
		}
		else {
		if (this->field773_0x30e == false) {
		iVar3 = playerIsFalling(this);
		fVar9 = 0.8;
		if (iVar3 == 0) {
		fVar9 = 1.2;
		}
		}
		else {
		fVar9 = -1.0;
		}
		if ((this->field773_0x30e == false) || (iVar3 = playerIsFalling(this), iVar3 == 0)) {
		fVar5 = 0.4;
		}
		else {
		fVar5 = 0.5;
		}
		dVar6 = *(double *)&this->field_0x328;
		iVar3 = flipMod(this);
		fVar5 = fVar8 * in_r1 * (float)(longlong)iVar3 * fVar9 * fVar5;
		}
		dVar6 = dVar6 - (double)(fVar5 / fVar7);
		*(double *)&this->field_0x328 = dVar6;
		if (this->m_gravityFlipped == false) {
		if ((int)((uint)(dVar6 < (double)(-6.4 / fVar7)) << 0x1f) < 0) {
		dVar6 = (double)(-6.4 / fVar7);
		}
		fVar8 = 8.0;
		}
		else {
		if ((int)((uint)(dVar6 < (double)(-8.0 / fVar7)) << 0x1f) < 0) {
		dVar6 = (double)(-8.0 / fVar7);
		}
		fVar8 = 6.4;
		}
		cVar3 = this->field773_0x30e;
		if ((double)(fVar8 / fVar7) < dVar6) {
		dVar6 = (double)(fVar8 / fVar7);
		}
		*(double *)&this->field_0x328 = dVar6;*/
	}
	else {
		float fVar5 = 0.6f;
		if (this->m_rollMode == false) {
			fVar5 = 1.0f;
		}
		if ((this->field773_0x30e != false) && (this->field772_0x30d != false)) {
			this->m_onGround = false;
			// this->field772_0x30d = false;
			// this->field777_0x312 = false;
			this->m_isJumping = true;
			// this->field775_0x310 = true;
			this->field736_0x328 = m_yStart * flipMod() * fVar7;
			//uVar4 = FUN_0019d1c8();
			//*(undefined4 *)&this->field_0x320 = uVar4;
			//this->incrementJumps();
			if (m_rollMode != false) {
				/*flipGravity(this,(bool)(this->m_gravityFlipped ^ 1),true);
				this->field781_0x316 = false;
				this->field773_0x30e = false;
				*(double *)&this->field_0x328 = *(double *)&this->field_0x328 * 0.6000000238418579;
				return;*/
			}
			this->runRotateAction();
			return;
		}
		/*if (this->m_isJumping != false) {
		dVar6 = *(double *)&this->field_0x328;
		iVar3 = flipMod(this);
		*(double *)&this->field_0x328 =
		dVar6 - (double)(fVar8 * in_r1 * (float)(longlong)iVar3 * fVar5);
		iVar3 = playerIsFalling(this);
		if (iVar3 == 0) {
		return;
		}
		this->m_isJumping = false;
		this->field774_0x30f = true;
		goto LAB_0019f658;
		}
		iVar3 = playerIsFalling(this);
		if (iVar3 != 0) {
		this->field772_0x30d = false;
		}
		dVar6 = *(double *)&this->field_0x328;
		iVar3 = flipMod(this);
		dVar6 = dVar6 - (double)(fVar8 * in_r1 * (float)(longlong)iVar3 * fVar5);
		*(double *)&this->field_0x328 = dVar6;
		if (this->m_gravityFlipped == false) {
		if ((int)((uint)(dVar6 < -15.0) << 0x1f) < 0) {
		dVar6 = -15.0;
		}
		}
		else if (15.0 < dVar6) {
		dVar6 = 15.0;
		}
		*(double *)&this->field_0x328 = dVar6;
		iVar3 = playerIsFalling(this);
		if (iVar3 == 0) {
		return;
		}
		if ((this->m_rollMode == false) &&
		(iVar2 = (CCAction *)cocos2d::CCNode::getActionByTag((CCNode *)this,0),
		iVar2 == (CCAction *)0x0)) {
		runRotateAction(this);
		}
		if (this->m_gravityFlipped == false) {
		cVar3 = (int)((uint)(*(double *)&this->field_0x328 < -4.0) << 0x1f) < 0;
		}
		else {
		cVar3 = 4.0 < *(double *)&this->field_0x328;
		}*/
	}
}

void PlayerObject::updateTimeMod(float timeMod)
{
	// add other code
	this->m_timeMod = timeMod;
	if (timeMod == 0.9f) {
		this->m_yStart = 11.18;
		//this->field704_0x2fc = 0x40265c2d;
		this->m_gravity = 0.958199;
		//this->field706_0x304 = 0x3feea991;
	}
	this->m_speed = 5.77;
	// add other code
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
	if (this->m_gravityFlipped == false) {
		return 1.0f;
	}
	else {
		return -1.0f;
	}
}

void PlayerObject::runRotateAction()
{
	if (this->m_isLocked != false) {
		return;
	}
	// this->stopRotation();
	if (!m_rollMode) {
		this->runNormalRotation();
		return;
	}
	// this->runBallRotation();
	return;
}

void PlayerObject::runNormalRotation()
{
	if (isFlying()) {
		return;
	}

	float rotateValue;
	if (m_playerScale == 1.0)
		rotateValue = 0.43333334;
	else
		rotateValue = 0.33333334;

	CCRotateBy* rotateAction = CCRotateBy::create(rotateValue, (180 * flipMod()));
	// *((_DWORD *)v6 + 8) = 0;
	this->runAction(rotateAction);
	return;
}