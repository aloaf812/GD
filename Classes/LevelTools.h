#ifndef __GeometryDash__LevelTools__
#define __GeometryDash__LevelTools__

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