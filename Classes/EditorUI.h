#ifndef __GeometryDash__EditorUI__
#define __GeometryDash__EditorUI__

#include "cocos2d.h"
#include "LevelEditorLayer.h"
#include "RT_COCOS/CCMenuItemSpriteExtra.h"
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
	void resetUI();

	void showMaxError();

	CC_SYNTHESIZE(EditMode, m_editMode, EditMode); // 0x190

protected:
	CCMenuItemSpriteExtra* m_deleteBtn; // 0x140
	CCMenuItemSpriteExtra* m_buildBtn; // 0x144
	CCMenuItemSpriteExtra* m_editBtn; // 0x148
};

#endif