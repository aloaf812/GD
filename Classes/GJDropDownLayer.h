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
    ~GJDropDownLayer();
    
    bool init(const char* title, float height);
    bool init(const char* title);
    virtual void disableUI();
    void enableUI();
    void draw();
    virtual void exitLayer(cocos2d::CCObject* obj);
    virtual void hideLayer(bool instantHide);
    void showLayer(bool instantShow);
    void keyBackClicked();
    void layerHidden();
    void registerWithTouchDispatcher();
    void enterLayer();
    void layerVisible();
    void enterAnimFinished() {}
    void customSetup() {}
    GJDropDownLayer* create(const char* title, float height);
    GJDropDownLayer* create(const char* title);
    
    bool ccTouchBegan() { return true; }
    void ccTouchCancelled() {}
    void ccTouchEnded() {}
    void ccTouchMoved() {}
    
    // these are from geode =)
    cocos2d::CCPoint m_endPosition;
    cocos2d::CCPoint m_startPosition;
    cocos2d::CCMenu* m_buttonMenu;
    GJListLayer* m_listLayer;
    bool m_controllerEnabled;
    cocos2d::CCLayer* m_mainLayer;
    bool m_hidden;
    GJDropDownLayerDelegate* m_delegate;
};

class GJDropDownLayerDelegate
{
public:
    virtual void dropDownLayerWillClose(GJDropDownLayer* p0);
};

#endif