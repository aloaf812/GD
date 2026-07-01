#include "SongsLayer.h"
#include "SongObject.h"
USING_NS_CC;
	
SongsLayer* SongsLayer::create()
{
	SongsLayer *pRet = new SongsLayer();
	if (pRet && pRet->init("Soundtracks"))
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

void SongsLayer::customSetup()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	CCArray* songArray = CCArray::create();
	int i = 0;
	do {
		songArray->addObject(SongObject::create(i++));
	} while (i != 15);

	songArray->addObject(SongObject::create(-1));
	// CustomListView and its parent classes are unimplemented
	// CustomListView* listView = CustomListView::create(this_00, 220, 356, 0, 9);
	// m_listLayer->addChild(listView, 6);
}