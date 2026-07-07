#include "GameObject.h"
#include "ObjectToolbox.h"
#include "GameManager.h"
USING_NS_CC;

// hi antimatter some of your code was kind of broken so i fixed it up

GameObject::GameObject() {
	unk_0x1b8 = 0;
	unk_0x1bc = 0;
	unk_0x1c0 = false;
	m_glowSprite = nullptr;
	unk_0x1c8 = false;
	unk_0x1c9 = false;
	m_myAction = nullptr;
	unk_0x1d0 = false;
	m_poweredOn = false;
	unk_0x1d4 = 0.0f;
	unk_0x1d8 = 0.0f;
	m_isActive = false;
	m_hasGlow = false;
	unk_0x1de = false;
	m_particleSystem = nullptr;
	m_particleString = "";
	m_particleAdded = false;
	unk_0x204 = false;
	unk_0x218 = false;
	m_hasColor = false;
	m_colorSprite = nullptr;
	m_ignoreScreenCheck = false;
	m_radius = 0.0f;
	m_isRotated = false;
	m_scaleModX = 0.0f;
	m_scaleModY = 0.0f;
	m_ID = 0;
	m_type = None;
	m_sectionIdx = 0;
	m_shouldSpawn = false;
	m_touchTriggered = false;
	m_startPos = CCPointZero;
	m_blendAdditive = false;
	m_frame = "";
	m_usePlayerColor = false;
	m_usePlayerColor2 = false;
	m_isDisabled = false;
	m_useAudioScale = false;
	m_isSleeping = false;
	m_startRotation = 0.0f;
	m_startScaleX = 0.0f;
	m_startScaleY = 0.0f;
	m_shouldHide = false;
	m_spawnXPos = 0;
	m_isInvisible = false;
	m_enterAngle = 0.0f;
	m_enterEffect = 0;
	m_tintDuration = 0.0f;
	m_tintGround = false;
	m_objectKey = 0;
	m_dontTransform = false;
	m_dontFade = false;
	m_dontFadeTinted = false;
	m_isTintObject = false;
	m_hasBeenActivated = false;
	m_stateVar = false;
	m_objectZ = 0;
	m_objectParent = nullptr;
	m_customAudioScale = false;
	m_minAudioScale = 0.0f;
	m_maxAudioScale = 0.0f;
	m_uniqueID = 0;
	m_invisibleMode = false;
	m_glowUseBGColor = false;
	m_useBGColor = false;
	m_useSpecialLight = false;
	m_opacityMod = 1.0f;
	m_glowOpacityMod = 1.0f;
	m_dontShow = false;
	m_editorSelected = false;
	m_copyPlayerColor1 = false;
	m_copyPlayerColor2 = false;
	m_tintObjectsUseBlend = false;
}

bool GameObject::init(const char *spriteName) {
    if (!CCSpritePlus::initWithSpriteFrameName(spriteName)) return false;
    m_objectZ = 2;
    m_opacityMod = 1.0f;
    m_glowOpacityMod = 1.0f;
    m_enterEffect = 0;
    m_frame = spriteName;
    m_shouldSpawn = false;
	// set to 0.1f for now since i just CANNOT figure out what these variables are, probably some inlined functions in CCSprite...
	unk_0x1d4 = 1.0f; // 0x138
	unk_0x1d8 = 1.0f; // 0x13c
    m_scaleModX = 1.0f;
    m_scaleModY = 1.0f;
    m_startScaleX = 1.0f;
    m_startScaleY = 1.0f;
    //  this->m_ID = dword_4B6E6C;
    m_startRotation = 0.0f;
    m_tintColor = ccc3(255, 255, 255);
    m_tintDuration = 0.5f;
    setScaleX(1.0f);
    setScaleY(1.0f);
    m_isActive = false;
    unk_0x204 = true;
    unk_0x218 = true;
    m_tintObjectsUseBlend = true;
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
	if (!objDict) return nullptr;

	if (!objDict->objectForKey("1")) return nullptr;
	int objID = atoi(objDict->valueForKey("1")->getCString());
	if (!objID) return nullptr;

	const char* frame = ObjectToolbox::sharedState()->keyToFrame(objDict->valueForKey("1")->getCString());

	float x = objDict->valueForKey("2")->floatValue();
	float y = objDict->valueForKey("3")->floatValue();
	bool flipX = objDict->objectForKey("4") ? objDict->valueForKey("4")->boolValue() : false;
	bool flipY = objDict->objectForKey("5") ? objDict->valueForKey("5")->boolValue() : false;
	int rotation = objDict->objectForKey("6") ? objDict->valueForKey("6")->intValue() : 0;

	GameObject* object = GameObject::create(frame);
	if (!object) return nullptr;

	object->setObjectKey(objID);
	object->setFlipX(flipX);
	object->setFlipY(flipY);
	object->setRotation((float)rotation);

	CCPoint startPos = ccp(x, y + 90.0f);
	object->m_startPos = startPos;
	object->setPosition(startPos);

	object->customSetup();
	object->calculateSpawnXPos();

	return object;

	// old thing i was doing, keeping it here just in case..
	/*CCDictionary* objDict = ObjectToolbox::stringSetupToDict(objString);

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
	object->customSetup();

	return object;*/
}

