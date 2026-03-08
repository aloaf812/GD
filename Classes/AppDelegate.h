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
    
    virtual void loadingIsFinished();
    void resumeSound();
    static bool musicTest();
    void pauseGame();
    void checkSound();
    virtual void trySaveGame();
	CC_SYNTHESIZE(bool, m_paused, Paused); // 0x8
	CC_SYNTHESIZE_READONLY(bool, m_loadingFinished, LoadingFinished); // 0x10
	CC_SYNTHESIZE_READONLY(bool, m_managersLoaded, ManagersLoaded); // 0x11
	CC_SYNTHESIZE_READONLY(bool, m_isIOS, IsIOS); // 0x12
	CC_SYNTHESIZE(cocos2d::CCNode*, m_scenePointer, ScenePointer); // 0x13
    
    static AppDelegate* get()
    {
        return static_cast<AppDelegate*>(sharedApplication());
    }

    
    // do not implement this right now: virtual void willSwitchToScene(cocos2d::CCScene* p0);
};

#endif // _APP_DELEGATE_H_

