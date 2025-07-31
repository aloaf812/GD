//
//  GameManager.h
//  GeometryDash
//
//  Created by bryan on 7/27/25.
//
//

#ifndef __GeometryDash__GameManager__
#define __GeometryDash__GameManager__

#include "cocos2d.h"
#include "GManager.h"

class GameManager: public GManager {
public:
    static GameManager* sharedState();
    char const* getBGTexture(int id);
    // void loadBackground(int p0);
};

#endif /* defined(__GeometryDash__GameManager__) */
