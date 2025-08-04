#ifndef __GeometryDash__LoadingLayer__
#define __GeometryDash__LoadingLayer__

#include "cocos2d.h"

class LoadingLayer : public cocos2d::CCLayer
{
public:
    static cocos2d::CCScene* scene();
    const char* getLoadingString();
    bool init();
    // void loadAssets();
    void loadingFinished();
    void updateProgress(int param_1);
    CREATE_FUNC(LoadingLayer);
};

#endif
