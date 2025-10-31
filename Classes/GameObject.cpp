#include "GameObject.h"
#include "GameManager.h"

GameObject::GameObject() {
    this->unk_0x1b8 = 0;
    this->unk_0x1bc = 0;
    this->unk_0x1c0 = false;
//  *(_DWORD *)this = &off_486138;
    this->glowSprite = nullptr;
//  *((_DWORD *)this + 0x3A) = &off_486538;
//  *((_DWORD *)this + 0x3E) = &off_486578;
    this->unk_0x1c8 = false;
    this->unk_0x1c9 = false;
    this->myAction = nullptr;
    this->unk_0x1d0 = false;
    this->m_poweredOn = false;
    this->unk_0x1d4 = 0;
    this->unk_0x1d8 = 0;
    this->m_isActive = false;
    this->m_hasGlow = false;
    this->unk_0x1de = false;
    this->unk_0x1e0 = 0;
    this->unk_0x1e4 = 0;
    this->unk_0x1e8 = false;
    // cocos2d::CCPoint::CCPoint((GameObject *)((char *)this + 0x1EC));
    // cocos2d::CCRect::CCRect((GameObject *)((char *)this + 0x1F4));
    this->unk_0x204 = false;
    // cocos2d::CCRect::CCRect((GameObject *)((char *)this + 0x208));
    this->unk_0x218 = false;

    this->m_hasColor = false;
    this->m_colorSprite = nullptr;
    this->m_ignoreScreenCheck = false;
    this->m_radius = 0;
    this->m_isRotated = false;
    this->m_scaleModX = 0;
    this->m_scaleModY = 0;
    this->m_ID = 0;
    this->m_objectType = GameObjectType::None;
    this->m_sectionIdx = 0;
    this->m_shouldSpawn = false;
    this->m_touchTriggered = false;
    // cocos2d::CCPoint::CCPoint((GameObject *)((char *)this + 0x244));
    this->m_blendAdditive = false;
    this->m_frame = "";
    this->m_usePlayerColor = false;
    this->m_usePlayerColor2 = false;
    this->m_isDisabled = false;
    this->m_useAudioScale = false;
    this->m_isSleeping = false;
    this->m_startRotation = 0;
    this->m_startScaleX = 0;
    this->m_startScaleY = 0;
    this->m_shouldHide = false;
    this->m_spawnXPos = 0;
    this->m_isInvisible = false;
    this->m_enterAngle = 0;
    this->m_enterEffect = 0;
    this->m_tintDuration = 0;
    this->m_tintGround = false;
    this->m_objectKey = 0;
    this->m_dontTransform = false;
    this->m_dontFade = false;
    this->m_dontFadeTinted = false;
    this->m_isTintObject = false;
    this->m_triggerActivated = false;
    this->m_stateVar = false;
    this->m_objectZ = 0;
    this->m_objectParent = nullptr;
    this->m_customAudioScale = false;
    this->m_minAudioScale = 0;
    this->m_maxAudioScale = 0;
    this->m_uniqueID = 0;
    this->m_invisibleMode = false;
    this->m_glowUseBGColor = false;
    this->m_useBGColor = false;
    this->m_useSpecialLight = false;
    this->m_opacityMod = 0;
    this->m_glowOpacityMod = 0;
    this->m_dontShow = false;
    this->m_editorSelected = false;
    this->m_copyPlayerColor1 = false;
    this->m_copyPlayerColor2 = false;
    this->m_tintObjectsUseBlend = false;
}

bool GameObject::init(const char* frame) {
    if (!CCSpritePlus::initWithSpriteFrameName(frame)) return false;
    this->m_objectZ = 2;
    this->m_opacityMod = 1;
    this->m_glowOpacityMod = 1;
    this->m_enterEffect = 0;
    this->m_frame = frame;
    this->m_shouldSpawn = false;
    this->unk_0x1d4 = 0; // this + 0x138
    this->unk_0x1d8 = 0; // this + 0x13c
    // sub_3A2FE8(v9, a2, &v8);
    this->m_scaleModX = 1;
    this->m_scaleModY = 1;
    this->m_startScaleX = 1;
    this->m_startScaleY = 1;
//  this->m_ID = dword_4B6E6C;
    this->m_startRotation = 0;
    this->m_tintColor = ccc3(255, 255, 255);
    this->m_tintDuration = 0.5;
    this->setScaleX(1f);
    this->setScaleY(1f);
    this->m_isActive = false;
    this->unk_0x204 = true;
    this->unk_0x218 = true;
    this->m_tintObjectsUseBlend = true;
    return true;
}

