#ifndef _FL_ALERT_LAYER_H_
#define _FL_ALERT_LAYER_H_

#include "cocos2d.h"
#include "FLAlertLayerProtocol.h"
#include <stdio.h>

class FLAlertLayer : public cocos2d::CCLayerColor {
public:
    // create methods
    static FLAlertLayer* create(FLAlertLayerProtocol* delegate, const char *title, const std::string &desc,const char *btn1,const char *btn2, float width,bool scroll,float height,float textScale);
    
    static FLAlertLayer* create(char const* title, const std::string& desc, char const* btn);
    static FLAlertLayer* create(FLAlertLayerProtocol* delegate, const char* title, const std::string& desc, const char* btn1, const char* btn2, float width);
    
    bool init(FLAlertLayerProtocol* delegate, char const* title, const std::string& desc, const char* btn1, const char* btn2, float width);
    
    virtual void show();
    virtual bool ccTouchBegan(cocos2d::CCTouch * touch, cocos2d::CCEvent * event);
    virtual void ccTouchMoved(cocos2d::CCTouch *touch,cocos2d::CCEvent *event);
    virtual void ccTouchEnded(cocos2d::CCTouch *touch,cocos2d::CCEvent *event);
    void incrementForcePrio();
protected:
    cocos2d::CCMenu* m_buttonMenu;
    cocos2d::CCLayer* m_mainLayer;
    // bool m_noElasticity;
    bool m_forcePrioRegistered;
    FLAlertLayerProtocol* m_alertProtocol;
};

#endif