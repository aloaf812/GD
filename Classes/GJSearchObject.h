#ifndef _GJ_SEARCHOBJECT_H
#define _GJ_SEARCHOBJECT_H

#include "cocos2d.h"
#include <stdio.h>

// https://github.com/geode-sdk/bindings/blob/main/bindings/include/Geode/Enums.hpp#L10
enum class SearchType {
	Featured = 6,
	MyLevels = 98
};


class GJSearchObject : public cocos2d::CCNode {
public:
	static GJSearchObject* create(SearchType type);
	static GJSearchObject* create(SearchType type, std::string string, std::string difficultyStr, std::string lengthStr, int page, bool star, bool uncompleted, bool featured, int song);
	bool init(SearchType type, std::string string, std::string difficultyStr, std::string lengthStr, int page, bool star, bool uncompleted, bool featured, int song);

	CC_SYNTHESIZE(SearchType, m_type, Type); // 0xe8
	CC_SYNTHESIZE(std::string, m_string, String); // 0xec
	CC_SYNTHESIZE(std::string, m_difficultyStr, DifficultyStr); // 0xf0
	CC_SYNTHESIZE(std::string, m_lengthStr, LengthStr); // 0xf4
	CC_SYNTHESIZE(int, m_page, Page); // 0xf8
	CC_SYNTHESIZE(bool, m_star, Star); // 0xfc
	CC_SYNTHESIZE(int, m_total, Total); // 0x100
	CC_SYNTHESIZE(bool, m_uncompleted, Uncompleted); // 0x104
	CC_SYNTHESIZE(bool, m_featured, Featured); // 0x105
	CC_SYNTHESIZE(int, m_song, Song); // 0x108

};

#endif