void setScaleX(float scaleX) {
    CCSpritePlus::setScaleX(this, scaleX);
    if (this->m_glowSprite) {
        this->m_glowSprite->setScaleX(scaleX);
    }
    if (this->m_hasColor) {
        this->m_colorSprite->setScaleX(scaleX);
    }
}

void setScaleY(float scaleY) {
    CCSpritePlus::setScaleY(this, scaleY);
    if (this->m_glowSprite) {
        this->m_glowSprite->setScaleY(scaleY);
    }
    if (this->m_hasColor) {
        this->m_colorSprite->setScaleY(scaleY);
    }
}

GameObject* GameObject::create(const char* frame)
{
    static GameObject* gGameObject = NULL;
    if (!gGameObject)
    {
        gGameObject = new GameObject();
        gGameObject->init(frame);
    }
    
    return gGJGameLevel;
}

void GameObject::disableObject() {
    this->m_objectType = GameObjectType::UnknownType;
    this->m_isDisabled = true;
    this->unk_0x1e8 = false;
    this->m_opacityMod = 0.2;
}

const char* GameObject::getBallFrame(int idx) {
    return cocos2d::CCString::createWithFormat("rod_ball_%02d_001.png", idx < 3 ? idx : 3)->getCString();
}

void GameObject::triggerActivated() {
    this->m_triggerActivated = true;
}

void GameObject::removeGlow() {
    if (!this->m_glowSprite) return;
    this->m_glowSprite->release();
    this->m_glowSprite->removeMeAndCleanup();
    this->m_glowSprite = nullptr;
}

void GameObject::powerOffObject() {
    if (this->m_poweredOn)
        this->m_poweredOn = false;
}
void GameObject::powerOnObject() {
    this->m_stateVar = true;
    if (!this->m_poweredOn)
        this->m_poweredOn = true;
}
void GameObject::activateObject() {
    this->m_shouldHide = false;
    if (this->m_isActive || this->m_isSleeping) return;

    this->m_isActive = true;
    if (this->m_isInvisible) return;

    this->setVisible(true);
    if (this->unk_0x1c9)
        PLAY_LAYER->registerStateObject(this);

    if (!this->m_dontShow && this->m_objectParent)
        this->m_objectParent->addChild(this, this->m_objectZ);
        
    if (this->m_hasGlow)
        PLAY_LAYER->getBatchNodeAdd()->addChild(this->m_glowSprite);

    if (this->m_hasColor) {
        if (PLAY_LAYER->getTintObjectsUseBlend()) {
            PLAY_LAYER->getBatchNodeAdd()->addChild(this->m_glowSprite);
        } else {
            PLAY_LAYER->getBatchNode()->addChild(this->m_glowSprite);
        }
    }
    // this = (GameManager *)(*(int (**)(void))(*(_DWORD *)v13 + 0xDC))();
    if (this->unk_0x1d0 && !this->getActionByTag(11) && this->m_myAction) {
        this->runAction(m_myAction);
    }
}

void GameObject::addColorSprite() {
    if (
        ((this->m_objectKey >= 207 && this->m_objectKey < 214) ||
        (this->m_objectKey >= 215 && this->m_objectKey < 220) ||
        (this->m_objectKey >= 247 && this->m_objectKey < 262) ||
        (this->m_objectKey >= 263 && this->m_objectKey <= 275))
        && this->m_hasColor
    ) {
        // replace _001.png with _color_001.png
        std::string* colorSpriteFrame = this->m_objectKey;
        colorSpriteFrame->replace(colorSpriteFrame->find("_001.png"), "_color_001.png");
        this->m_colorSprite = cocos2d::CCSprite::createWithSpriteFrameName(colorSprite->c_str());
        this->m_colorSprite->retain();
        this->m_colorSprite->setPosition(this->getPosition());
        GameManager& gman = GameManager::sharedState();
        if (gman->getEditMode()) {
            this->m_colorSprite->setOpacity(100);
        }
    }
}