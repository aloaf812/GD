#ifndef _FL_ALERT_LAYER_H_
#define _FL_ALERT_LAYER_H_

#include "cocos2d.h"
#include "FLAlertLayerProtocol.h"
#include <stdio.h>

class FLAlertLayer : public cocos2d::CCLayerColor {
public:
    FLAlertLayer();
    
	bool init(FLAlertLayerProtocol* protocol, char const* title, std::string caption, char const* button1, char const* button2, float unk1);
    
    virtual void show();
    virtual bool ccTouchBegan(cocos2d::CCTouch * touch, cocos2d::CCEvent * event);
    virtual void ccTouchMoved(cocos2d::CCTouch *touch,cocos2d::CCEvent *event);
    virtual void ccTouchEnded(cocos2d::CCTouch *touch,cocos2d::CCEvent *event);
    void incrementForcePrio();

	CC_SYNTHESIZE(FLAlertLayerProtocol*, m_pParent, PParent); // 0x194
	CC_SYNTHESIZE(cocos2d::CCNode*, m_targetScene, TargetScene); // 0x198
	CC_SYNTHESIZE(bool, m_reverseKeyBack, ReverseKeyBack); // 0x19c
	CC_SYNTHESIZE_READONLY(cocos2d::CCLayer*, m_internalLayer, InternalLayer); // 0x1a0

protected:
    cocos2d::CCMenu* m_buttonMenu;
    int m_ZOrder;
    cocos2d::CCLayer* m_mainLayer; // m_internalLayer
    int m_scrollAction;
    bool m_containsBorder;
    bool m_noAction;
};

#endif