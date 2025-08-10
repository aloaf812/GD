#ifndef  _LOCAL_LEVEL_MANAGER_H_
#define  _LOCAL_LEVEL_MANAGER_H_

#include "cocos2d.h"
#include "GManager.h"

class LocalLevelManager : public GManager {
    public:
        static LocalLevelManager* sharedState();
};
#endif