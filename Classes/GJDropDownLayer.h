#ifndef _GJ_DROP_DOWN_LAYER_
#define _GJ_DROP_DOWN_LAYER_
#include "cocos2d.h"
#include "GJListLayer.h"
using cocos2d::SEL_CallFunc;
using cocos2d::SEL_MenuHandler;

class GJDropDownLayerDelegate;

class GJDropDownLayer : public cocos2d::CCLayerColor {
public:
    GJDropDownLayer();
    
    bool init(const char* title, float height);
    bool init(const char* title);
    void draw();
    virtual void customSetup() {}
    virtual void enterLayer();
    virtual void exitLayer(cocos2d::CCObject* sender);
    virtual void showLayer(bool instantShow);
    virtual void hideLayer(bool instantHide);
    virtual void layerVisible();
    virtual void layerHidden();
    virtual void enterAnimFinished() {}
    virtual void disableUI();
    virtual void enableUI();
    void keyBackClicked();
    void registerWithTouchDispatcher();
    GJDropDownLayer* create(const char* title, float height);
    GJDropDownLayer* create(const char* title);
    
	bool ccTouchBegan(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
    
    // these are from geode =)
    cocos2d::CCPoint m_endPosition; // 0x188
    cocos2d::CCPoint m_startPosition; // 0x190
	cocos2d::CCMenu* m_uiMenu; // 0x198
    GJListLayer* m_listLayer; // 0x19c

	CC_SYNTHESIZE_READONLY(cocos2d::CCLayer*, m_internalLayer, InternalLayer); // 0x1a0
	CC_SYNTHESIZE(bool, m_removeOnExit, RemoveOnExit); // 0x1a4

    bool m_hidden;
    GJDropDownLayerDelegate* m_delegate;
};

class GJDropDownLayerDelegate
{
public:
    virtual void dropDownLayerWillClose(GJDropDownLayer* p0);
};

#endif