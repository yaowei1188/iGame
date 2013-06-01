LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := game_shared

LOCAL_MODULE_FILENAME := libgame

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/LoginScene.cpp \
                   ../../Classes/MainLayerBase.cpp \
                   ../../Classes/LoadingScene.cpp \
                   ../../Classes/MainGameScene.cpp \
                   ../../Classes/MainSceneTemplate.cpp \
                   ../../Classes/ThirdLoginScene.cpp \
                   ../../Classes/FriendListScene.cpp \
                   ../../Classes/AddFriendScene.cpp \
                   ../../Classes/NewMailScene.cpp \
                   ../../Classes/CCMessageDialog.cpp \
                   ../../Classes/XmlParser.cpp \
                   ../../library/JsonBox/src/Array.cpp \
                   ../../library/JsonBox/src/Convert.cpp \
                   ../../library/JsonBox/src/Escaper.cpp \
                   ../../library/JsonBox/src/IndentCanceller.cpp \
                   ../../library/JsonBox/src/Indenter.cpp \
                   ../../library/JsonBox/src/Object.cpp \
                   ../../library/JsonBox/src/SolidusEscaper.cpp \
                   ../../library/JsonBox/src/Value.cpp
                   
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes  \
                    $(LOCAL_PATH)/../../library/JsonBox/include                   

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static cocosdenshion_static cocos_extension_static
            
include $(BUILD_SHARED_LIBRARY)

$(call import-module,CocosDenshion/android) \
$(call import-module,cocos2dx) \
$(call import-module,extensions)
