LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AdToolbox.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/BoomScrollLayer.cpp \
                   ../../Classes/CCMenuItemSpriteExtra.cpp \
                   ../../Classes/CreatorLayer.cpp \
                   ../../Classes/EndLevelLayer.cpp \
                   ../../Classes/FLAlertLayer.cpp \
                   ../../Classes/FLAlertLayerProtocol.cpp \
                   ../../Classes/GameManager.cpp \
                   ../../Classes/GameSoundManager.cpp \
                   ../../Classes/GameToolbox.cpp \
                   ../../Classes/GJDropDownLayer.cpp \
                   ../../Classes/GJGarageLayer.cpp \
                   ../../Classes/GJListLayer.cpp \
                   ../../Classes/GManager.cpp \
                   ../../Classes/LevelSelectLayer.cpp \
                   ../../Classes/LevelTools.cpp \
                   ../../Classes/LoadingLayer.cpp \
                   ../../Classes/LocalLevelManager.cpp \
                   ../../Classes/MenuGameLayer.cpp \
                   ../../Classes/MenuLayer.cpp \
                   ../../Classes/OptionsLayer.cpp \
                   ../../Classes/PlatformToolbox.cpp \
                   ../../Classes/SimplePlayer.cpp \
                   ../../Classes/SongInfoLayer.cpp \
                   ../../Classes/TextArea.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
LOCAL_WHOLE_STATIC_LIBRARIES += chipmunk_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,cocos2dx)
$(call import-module,cocos2dx/platform/third_party/android/prebuilt/libcurl)
$(call import-module,CocosDenshion/android)
$(call import-module,extensions)
$(call import-module,external/Box2D)
$(call import-module,external/chipmunk)
