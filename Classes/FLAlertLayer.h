#ifndef _FL_ALERT_LAYER_H_
#define _FL_ALERT_LAYER_H_

#include "cocos2d.h"
#include "FLAlertLayerProtocol.h"
#include <stdio.h>

class FLAlertLayer : public cocos2d::CCLayerColor {
public:
    FLAlertLayer();
    // create methods
    static FLAlertLayer* create(FLAlertLayerProtocol* delegate, const char *title, const std::string &desc,const char *btn1,const char *btn2, float width,bool scroll,float height,float textScale);
    
    static FLAlertLayer* create(char const* title, const std::string& desc, char const* btn);
    static FLAlertLayer* create(FLAlertLayerProtocol* delegate, const char* title, const std::string& desc, const char* btn1, const char* btn2, float width);
    
    //bool FLAlertLayer::init(FLAlertLayerProtocol* target, char const* title, std::string caption, char const* button1, char const* button2, float width, bool border, float height);
    
    virtual void show();
    virtual bool ccTouchBegan(cocos2d::CCTouch * touch, cocos2d::CCEvent * event);
    virtual void ccTouchMoved(cocos2d::CCTouch *touch,cocos2d::CCEvent *event);
    virtual void ccTouchEnded(cocos2d::CCTouch *touch,cocos2d::CCEvent *event);
    void incrementForcePrio();
protected:
    cocos2d::CCMenu* m_buttonMenu;
    int m_ZOrder;
    FLAlertLayerProtocol* m_alertProtocol; // m_pParent
    cocos2d::CCNode* m_scene; // m_targetScene
    bool m_reverseKeyBack;
    cocos2d::CCLayer* m_mainLayer; // m_internalLayer
    int m_scrollAction;
    bool m_containsBorder;
    bool m_noAction;
};

#endif