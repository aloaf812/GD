#include "EditorUI.h"
USING_NS_CC;

EditorUI* EditorUI::create()
{
	EditorUI* ret = new EditorUI();
	if (ret) {
		if (ret->init()) {
			ret->autorelease();
			return ret;
		}

		delete ret;
	}

	return NULL;
}

bool EditorUI::init()
{
    return true;
}

void EditorUI::setupCreateMenu()
{
    
}