#include "AdToolbox.h"
#include "AppDelegate.h"
#include "GameToolbox.h"
#include "LoadingLayer.h"
#include "PlatformToolbox.h"
#include "SimpleAudioEngine.h"
#include "GameManager.h"
#include "GManager.h"
#include "LocalLevelManager.h"
#include "AchievementNotifier.h"
#include "RT_COCOS/CCContentManager.h"
USING_NS_CC;
using namespace CocosDenshion;

AppDelegate::AppDelegate() {
}

AppDelegate::~AppDelegate() 
{
}

AppDelegate* AppDelegate::get() { return static_cast<AppDelegate*>(sharedApplication()); }

bool AppDelegate::applicationDidFinishLaunching() {
    
    
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);
	pDirector->setProjection(kCCDirectorProjection2D);
	pDirector->setupScreenScale(CCSizeMake(480.0f, 320.0f));
    
    CCTexture2D::setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_RGBA4444);
    CCTexture2D::PVRImagesHavePremultipliedAlpha(true);
    pDirector->setDepthTest(false);
	pDirector->setAnimationInterval(1.0 / 60.0);

	#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		CCFileUtils::sharedFileUtils()->addSearchPath("Resources");
	#endif
	
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

	#else
		this->m_isIOS = false;
	#endif

	CCContentManager::sharedManager();
    // check performance with this: pDirector->setDisplayStats(true);
	AdToolbox::setupAds();
    
	// run
    CCScene *pScene = LoadingLayer::scene();
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
	pauseGame();
	trySaveGame();
    
	CCDirector::sharedDirector()->stopAnimation();
	CCDirector::sharedDirector()->pause();

	SimpleAudioEngine::sharedEngine()->pauseAllEffects();

	if (m_loadingFinished) {
		SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
        PlatformToolbox::onNativePause();
        GameManager::sharedState()->applicationDidEnterBackground();
    }
}

void AppDelegate::applicationWillResignActive()
{
	pauseGame();
}

void AppDelegate::willSwitchToScene(CCScene* scene)
{
	AchievementNotifier::sharedState()->willSwitchToScene(scene);
}

bool AppDelegate::musicTest(){
	CCScene* runScene = CCDirector::sharedDirector()->getRunningScene();
	if (!runScene)
		return false;

	if (runScene->getObjType() == CCObjectType::PlayLayer) {
		if (PLAY_LAYER) {
			if (get()->getPaused())
				return true;

			if (PLAY_LAYER->getShowingEndLayer())
				return true;
		}
	}

	return runScene->getObjType() == CCObjectType::LevelEditorLayer;
}

void AppDelegate::checkSound()
{
    if (musicTest()) {
        SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    }
}

void AppDelegate::resumeSound(){
    if (!musicTest())
		SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	
	SimpleAudioEngine::sharedEngine()->resumeAllEffects();
}

// i have a feeling rob wasn't the best programmer when he first wrote this code...
// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->stopAnimation();
	CCDirector::sharedDirector()->resume();
	CCDirector::sharedDirector()->startAnimation();

	if (PlatformToolbox::shouldResumeSound())
		resumeSound();

	PlatformToolbox::onNativeResume();
	PlatformToolbox::onToggleKeyboard();

	CCDirector::sharedDirector()->getActionManager()->removeActionByTag(1, GameManager::sharedState());
	CCDelayTime* delay = CCDelayTime::create(0.0f);

	CCCallFunc* callFunc = CCCallFunc::create(GameManager::sharedState(), callfunc_selector(GameManager::applicationWillEnterForeground));
	CCSequence* sequence = CCSequence::create(delay, callFunc, nullptr);
	sequence->setTag(1);

	CCDirector::sharedDirector()->getActionManager()->addAction(sequence, GameManager::sharedState(), false);
}

void AppDelegate::pauseGame(){
	CCScene* runScene = CCDirector::sharedDirector()->getRunningScene();
	if (runScene && runScene->getObjType() == CCObjectType::PlayLayer) {
		if (PLAY_LAYER) {
			if (!PLAY_LAYER->getShowingEndLayer()) {
				if (!get()->getPaused()) {
					PLAY_LAYER->pauseGame();
				}
			}
		}
	}
}

void AppDelegate::trySaveGame(){
	if (m_loadingFinished) {
		GameManager::sharedState()->save();
		LocalLevelManager::sharedState()->save();
	}
}

void AppDelegate::loadingIsFinished()
{
	m_loadingFinished = true;
	PlatformToolbox::reportLoadingFinished();
}


void AppDelegate::showLoadingCircle(bool, bool, bool) {}
void AppDelegate::hideLoadingCircle() {}
void AppDelegate::setIdleTimerDisabled(bool) {}