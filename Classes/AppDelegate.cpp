#include "AdToolbox.h"
#include "AppDelegate.h"
#include "GameToolbox.h"
#include "LoadingLayer.h"
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
        // another robtop function: CCShaderCache::sharedShaderCache()->reloadDefaultShaders();
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

    CCTexture2D::setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_RGBA4444);
    CCTexture2D::PVRImagesHavePremultipliedAlpha(true);

    pDirector->setDepthTest(false);
    AdToolbox::setupAds();
    
    // run
    CCScene *pScene = LoadingLayer::scene();
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    AppDelegate::pauseGame();
    AppDelegate::trySaveGame();
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

void pauseGame(){
    return;
}

void trySaveGame(bool p0){
    PlatformToolbox::gameDidSave();
    return;
}

AppDelegate* AppDelegate::get(){
    
    return;
}

/* void loadingIsFinished()
{
    return;
}
*/
