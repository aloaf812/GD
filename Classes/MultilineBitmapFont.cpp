// decompiled by ItzZyann
#include "MultilineBitmapFont.h"
#include "ColoredSection.h"

USING_NS_CC;

MultilineBitmapFont* MultilineBitmapFont::createWithFont(
	const char* fontFile,
	const char* text,
	float scale,
	float width,
	cocos2d::CCPoint* align,
	float lineSpace)
{
	MultilineBitmapFont* pRet = new MultilineBitmapFont();

	if (pRet && pRet->initWithFont(fontFile, text, scale, width, align, lineSpace))
	{
		pRet->autorelease();
		return pRet;
	}

	delete pRet;
	return NULL;
}

bool MultilineBitmapFont::initWithFont(
	const char* fontFile,
	const char* text,
	float scale,
	float width,
	cocos2d::CCPoint* align,
	float lineSpace)
{
	if (!cocos2d::CCSprite::init())
	{
		return false;
	}

	float scaleFactor = cocos2d::CCDirector::sharedDirector()->getContentScaleFactor();
	float maxWidth = width * scaleFactor;

	m_lines = cocos2d::CCArray::create();
	m_lines->retain();

	m_characters = cocos2d::CCArray::create();
	m_characters->retain();

	m_unkArray = cocos2d::CCArray::create();
	m_unkArray->retain();

	BitmapFontCache* fontCache = BitmapFontCache::sharedFontCache();
	FontObject* fontObject = fontCache->fontWithConfigFile(fontFile, scale);

	for (int i = 0; i < 300; ++i)
	{
		this->m_fontWidths[i] = fontObject->getFontWidth(i);
	}

	std::string coloredText;
	this->readColorInfo(&coloredText, this, text);

	int currentYOffset = 0;
	int totalProcessedChars = 0;
	int lineCount = 0;

	while (coloredText.length() > 0)
	{
		std::string lineStr;
		this->stringWithMaxWidth(&lineStr, this, coloredText, maxWidth, scale);

		cocos2d::CCLabelBMFont* labelLine = cocos2d::CCLabelBMFont::create(lineStr.c_str(), fontFile);
		labelLine->setPosition(cocos2d::CCPointMake(0.0f, (float)currentYOffset));
		labelLine->setScale(scale);

		float currentHeight = m_sizeHeight;
		float labelHeight = labelLine->getContentSize().height;
		if (currentHeight < (labelHeight * labelLine->getScaleY()))
		{
			m_sizeHeight = labelHeight * labelLine->getScaleY();
		}

		labelLine->setAnchorPoint(*align);

		if (labelLine->getAnchorPoint().x == 0.5f)
		{
			labelLine->setAnchorPoint(cocos2d::CCPointMake(0.0f, labelLine->getAnchorPoint().y));
			float posX = roundf(labelLine->getPosition().x - (labelLine->getContentSize().width * 0.5f));
			labelLine->setPosition(cocos2d::CCPointMake(posX, labelLine->getPosition().y));
		}

		if (labelLine->getAnchorPoint().y == 0.5f)
		{
			labelLine->setAnchorPoint(cocos2d::CCPointMake(labelLine->getAnchorPoint().x, 0.0f));
			float posY = roundf(labelLine->getPosition().y - (labelLine->getContentSize().height * 0.5f));
			labelLine->setPosition(cocos2d::CCPointMake(labelLine->getPosition().x, posY));
		}

		int lineStrLen = lineStr.length();
		int endCharIdx = totalProcessedChars + lineStrLen;

		// FIX: cast to ColoredSection* (not CustomColoredSection*) so getStartIndex/
		// getEndIndex/getColor read the actual m_startPos/m_endPos/m_col fields that
		// ColoredSection::init() set. CustomColoredSection had its own shadow fields
		// that were never initialized, so colors were always garbage.
		// Also fixed loop to iterate all blocks (not just index 0) and corrected
		// the start index calculation to not break on the first line.
		int blockIdx = 0;
		while (blockIdx < (int)m_lines->count())
		{
			ColoredSection* colorBlock = static_cast<ColoredSection*>(m_lines->objectAtIndex(blockIdx));

			if (colorBlock->getEndPos() < totalProcessedChars)
			{
				m_lines->removeObjectAtIndex(blockIdx, true);
				continue;
			}

			if (colorBlock->getStartPos() >= endCharIdx)
			{
				break;
			}

			int blockStart = colorBlock->getStartPos();
			int blockEnd = colorBlock->getEndPos();

			int applyStart = blockStart - totalProcessedChars;
			int applyEnd = (blockEnd < endCharIdx ? blockEnd : endCharIdx - 1) - totalProcessedChars;

			for (int ci = applyStart; ci <= applyEnd; ++ci)
			{
				cocos2d::CCSprite* fontChar = static_cast<cocos2d::CCSprite*>(labelLine->getChildByTag(ci));
				if (fontChar)
				{
					fontChar->setColor(colorBlock->getCol());
				}
			}

			if (blockEnd < endCharIdx)
			{
				m_lines->removeObjectAtIndex(blockIdx, true);
			}
			else
			{
				colorBlock->setStartPos(endCharIdx);
				++blockIdx;
			}
		}

		this->addChild(labelLine);

		for (unsigned int j = 0; j < labelLine->getChildren()->count(); ++j)
		{
			cocos2d::CCObject* childChar = labelLine->getChildren()->objectAtIndex(j);
			m_unkArray->addObject(childChar);
		}

		coloredText.erase(0, lineStrLen);
		totalProcessedChars += lineStrLen;
		++lineCount;
		currentYOffset -= lineSpace;
	}

	m_lines->release();
	m_characters->release();

	float targetX = 0.0f;
	int computedHeight = (lineCount - 1) * lineSpace;
	m_textHeight = (float)computedHeight;

	int computedWidth = (int)maxWidth;
	m_textWidth = (float)computedWidth;

	if (align->x != 0.0f)
	{
		if (align->x != 1.0f)
		{
			computedWidth /= 2;
		}
		targetX = (float)-computedWidth;
	}

	m_textPos = cocos2d::CCPointMake(-targetX, (float)computedHeight);

	return true;
}

