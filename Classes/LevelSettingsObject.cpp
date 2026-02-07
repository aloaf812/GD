#include "LevelSettingsObject.h"
#include "ObjectToolbox.h"
USING_NS_CC;

LevelSettingsObject::LevelSettingsObject()
{
    m_BGIdx = 0;
}

bool LevelSettingsObject::init()
{
	m_startGColor = ccc3(0, 102, 255);
	m_startBGColor = ccc3(40, 125, 255);
	m_startLineColor = ccc3(255, 255, 255);
	m_startObjColor = ccc3(255, 255, 255);
	m_startTintObjColor = ccc3(255, 255, 255);
	this->m_audioTrack = 0;
	this->m_startMiniMode = false;
	this->m_startMode = 0;
	this->m_startSpeed = 0;
	this->m_BGIdx = 0;
	this->m_GIdx = 0;
	this->m_tintObjectsUseBlend = true;
    return true;
}

LevelSettingsObject* LevelSettingsObject::objectFromString(std::string str) {
    CCDictionary* dict = ObjectToolbox::stringSetupToDict(str);
    LevelSettingsObject* obj = LevelSettingsObject::create();
    
    if (!dict)
        return obj;
    
    auto color = [&](const char* r, const char* g, const char* b) {
        return ccColor3B{
            (GLubyte)dict->valueForKey(r)->intValue(),
            (GLubyte)dict->valueForKey(g)->intValue(),
            (GLubyte)dict->valueForKey(b)->intValue()
        };
    };
    
    // big credits to https://wyliemaster.github.io/gddocs/#/resources/client/level-components/level-start
    obj->setStartBGColor(color("kS1", "kS2", "kS3")); // bg color
    obj->setStartGColor(color("kS4", "kS5", "kS6")); // ground color
    
    obj->setAudioTrack(dict->valueForKey("kA1")->intValue()); // audio track
    
    if (dict->objectForKey("kS7")) {
        obj->setStartLineColor(color("kS7", "kS8", "kS9")); // line color
        // this might be setStartObjColor: obj->setColor4(color("kS10", "kS11", "kS12")); // object color
        // same for this but tint: obj->setColor5(color("kS13", "kS14", "kS15")); // obj-2 color
    }
    obj->setStartMode(dict->valueForKey("kA2")->intValue()); // gamemode
    obj->setStartMiniMode(dict->valueForKey("kA3")->boolValue()); // mini mode
    obj->setStartSpeed(dict->valueForKey("kA4")->intValue()); // speed
    
    /*obj->setS16(dict->valueForKey("kS16")->intValue());
     obj->setS17(dict->valueForKey("kS17")->intValue());
     obj->setS18(dict->valueForKey("kS18")->intValue());
     obj->setS19(dict->valueForKey("kS19")->intValue());
     obj->setS20(dict->valueForKey("kS20")->intValue());*/
    
    //obj->setA5(dict->valueForKey("kA5")->boolValue());
    obj->setBGIdx(dict->valueForKey("kA6")->intValue()); // bg texture
    obj->setGIdx(dict->valueForKey("kA7")->intValue()); // ground texture
    
    return obj;
}
