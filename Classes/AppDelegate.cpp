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
	pDirector->setProjection(kCCDirectorProjection2D);
    const CCSize windowSize = pEGLView->getFrameSize();
    pDirector->setupScreenScale(contentSize, windowSize);
    
    CCTexture2D::setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_RGBA4444);
    CCTexture2D::PVRImagesHavePremultipliedAlpha(true);
    pDirector->setDepthTest(false);

	#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		CCFileUtils::sharedFileUtils()->addSearchPath("Resources");
	#endif
	
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

	#else
		this->m_isIOS = false;
	#endif

    // check performance with this: pDirector->setDisplayStats(true);
	// AdToolbox::setupAds();
    
	// run
    CCScene *pScene = LoadingLayer::node();
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector* pDirector = CCDirector::sharedDirector();
    SimpleAudioEngine* SAE = SimpleAudioEngine::sharedEngine();
    // what?: pDirector->__cxa_pure_virtual)();
    pDirector->pause();
    SimpleAudioEngine::sharedEngine()->pauseAllEffects();
    if (false) {
        SAE->pauseBackgroundMusic();
        PlatformToolbox::onNativePause();
        GameManager::sharedState()->applicationDidEnterBackground();
    }
}

bool AppDelegate::musicTest(){
    return true;
}

void AppDelegate::checkSound()
{
    if (!musicTest()) {
        SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    }
}

void AppDelegate::resumeSound(){
    SimpleAudioEngine* SAE = SimpleAudioEngine::sharedEngine();
    if (!musicTest())
    {
        SAE->resumeBackgroundMusic();
    }
    SAE->resumeAllEffects();
}
// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector* pDirector = CCDirector::sharedDirector();
    GameManager* pGameManager = GameManager::sharedState();
    pDirector->startAnimation();
    if (!PlatformToolbox::shouldResumeSound())
    {
        resumeSound();
    }
    pGameManager->applicationWillEnterForeground();
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
