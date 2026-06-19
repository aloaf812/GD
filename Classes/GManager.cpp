#include "GManager.h"
USING_NS_CC;

bool GManager::init(){
	unk_0xec = true;
	unk_0xed = false;
    return true;
}

void GManager::setup(){
    return;
}

void GManager::save(){

}

void GManager::load(){

}

void GManager::saveData(DS_Dictionary* dict, std::string file) {
	dict->saveRootSubDictToFile(file.c_str());
}