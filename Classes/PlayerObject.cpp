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

	m_iconSprite = CCSprite::createWithSpriteFrameName(frameFile);
	this->addChild(m_iconSprite, 1);
	m_iconSpriteSecondary = CCSprite::createWithSpriteFrameName(frameFile2);
	m_iconSprite->addChild(m_iconSpriteSecondary);
	m_iconSpriteSecondary->setPosition(m_iconSprite->getContentSize() / 2);

	this->m_isJumping = false;
	this->field736_0x328 = 0; // possibly yvelocity
	//this->field737_0x32c = 0;
	//this->field709_0x30d = false;
	this->m_onGround = false;
	this->m_isDead = false;
	this->m_playerScale = 1.0;
	// this->updateTimeMod(fVar17);
	//this->field758_0x344 = 0;

	this->m_pGround = CCParticleSystemQuad::create("dragEffect.plist");
	m_pGround->setPositionType(tCCPositionType::kCCPositionTypeFree);
	m_gameLayer->addChild(m_pGround, -1);
	m_pGround->stopSystem();
	this->m_pGroundActive = false;


	field695_0x2e4 = CCSprite::createWithSpriteFrameName(frameFile);
	// field695_0x2e4->setTextureRect
	field695_0x2e4->setBlendFunc({ GL_SRC_ALPHA, GL_ONE });

	if (!m_isPlayLayer) 
		m_gameLayer->addChild(field695_0x2e4);
	else
		PLAY_LAYER->getBatchNodeAdd()->addChild(field695_0x2e4, 20);

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
		if (!this->m_isLocked)
		{
			float x = dt * 5.77f * m_timeMod;
			this->setPosition({ this->getPosition() + ccp(x, 0.0f)});
			//CCLOG("%f", this->getPosition().x);
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

void PlayerObject::setPosition(CCPoint const &position) {
	GameObject::setPosition(position);
	field695_0x2e4->setPosition(position);


	m_pGround->setPosition(position);
	//CCLOG("x: %f, y: %f", m_pGround->getPosition().x, m_pGround->getPosition().y);

}

void PlayerObject::updateShipRotation(float dt)
{

}