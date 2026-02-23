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
	CREATE_OBJ("portal_01_front_001.png", 10); // Blue Gravity Portal
	CREATE_OBJ("portal_02_front_001.png", 11); // Yellow Gravity Portal
	CREATE_OBJ("portal_03_front_001.png", 12); // Cube Portal
	CREATE_OBJ("portal_04_front_001.png", 13); // Ship Portal
	CREATE_OBJ("portal_05_front_001.png", 45); // Orange Mirror Portal
	CREATE_OBJ("portal_06_front_001.png", 46); // Blue Mirror Portal
	CREATE_OBJ("portal_07_front_001.png", 47); // Ball Portal
	CREATE_OBJ("portal_08_front_001.png", 99); // Green Size Portal
	CREATE_OBJ("portal_09_front_001.png", 101); // Pink Size Portal

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

	// triggers (editor only)
	CREATE_OBJ("edit_eeNoneBtn_001.png", 22); // No Enter Effect
	CREATE_OBJ("edit_eeFBBtn_001.png", 23); // Fade Bottom Enter Effect
	CREATE_OBJ("edit_eeFTBtn_001.png", 24); // Fade Top Enter Effect
	CREATE_OBJ("edit_eeFLBtn_001.png", 25); // Fade Left Enter Effect
	CREATE_OBJ("edit_eeFRBtn_001.png", 26); // Fade Right Enter Effect
	CREATE_OBJ("edit_eeSUBtn_001.png", 27); // Small to Big Enter Effect
	CREATE_OBJ("edit_eeSDBtn_001.png", 28); // Big to Small Enter Effect
	CREATE_OBJ("edit_eTintBGBtn_001.png", 29); // BG Color Trigger (not in list)
	CREATE_OBJ("edit_eTintGBtn_001.png", 30); // Ground Color Trigger (not in list)
	CREATE_OBJ("edit_eTintLBtn_001.png", 104); // Line Color Trigger (not in list)
	CREATE_OBJ("edit_eTintObjBtn_001.png", 105); // Object Color Trigger (not in list)
	CREATE_OBJ("edit_eStartPosBtn_001.png", 31); // Start Position
	CREATE_OBJ("edit_eLevelEndBtn_001.png", 34); // 1.0 Level End Trigger
	CREATE_OBJ("edit_eBGEOn_001.png", 42); // BG Effect On Trigger (not in list)
	CREATE_OBJ("edit_eBGEOff_001.png", 43); // BG Effect Off Trigger (not in list)
	CREATE_OBJ("edit_eGhostEBtn_001.png", 32); // Enable Ghost Trail
	CREATE_OBJ("edit_eGhostDBtn_001.png", 33); // Disable Ghost Trail

	// pad (just one)
	CREATE_OBJ("bump_01_001.png", 35); // Yellow Jump Pad

	// orb (also just one)
	CREATE_OBJ("ring_01_001.png", 36); // Yellow Jump Orb

	// plank (still one)
	CREATE_OBJ("plank_01_001.png", 40); // Black Gradient Single Slab

	// chain (when does this end)
	CREATE_OBJ("chain_01_001.png", 41); // Tall Chain

	// clouds
	CREATE_OBJ("d_cloud_01_001.png", 48); // Large Fading Cloud

	// other objects i'm too lazy to properly organize
	CREATE_OBJ("d_ball_05_001.png", 54); // Pulsing Star

	CREATE_OBJ("square_b_01_001.png", 62); // Wavy Black Slab
	
	CREATE_OBJ("square_b_04_001.png", 65); // Wavy Black Slab Right Edge

	CREATE_OBJ("gravbump_01_001.png", 67); // Blue Gravity Pad

	CREATE_OBJ("square_b_06_001.png", 68); // Wavy Black Single Slab

	CREATE_OBJ("square_c_05_001.png", 73); // Beveled Inner Square

	CREATE_OBJ("d_chain_02_001.png", 110); // Small Chain

	CREATE_OBJ("square_f_02_001.png", 117); // Brick Top Square
	CREATE_OBJ("square_f_03_001.png", 118); // Brick Outer Corner Square

	CREATE_OBJ("bump_03_001.png", 140); // Pink Jump Pad

	CREATE_OBJ("secretCoin_01_001.png", 142); // Secret Coin (not in list)

	CREATE_OBJ("d_spikewheel_01_001.png", 154); // Large Spike Wheel

	CREATE_OBJ("d_link_02_001.png", 238); // Corner Square Pipe
#pragma endregion Objects
	return true;
}

ObjectToolbox* ObjectToolbox::sharedState()
{
	static ObjectToolbox* pObjectToolbox = NULL;
	if (!pObjectToolbox)
	{
		pObjectToolbox = new ObjectToolbox();
		pObjectToolbox->init();
	}

	return pObjectToolbox;
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
		else dict->setObject(CCString::create(currentKey.c_str()), keyID);
        i++;
    }
    
    return dict;
}

char const* ObjectToolbox::keyToFrame(char const* key)
{
	char const* frame = m_keys->valueForKey(atoi(key))->getCString();
	//CCLOG(frame);
	return frame;
}