void MultilineBitmapFont::readColorInfo(std::string* outStr, MultilineBitmapFont* font, std::string text)
{
	while (true)
	{
		size_t startTagPos = text.find("<c");
		if (startTagPos == std::string::npos)
		{
			break;
		}

		char colorChar = text[startTagPos + 2];
		text.replace(startTagPos, 4, "");

		size_t endTagPos = text.find("</c>");
		text.replace(endTagPos, 4, "");

		cocos2d::ccColor3B color = cocos2d::ccc3(255, 0, 0);

		switch (colorChar)
		{
		case 'b':
			color = cocos2d::ccc3(74, 82, 225);
			break;
		case 'g':
			color = cocos2d::ccc3(64, 227, 72);
			break;
		case 'l':
			color = cocos2d::ccc3(96, 172, 239);
			break;
		case 'y':
			color = cocos2d::ccc3(255, 255, 0);
			break;
		case 'o':
			color = cocos2d::ccc3(255, 165, 75);
			break;
		case 'r':
			color = cocos2d::ccc3(255, 90, 90);
			break;
		case 'p':
			color = cocos2d::ccc3(255, 0, 255);
			break;
		default:
			color = cocos2d::ccc3(255, 0, 0);
			break;
		}

		ColoredSection* block = ColoredSection::create(color, startTagPos, endTagPos - 1);
		font->m_lines->addObject(block);
	}

	*outStr = text;
}

void MultilineBitmapFont::stringWithMaxWidth(std::string* outStr, MultilineBitmapFont* font, std::string text, float maxWidth, float scale)
{
	size_t length = text.length();
	std::string lineBuffer = "";

	int currentLineWidth = 0;
	int lastSpaceWidth = 0;
	int index = 0;
	unsigned int spaceCharWidth = 0;

	while (index < length && (float)currentLineWidth < (maxWidth * 2.0f))
	{
		char currentChar = text[index];
		unsigned int charWidth = font->m_fontWidths[static_cast<unsigned char>(currentChar)];
		std::string singleCharStr(1, currentChar);

		if (singleCharStr == "\n")
		{
			lineBuffer += " ";
			currentLineWidth += static_cast<int>(scale * static_cast<float>(charWidth));
			index = 1000;
			break;
		}

		if (currentChar == ' ')
		{
			lastSpaceWidth = currentLineWidth;
			spaceCharWidth = static_cast<unsigned int>(scale * static_cast<float>(font->m_fontWidths[32]));
		}

		lineBuffer += singleCharStr;
		++index;
		currentLineWidth += static_cast<int>(scale * static_cast<float>(charWidth));
	}

	int halfSpacePos = lastSpaceWidth / 2;
	if (!font->m_fadeInFinished && (float)currentLineWidth < (maxWidth * 2.0f))
	{
		font->m_order = currentLineWidth / 2 - spaceCharWidth;
	}
	font->m_fadeInFinished = true;

	if (halfSpacePos > font->m_order)
	{
		font->m_order = halfSpacePos;
	}

	if (length > index)
	{
		int backtrackCount = 0;
		int backtrackIdx = index;

		while (backtrackIdx > 0)
		{
			if (lineBuffer[backtrackIdx - 1] == ' ')
			{
				break;
			}
			++backtrackCount;
			--backtrackIdx;
			if (backtrackCount > index)
			{
				break;
			}
		}

		if (index - backtrackCount > 1)
		{
			lineBuffer = lineBuffer.substr(0, lineBuffer.length() - backtrackCount);
		}
	}

	cocos2d::CCString* ccStr = cocos2d::CCString::create(lineBuffer);
	*outStr = ccStr->getCString();
}

MultilineBitmapFont::MultilineBitmapFont()
{
	m_lines = NULL;
	m_characters = NULL;
	m_unkArray = NULL;
	m_order = 0;
	m_fadeInFinished = false;
	m_textHeight = 0.0f;
	m_textWidth = 0.0f;

	m_textPos = cocos2d::CCPointMake(0.0f, 0.0f);
	m_sizeHeight = 0.0f;
}
BitmapFontCache* BitmapFontCache::sharedFontCache()
{
	static BitmapFontCache* s_sharedFontCache = nullptr;
	if (!s_sharedFontCache) {
		s_sharedFontCache = new BitmapFontCache();
	}
	return s_sharedFontCache;
}

FontObject* BitmapFontCache::fontWithConfigFile(const char* fontFile, float scale)
{
	return reinterpret_cast<FontObject*>(cocos2d::CCBMFontConfiguration::create(fontFile));
}

float FontObject::getFontWidth(int charId)
{
	cocos2d::CCBMFontConfiguration* config = reinterpret_cast<cocos2d::CCBMFontConfiguration*>(this);
	if (!config) return 0.0f;

	if (!config->m_pFontDefDictionary) return 15.0f;

	return 15.0f;
}