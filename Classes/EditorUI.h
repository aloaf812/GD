#ifndef __GeometryDash__EditorUI__
#define __GeometryDash__EditorUI__

#include "cocos2d.h"
#include "ButtonSprite.h"
#include "LevelEditorLayer.h"
#include "RT_COCOS/CCMenuItemSpriteExtra.h"
#include "Slider.h"
// class CreateMenuItem;

enum class EditMode {

};

class EditorUI : public cocos2d::CCLayer {
public:
    static EditorUI* create(LevelEditorLayer* editorLayer);
    bool init(LevelEditorLayer* editorLayer);
    void setupCreateMenu();
	CCMenuItemSpriteExtra* getModeBtn(char const* sprite, int tag);
	void toggleMode(cocos2d::CCObject* sender);
	void toggleSwipe(cocos2d::CCObject* sender);
	void resetUI();

	void showMaxError();
	void sliderChanged(cocos2d::CCObject* sender);

	Slider* unk_0x11c; // 0x11c

	bool unk_0x12c;

	CCMenuItemSpriteExtra* m_deleteBtn; // 0x140
	CCMenuItemSpriteExtra* m_buildBtn; // 0x144
	CCMenuItemSpriteExtra* m_editBtn; // 0x148
	
	ButtonSprite* unk_0x14c; // 0x14c
	
	CC_SYNTHESIZE(EditMode, m_editMode, EditMode); // 0x190
	LevelEditorLayer* m_editorLayer; // 0x194
};

#endif