#ifndef __RINGOBJECT_H__
#define __RINGOBJECT_H__

#include "cocos2d.h"
#include "GameObject.h"

class RingObject : public GameObject {
public:
	RingObject();
	virtual ~RingObject();

	static RingObject* create(const char* spriteName);

	virtual bool init(const char* spriteName);
	virtual void setScale(float scale) override;
	virtual void setVisible(bool visible) override;
	virtual void setPosition(const cocos2d::CCPoint& pos) override;

	virtual void triggerActivated();
	virtual void powerOffObject();
	virtual void resetObject();
	virtual void spawnCircle();
	virtual void powerOnObject();
	virtual void updateColors();

	CC_SYNTHESIZE(bool, m_isActivated, IsActivated);
	CC_SYNTHESIZE(bool, m_isPoweredOn, IsPoweredOn);
	CC_SYNTHESIZE(bool, m_unknownFlag, UnknownFlag);
};

#endif

// just finished header
// will be decompiled later