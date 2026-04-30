#ifndef __SONG_OBJECT_H__
#define __SONG_OBJECT_H__

#include "cocos2d.h"

class SongObject : cocos2d::CCObject{
public:
	static SongObject* create(int track);
    virtual bool init(int track);
    
    CC_SYNTHESIZE_READONLY(int, m_audioTrack, AudioTrack);
};

#endif /* __SONG_OBJECT_H__ */