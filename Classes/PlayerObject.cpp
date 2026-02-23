#include "PlayerObject.h"
#include "GameManager.h"
USING_NS_CC;

PlayerObject::PlayerObject()
{
	this->m_flyMode = false;
	this->m_birdMode = false;
	this->m_rollMode = false;
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

#pragma region Icon Frames
	m_iconSprite = CCSprite::createWithSpriteFrameName(frameFile);
	this->addChild(m_iconSprite, 1);
	m_iconSpriteSecondary = CCSprite::createWithSpriteFrameName(frameFile2);
	m_iconSprite->addChild(m_iconSpriteSecondary);
	m_iconSpriteSecondary->setPosition(m_iconSprite->getContentSize() / 2);
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

#pragma region Ground Particles
	this->m_pGround = CCParticleSystemQuad::create("dragEffect.plist");
	m_pGround->setPositionType(tCCPositionType::kCCPositionTypeFree);
	m_gameLayer->addChild(m_pGround, -1);
	m_pGround->stopSystem();
	this->m_pGroundActive = false;
#pragma endregion Ground Particles

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
	// idk
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
		if (!this->m_isJumping)
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

}

void PlayerObject::updateTimeMod(float timeMod)
{
	// add other code
	this->m_timeMod = timeMod;
	if (timeMod == 0.9) {
		//this->m_yStart = 0x20000000;
		//this->field704_0x2fc = 0x40265c2d;
		//this->m_gravity = 0;
		//this->field706_0x304 = 0x3feea991;
	}
	this->m_speed = 5.77;
	// add other code
}