#include "CCCircleWave.h"
USING_NS_CC;

CCCircleWave::CCCircleWave() {
	m_followedObject = nullptr;
	m_width = 0.0f;
	m_radius = 0.0f;
	m_opacity = 0.0f;
	m_wavePosition = cocos2d::CCPointZero;
	m_circleMode = CircleMode::Filled;
	m_lineWidth = 0;
	m_opacityMod = 0.0f;
	m_blendAdditive = false;
	m_delegate = nullptr;
}

CCCircleWave::~CCCircleWave() {
	if (m_followedObject) {
		m_followedObject->release();
	}
}

void CCCircleWave::baseSetup(float startRadius) {
	m_radius = startRadius;
	m_opacity = 255.0f;
	m_opacityMod = 1.0f;
	m_color = cocos2d::ccc3(255, 255, 255);
	m_circleMode = CircleMode::Filled;
	m_followedObject = nullptr;
	m_lineWidth = 2;
	m_blendAdditive = true;
}

bool CCCircleWave::init(float startRadius, float endRadius, float duration, bool fadeInOut, bool easeOut) {
	baseSetup(startRadius);

	cocos2d::CCActionInterval* finalAction = nullptr;

	if (fadeInOut) {
		m_opacity = 0.0f;
		auto radiusTween = cocos2d::CCActionTween::create(duration, "radius", startRadius, endRadius);

		float halfDuration = duration * 0.5f;
		auto fadeIn = cocos2d::CCActionTween::create(halfDuration, "opacity", 0.0f, 255.0f);
		auto fadeOut = cocos2d::CCActionTween::create(halfDuration, "opacity", 255.0f, 0.0f);
		auto cleanupCall = cocos2d::CCCallFunc::create(this, callfunc_selector(CCCircleWave::removeMeAndCleanup));

		auto alphaSeq = cocos2d::CCSequence::create(fadeIn, fadeOut, cleanupCall, nullptr);
		finalAction = cocos2d::CCSpawn::create(radiusTween, alphaSeq, nullptr);
	}
	else {
		cocos2d::CCActionInterval* radiusTween = cocos2d::CCActionTween::create(duration, "radius", startRadius, endRadius);
		if (easeOut) {
			radiusTween = cocos2d::CCEaseOut::create(radiusTween, 2.0f);
		}

		cocos2d::CCActionInterval* opacityTween = cocos2d::CCActionTween::create(duration, "opacity", m_opacity, 0.0f);
		if (easeOut) {
			opacityTween = cocos2d::CCEaseOut::create(opacityTween, 2.0f);
		}

		auto spawn = cocos2d::CCSpawn::create(radiusTween, opacityTween, nullptr);
		auto cleanupCall = cocos2d::CCCallFunc::create(this, callfunc_selector(CCCircleWave::removeMeAndCleanup));
		finalAction = cocos2d::CCSequence::create(spawn, cleanupCall, nullptr);
	}

	cocos2d::CCActionManager* actionManager = cocos2d::CCDirector::sharedDirector()->getActionManager();
	actionManager->addAction(finalAction, this, false);

	return true;
}

CCCircleWave* CCCircleWave::create(float startRadius, float endRadius, float duration, bool fadeInOut, bool easeOut) {
	CCCircleWave* pRet = new CCCircleWave();
	if (pRet && pRet->init(startRadius, endRadius, duration, fadeInOut, easeOut)) {
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return nullptr;
}

CCCircleWave* CCCircleWave::create(float startRadius, float endRadius, float duration, bool fadeInOut) {
	return CCCircleWave::create(startRadius, endRadius, duration, fadeInOut, true);
}

void CCCircleWave::draw() {
	if (m_blendAdditive) {
		cocos2d::ccGLBlendFunc(GL_SRC_ALPHA, GL_ONE);
	}

	GLfloat currentLineWidth;
	glGetFloatv(GL_LINE_WIDTH, &currentLineWidth);
	if (currentLineWidth != (GLfloat)m_lineWidth) {
		glLineWidth((GLfloat)m_lineWidth);
	}

	float calculatedAlpha = m_opacity * m_opacityMod;
	GLubyte finalAlpha = 0;
	if (calculatedAlpha > 0.0f) {
		finalAlpha = (calculatedAlpha >= 255.0f) ? 255 : (GLubyte)calculatedAlpha;
	}

	cocos2d::ccDrawColor4B(m_color.r, m_color.g, m_color.b, finalAlpha);

	int segments = (m_radius <= 200.0f) ? 30 : 50;

	if (m_circleMode == CircleMode::Outline) {
		cocos2d::ccDrawCircle(m_wavePosition, m_radius, 0.0f, segments, false);
	}
	else {
		cocos2d::CCPoint* vertices = new cocos2d::CCPoint[segments];
		float coef = 2.0f * (float)M_PI / segments;
		for (int i = 0; i < segments; ++i) {
			float rads = i * coef;
			vertices[i].x = m_radius * cosf(rads) + m_wavePosition.x;
			vertices[i].y = m_radius * sinf(rads) + m_wavePosition.y;
		}
		cocos2d::ccDrawSolidPoly(vertices, segments, cocos2d::ccc4f(m_color.r / 255.0f, m_color.g / 255.0f, m_color.b / 255.0f, finalAlpha / 255.0f));
		delete[] vertices;
	}

	if (m_blendAdditive) {
		cocos2d::ccGLBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	}
}

void CCCircleWave::updatePosition(float dt) {
	if (m_followedObject) {
		m_wavePosition = m_followedObject->getPosition();
		this->setPosition(m_wavePosition);
	}
}

void CCCircleWave::updateTweenAction(float value, const char* key) {
	if (strcmp(key, "opacity") == 0) {
		m_opacity = value;
	}
	else if (strcmp(key, "radius") == 0) {
		m_radius = value;
	}

	if (m_followedObject) {
		m_wavePosition = m_followedObject->getPosition();
		this->setPosition(m_wavePosition);
	}
}

void CCCircleWave::followObject(cocos2d::CCNode* target, bool manualUpdate) {
	if (m_followedObject) {
		m_followedObject->release();
	}
	m_followedObject = target;
	if (m_followedObject) {
		m_followedObject->retain();
	}

	this->unschedule(schedule_selector(CCCircleWave::updatePosition));
	if (!manualUpdate) {
		this->schedule(schedule_selector(CCCircleWave::updatePosition));
	}

	if (m_followedObject) {
		m_wavePosition = m_followedObject->getPosition();
		this->setPosition(m_wavePosition);
	}
}

void CCCircleWave::removeMeAndCleanup() {
	if (m_delegate) {
		m_delegate->onRemove(this);
	}
	this->removeFromParentAndCleanup(true);
}