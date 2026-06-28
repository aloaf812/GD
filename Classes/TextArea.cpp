// decompiled by ItzZyann
#include "TextArea.h"
USING_NS_CC;

TextArea::TextArea()
	: m_label(NULL)
	, m_width(0.0f)
	, m_order(0)
	, m_lineSpace(0.0f)
	, m_onTimer(false)
	, m_align(ccp(0.0f, 0.0f))
	, m_fadeInFinished(false)
	, m_textHeight(0.0f)
	, m_textWidth(0.0f)
	, m_sizeWidth(0.0f)
	, m_textPosition(ccp(0.0f, 0.0f))
{
}

void TextArea::onExit()
{
	if (m_label) {
		m_label->stopAllActions();
		m_label->removeFromParentAndCleanup(true);
		m_label = nullptr;
	}
	CCSprite::onExit();
}

bool TextArea::init(char const* text, float width, int order, cocos2d::CCPoint align, char const* fontFile, float height)
{
	if (!CCSprite::init()) return false;

	m_order = order;
	m_width = width;
	m_align = align;
	m_fontFileName = fontFile;
	m_lineSpace = height;

	this->setString(text);
	return true;
}

TextArea* TextArea::create(char const* text, float width, int order, cocos2d::CCPoint align, char const* fontFile, float height)
{
	TextArea* pRet = new TextArea();
	if (pRet && pRet->init(text, width, order, align, fontFile, height)) {
		pRet->autorelease();
		return pRet;
	}
	delete pRet;
	return NULL;
}

TextArea* TextArea::create(char const* text, float width, int order, cocos2d::CCPoint align, char const* fontFile)
{
	return TextArea::create(text, width, order, align, fontFile, 20.0f);
}

void TextArea::setString(char const* text)
{
	if (m_label) {
		this->hideAll();
		m_label->removeFromParentAndCleanup(true);
		m_label = nullptr;
	}

	std::string processedText = (text && *text) ? text : " ";
	size_t pos = 0;
	while ((pos = processedText.find("\\n", pos)) != std::string::npos) {
		processedText.replace(pos, 2, "\n");
		pos += 1;
	}

	m_label = MultilineBitmapFont::createWithFont(
		m_fontFileName.c_str(),
		processedText.c_str(),
		1.0f,
		m_width,
		&m_align,
		m_lineSpace
		);

	// FIX: MultilineBitmapFont lines are laid out starting at y=0 going downward,
	// so offset the label up by m_textHeight to align top of text with TextArea origin.
	// Also set content size from actual text dimensions instead of the sprite default (0,0).
	this->setContentSize(CCSize(m_width, m_label->getTextHeight() + m_label->getSizeHeight()));
	this->addChild(m_label, 1);
	m_label->setPosition(ccp(m_width * 0.5f, m_label->getTextHeight()));
}

void TextArea::hideAll()
{
	this->stopAllCharacterActions();
	this->setOpacity(0);
}

void TextArea::showAll()
{
	this->stopAllCharacterActions();
	this->setOpacity(255);
	m_fadeInFinished = true;
}

void TextArea::stopAllCharacterActions()
{
	if (!m_label) return;

	CCArray* lines = m_label->getChildren();
	if (!lines) return;

	for (int i = 0; i < lines->count(); ++i) {
		CCNode* line = static_cast<CCNode*>(lines->objectAtIndex(i));
		CCArray* chars = line->getChildren();
		if (chars) {
			for (int j = 0; j < chars->count(); ++j) {
				static_cast<CCNode*>(chars->objectAtIndex(j))->stopAllActions();
			}
		}
	}
}

void TextArea::colorAllCharactersTo(ccColor3B color)
{
	if (!m_label) return;

	CCArray* lines = m_label->getChildren();
	if (!lines) return;

	for (int i = 0; i < lines->count(); ++i) {
		CCNode* line = static_cast<CCNode*>(lines->objectAtIndex(i));
		CCArray* chars = line->getChildren();
		if (chars) {
			for (int j = 0; j < chars->count(); ++j) {
				CCRGBAProtocol* charNode = dynamic_cast<CCRGBAProtocol*>(chars->objectAtIndex(j));
				if (charNode) charNode->setColor(color);
			}
		}
	}
}