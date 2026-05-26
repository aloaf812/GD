#ifndef _BOOM_SCROLL_LAYER_H_
#define _BOOM_SCROLL_LAYER_H_

#include "cocos2d.h"
#include "ExtendedLayer.h"

class BoomScrollLayerDelegate;

class BoomScrollLayer : public cocos2d::CCLayer {
public:
	BoomScrollLayer();
    static BoomScrollLayer* create(cocos2d::CCArray* pages, int offset, bool looped);
    virtual bool init(cocos2d::CCArray* pages, int offset, bool looped);
    void updateDots(float);
    void updatePages();
    void quickUpdate();
    void moveToPage(int page);
	void moveToPageEnded();
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	cocos2d::CCPoint positionForPageWithNumber(int page);
	void repositionPagesLooped();
	void setPagesIndicatorPosition(cocos2d::CCPoint position);
	int getTotalPages();

    cocos2d::CCArray* m_dotsArray; // 0x10c
	int m_animatingToPage; // 0x110
	bool m_looped; // 0x11c

	cocos2d::CCArray* unk_0x120; // 0x120
	bool unk_0x124; // 0x124
	cocos2d::CCArray* unk_0x134; // 0x134
	cocos2d::CCPoint m_targetPos; // 0x13c

	// vars
	CC_SYNTHESIZE_READONLY(ExtendedLayer*, m_internalLayer, InternalLayer); // 0x144
	CC_SYNTHESIZE(cocos2d::CCRect, m_scrollArea, ScrollArea); // 0x148

	// touch speeds
	CC_SYNTHESIZE(float, m_minTouchSpeed, MinTouchSpeed); // 0x158
	CC_SYNTHESIZE(float, m_touchSpeedFast, TouchSpeedFast); // 0x15c
	CC_SYNTHESIZE(float, m_touchSpeedMid, TouchSpeedMid); // 0x160

	CC_SYNTHESIZE(BoomScrollLayerDelegate*, m_delegate, Delegate); // 0x164
	CC_SYNTHESIZE_READONLY(bool, m_movingToPage, MovingToPage); // 0x168

	CC_SYNTHESIZE(float, m_minimumTouchLengthToSlide, MinimumTouchLengthToSlide); // 0x16c
	CC_SYNTHESIZE(float, m_minimumTouchLengthToChangePage, MinimumTouchLengthToChangePage); // 0x170

	CC_SYNTHESIZE(float, m_marginOffset, MarginOffset); // 0x174
	CC_SYNTHESIZE(bool, m_stealTouches, StealTouches); // 0x178
	CC_SYNTHESIZE(bool, m_showPagesIndicator, ShowPagesIndicator); // 0x179

	cocos2d::CCPoint m_pagesIndicatorPosition; // 0x17c

	CC_SYNTHESIZE(cocos2d::ccColor4B, m_pagesIndicatorSelectedColor, PagesIndicatorSelectedColor); // 0x184
	CC_SYNTHESIZE(cocos2d::ccColor4B, m_pagesIndicatorNormalColor, PagesIndicatorNormalColor); // 0x188

    CC_SYNTHESIZE_READONLY(int, m_currentScreen, CurrentScreen); // 0x18c
	CC_SYNTHESIZE(float, m_pagesWidthOffset, PagesWidthOffset); // 0x190
	CC_SYNTHESIZE_READONLY(cocos2d::CCArray*, m_pages, pages); // 0x194
};

class BoomScrollLayerDelegate {
public:
    virtual void scrollLayerMoved(cocos2d::CCPoint p0);
    virtual void scrollLayerScrolledToPage(BoomScrollLayer* bsl, int p1);
    virtual void scrollLayerScrollingStarted(BoomScrollLayer* bsl);
};


#endif