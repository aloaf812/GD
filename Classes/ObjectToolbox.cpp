#include "ObjectToolbox.h"
USING_NS_CC;

// thank you smjs for that reddit post
#define CREATE_OBJ(filename, index) \
	key = CCString::createWithFormat("%i", index); \
	ObjectToolbox::m_objects->setObject(key, filename); \
	ObjectToolbox::m_keys->setObject(CCString::create(filename), index);

// the whole macro mess makes this function expand to around 2,800 lines in the end of it all
bool ObjectToolbox::init()
{
	m_objects = CCDictionary::create();
	m_objects->retain();

	m_keys = CCDictionary::create();
	m_keys->retain();

	CCString* key;
	// object names taken from https://flowvix.github.io/gd-info-explorer/ids 
#pragma region Objects
	CREATE_OBJ("square_01_001.png", 1);
	CREATE_OBJ("square_02_001.png", 2);
	CREATE_OBJ("square_03_001.png", 3);
	CREATE_OBJ("square_04_001.png", 4);
	CREATE_OBJ("square_05_001.png", 5);
	CREATE_OBJ("square_06_001.png", 6);
	CREATE_OBJ("square_07_001.png", 7);
	CREATE_OBJ("square_08_001.png", 83); // Grid Patterned Square

	// spikes
	CREATE_OBJ("spike_01_001.png", 8); // Black Gradient Spike
	CREATE_OBJ("spike_02_001.png", 39); // Half Black Gradient Spike
	CREATE_OBJ("spike_03_001.png", 103); // Small Black Gradient Spike

	// portals
	CREATE_OBJ("portal_01_front_001.png", 10); // blue gravity portal
	CREATE_OBJ("portal_02_front_001.png", 11); // yellow gravity portal
	CREATE_OBJ("portal_03_front_001.png", 12); // cube portal
	CREATE_OBJ("portal_04_front_001.png", 13); // ship portal
	CREATE_OBJ("portal_05_front_001.png", 45); // orange mirror portal
	CREATE_OBJ("portal_06_front_001.png", 46); // blue mirror portal
	CREATE_OBJ("portal_07_front_001.png", 47); // ball portal
	CREATE_OBJ("portal_08_front_001.png", 99); // green size portal
	CREATE_OBJ("portal_09_front_001.png", 101); // pink size portal

	// ground/pit spikes
	CREATE_OBJ("pit_01_001.png", 9); // Non-Colorable Spike Black Pit Hazard

	// floor spike deco
	CREATE_OBJ("d_spikes_01_001.png", 18); // Large Decorative Spikes
	CREATE_OBJ("d_spikes_02_001.png", 19); // Medium Decorative Spikes
	CREATE_OBJ("d_spikes_03_001.png", 20); // Small Decorative Spikes
	CREATE_OBJ("d_spikes_04_001.png", 21); // Very Small Decorative Spikes

	// rods
	CREATE_OBJ("rod_01_001.png", 15); // Tall Rod
	CREATE_OBJ("rod_02_001.png", 16); // Medium Rod
	CREATE_OBJ("rod_03_001.png", 17); // Short Rod

	// triggers
	CREATE_OBJ("edit_eeNoneBtn_001.png", 22); // No Enter Effect
#pragma endregion Objects
	return true;
}

CCDictionary* ObjectToolbox::stringSetupToDict(std::string str)
{
    CCDictionary* dict = CCDictionary::create();
    
    std::stringstream strStream(str);
    std::string currentKey;
    std::string keyID;
    
    unsigned int i = 0;
    while(getline(strStream, currentKey, ',')){
        
        if(i % 2 == 0) keyID = currentKey;
        else dict->setObject(CCString::create(currentKey.c_str()),keyID);
        i++;
    }
    
    return dict;
}