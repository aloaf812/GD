#include "SongObject.h"

SongObject* SongObject::create(int track)
{
	SongObject *pRet = new SongObject();
	if (pRet && pRet->init(track))
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

bool SongObject::init(int track)
{
	m_audioTrack = track;
	return true;
}