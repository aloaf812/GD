#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

#include "cocos2d.h"

/**
@brief    The cocos2d Application.

*/
class  AppDelegate : public cocos2d::CCApplication
{
public:
    AppDelegate();
    virtual ~AppDelegate();

    /**
    @brief    Implement CCDirector and CCScene init code here.
    @return true    Initialize success, app continue.
    @return false   Initialize failed, app terminate.
    */
    virtual bool applicationDidFinishLaunching();

    /**
    @brief  The function be called when the application enter background
    @param  the pointer of the application
    */
    virtual void applicationDidEnterBackground();

    /**
    @brief  The function be called when the application enter foreground
    @param  the pointer of the application
    */
    virtual void applicationWillEnterForeground();
    
	virtual void applicationWillResignActive();
	virtual void willSwitchToScene(cocos2d::CCScene* scene);

    void resumeSound();
    void pauseGame();
    void checkSound();
    void trySaveGame();
    void loadingIsFinished();
    static bool musicTest();

	void showLoadingCircle(bool, bool, bool);
	void hideLoadingCircle();
	void setIdleTimerDisabled(bool);

	CC_SYNTHESIZE(bool, m_paused, Paused); // 0x8
	CC_SYNTHESIZE(cocos2d::CCNode*, m_scenePointer, ScenePointer); // 0xc
	CC_SYNTHESIZE_READONLY(bool, m_loadingFinished, LoadingFinished); // 0x10
	CC_SYNTHESIZE(bool, m_managersLoaded, ManagersLoaded); // 0x11
	CC_SYNTHESIZE_READONLY(bool, m_isIOS, IsIOS); // 0x12
    

	static AppDelegate* get();
    
};

#endif // _APP_DELEGATE_H_

