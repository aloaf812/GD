#include "GJGarageLayer.h"

#include "AppDelegate.h"
#include "CCMenuItemSpriteExtra.h"
#include "MenuLayer.h"
#include "SimplePlayer.h"
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
    CCSize winSize = pDirector->getWinSize();
    
    this->setKeypadEnabled(true);
    
    m_backgroundSprite = CCSprite::create("GJ_gradientBG.png");
    m_backgroundSprite->setAnchorPoint(CCPoint(0.0f, 0.0f));
    this->addChild(m_backgroundSprite, -2);
    m_backgroundSprite->setScaleX((winSize.width + 10.0f) / m_backgroundSprite->getTextureRect().size.width);
    m_backgroundSprite->setScaleY((winSize.height + 10.0f) / m_backgroundSprite->getTextureRect().size.height);
    m_backgroundSprite->setPosition(CCPoint(-5.0f, -5.0f));
    ccColor3B c = {150, 150, 150};
    m_backgroundSprite->setColor(c);

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
    
    CCSprite* editBarBG = CCSprite::create("edit_barBG_001.png");
    editBarBG->setAnchorPoint(CCPoint(0.0f, 0.0f));
    editBarBG->setPosition(CCPoint(pDirector->getScreenLeft(), pDirector->getScreenBottom()));
    this->addChild(editBarBG, 1);

    SimplePlayer* player = SimplePlayer::create(4);
    player->setAnchorPoint(CCPoint(0.0f, 0.0f));
    player->setPosition(CCPoint(pDirector->getScreenRight() - 1.0f, pDirector->getScreenTop() - 1.0f));
    this->addChild(player, 1);
    
    

