#ifndef _LEVEL_TOOLS_H_
#define _LEVEL_TOOLS_H_

#include "cocos2d.h"
#include <stdio.h>
#include "GJGameLevel.h"

class LevelTools
{
public:
    /**
    @brief Fetches the audio title of a song
    @param audio The number of the song you want to get the name of
     */
    static std::string getAudioTitle(int audio);
    static std::string getAudioFileName(int audio);
    static GJGameLevel* getLevel(int level);
    static std::string getAudioString(int audio);
    static const char* nameForArtist(int artist);
    static const char* ytURLForArtist(int artist);
    static const char* ngURLforArtist(int artist);
    static const char* urlForAudio(int audio);
};

#endif