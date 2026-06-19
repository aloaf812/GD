#include "GameLevelManager.h"
#include "LevelInfoLayer.h"
#include "LevelTools.h"
#include "GameStatsManager.h"
USING_NS_CC;
USING_NS_CC_EXT;

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
	unk_0xf0 = CCDictionary::create();
	unk_0xf0->retain();

	unk_0xf4 = CCDictionary::create();
	unk_0xf4->retain();
	
	unk_0x100 = CCDictionary::create();
	unk_0x100->retain();
	
	unk_0x10c = CCDictionary::create();
	unk_0x10c->retain();

	unk_0xf8 = CCDictionary::create();
	unk_0xf8->retain();
	
	unk_0xfc = CCDictionary::create();
	unk_0xfc->retain();
	
	unk_0x110 = CCDictionary::create();
	unk_0x110->retain();

	unk_0x108 = CCDictionary::create();
	unk_0x108->retain();

	m_lastLeaderboard = 1;
	m_lastSearchType = SearchType::SavedLevels;
    return true;
}

void GameLevelManager::dataLoaded(DS_Dictionary* dict) {
	unk_0xe8 = dict->getDictForKey("GLM_01");
	unk_0xe8->retain();
	
	m_localLevels = dict->getArrayForKey("GLM_02");
	m_localLevels->retain();

	unk_0x104 = dict->getDictForKey("GLM_03");
	unk_0x104->retain();

	unk_0xec = dict->getDictForKey("GLM_04");
	unk_0xec->retain();

	int lastLB;
	if (GameStatsManager::sharedState()->getStat("6") < 1) {
		lastLB = 1;
	}
	else {
		lastLB = 2;
	}

	m_lastLeaderboard = lastLB;
	limitSavedLevels();
}

void GameLevelManager::downloadLevel(int level_id)
{
	char const* lvlKey = getLevelKey(level_id);
	if (!isDLActive(lvlKey)) {
		addDLToActive(lvlKey);
		CCHttpRequest *request = new CCHttpRequest();
		request->setUrl("http://www.boomlings.com/database/downloadGJLevel.php");
		request->setRequestType(CCHttpRequest::kHttpPost);
		request->setResponseCallback(this, httpresponse_selector(GameLevelManager::onDownloadLevelComplete));
		char const* secretStr = CCString::createWithFormat("%c%s%s%c%c%s", 0x57, "mfd", "2893", 0x67, 0x62, "7")->getCString();
		char const* postData = CCString::createWithFormat("secret=%s&levelID=%i&inc=%i", secretStr, level_id, (hasDownloadedLevel(level_id) ^ 1))->getCString();
		request->setRequestData(postData, strlen(postData));
		request->setTag(CCString::createWithFormat("%i", level_id)->getCString());
		CCHttpClient::getInstance()->send(request);
		request->release();
	}
}

void GameLevelManager::limitSavedLevels()
{
	// todo
}

bool GameLevelManager::isDLActive(char const* key) {
	return unk_0x10c->objectForKey(key) != nullptr;
}

void GameLevelManager::addDLToActive(char const* key) {
	unk_0x10c->setObject(CCNode::create(), key);
}

bool GameLevelManager::hasDownloadedLevel(int level) {
	return unk_0xec->objectForKey(getLevelKey(level)) != nullptr;
}

void GameLevelManager::getLeaderboardScores(const char *leaderboardType)
{
    extension::CCHttpRequest *request = new extension::CCHttpRequest();
    request->setUrl("http://www.boomlings.com/database/getGJScores.php");
    request->setRequestType(extension::CCHttpRequest::kHttpPost);
	char const* secretStr = CCString::createWithFormat("%c%s%s%c%c%s", 0x57, "mfd", "2893", 0x67, 0x62, "7")->getCString();
    char const* postData = CCString::createWithFormat("secret=%s&type=top", secretStr)->getCString();
    request->setRequestData(postData, strlen(postData));
    request->setResponseCallback(this, httpresponse_selector(GameLevelManager::onGetLeaderboardScoresCompleted));
    extension::CCHttpClient::getInstance()->send(request);
    request->release();

}

void GameLevelManager::getOnlineLevels()
{
    extension::CCHttpRequest *request = new extension::CCHttpRequest();
    request->setUrl("http://www.boomlings.com/database/downloadGJLevel.php");
	request->setRequestType(extension::CCHttpRequest::kHttpPost);
	char const* secretStr = CCString::createWithFormat("%c%s%s%c%c%s", 0x57, "mfd", "2893", 0x67, 0x62, "7")->getCString();
	char const* postData = CCString::createWithFormat("secret=%s&type=top", secretStr)->getCString();
	request->setRequestData(postData, strlen(postData));
    request->setResponseCallback(this, httpresponse_selector(GameLevelManager::onGetLeaderboardScoresCompleted));
    extension::CCHttpClient::getInstance()->send(request);
    request->release();
    
}

char const* GameLevelManager::getLevelKey(int level)
{
    return CCString::createWithFormat("%i", level)->getCString();
    
}

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
    GJGameLevel* level = GJGameLevel::create(responseToDict(responseData, false));
    CCScene* scene = LevelInfoLayer::scene(level);
    CCTransitionFade* fade = CCTransitionFade::create(0.5f, scene);
    pDirector->replaceScene(fade);
}

void GameLevelManager::onGetLeaderboardScoresCompleted(cocos2d::extension::CCHttpClient* client, cocos2d::extension::CCHttpResponse* response)
{
    if (!response || !response->isSucceed())
    {
        CCLOG("failed");
        return;
    }
    std::vector<char> *buffer = response->getResponseData();
    std::string responseData(buffer->begin(), buffer->end());
    CCLOG("response data: %s", responseData.c_str());
    /*
    CCDirector* pDirector = CCDirector::sharedDirector();
    GJGameLevel* level = GJGameLevel::create(responseToDict(responseData, false));
    CCScene* scene = LevelInfoLayer::scene(level);
    CCTransitionFade* fade = CCTransitionFade::create(0.5f, scene);
    pDirector->replaceScene(fade);*/
}

// thanks cvolton: https://github.com/Cvolton/betterinfo-geode/blob/master/src/utils.cpp#L309
CCDictionary* GameLevelManager::responseToDict(std::string response, bool p0){
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

/*void GameLevelManager::storeUserNames(std::string usernameString){
    CCArray* usernames = CCArray::create();
    
    std::stringstream responseStream(response);
    std::string currentKey;
    std::string keyID;
    
    unsigned int i = 0;
    while(getline(responseStream, currentKey, '|')){
        
        if(i % 2 == 0) keyID = currentKey;
        else usernames->setObject(CCString::create(currentKey.c_str()),keyID);
        i++;
    }
    
    return dict;
}*/


GJGameLevel* GameLevelManager::getMainLevel(int mainLevel)
{
    return LevelTools::getLevel(mainLevel);
}