void GameObject::disableObject() {
	m_type = GameObjectType::Decoration;
    m_isDisabled = true;
	m_particleAdded = false;
    m_opacityMod = 0.2f;
}

const char* GameObject::getBallFrame(int idx) {
    return cocos2d::CCString::createWithFormat("rod_ball_%02d_001.png", idx < 3 ? idx : 3)->getCString();
}

void GameObject::triggerActivated() {
    this->m_hasBeenActivated = true;
}

void GameObject::removeGlow() {
    if (!m_glowSprite) return;
    m_glowSprite->release();
    m_glowSprite->removeMeAndCleanup();
    m_glowSprite = nullptr;
}

void GameObject::powerOnObject() {
    this->m_stateVar = true;
    if (!this->m_poweredOn)
        this->m_poweredOn = true;
}
void GameObject::powerOffObject() {
    if (this->m_poweredOn)
        this->m_poweredOn = false;
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

    if (this->m_glowSprite) {
        m_glowSprite->setFlipX(flipX);
    }
    if (this->m_hasColor) {
        m_colorSprite->setFlipX(flipX);
    }
}

void GameObject::setFlipY(bool flipY) {
    CCSpritePlus::setFlipY(flipY);
    if (this->m_glowSprite) {
        m_glowSprite->setFlipY(flipY);
    }
    if (this->m_hasColor) {
        m_colorSprite->setFlipY(flipY);
    }
}

void GameObject::setScaleX(float scaleX) {
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
}

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
    if (m_particleSystem) {
		m_particleSystem->setPosition(position);
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
	switch (m_objectKey) {
	case 5:
	case 73:
	case 80:
	case 120:
	case 164:
	case 191:
	case 193:
	case 198:
	case 199:
	case 245:
	case 246:
		m_type = GameObjectType::Decoration;
		m_objectZ = -2;
		break;
	default:
		if (m_frame.find("edit_e", 0)) {
			m_type = GameObjectType::None;
			break;
		}
		m_type = GameObjectType::Decoration;
		m_shouldSpawn = true;
		unk_0x1c8 = true;
		m_isInvisible = true;
		unk_0x1d4 = 30.0f;
		unk_0x1d8 = 60.0f;
		break;
	case 8:
	case 39:
	case 103:
	case 117:
	case 118:
	case 119:
	case 216:
	case 217:
	case 218:
		m_type = GameObjectType::Hazard;
		m_scaleModX = 0.2f;
		m_scaleModY = 0.4f;
		if (m_objectKey - 117U < 3) {
			m_glowUseBGColor = true;
		}
		break;
	}

	// if (((uVar13 < 0xf) && ((1 << (uVar13 & 0xff) & 0x7002U) != 0)) || (this->m_objectKey == 8)) {
	if (m_objectKey == 8) {
		unk_0x1d4 = 30.0f;
		unk_0x1d8 = 30.0f;
	}

	/*if (m_touchTriggered) {
		m_type = GameObjectType::unk21;
		m_isDisabled = false;
	}*/
}

CCRect GameObject::getObjectRect()
{
	return getObjectRect2(m_scaleModX, m_scaleModY);
}

CCRect GameObject::getObjectRect(float scaleModX, float scaleModY)
{
	CCSize objSize = CCSizeMake(unk_0x1d4, unk_0x1d8);

	float newSizeWidth = scaleModX * objSize.width;
	float newSizeHeight = scaleModY * objSize.height;

	objSize.width = scaleModX * objSize.width;
	objSize.height = scaleModY * objSize.height;

	// This inverses the values (i assume this was changed in update 2.0 when free rotate was added)
	if (m_isRotated) {
		objSize.width = newSizeHeight;
		objSize.height = newSizeWidth;
	}

	CCPoint realPos = getRealPosition();
	return CCRectMake(realPos.x - objSize.width * 0.5f, realPos.y - objSize.height * 0.5f, objSize.width, objSize.height);
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

void GameObject::deactivateObject()
{
	// todo
}

CCRect GameObject::getObjectTextureRect()
{
	// todo
	return CCRect();
}

CCPoint GameObject::getRealPosition()
{
	return m_startPos;
}

void GameObject::setStartPos(CCPoint position)
{
	m_startPos = position;
	this->setPosition(position);
}

std::string GameObject::getSaveString()
{
	// this is like a pretty big function and i don't know if it's worth decompiling yet
	return "";
}

void GameObject::calculateSpawnXPos()
{
	m_spawnXPos = m_startPos.x;
}