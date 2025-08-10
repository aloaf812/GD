#ifndef __GeometryDash__GameManager__
#define __GeometryDash__GameManager__

#include "cocos2d.h"
#include "GManager.h"
#include <stdio.h>

class GameManager: public GManager {
public:
    static GameManager* sharedState();
    char const* getBGTexture(int id);
    // void fadeInMusic(char const*);
    virtual bool init();
    /**
    @param ach_ID The ID of the achievment of the achievement being reported (e.g. geometry.ach.moreGames)
    @param percentage The completion percentage of the achievement
    @param param_3 A bool parameter 
    */
    void reportAchievementWithID(char const* ach_ID, int percentage, bool param_3);
    /**
    @param fileName The file of the music which will be faded in.
    */
    void fadeInMusic(char const* fileName);
    void loadBackground(int param_1);
};

#endif /* defined(__GeometryDash__GameManager__) */
