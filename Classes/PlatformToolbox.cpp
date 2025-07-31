//
//  PlatformToolbox.cpp
//  GeometryDash
//
//  Created by bryan on 7/27/25.
//
//

#include "PlatformToolbox.h"

// this class is basically useless on iOS apart from the gameDidSave function

void PlatformToolbox::gameDidSave(){
    CCLOG("game was saved");
    return;
}