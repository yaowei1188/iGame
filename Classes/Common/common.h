//
//  common.h
//  iGame
//
//  Created by China Team on 4/18/13.
//
//

#ifndef iGame_common_h
#define iGame_common_h

#define API_URL "http://www.runapk.com/dzxy"

#define CELL_ITEMS_Y 25
#define CELL_ITEMS_GAP 30
#define CELL_LOVE_XGAP 15

#define LOGIN_MENU_BAR_QQ_TAG 101
#define LOGIN_MENU_BAR_SINA_TAG 102
#define LOGIN_MENU_BAR_RENREN_TAG 103
#define LOGIN_BUTTON_ACTION_SIGNIN_TAG 104
#define LOGIN_BUTTON_ACTION_SIGNUP_TAG 105
#define LOGIN_BUTTON_ACTION_TOURIST_TAG 106
#define LOGIN_BUTTON_ACTION_FORGOT_PWD_TAG 107

//竞技
#define TOOLBAR_BTN_COMPETITION_TAG 1
//神魔录
#define TOOLBAR_BTN_GOD_DEMON_TAG 2
//排行榜
#define TOOLBAR_BTN_RANKLIST_TAG 3
//好友
#define TOOLBAR_BTN_FRIENDS_TAG 4
//物品
#define TOOLBAR_BTN_ITEMS_TAG 5
//信件
#define TOOLBAR_BTN_MAIL_TAG 6
//设置
#define TOOLBAR_BTN_SETTING_TAG 7

//主页
#define MENUBAR_MAINPAGE_TAG 11
//任务
#define MENUBAR_TASK_TAG 12
//副本
#define MENUBAR_COPY_TAG 13
//英雄
#define MENUBAR_HERO_TAG 14
//门派
#define MENUBAR_GROUP_TAG 15
//商店
#define MENUBAR_SHOP_TAG 16
#endif


// android effect only support ogg
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#define EFFECT_FILE        "effect2.ogg"
#else
#define EFFECT_FILE        "effect1.wav"
#endif // CC_PLATFORM_ANDROID

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#define MUSIC_FILE        "music.mid"
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_BLACKBERRY)
#define MUSIC_FILE        "background.ogg"
#else
#define MUSIC_FILE        "background.mp3"
#endif // CC_PLATFORM_WIN32

/*Function url*/
//User
#define URL_USER_LOGIN                             "/user/login/"
#define URL_USER_REGISTER                          "/user/register/"

//Friends
#define URL_FRIEND_LIST                             "/friend/list/"
#define URL_FRIEND_ADD_NEW                          "/friend/addFriend/"
#define URL_FRIEND_INVITATION_LIST                  "/friend/invitation/"
#define URL_FRIEND_SEARCH                           "/friend/search/"
#define URL_FRIEND_DELETE                           "/friend/delete/"
#define URL_FRIEND_CONFIRM                          "/friend/confirm/"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#define ShowString(text)  WStrToUTF8(L##text)
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#define ShowString(text)  text
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#define ShowString(text)  WStrToUTF8(L##text)
#endif

//Color
#define TITLE_COLOR ccc3(250, 250, 0)

//font
#define FONT_LOGIN "Helvetica-Bold"

