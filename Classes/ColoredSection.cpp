#include "ColoredSection.h"
USING_NS_CC;

ColoredSection* ColoredSection::create(ccColor3B col, int startPos, int endPos)
{
	ColoredSection* pRet = new ColoredSection();
	if (pRet && pRet->init(col, startPos, endPos))
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


bool ColoredSection::init(ccColor3B col, int startPos, int endPos)
{
	m_col = col;
	m_startPos = startPos;
	m_endPos = endPos;
	return true;
}