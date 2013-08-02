LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := game_shared

LOCAL_MODULE_FILENAME := libgame

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/MainGameScene.cpp \
                   ../../Classes/Common/MainLayerBase.cpp \
                   ../../Classes/Common/GlobalData.cpp \
                   ../../Classes/main/MainInnerLayer.cpp \
                   ../../Classes/main/MainOuterLayer.cpp \
                   ../../Classes/Friends/FriendListScene.cpp \
                   ../../Classes/Friends/AddFriendScene.cpp \
                   ../../Classes/Login/CharacterScene.cpp \
                   ../../Classes/Login/LoginScene.cpp \
                   ../../Classes/Login/RegisterScene.cpp \
                   ../../Classes/Login/ServerListScene.cpp \
                   ../../Classes/Login/ThirdLoginScene.cpp \
                   ../../Classes/Mail/MailListScene.cpp \
                   ../../Classes/Mail/MailMainScene.cpp \
                   ../../Classes/Mail/SysMailListScene.cpp \
                   ../../Classes/Mail/NewMailScene.cpp \
                   ../../Classes/Other/AboutScene.cpp \
                   ../../Classes/Other/MDCatalogueLayer.cpp \
                   ../../Classes/Other/MDSettingLayer.cpp \
                   ../../Classes/Package/MDPackageLayer.cpp \
                   ../../Classes/Task/TaskDetailScene.cpp \
                   ../../Classes/Task/TaskListScene.cpp \
                   ../../Classes/Task/TaskRewardScene.cpp \
                   ../../Classes/Task/MDTaskBoxLayer.cpp \
                   ../../Classes/Chat/ChatLayer.cpp \
                   ../../Classes/Battle/MDCardPlayer.cpp \
                   ../../Classes/Battle/MDBattleLayer.cpp \
                   ../../Classes/UILibrary/CCMessageDialog.cpp \
                   ../../Classes/UILibrary/CCShake.cpp \
                   ../../Classes/UILibrary/CCTabView.cpp \
                   ../../Classes/UILibrary/EllipseActionInterval.cpp \
                   ../../Classes/UILibrary/LoadingScene.cpp \
                   ../../Classes/UILibrary/MDProgressBar.cpp \
                   ../../Classes/UILibrary/SlidingMenu.cpp \
                   ../../Classes/UILibrary/SharpLabelTTF.cpp \
                   ../../library/XmlParser/XmlParser.cpp \
                   ../../library/sqlite3/sqlite3.c \
                   ../../library/jsonconverter/cJSON.c \
                   ../../library/jsonconverter/CCJSONConverter.cpp \
                   ../../Classes/Card/MDCardAlchemyLayer.cpp \
                   ../../Classes/Card/MDHeroDetailLayer.cpp \
                   ../../Classes/Card/MDHeroListLayer.cpp \
                   ../../Classes/Card/MDHeroMainLayer.cpp \
                   ../../Classes/Card/MDHeroPrePromoLayer.cpp \
                   ../../Classes/Card/MDHeroPromoLayer.cpp \
                   ../../Classes/Card/MDHerosFormationLayer.cpp
                   
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes  \
					$(LOCAL_PATH)/../../Classes/Battle  \
					$(LOCAL_PATH)/../../Classes/Card  \
					$(LOCAL_PATH)/../../Classes/Chat  \
					$(LOCAL_PATH)/../../Classes/Common  \
					$(LOCAL_PATH)/../../Classes/Friends  \
					$(LOCAL_PATH)/../../Classes/Login  \
					$(LOCAL_PATH)/../../Classes/Mail  \
					$(LOCAL_PATH)/../../Classes/main  \
					$(LOCAL_PATH)/../../Classes/Other  \
					$(LOCAL_PATH)/../../Classes/Package  \
					$(LOCAL_PATH)/../../Classes/Task  \
					$(LOCAL_PATH)/../../Classes/UILibrary  \
                    $(LOCAL_PATH)/../../library/sqlite3  \
                    $(LOCAL_PATH)/../../library/jsonconverter  \
                    $(LOCAL_PATH)/../../library/XmlParser 
                    
LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static cocosdenshion_static cocos_extension_static
            
include $(BUILD_SHARED_LIBRARY)
$(call import-module,CocosDenshion/android) \
$(call import-module,cocos2dx) \
$(call import-module,extensions)
