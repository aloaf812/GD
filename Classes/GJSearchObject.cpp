#include "GJSearchObject.h"
USING_NS_CC;

GJSearchObject* GJSearchObject::create(SearchType type)
{
	return GJSearchObject::create(type, "", "", "", 0, false, false, false, 0);
}


GJSearchObject* GJSearchObject::create(SearchType type, std::string string, std::string difficultyStr, std::string lengthStr, int page, bool star, bool uncompleted, bool featured, int song)
{
	GJSearchObject* pRet = new GJSearchObject();
	if (pRet && pRet->init(type, string, difficultyStr, lengthStr, page, star, uncompleted, featured, song))
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

bool GJSearchObject::init(SearchType type, std::string string, std::string difficultyStr, std::string lengthStr, int page, bool star, bool uncompleted, bool featured, int song)
{
	m_type = type;
	m_string = string;
	m_difficultyStr = difficultyStr;
	m_lengthStr = lengthStr;
	m_page = page;
	m_star = star;
	m_uncompleted = uncompleted;
	m_featured = featured;
	m_song = song;
	return true;
}