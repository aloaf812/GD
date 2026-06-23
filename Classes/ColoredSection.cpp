#include "ColoredSection.h"

USING_NS_CC;

ColoredSection* ColoredSection::create(cocos2d::ccColor3B col, int startPos, int endPos)
{
	ColoredSection* pRet = new ColoredSection();
	if (pRet && pRet->init(col, startPos, endPos))
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool ColoredSection::init(cocos2d::ccColor3B col, int startPos, int endPos)
{
	m_col = col;
	m_startPos = static_cast<float>(startPos);
	m_endPos = endPos;
	return true;
}

int ColoredSection::getStartIndex()
{
	return static_cast<int>(m_startPos);
}

void ColoredSection::setStartIndex(int index)
{
	m_startPos = static_cast<float>(index);
}

int ColoredSection::getEndIndex()
{
	return m_endPos;
}

cocos2d::ccColor3B ColoredSection::getColor()
{
	return m_col;
}