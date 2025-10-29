#include "GJGroundLayer.h"
#include "GameManager.h"
USING_NS_CC;

GJGroundLayer::GJGroundLayer()
{
	this->m_groundWidth = 0.0;
	this->m_groundSprite = NULL;
	this->m_line = NULL;
	this->m_isActive = false;
}

GJGroundLayer* GJGroundLayer::create(int gID)
{
    GJGroundLayer* ret = new GJGroundLayer();
    if (ret) {
        if (ret->init(gID)) {
            ret->autorelease();
            return ret;
        }

        delete ret;
    }

    return NULL;
}

bool GJGroundLayer::init(int gID)
{
	if (!CCLayer::init())
    	return false;

    CCDirector* pDirector = CCDirector::sharedDirector();
    GameManager* pGameManager = GameManager::sharedState();

   	this->m_groundSprite = CCSprite::create(pGameManager->getGTexture(gID));

   	ccColor3B gColor = { 0, 102, 255 };
   	this->m_groundSprite->setColor(gColor);


    return true;
}

void GJGroundLayer::fadeInGround(float duration)
{

}

void GJGroundLayer::fadeInFinished()
{
	this->m_isActive = true;
}

void GJGroundLayer::fadeOutGround(float duration)
{

}


void GJGroundLayer::draw()
{

}

CCSprite* GJGroundLayer::getGroundSprite() const
{
	return this->m_groundSprite;
}

CCSprite* GJGroundLayer::getLine() const
{
	return this->m_line;
}

float GJGroundLayer::getGroundWidth() const
{
	return this->m_groundWidth;
}

bool GJGroundLayer::getIsActive() const
{
	return this->m_isActive;
}
