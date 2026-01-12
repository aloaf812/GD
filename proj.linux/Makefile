EXECUTABLE = GeometryDash

INCLUDES = -I.. \
		-I../Classes \
		-I$(COCOS_ROOT)/CocosDenshion/include \
		-I$(COCOS_ROOT)/extensions \
		-I$(COCOS_ROOT)/external \
		-I$(COCOS_ROOT)/external/chipmunk/include/chipmunk

SOURCES = main.cpp \
        ../Classes/AchievementBar.cpp \
    	../Classes/AchievementManager.cpp \
    	../Classes/AchievementNotifier.cpp \
    	../Classes/AppDelegate.cpp \
    	../Classes/BoomScrollLayer.cpp \
    	../Classes/RT_COCOS/CCContentManager.cpp \
    	../Classes/RT_COCOS/CCMenuItemSpriteExtra.cpp \
    	../Classes/RT_COCOS/CCSpritePlus.cpp \
    	../Classes/CreatorLayer.cpp \
    	../Classes/ExtendedLayer.cpp \
    	../Classes/FLAlertLayerProtocol.cpp \
    	../Classes/GameLevelManager.cpp \
        ../Classes/GameManager.cpp \
        ../Classes/GameObject.cpp \
        ../Classes/GameToolbox.cpp \
        ../Classes/GameStatsManager.cpp \
        ../Classes/GJDropDownLayer.cpp \
        ../Classes/GJGameLevel.cpp \
        ../Classes/GJGarageLayer.cpp \
        ../Classes/GJGroundLayer.cpp \
    	../Classes/GJListLayer.cpp \
    	../Classes/GManager.cpp \
    	../Classes/LevelInfoLayer.cpp \
    	../Classes/LevelPage.cpp \
        ../Classes/LevelSelectLayer.cpp \
        ../Classes/LevelSettingsObject.cpp \
        ../Classes/LevelTools.cpp \
        ../Classes/LoadingLayer.cpp \
        ../Classes/LocalLevelManager.cpp \
    	../Classes/MenuGameLayer.cpp \
        ../Classes/MenuLayer.cpp \
        ../Classes/ObjectToolbox.cpp \
        ../Classes/OptionsLayer.cpp \
        ../Classes/PlatformToolbox.cpp \
        ../Classes/PlayerObject.cpp \
        ../Classes/PlayLayer.cpp \
        ../Classes/SimplePlayer.cpp \
        ../Classes/TextArea.cpp
		


COCOS_ROOT = ../../..
include $(COCOS_ROOT)/cocos2dx/proj.linux/cocos2dx.mk

SHAREDLIBS += -lcocos2d -lcocosdenshion -lcurl -lpthread
COCOS_LIBS = $(LIB_DIR)/libcocos2d.so $(LIB_DIR)/libcocosdenshion.so

STATICLIBS += \
	$(LIB_DIR)/libextension.a \
	$(LIB_DIR)/libbox2d.a \
	$(LIB_DIR)/libchipmunk.a

####### Build rules
$(TARGET): $(OBJECTS) $(STATICLIBS) $(COCOS_LIBS) $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_LINK)$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@ $(STATICLIBS) $(SHAREDLIBS)

####### Compile
$(OBJ_DIR)/%.o: %.cpp $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CXX)$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -c $< -o $@

$(OBJ_DIR)/%.o: ../%.cpp $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CXX)$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -c $< -o $@
