#include "ObjectToolbox.h"
USING_NS_CC;

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