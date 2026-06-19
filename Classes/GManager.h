#ifndef __GeometryDash__GManager__
#define __GeometryDash__GManager__

#include "cocos2d.h"

class GManager : public cocos2d::CCNode {
public:
    virtual bool init();
    virtual void setup();
    void save();
	void load();
	void saveData(DS_Dictionary* dict, std::string file);

	std::string m_saveFile; // 0xe8
	
	bool unk_0xec; // 0xec
	bool unk_0xed; // 0xed
};


#endif