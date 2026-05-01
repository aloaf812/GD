#include "EndPortalObject.h"
USING_NS_CC;

bool EndPortalObject::init() {
	if (!GameObject::init("edit_eLevelEndBtn_001.png"))
		return false;

	// this->setTextureRect(&DAT_004c714c);
	CCDirector* pDirector = CCDirector::sharedDirector();
	CCSize winSize = pDirector->getWinSize();
	
	// unfinished

	return true;
}