/*  piVar2 = (int *)GameManager::sharedState();
  (**(code **)(*piVar2 + 0x1d8))(piVar2,1);
  piVar2 = (int *)GameManager::sharedState();
  (**(code **)(*piVar2 + 0x250))(piVar2,0);
  (*((this->CCLayer).vftablePtr)->setKeypadEnabled)(this,true);
  cocos2d::CCDirector::sharedDirector();
  cocos2d::CCDirector::getWinSize();
  pCVar3 = (CCNode *)cocos2d::CCSprite::create("GJ_gradientBG.png");
  pcVar15 = *(code **)(*(int *)pCVar3 + 0x8c);
  cocos2d::CCPoint::CCPoint(&CStack_100,extraout_s0,extraout_s1);
  (*pcVar15)(pCVar3,&CStack_100);
  (*((this->CCLayer).vftablePtr)->addChild)(this,pCVar3);
  (**(code **)(*(int *)pCVar3 + 0x40))(pCVar3,(local_108 + 10.0) / *(float *)(pCVar3 + 0x138));
  uVar19 = (**(code **)(*(int *)pCVar3 + 0x48))
                     (pCVar3,(local_104 + 10.0) / *(float *)(pCVar3 + 0x13c));
  pcVar15 = *(code **)(*(int *)pCVar3 + 0x5c);
  cocos2d::CCPoint::CCPoint(&CStack_f8,(float)uVar19,(float)((ulonglong)uVar19 >> 0x20));
  (*pcVar15)(pCVar3,&CStack_f8);
  local_11c = 0xaf;
  local_11b = 0xaf;
  local_11a = 0xaf;
  (**(code **)(*(int *)pCVar3 + 0x1cc))(pCVar3,&local_11c);
  pCVar4 = (CCSprite *)cocos2d::CCSprite::createWithSpriteFrameName("GJ_sideArt_001.png");
  psVar16 = ((pCVar4->CCNodeRGBA).vftablePtr)->setAnchorPoint;
  cocos2d::CCPoint::CCPoint(&CStack_f0,extraout_s0_00,extraout_s1_00);
  (*psVar16)(pCVar4,(CCPoint *)&CStack_f0);
  psVar17 = ((pCVar4->CCNodeRGBA).vftablePtr)->setPosition;
  pCVar5 = (CCDirector *)cocos2d::CCDirector::sharedDirector();
  cocos2d::CCDirector::getScreenLeft(pCVar5);
  pCVar5 = (CCDirector *)cocos2d::CCDirector::sharedDirector();
  uVar19 = cocos2d::CCDirector::getScreenTop(pCVar5);
  cocos2d::CCPoint::CCPoint(&CStack_e8,(float)uVar19,(float)((ulonglong)uVar19 >> 0x20));
  (*psVar17)(pCVar4,(CCPoint *)&CStack_e8);
  cocos2d::CCSprite::setFlipY(pCVar4,true);
  (*((this->CCLayer).vftablePtr)->addChild)(this,(CCNode *)pCVar4);
  pCVar4 = (CCSprite *)cocos2d::CCSprite::createWithSpriteFrameName("GJ_sideArt_001.png");
  psVar16 = ((pCVar4->CCNodeRGBA).vftablePtr)->setAnchorPoint;
  cocos2d::CCPoint::CCPoint(&CStack_e0,extraout_s0_01,extraout_s1_01);
  (*psVar16)(pCVar4,(CCPoint *)&CStack_e0);
  psVar17 = ((pCVar4->CCNodeRGBA).vftablePtr)->setPosition;
  pCVar5 = (CCDirector *)cocos2d::CCDirector::sharedDirector();
  cocos2d::CCDirector::getScreenRight(pCVar5);
  pCVar5 = (CCDirector *)cocos2d::CCDirector::sharedDirector();
  uVar19 = cocos2d::CCDirector::getScreenTop(pCVar5);
  cocos2d::CCPoint::CCPoint(&CStack_d8,(float)uVar19,(float)((ulonglong)uVar19 >> 0x20));
  (*psVar17)(pCVar4,(CCPoint *)&CStack_d8);
  cocos2d::CCSprite::setFlipY(pCVar4,true);
  cocos2d::CCSprite::setFlipX(pCVar4,true);
  uVar19 = (*((this->CCLayer).vftablePtr)->addChild)(this,(CCNode *)pCVar4);
  this_00 = (CCTextInputNode *)
            CCTextInputNode::create
                      ((float)uVar19,(float)((ulonglong)uVar19 >> 0x20),(char *)0x43480000,
                       (char *)0x42480000,0x40385e,"Thonburi");
  (*(this_00->CCLayer).vftablePtr[1].setVertexZ)(this_00,extraout_s0_02);
  (*((this->CCLayer).vftablePtr)->addChild)(this,(CCNode *)this_00);
  (*(this_00->CCLayer).vftablePtr[1].canEncode)(this_00);
  psVar17 = ((this_00->CCLayer).vftablePtr)->setPosition;
  pCVar5 = (CCDirector *)cocos2d::CCDirector::sharedDirector();
  uVar19 = cocos2d::CCDirector::getScreenTop(pCVar5);
  cocos2d::CCPoint::CCPoint(&CStack_d0,(float)uVar19,(float)((ulonglong)uVar19 >> 0x20));
  (*psVar17)(this_00,(CCPoint *)&CStack_d0);
  piVar2 = (int *)(*(this_00->CCLayer).vftablePtr[1].setObjType)(this_00,extraout_r1);
  (**(code **)(*piVar2 + 0xa0))(piVar2,0);
  (*(this_00->CCLayer).vftablePtr[1].setZOrder)(this_00);
  local_118 = CONCAT13(local_118._3_1_,0xf0aa78);
  fVar18 = (float)CCTextInputNode::setLabelPlaceholderColor(this_00,local_118);
  CCTextInputNode::setLabelPlaceholderScale(this_00,fVar18);
  piVar2 = (int *)GameManager::sharedState();
  (**(code **)(*piVar2 + 0x204))(auStack_114,piVar2);
  FUN_003b2e28(auStack_110,&DAT_00401d62,auStack_120);
  iVar6 = FUN_003b1294(auStack_114,auStack_110);
  FUN_003b16dc(auStack_110);
  FUN_003b16dc(auStack_114);
  if (iVar6 != 0) {
    piVar2 = (int *)GameManager::sharedState();
    (**(code **)(*piVar2 + 0x204))(local_10c,piVar2);
    CCTextInputNode::setString((char *)this_00);
    FUN_003b16dc(local_10c);
  }
  piVar2 = (int *)GameManager::sharedState();
  iVar6 = (**(code **)(*piVar2 + 0x2fc))();
  if (iVar6 == 0) {
    pCVar3 = (CCNode *)cocos2d::CCSprite::createWithSpriteFrameName("GJ_nameTxt_001.png");
    (*((this->CCLayer).vftablePtr)->addChild)(this,pCVar3);
    pcVar15 = *(code **)(*(int *)pCVar3 + 0x5c);
    pCVar7 = (CCPoint *)(*((this_00->CCLayer).vftablePtr)->getPosition)(this_00);
    cocos2d::CCPoint::CCPoint(&CStack_c8,extraout_s0_03,extraout_s1_02);
    cocos2d::CCPoint::operator+(&CStack_c0,pCVar7);
    (*pcVar15)(pCVar3,&CStack_c0);
  }
  pCVar3 = (CCNode *)cocos2d::CCSprite::createWithSpriteFrameName("floorLine_001.png");
  uVar19 = (*((this->CCLayer).vftablePtr)->addChild)(this,pCVar3);
  pcVar15 = *(code **)(*(int *)pCVar3 + 0x5c);
  cocos2d::CCPoint::CCPoint(&CStack_b8,(float)uVar19,(float)((ulonglong)uVar19 >> 0x20));
  (*pcVar15)(pCVar3,&CStack_b8);
  local_b0 = 0x302;
  uStack_ac = 1;
  (**(code **)(*(int *)pCVar3 + 0x208))(pCVar3,0x302,1);
  pCVar8 = (CCNode *)cocos2d::CCSprite::create("edit_barBG_001.png");
  uVar19 = (**(code **)(*(int *)pCVar8 + 0x40))
                     (pCVar8,(local_108 + 2.0) / *(float *)(pCVar8 + 0x138));
  pcVar15 = *(code **)(*(int *)pCVar8 + 0x8c);
  cocos2d::CCPoint::CCPoint(&CStack_a8,(float)uVar19,(float)((ulonglong)uVar19 >> 0x20));
  (*pcVar15)(pCVar8,&CStack_a8);
  pcVar15 = *(code **)(*(int *)pCVar8 + 0x5c);
  pCVar5 = (CCDirector *)cocos2d::CCDirector::sharedDirector();
  cocos2d::CCDirector::getScreenLeft(pCVar5);
  pCVar5 = (CCDirector *)cocos2d::CCDirector::sharedDirector();
  uVar19 = cocos2d::CCDirector::getScreenBottom(pCVar5);
  cocos2d::CCPoint::CCPoint(&CStack_a0,(float)uVar19,(float)((ulonglong)uVar19 >> 0x20));
  (*pcVar15)(pCVar8,&CStack_a0);
  (**(code **)(*(int *)pCVar8 + 0x48))(pCVar8,0x3f4ccccd);
  fVar20 = *(float *)(pCVar8 + 0x13c);
  fVar18 = (float)(**(code **)(*(int *)pCVar8 + 0x4c))(pCVar8);
  this[1].CCLayer.data.offset_0x0 = fVar20 * fVar18;
  iVar6 = (**(code **)(*(int *)pCVar8 + 0x60))(pCVar8);
  pCVar14 = (this->CCLayer).vftablePtr;
  this[1].CCLayer.data.offset_0x4 = *(float *)(iVar6 + 4) + (float)this[1].CCLayer.data.offset_0x0;
  (*pCVar14->addChild)(this,pCVar8);
  piVar2 = (int *)GameManager::sharedState();
  this_01 = (SimplePlayer *)(**(code **)(*piVar2 + 0x264))();
  pCVar14 = (CCLayer_vftable_for_CCNode *)SimplePlayer::SimplePlayer(this_01);
  this[1].CCLayer.vftablePtr = pCVar14;
  (*((this->CCLayer).vftablePtr)->addChild)(this,(CCNode *)pCVar14);
  pCVar14 = this[1].CCLayer.vftablePtr;
  (**(code **)(pCVar14->copyWithZone + 0x50))(pCVar14,0x3fcccccd);
  pCVar14 = this[1].CCLayer.vftablePtr;
  pcVar15 = *(code **)(pCVar14->copyWithZone + 0x5c);
  pCVar7 = (CCPoint *)(**(code **)(*(int *)pCVar3 + 0x60))(pCVar3);
  uVar19 = (**(code **)((this[1].CCLayer.vftablePtr)->copyWithZone + 0x54))();
  cocos2d::CCPoint::CCPoint(&CStack_98,(float)uVar19,(float)((ulonglong)uVar19 >> 0x20));
  cocos2d::CCPoint::operator+(&CStack_90,pCVar7);
  (*pcVar15)(pCVar14,&CStack_90);
  pCVar14 = this[1].CCLayer.vftablePtr;
  pcVar15 = *(code **)(pCVar14->copyWithZone + 0x250);
  piVar2 = (int *)GameManager::sharedState();
  uVar9 = (**(code **)(*piVar2 + 0x294))();
  (*pcVar15)(pCVar14,uVar9);
  updatePlayerColors(this);
  piVar2 = (int *)GameManager::sharedState();
  iVar6 = (**(code **)(*piVar2 + 0x29c))();
  if (iVar6 == 2) {
    pCVar14 = this[1].CCLayer.vftablePtr;
    piVar2 = (int *)GameManager::sharedState();
    pcVar15 = *(code **)(*piVar2 + 0x274);
  }
  else if (iVar6 == 3) {
    pCVar14 = this[1].CCLayer.vftablePtr;
    piVar2 = (int *)GameManager::sharedState();
    pcVar15 = *(code **)(*piVar2 + 0x27c);
  }
  else {
    if (iVar6 != 1) goto LAB_001ca1a6;
    pCVar14 = this[1].CCLayer.vftablePtr;
    piVar2 = (int *)GameManager::sharedState();
    pcVar15 = *(code **)(*piVar2 + 0x26c);
  }
  uVar9 = (*pcVar15)();
  SimplePlayer::updatePlayerFrame((SimplePlayer *)pCVar14,uVar9,iVar6);
LAB_001ca1a6:
  setupIconSelect(this);
  setupColorSelect(this);
  pCVar3 = (CCNode *)cocos2d::CCSprite::createWithSpriteFrameName("GJ_arrow_03_001.png");
  local_34 = 0;
  local_38 = (code *)0x1c78bb;
  pCVar10 = (CCMenuItem *)
            CCMenuItemSpriteExtra::create
                      (pCVar3,(CCNode *)0x0,(CCObject *)this,(_func_void_CCObject_ptr *)0x1c78bb);
  CCMenuItemSpriteExtra::setSizeMult(extraout_s0_04);
  pCVar3 = (CCNode *)cocos2d::CCMenu::create(pCVar10,0);
  (*((this->CCLayer).vftablePtr)->addChild)(this,pCVar3);
  pcVar15 = *(code **)(*(int *)pCVar3 + 0x5c);
  pCVar5 = (CCDirector *)cocos2d::CCDirector::sharedDirector();
  cocos2d::CCDirector::getScreenLeft(pCVar5);
  pCVar5 = (CCDirector *)cocos2d::CCDirector::sharedDirector();
  uVar19 = cocos2d::CCDirector::getScreenTop(pCVar5);
  cocos2d::CCPoint::CCPoint(&CStack_88,(float)uVar19,(float)((ulonglong)uVar19 >> 0x20));
  (*pcVar15)(pCVar3,&CStack_88);
  pCVar3 = (CCNode *)cocos2d::CCSprite::createWithSpriteFrameName("GJ_starsIcon_001.png");
  (*((this->CCLayer).vftablePtr)->addChild)(this,pCVar3);
  pcVar15 = *(code **)(*(int *)pCVar3 + 0x5c);
  pCVar5 = (CCDirector *)cocos2d::CCDirector::sharedDirector();
  cocos2d::CCDirector::getScreenRight(pCVar5);
  pCVar5 = (CCDirector *)cocos2d::CCDirector::sharedDirector();
  uVar19 = cocos2d::CCDirector::getScreenTop(pCVar5);
  cocos2d::CCPoint::CCPoint(&CStack_80,(float)uVar19,(float)((ulonglong)uVar19 >> 0x20));
  pGVar11 = (GameStatsManager *)(*pcVar15)(pCVar3,&CStack_80);
  pGVar11 = GameStatsManager::GameStatsManager(pGVar11);
  uVar9 = GameStatsManager::getStat(pGVar11,"6");
  pCVar12 = (CCString *)cocos2d::CCString::createWithFormat("%i",uVar9);
  pcVar13 = (char *)cocos2d::CCString::getCString(pCVar12);
  pCVar8 = (CCNode *)cocos2d::CCLabelBMFont::create(pcVar13,"bigFont.fnt");
  uVar19 = (*((this->CCLayer).vftablePtr)->addChild)(this,pCVar8);
  pcVar15 = *(code **)(*(int *)pCVar8 + 0x8c);
  cocos2d::CCPoint::CCPoint(&CStack_78,(float)uVar19,(float)((ulonglong)uVar19 >> 0x20));
  (*pcVar15)(pCVar8,&CStack_78);
  pcVar15 = *(code **)(*(int *)pCVar8 + 0x5c);
  pCVar7 = (CCPoint *)(**(code **)(*(int *)pCVar3 + 0x60))(pCVar3);
  cocos2d::CCPoint::CCPoint(&CStack_70,extraout_s0_05,extraout_s1_03);
  cocos2d::CCPoint::operator+(&CStack_68,pCVar7);
  (*pcVar15)(pCVar8,&CStack_68);
  (**(code **)(*(int *)pCVar8 + 0x50))(pCVar8,0x3f000000);
  pCVar8 = (CCNode *)cocos2d::CCSprite::createWithSpriteFrameName("GJ_coinsIcon_001.png");
  (*((this->CCLayer).vftablePtr)->addChild)(this,pCVar8);
  pcVar15 = *(code **)(*(int *)pCVar8 + 0x5c);
  pCVar7 = (CCPoint *)(**(code **)(*(int *)pCVar3 + 0x60))(pCVar3);
  cocos2d::CCPoint::CCPoint(&CStack_60,extraout_s0_06,extraout_s1_04);
  cocos2d::CCPoint::operator+(&CStack_58,pCVar7);
  pGVar11 = (GameStatsManager *)(*pcVar15)(pCVar8,&CStack_58);
  pGVar11 = GameStatsManager::GameStatsManager(pGVar11);
  uVar9 = GameStatsManager::getStat(pGVar11,"8");
  pCVar12 = (CCString *)cocos2d::CCString::createWithFormat("%i",uVar9);
  pcVar13 = (char *)cocos2d::CCString::getCString(pCVar12);
  pCVar3 = (CCNode *)cocos2d::CCLabelBMFont::create(pcVar13,"bigFont.fnt");
  uVar19 = (*((this->CCLayer).vftablePtr)->addChild)(this,pCVar3);
  pcVar15 = *(code **)(*(int *)pCVar3 + 0x8c);
  cocos2d::CCPoint::CCPoint(&CStack_50,(float)uVar19,(float)((ulonglong)uVar19 >> 0x20));
  (*pcVar15)(pCVar3,&CStack_50);
  pcVar15 = *(code **)(*(int *)pCVar3 + 0x5c);
  pCVar7 = (CCPoint *)(**(code **)(*(int *)pCVar8 + 0x60))(pCVar8);
  cocos2d::CCPoint::CCPoint(&CStack_48,extraout_s0_07,extraout_s1_05);
  cocos2d::CCPoint::operator+(&CStack_40,pCVar7);
  (*pcVar15)(pCVar3,&CStack_40);
  (**(code **)(*(int *)pCVar3 + 0x50))(pCVar3,0x3f000000);*/
    
    return true;
}

void GJGarageLayer::onBack(CCObject* sender)
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCScene* scene = MenuLayer::scene();
    CCTransitionFade* fade = CCTransitionFade::create(0.5f, scene);
    pDirector->replaceScene(fade);
}
