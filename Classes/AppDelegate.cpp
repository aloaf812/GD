#include "AppDelegate.h"
#include "LoadingLayer.h"
#include "GameToolbox.h"
#include "PlatformToolbox.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;

AppDelegate::AppDelegate() {
    if false {
        // do this
    }
    else {
        ccGLInvalidateStateCache();
        // another robtop function CCShaderCache::sharedShaderCache()->reloadDefaultShaders();
        CCNotificationCenter::sharedNotificationCenter()->postNofitication("event_come_to_foreground");
        CCDirector::sharedDirector()->setGLDefaultValues();
    }
}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);
	
    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);
    
    // create a scene. it's an autorelease object
    CCTexture2D::setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_RGBA4444);
    CCTexture2D::PVRImagesHavePremultipliedAlpha(true);
    pDirector->setDepthTest(false);
    // run
    CCScene *pScene = LoadingLayer::scene();
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->pause();
    SimpleAudioEngine::sharedEngine()->pauseAllEffects();
    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

bool AppDelegate::musicTest(){
    return true;
}
void AppDelegate::resumeSound(){
    if (!AppDelegate::musicTest())
    {
        SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    }
    SimpleAudioEngine::sharedEngine()->resumeAllEffects();
    return;
}
// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    if (!PlatformToolbox::shouldResumeSound())
    {
        AppDelegate::resumeSound();
    }
}



void trySaveGame(bool p0){
    PlatformToolbox::gameDidSave();
    return;
}

/* void loadingIsFinished()
{
    return;
}
*/
