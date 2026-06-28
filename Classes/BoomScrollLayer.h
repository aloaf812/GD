#ifndef _BOOM_SCROLL_LAYER_H_
#define _BOOM_SCROLL_LAYER_H_

#include "cocos2d.h"
// #include "ExtendedLayer.h"

// i really gotta make some big include header file...
#define WIN_SIZE cocos2d::CCDirector::sharedDirector()->getWinSize()

class ExtendedLayer;
class BoomScrollLayerDelegate;

class BoomScrollLayer : public cocos2d::CCLayer {
public:
	BoomScrollLayer();
    static BoomScrollLayer* create(cocos2d::CCArray* pages, int offset, bool looped);
    bool init(cocos2d::CCArray* pages, int offset, bool looped);
    void updateDots(float);
    void updatePages();
    void quickUpdate();
    void moveToPage(int page);
	void instantMoveToPage(int page);
	void moveToPageEnded();
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	cocos2d::CCPoint positionForPageWithNumber(int page);
	cocos2d::CCPoint getRelativePosForPage(int page);
	void repositionPagesLooped();
	void setPagesIndicatorPosition(cocos2d::CCPoint position);
	unsigned int getTotalPages();
	int pageNumberForPosition(cocos2d::CCPoint pos);
	int getRelativePageForNum(int page);
	void selectPage(unsigned int pageNumber);
	void addPage(cocos2d::CCLayer* aPage);
	void addPage(cocos2d::CCLayer* aPage, int pageNumber);

	cocos2d::CCLayer* getPage(int page);

    cocos2d::CCArray* m_dotsArray; // 0x10c
	int m_animatingToPage; // 0x110
	float unk_0x114; // 0x114
	float unk_0x118; // 0x118
	bool m_looped; // 0x11c

	cocos2d::CCArray* unk_0x120; // 0x120
	bool unk_0x124; // 0x124
	int unk_0x128; // 0x128
	bool unk_0x12c; // 0x12c
	cocos2d::CCTouch* unk_0x130; // 0x130
	cocos2d::CCArray* m_actualPages; // 0x134
	float unk_0x138; // 0x138
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
	/** Called when scroll layer begins scrolling.
	* Usefull to cancel CCTouchDispatcher standardDelegates.
	*/
	virtual void scrollLayerScrollingStarted(BoomScrollLayer* sender) {};

	/** Called at the end of moveToPage:
	* Doesn't get called in selectPage:
	*/
	virtual void scrollLayerScrolledToPage(BoomScrollLayer* sender, int page) {};
	virtual void scrollLayerMoved(cocos2d::CCPoint p0) {};
};


#endif