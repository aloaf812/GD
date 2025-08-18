#include "GJGarageLayer.h"

#include "AppDelegate.h"
#include "CCMenuItemSpriteExtra.h"
#include "MenuLayer.h"
USING_NS_CC;


CCScene* GJGarageLayer::scene()
{
    // 'scene' is an autorelease object
    CCScene* scene = CCScene::create();
    AppDelegate* pApp = AppDelegate::get();
    
    pApp->mMenuScene = scene;
    
    // 'layer' is an autorelease object
    GJGarageLayer* layer = GJGarageLayer::node();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

GJGarageLayer* GJGarageLayer::node()
{
    GJGarageLayer* pRet = new GJGarageLayer();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

bool GJGarageLayer::init()
{
    if (!CCLayer::init())
        return false;
    
    CCDirector* pDirector = CCDirector::sharedDirector();
    // CCSize winSize = pDirector->getWinSize();
    
    this->setKeypadEnabled(true);
    
    
    // looks matching enough
    CCSprite* sideArtLeft = CCSprite::createWithSpriteFrameName("GJ_sideArt_001.png");
    sideArtLeft->setAnchorPoint(CCPoint(0.0f, 0.0f));
    sideArtLeft->setPosition(CCPoint(pDirector->getScreenLeft() - 1.0f, pDirector->getScreenTop() - 71.0f));
    sideArtLeft->setFlipY(true);
    this->addChild(sideArtLeft, 1);
    
    CCSprite* sideArtRight = CCSprite::createWithSpriteFrameName("GJ_sideArt_001.png");
    sideArtRight->setAnchorPoint(CCPoint(1.0f, 0.0f));
    sideArtRight->setPosition(CCPoint(pDirector->getScreenRight() + 1.0f, pDirector->getScreenTop() - 71.0f));
    sideArtRight->setFlipY(true);
    sideArtRight->setFlipX(true);
    this->addChild(sideArtRight, 1);
    
    CCSprite* backBtnSprite = CCSprite::createWithSpriteFrameName("GJ_arrow_03_001.png");
    CCMenuItemSpriteExtra* backBtn = CCMenuItemSpriteExtra::create(backBtnSprite, NULL, this, menu_selector(GJGarageLayer::onBack));
    backBtn->setSizeMult(1.6f);
    CCMenu* backMenu = CCMenu::create(backBtn, NULL);
    this->addChild(backMenu, 1);
    backMenu->setPosition(CCPoint(pDirector->getScreenLeft() + 25.0f, pDirector->getScreenTop() - 22.0f));
    
    CCSprite* starStat = CCSprite::createWithSpriteFrameName("GJ_starsIcon_001.png");
    starStat->setAnchorPoint(CCPoint(0.0f, 0.0f));
    starStat->setPosition(CCPoint(pDirector->getScreenRight() - 1.0f, pDirector->getScreenTop() - 1.0f));
    this->addChild(starStat, 1);
    
    return true;
}

void GJGarageLayer::onBack(CCObject* sender)
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCScene* scene = MenuLayer::scene();
    CCTransitionFade* fade = CCTransitionFade::create(0.5f, scene);
    pDirector->replaceScene(fade);
}
