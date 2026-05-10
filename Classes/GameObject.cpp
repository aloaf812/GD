#include "GameObject.h"
#include "ObjectToolbox.h"
#include "GameManager.h"
USING_NS_CC;

// hi antimatter some of your code was kind of broken so i fixed it up

GameObject::GameObject() {
    this->unk_0x1b8 = 0;
    this->unk_0x1bc = 0;
    this->unk_0x1c0 = false;
    //  *(_DWORD *)this = &off_486138;
    this->m_glowSprite = nullptr;
    //  *((_DWORD *)this + 0x3A) = &off_486538;
    //  *((_DWORD *)this + 0x3E) = &off_486578;
    this->unk_0x1c8 = false;
    this->unk_0x1c9 = false;
    this->m_myAction = nullptr;
    this->unk_0x1d0 = false;
    this->m_poweredOn = false;
    this->unk_0x1d4 = 0;
    this->unk_0x1d8 = 0;
    this->m_isActive = false;
    this->m_hasGlow = false;
    this->unk_0x1de = false;
    this->m_particleSystem = nullptr;
	this->m_particleString = "";
    this->m_particleAdded = false;
    // cocos2d::CCPoint::CCPoint((GameObject *)((char *)this + 0x1EC));
    // cocos2d::CCRect::CCRect((GameObject *)((char *)this + 0x1F4));
    this->unk_0x204 = false;
    // cocos2d::CCRect::CCRect((GameObject *)((char *)this + 0x208));
    this->unk_0x218 = false;
	this->m_hasColor = false;
    this->m_colorSprite = nullptr;
    this->m_ignoreScreenCheck = false;
    this->m_radius = 0.0f;
	this->m_isRotated = false;
    this->m_scaleModX = 0;
    this->m_scaleModY = 0;
    this->m_ID = 0;
    this->m_type = GameObjectType::None;
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
    this->m_hasBeenActivated = false;
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
bool GameObject::init(const char *spriteName) {
    if (!CCSpritePlus::initWithSpriteFrameName(spriteName)) return false;
    this->m_objectZ = 2;
    this->m_opacityMod = 1.0f;
    this->m_glowOpacityMod = 1.0f;
    this->m_enterEffect = 0;
    this->m_frame = spriteName;
    this->m_shouldSpawn = false;
    // this->unk_0x1d4 = 0; // this + 0x138
    // this->unk_0x1d8 = 0; // this + 0x13c
    this->m_scaleModX = 1;
    this->m_scaleModY = 1;
    this->m_startScaleX = 1;
    this->m_startScaleY = 1;
    //  this->m_ID = dword_4B6E6C;
    this->m_startRotation = 0.0f;
    this->m_tintColor = ccc3(255, 255, 255);
    this->m_tintDuration = 0.5f;
    this->setScaleX(1.0f);
    this->setScaleY(1.0f);
    this->m_isActive = false;
    this->unk_0x204 = true;
    this->unk_0x218 = true;
    this->m_tintObjectsUseBlend = true;
    return true;
}

GameObject* GameObject::create(const char* frame)
{
	GameObject *pRet = new GameObject();
	if (pRet && pRet->init(frame))
	{
		pRet->autorelease();
		return pRet;
	}

	CC_SAFE_DELETE(pRet);
	return NULL;
}

GameObject* GameObject::objectFromString(std::string objString)
{
	CCDictionary* objDict = ObjectToolbox::stringSetupToDict(objString);



	char const* key = objDict->valueForKey("1")->getCString();
	int objID = atoi(key);
	char const* frame = ObjectToolbox::sharedState()->keyToFrame(key);

	if (!objID)
		return nullptr;

	GameObject* object;

	if (objID == 84 || objID == 36 || objID == 141) {
		// object = RingObject::create();
		return nullptr;
	}
	else {
		object = GameObject::create(frame);
		object->setObjectKey(objID);
		object->setPosition(ccp(objDict->valueForKey("2")->floatValue(), objDict->valueForKey("3")->floatValue() + 90.0f));
	}

	object->setObjectKey(objID);

	return object;
}

void GameObject::disableObject() {
	this->m_type = GameObjectType::Decoration;
    this->m_isDisabled = true;
	this->m_particleAdded = false;
    this->m_opacityMod = 0.2f;
}

const char* GameObject::getBallFrame(int idx) {
    return cocos2d::CCString::createWithFormat("rod_ball_%02d_001.png", idx < 3 ? idx : 3)->getCString();
}

/*void GameObject::triggerActivated() {
    this->m_triggerActivated = true;
}

void GameObject::removeGlow() {
    if (!this->m_glowSprite) return;
    this->m_glowSprite->release();
    this->m_glowSprite->removeMeAndCleanup();
    this->m_glowSprite = nullptr;
}*/

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

/*void GameObject::addColorSprite() {
    if (
        ((this->m_objectKey >= 207 && this->m_objectKey < 214) ||
         (this->m_objectKey >= 215 && this->m_objectKey < 220) ||
         (this->m_objectKey >= 247 && this->m_objectKey < 262) ||
         (this->m_objectKey >= 263 && this->m_objectKey <= 275))
        && this->m_hasColor
        ) {
        // replace _001.png with _color_001.png
        std::string colorSpriteFrame = CCString::createWithFormat("%i", this->m_objectKey)->getCString();
        // this isn't how it works but it also kind of works
        colorSpriteFrame.replace(0, colorSpriteFrame.find("_001.png"), "_color_001.png");
        this->m_colorSprite = cocos2d::CCSprite::createWithSpriteFrameName(colorSpriteFrame.c_str());
        this->m_colorSprite->retain();
        this->m_colorSprite->setPosition(this->getPosition());
        GameManager* gman = GameManager::sharedState();
        if (gman->getEditMode()) {
            this->m_colorSprite->setOpacity(100);
        }
    }
}*/

void GameObject::setFlipX(bool flipX) {
    CCSpritePlus::setFlipX(flipX);

    /*if (this->m_glowSprite) {
        m_glowSprite->setFlipX(flipX);
    }
    if (this->m_hasColor) {
        m_colorSprite->setFlipX(flipX);
    }*/
}

void GameObject::setFlipY(bool flipY) {
    CCSpritePlus::setFlipY(flipY);
    /*if (this->m_glowSprite) {
        m_glowSprite->setFlipY(flipY);
    }
    if (this->m_hasColor) {
        m_colorSprite->setFlipY(flipY);
    }*/
}

/*void GameObject::setScaleX(float scaleX) {
    CCSpritePlus::setScaleX(scaleX);
    if (this->m_glowSprite) {
        this->m_glowSprite->setScaleX(scaleX);
    }
    if (this->m_hasColor) {
        m_colorSprite->setScaleX(scaleX);
    }
}

void GameObject::setScaleY(float scaleY) {
    CCSpritePlus::setScaleY(scaleY);
    if (this->m_glowSprite) {
        this->m_glowSprite->setScaleY(scaleY);
    }
    if (this->m_hasColor) {
        m_colorSprite->setScaleY(scaleY);
    }
}*/

void GameObject::resetObject() {
    this->m_hasBeenActivated = false;
    this->m_isSleeping = false;
    this->unk_0x1de = false;
}

/*void GameObject::setGlowColor(cocos2d::ccColor3B color) {
    if (this->m_glowSprite) {
        this->m_glowSprite->setColor(color);
    }
}*/

void GameObject::setPosition(cocos2d::CCPoint const &position) {
    this->unk_0x218 = true;
    CCSpritePlus::setPosition(position);
    if (this->m_particleSystem) {
        // this->m_particleSystem->setPosition()
    }
}

/*CCRepeatForever* GameObject::createRotateAction(float duration) {
    int sign;
    if (rand() / RAND_MAX < 0.5) {
        sign = -1;
    } else {
        sign = 1;
    }
    return cocos2d::CCRepeatForever::create(cocos2d::CCRotateBy::create(1, duration * sign));
}

void GameObject::setVisible(bool visible) {
    if (this->unk_0x1e8 && this->isVisible() != visible) {
        if (visible) {
            this->m_particleSystem = PLAY_LAYER->claimParticle(this->unk_0x1e4);
            this->setPosition(this->getPosition());
            if (this->m_particleSystem) {
                PLAY_LAYER->getGameLayer();
                CCPoint point = this-> + this->unk_0x1ec;
            }
        } else {
            
        }
    }
    cocos2d::CCSprite::setVisible(visible);
}*/

void GameObject::updateState()
{
	if (!m_stateVar) {
		this->powerOffObject();
	}
}

void GameObject::customSetup()
{
	GameManager* pGameManager = GameManager::sharedState();

	switch (m_objectKey) {
	case 5:
	case 73:
	case 74:
		// ok skip some of this
	case 246:
		m_type = GameObjectType::Decoration;
		m_objectZ = -2;
	default:
		if (m_frame.find("edit_e", 0)) {
			m_type = GameObjectType::None;
			break;
		}
		m_type = GameObjectType::Decoration;
		m_shouldSpawn = true;
		// field_0x1c8 = 1;
		m_isInvisible = true;
		// field468_0x1d4 = 30.0f;
		// field469_0x1d = 60.0f
		break;
	case 8:
	case 39:
	case 103:
	case 177:
	case 178:
	case 179:
	case 216:
	case 217:
	case 218:
		this->m_type = GameObjectType::Hazard;
		this->m_scaleModX = 0.2f;
		this->m_scaleModY = 0.4f;
		/*if (iVar11 - 0xb1U < 3)
			this->field_0x2a9 = 1;*/
		break;
	// more left
	case 13:
		this->m_type = GameObjectType::ShipPortal;
		this->m_objectZ = 10;
		if (pGameManager->getEditMode()) break;
		this->createAndAddParticle(m_type, "portalEffect04.plist", 3, tCCPositionType::kCCPositionTypeGrouped);
		break;
	// skipping
	case 211:
		m_type = GameObjectType::Decoration;
		m_objectZ = -2;
		// m_dontFadeTinted = true;
		// m_dontFade = true;
		// m_dontShow = true;
		break;
	// skipping some
	case 273:
		m_type = GameObjectType::Decoration;
		// m_dontShow = true;
		m_objectZ = -2;
	}

	//if (m_type - 7 < 2)
		//m_isDisabled = true;
}

CCRect GameObject::getObjectRect()
{
	return getObjectRect2(m_scaleModX, m_scaleModY);
}

CCRect GameObject::getObjectRect(float scaleModX, float scaleModY)
{
	// this function seems a bit complicated, will finish later
	return CCRectMake(0, 0, scaleModX, scaleModY);
}

CCRect GameObject::getObjectRect2(float scaleModX, float scaleModY)
{
	if (unk_0x218) {
		unk_0x218 = true;
		unk_0x208 = getObjectRect(scaleModX, scaleModY);
	}
	return unk_0x208;
}

void GameObject::createAndAddParticle(int objType, char const* file, int zOrder, cocos2d::tCCPositionType positionType)
{
	PLAY_LAYER->createParticle(objType, file, zOrder, positionType);
	m_particleString = PLAY_LAYER->getParticleKey(objType, file, zOrder, positionType);
	m_particleAdded = true;
}

void GameObject::triggerObject()
{
	// todo
}