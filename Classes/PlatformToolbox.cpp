#include "PlatformToolbox.h"

// this class is basically useless on iOS apart from the gameDidSave function

void PlatformToolbox::gameDidSave(){
    CCLOG("game was saved");
    return;
}

uint PlatformToolbox::shouldResumeSound(){
    return true;
}