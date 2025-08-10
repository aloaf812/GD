#ifndef __GeometryDash__LoadingLayer__
#define __GeometryDash__LoadingLayer__

#include "cocos2d.h"
/**

@brief  The scene shown while loading the game

*/
class LoadingLayer : public cocos2d::CCLayer
{
public:
    static cocos2d::CCScene* scene();
    /**
    @brief Randomly picks a loading message to be shown while the game is loading
    @returns A randomly picked loading message
    */
    const char* getLoadingString();
    bool init();
    /**
    @brief Loads all of the game's assets.
    */
    void loadAssets();
    /**
    @brief Changes the LoadingLayer scene to the MenuLayer scene.
    */
    void loadingFinished();
    void updateProgress(int param_1);
    CREATE_FUNC(LoadingLayer);

    // class fields
    int m_loadStep;
    float m_sliderGrooveXPos;
    float m_sliderGrooveXHeight;
    cocos2d::CCSprite* m_sliderBar;
};

#endif
