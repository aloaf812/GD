#ifndef __GeometryDash__ObjectToolbox__
#define __GeometryDash__ObjectToolbox__

#include "cocos2d.h"

class ObjectToolbox : public cocos2d::CCNode {
public:
	static ObjectToolbox* sharedState();
	virtual bool init();
    static cocos2d::CCDictionary* stringSetupToDict(std::string str);

	char const* keyToFrame(char const* key);

	cocos2d::CCDictionary* m_objects;
	cocos2d::CCDictionary* m_keys;
};

#endif /* defined(__GeometryDash__ObjectToolbox__) */
