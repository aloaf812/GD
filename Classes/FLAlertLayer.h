#ifndef __GeometryDash__FLAlertLayer__
#define __GeometryDash__FLAlertLayer__

#include "cocos2d.h"
#include "FLAlertLayerProtocol.h"
#include <stdio.h>

class FLAlertLayer : public cocos2d::CCLayerColor {
    bool init(FLAlertLayerProtocol* param_1, char const* param_2, std::string param_3, char const* param_4, char const* param_5, float param_6);
}

#endif