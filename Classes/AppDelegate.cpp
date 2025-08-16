#include "AdToolbox.h"
#include "AppDelegate.h"
#include "GameToolbox.h"
#include "LoadingLayer.h"
#include "PlatformToolbox.h"
#include "SimpleAudioEngine.h"
#include "GameManager.h"
#include "GManager.h"
#include "LocalLevelManager.h"
USING_NS_CC;
using namespace CocosDenshion;

AppDelegate::AppDelegate() {
}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    
    CCSize contentSize(480.0f, 320.0f);
    
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);

    const CCSize windowSize = pEGLView->getFrameSize();
    pDirector->setupScreenScale(contentSize, windowSize);
    
    CCTexture2D::setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_RGBA4444);
    CCTexture2D::PVRImagesHavePremultipliedAlpha(true);

    pDirector->setDepthTest(false);
    // AdToolbox::setupAds();
    
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

void AppDelegate::pauseGame(){
    return;
}

void AppDelegate::trySaveGame(){
    // GManager* pManagers = GameManager::sharedState();
    // pManagers()->GManager::save();
    // LocalLevelManager::sharedState()->GManager::save();
    return;
}

float AppDelegate::bgScale()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    float scaleFactor = pDirector->getScreenScaleFactorMax();
    
    return scaleFactor;
}

void AppDelegate::loadingIsFinished()
{
    // :wilted_rose:
    return;
}
