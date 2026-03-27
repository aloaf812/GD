#include "ColorAction.h"
USING_NS_CC;

ColorAction* ColorAction::create(ccColor3B fromColor, ccColor3B toColor, float duration, double timeStamp)
{
	ColorAction* pRet = new ColorAction();
	if (pRet && pRet->init(fromColor, toColor, duration, timeStamp))
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


bool ColorAction::init(ccColor3B fromColor, ccColor3B toColor, float duration, double timeStamp)
{
	m_fromColor = fromColor;
	m_toColor = toColor;
	m_duration = duration;
	m_timeStamp = timeStamp;
	return true;
}