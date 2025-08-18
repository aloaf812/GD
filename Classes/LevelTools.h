#ifndef _LEVEL_TOOLS_H_
#define _LEVEL_TOOLS_H_

#include "cocos2d.h"
#include <stdio.h>

class LevelTools
{
public:
    /**
    @brief Fetches the audio title of a song
    @param p0 The number of the song you want to get the name of
     */
    static std::string getAudioTitle(int p0);
    static std::string getAudioFileName(int p0);

};

#endif