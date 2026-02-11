#ifndef _GJ_SEARCHOBJECT_H
#define _GJ_SEARCHOBJECT_H

#include "cocos2d.h"
#include <stdio.h>

enum class SearchType {
	MyLevels = 98
};


class GJSearchObject : public cocos2d::CCNode {
public:
	static GJSearchObject* create(SearchType type);
	static GJSearchObject* create(SearchType type, std::string, std::string, std::string, int, bool, bool, bool, int);
	bool init(SearchType* editorLayer);

	CC_SYNTHESIZE(SearchType, m_type, Type);


	CC_SYNTHESIZE(int, m_page, Page);
	CC_SYNTHESIZE(bool, m_star, Star);
	CC_SYNTHESIZE(bool, m_uncompleted, Uncompleted);
	CC_SYNTHESIZE(bool, m_featured, Featured);
	CC_SYNTHESIZE(int, m_song, Song);

};

#endif