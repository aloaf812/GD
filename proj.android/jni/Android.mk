LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AchievementBar.cpp \
                   ../../Classes/AchievementManager.cpp \
                   ../../Classes/AchievementNotifier.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/BoomScrollLayer.cpp \
                   ../../Classes/RT_COCOS/CCBlockLayer.cpp \
                   ../../Classes/RT_COCOS/CCContentManager.cpp \
                   ../../Classes/RT_COCOS/CCMenuItemSpriteExtra.cpp \
                   ../../Classes/RT_COCOS/CCSpritePlus.cpp \
                   ../../Classes/RT_COCOS/CCTextInputNode.cpp \
                   ../../Classes/CreatorLayer.cpp \
                   ../../Classes/EditorUI.cpp \
                   ../../Classes/EndLevelLayer.cpp \
                   ../../Classes/ExtendedLayer.cpp \
                   ../../Classes/FLAlertLayer.cpp \
                   ../../Classes/FLAlertLayerProtocol.cpp \
                   ../../Classes/GameLevelManager.cpp \
                   ../../Classes/GameManager.cpp \
                   ../../Classes/GameObject.cpp \
                   ../../Classes/GameStatsManager.cpp \
                   ../../Classes/GameSoundManager.cpp \
                   ../../Classes/GameToolbox.cpp \
                   ../../Classes/GJDropDownLayer.cpp \
                   ../../Classes/GJGameLevel.cpp \
                   ../../Classes/GJGarageLayer.cpp \
                   ../../Classes/GJGroundLayer.cpp \
                   ../../Classes/GJListLayer.cpp \
                   ../../Classes/GManager.cpp \
                   ../../Classes/LevelEditorLayer.cpp \
                   ../../Classes/LevelInfoLayer.cpp \
                   ../../Classes/LevelPage.cpp \
                   ../../Classes/LevelSelectLayer.cpp \
                   ../../Classes/LevelSettingsObject.cpp \
                   ../../Classes/LevelTools.cpp \
                   ../../Classes/LoadingLayer.cpp \
                   ../../Classes/LocalLevelManager.cpp \
                   ../../Classes/MenuGameLayer.cpp \
                   ../../Classes/MenuLayer.cpp \
                   ../../Classes/MyLevelsLayer.cpp \
                   ../../Classes/ObjectToolbox.cpp \
                   ../../Classes/OptionsLayer.cpp \
                   ../../Classes/PauseLayer.cpp \
                   ../../Classes/PlatformToolbox.cpp \
                   ../../Classes/PlayerObject.cpp \
                   ../../Classes/PlayLayer.cpp \
                   ../../Classes/SimplePlayer.cpp \
                   ../../Classes/Slider.cpp \
                   ../../Classes/SongInfoLayer.cpp \
                   ../../Classes/TextArea.cpp \
                   ../../Classes/UILayer.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,cocos2dx)
$(call import-module,cocos2dx/platform/third_party/android/prebuilt/libcurl)
$(call import-module,CocosDenshion/android)
$(call import-module,extensions)
