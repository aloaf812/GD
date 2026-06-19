#ifndef _GJ_COMMENT_H_
#define _GJ_COMMENT_H_

#include "cocos2d.h"

class GJComment : public cocos2d::CCNode {
public:
	CC_SYNTHESIZE(std::string, m_comment, Comment); // 0xe8
	CC_SYNTHESIZE(std::string, m_userName, UserName); // 0xec
	CC_SYNTHESIZE(long, m_commentID, CommentID); // 0xf0
	CC_SYNTHESIZE(int, m_userID, UserID); // 0xf4
	CC_SYNTHESIZE(int, m_likes, Likes); // 0xf8
	CC_SYNTHESIZE(int, m_dislikes, Dislikes); // 0xfc
	CC_SYNTHESIZE(int, m_levelID, LevelID); // 0x100
	CC_SYNTHESIZE(bool, m_isHidden, IsHidden); // 0x104
};

#endif