#ifndef __GeometryDash__EditorUI__
#define __GeometryDash__EditorUI__

#include "cocos2d.h"

// class CreateMenuItem;

class EditorUI : public cocos2d::CCLayer {
public:
    // missing LevelEditorLayer
    // static EditorUI* create(LevelEditorLayer* editorLayer);
    // bool init(LevelEditorLayer* editorLayer);
    static EditorUI* create();
    bool init();
    void setupCreateMenu();
};

#endif