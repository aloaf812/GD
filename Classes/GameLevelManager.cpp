#include "GameLevelManager.h"
#include "GJGameLevel.h"
#include "LevelInfoLayer.h"
USING_NS_CC;

GameLevelManager* GameLevelManager::sharedState()
{
    static GameLevelManager* GLM = NULL;
    if (!GLM)
    {
        GLM = new GameLevelManager();
        GLM->init();
    }
    
    return GLM;
}

bool GameLevelManager::init()
{
    return true;
}

void GameLevelManager::downloadLevel(int level_id)
{
    extension::CCHttpRequest *request = new extension::CCHttpRequest();
    request->setUrl("http://www.boomlings.com/database/downloadGJLevel.php");
    request->setRequestType(extension::CCHttpRequest::kHttpPost);
    std::string postData = CCString::createWithFormat("secret=Wmfd2893gb7&levelID=%i&inc=1", level_id)->getCString();
    request->setRequestData(postData.c_str(), postData.length());
    request->setResponseCallback(this, httpresponse_selector(GameLevelManager::onDownloadLevelComplete));
    extension::CCHttpClient::getInstance()->send(request);
    request->release();
}

/*char GameLevelManager::getLevelKey(int level)
{
    return CCString::createWithFormat("%i", level)->getCString();
    
}*/

void GameLevelManager::onDownloadLevelComplete(extension::CCHttpClient* client, extension::CCHttpResponse* response)
{
    if (!response || !response->isSucceed())
    {
        CCLOG("failed");
        return;
    }
    std::vector<char> *buffer = response->getResponseData();
    std::string responseData(buffer->begin(), buffer->end());
    CCLOG("response data: %s", responseData.c_str());
    CCDirector* pDirector = CCDirector::sharedDirector();
    GJGameLevel* level = GJGameLevel::create(responseToDict(responseData));
    CCScene* scene = LevelInfoLayer::scene(level);
    CCTransitionFade* fade = CCTransitionFade::create(0.5f, scene);
    pDirector->replaceScene(fade);
}

// thanks cvolton: https://github.com/Cvolton/betterinfo-geode/blob/master/src/utils.cpp#L309
CCDictionary* GameLevelManager::responseToDict(const std::string& response){
    CCDictionary* dict = CCDictionary::create();
    
    std::stringstream responseStream(response);
    std::string currentKey;
    std::string keyID;
    
    unsigned int i = 0;
    while(getline(responseStream, currentKey, ':')){
        
        if(i % 2 == 0) keyID = currentKey;
        else dict->setObject(CCString::create(currentKey.c_str()),keyID);
        i++;
    }
    
    return dict;
}

CCObject* GameLevelManager::getMainLevel(int mainLevel)
{
    
}
