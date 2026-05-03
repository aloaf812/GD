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
    NODE_FUNC(LoadingLayer);
private:
    int m_loadStep; // 0x110
    cocos2d::CCLabelBMFont* m_caption; // 0x114
    TextArea* m_textArea; // 0x118
    cocos2d::CCSprite* m_sliderBar; // 0x11c
	float m_sliderGrooveXPos; // 0x120
	float m_sliderGrooveHeight; // 0x124
};

#endif
