#ifndef __GeometryDash__GameManager__
#define __GeometryDash__GameManager__

#include "cocos2d.h"
#include "GManager.h"
#include <stdio.h>

class IconType;

class GameManager: public GManager {
public:
    static GameManager* sharedState();
    /**
    @returns A texture file depending on the value in the id field.
    */
    char const* getBGTexture(int id);
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
    // char const* iconKey(int id, IconType type);
    void loadBackground(int param_1);
    void syncPlatformAchievements();
    void followTwitter();
    void likeFacebook();
    bool m_clickedGarage;
    bool m_clickedEditor;
};

#endif /* defined(__GeometryDash__GameManager__) */
