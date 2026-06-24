#include "CCCircleWave.h"

USING_NS_CC;

CCCircleWave::CCCircleWave() {
	m_width = 0.0f;
	m_targetNode = nullptr;
	m_radius = 0.0f;
	m_opacity = 0.0f;
	m_positionInternal = CCPointZero;
	m_circleMode = CircleMode::Filled;
	m_lineWidth = 0;
	m_opacityMod = 0.0f;
	m_blendAdditive = false;
	m_delegate = nullptr;
}

CCCircleWave::~CCCircleWave() {
	CC_SAFE_RELEASE(m_targetNode);
}

CCCircleWave* CCCircleWave::create(float radius, float duration, float speed, bool fadeOut, bool easeOut) {
	CCCircleWave* pRet = new CCCircleWave();
	if (pRet && pRet->init(radius, duration, speed, fadeOut, easeOut)) {
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return nullptr;
}

CCCircleWave* CCCircleWave::create(float radius, float duration, float speed, bool fadeOut) {
	return CCCircleWave::create(radius, duration, speed, fadeOut, true);
}

void CCCircleWave::baseSetup(float radius) {
	m_radius = radius;
	m_opacity = 255.0f; // Hex 0x437F0000 = 255.0f
	m_opacityMod = 1.0f; // Hex 0x3F800000 = 1.0f

	m_color = ccc3(255, 255, 255);

	m_circleMode = CircleMode::Filled;
	m_targetNode = nullptr;
	m_lineWidth = 2;
	m_blendAdditive = true;
}

bool CCCircleWave::init(float radius, float duration, float speed, bool fadeOut, bool easeOut) {
	this->baseSetup(radius);

	CCFiniteTimeAction* radiusAction = nullptr;
	CCFiniteTimeAction* opacityAction = nullptr;

	if (fadeOut) {
		radiusAction = CCActionTween::create(speed, "radius", m_radius, duration);

		float halfSpeed = speed * 0.5f;
		auto fadeIn = CCActionTween::create(halfSpeed, "opacity", m_opacity, 255.0f);
		auto fadeOutSeq = CCActionTween::create(halfSpeed, "opacity", 255.0f, 0.0f);
		auto cleanupCall = CCCallFunc::create(this, callfunc_selector(CCCircleWave::removeMeAndCleanup));

		opacityAction = CCSequence::create(fadeIn, fadeOutSeq, cleanupCall, nullptr);

		auto masterSpawn = CCSpawn::create(radiusAction, opacityAction, nullptr);
		CCDirector::sharedDirector()->getActionManager()->addAction(masterSpawn, this, false);
	}
	else {
		auto rawRadius = CCActionTween::create(speed, "radius", m_radius, duration);
		radiusAction = easeOut ? CCEaseOut::create(rawRadius, 2.0f) : static_cast<CCActionInterval*>(rawRadius);

		auto rawOpacity = CCActionTween::create(speed, "opacity", m_opacity, 0.0f);
		opacityAction = easeOut ? CCEaseOut::create(rawOpacity, 2.0f) : static_cast<CCActionInterval*>(rawOpacity);

		auto actionSpawn = CCSpawn::create(radiusAction, opacityAction, nullptr);
		auto cleanupCall = CCCallFunc::create(this, callfunc_selector(CCCircleWave::removeMeAndCleanup));
		auto fullSequence = CCSequence::create(actionSpawn, cleanupCall, nullptr);

		CCDirector::sharedDirector()->getActionManager()->addAction(fullSequence, this, false);
	}

	return true;
}

void CCCircleWave::draw() {
	if (m_blendAdditive) {
		ccGLBlendFunc(GL_SRC_ALPHA, GL_ONE);
	}

	GLfloat currentLineWidth = 1.0f;
	glGetFloatv(GL_LINE_WIDTH, &currentLineWidth);
	if (currentLineWidth != (float)m_lineWidth) {
		glLineWidth((float)m_lineWidth);
	}

	float calculatedAlpha = m_opacity * m_opacityMod;
	GLubyte finalAlpha = 0;
	if (calculatedAlpha >= 255.0f) {
		finalAlpha = 255;
	}
	else if (calculatedAlpha > 0.0f) {
		finalAlpha = (GLubyte)calculatedAlpha;
	}

	int segments = (m_radius <= 200.0f) ? 30 : 50;

	if (m_circleMode == CircleMode::Outline) {
		ccDrawColor4B(m_color.r, m_color.g, m_color.b, finalAlpha);
		ccDrawCircle(m_positionInternal, m_radius, 0.0f, segments, false);
	}
	else {
		ccVertex2F* vertices = new ccVertex2F[segments];
		const float coef = 2.0f * (float)M_PI / segments;

		for (int i = 0; i < segments; ++i) {
			float rads = i * coef;
			vertices[i].x = m_radius * cosf(rads) + m_positionInternal.x;
			vertices[i].y = m_radius * sinf(rads) + m_positionInternal.y;
		}

		ccColor4F solidColor = ccc4FFromccc4B(ccc4(m_color.r, m_color.g, m_color.b, finalAlpha));

		ccDrawSolidPoly(reinterpret_cast<CCPoint*>(vertices), segments, solidColor);

		delete[] vertices;
	}

	if (m_blendAdditive) {
		ccGLBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
}

void CCCircleWave::updatePosition(float dt) {
	if (m_targetNode) {
		this->setPosition(m_targetNode->getPosition());
	}
}

void CCCircleWave::updateTweenAction(float value, const char* key) {
	std::string keyStr(key);
	if (keyStr == "opacity") {
		m_opacity = value;
	}
	else if (keyStr == "radius") {
		m_radius = value;
	}

	if (m_targetNode) {
		this->setPosition(m_targetNode->getPosition());
	}
}

int CCCircleWave::followObject(cocos2d::CCNode* target, bool snapToPosition) {
	if (m_targetNode) {
		m_targetNode->release();
	}

	m_targetNode = target;
	if (m_targetNode) {
		m_targetNode->retain();
	}

	this->unschedule(schedule_selector(CCCircleWave::updatePosition));

	if (!snapToPosition) {
		this->schedule(schedule_selector(CCCircleWave::updatePosition), 0.0f);
	}

	if (m_targetNode) {
		this->setPosition(m_targetNode->getPosition());
	}
	return 1;
}

void CCCircleWave::removeMeAndCleanup() {
	if (m_delegate) {
		m_delegate->circleWaveWillBeRemoved(this);
	}
	this->removeFromParentAndCleanup(true);
}