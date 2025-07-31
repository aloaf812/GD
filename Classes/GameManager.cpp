#include "GameManager.h"
USING_NS_CC;

/* i don't understand this function
void GameManager::loadBackground(int p0)
{
    int bgID = p0;
    if (3 < p0) {
        bgID = 4;
    }
    if (p0 < 1) {
        bgID = 1;
    }
    CCString *this_00 = CCString::createWithFormat("game_bg_%02d_001.png", bgID);
    CCLOG(this_00->CCString::getCString());
    return;
}
*/

char const* GameManager::getBGTexture(int id)
{
    int bgID = id;
    if (3 < id) {
        bgID = 4;
    }
    if (id < 1) {
        bgID = 1;
    }
    // GameManager::loadBackground(bgid);
    CCString *this_00 = CCString::createWithFormat("game_bg_%02d_001.png", bgID);
    CCLOG(this_00->CCString::getCString());
    return this_00->CCString::getCString();
}

GameManager* GameManager::sharedState()
{
    return NULL;
}