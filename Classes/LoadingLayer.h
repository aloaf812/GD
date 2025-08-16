#ifndef __GeometryDash__LoadingLayer__
#define __GeometryDash__LoadingLayer__

#include "cocos2d.h"

class TextArea;

/**

@brief  The scene shown while loading the game

*/
class LoadingLayer : public cocos2d::CCLayer
{
public:
    LoadingLayer();
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
    /**
    @brief Updates the width of the loading bar depending how much of the loading is complete.
    @param progress The percentage the bar will be filled to.
     */
    void updateProgress(int progress);
    CREATE_FUNC(LoadingLayer);

private:
    cocos2d::CCLabelBMFont* m_caption;
    TextArea* m_textArea;
    cocos2d::CCSprite* m_sliderBar;
    cocos2d::CCSize m_progressBarSize;
    int m_loadStep;
};

#endif
