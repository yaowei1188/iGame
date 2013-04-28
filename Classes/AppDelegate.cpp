#include "cocos2d.h"
#include "CCEGLView.h"
#include "AppDelegate.h"
#include "SimpleAudioEngine.h"
#include "FriendListScene.h"
#include "LoginScene.h"
#include "MainGameScene.h"
#include "MainGameSceneLoader.h"
#include "LoginSceneLoader.h"
#include "CCEditBoxLoader.h"
#include "FriendListSceneLoader.h"
#include "CCTableViewLoader.h"
#include "TaskListSceneLoader.h"
#include "AddFriendSceneLoader.h"
#include "MainSceneTemplateLoader.h"
#include "CCControlSwitchLoader.h"
#include "ThirdLoginSceneLoader.h"

using namespace CocosDenshion;

USING_NS_CC;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
    SimpleAudioEngine::end();
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);
    
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    ccNodeLoaderLibrary->registerCCNodeLoader("MainGameScene", MainGameSceneLoader::loader());
    ccNodeLoaderLibrary->registerCCNodeLoader("LoginScene", LoginSceneLoader::loader());
    ccNodeLoaderLibrary->registerCCNodeLoader("CCEditBox", CCEditBoxLoader::loader());
    ccNodeLoaderLibrary->registerCCNodeLoader("CCControlSwitch", CCControlSwitchLoader::loader());
    ccNodeLoaderLibrary->registerCCNodeLoader("CCTableView", CCTableViewLoader::loader());
    ccNodeLoaderLibrary->registerCCNodeLoader("MainSceneTemplate", MainSceneTemplateLoader::loader());    
    ccNodeLoaderLibrary->registerCCNodeLoader("FriendListScene", FriendListSceneLoader::loader());
    ccNodeLoaderLibrary->registerCCNodeLoader("TaskListScene", TaskListSceneLoader::loader());
    ccNodeLoaderLibrary->registerCCNodeLoader("AddFriendScene", AddFriendSceneLoader::loader());
    ccNodeLoaderLibrary->registerCCNodeLoader("ThirdLoginScene", ThirdLoginSceneLoader::loader());
    
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    ccbReader->autorelease();
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Image/login.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Image/main.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Image/login.plist");
    
    CCScene *pScene = ccbReader->createSceneWithNodeGraphFromFile("LoginScene.ccbi");
//        CCScene *pScene = ccbReader->createSceneWithNodeGraphFromFile("MainGameScene.ccbi");
//    CCScene *pScene = ccbReader->createSceneWithNodeGraphFromFile("FriendListScene.ccbi");
//    CCScene *pScene = ccbReader->createSceneWithNodeGraphFromFile("TaskListScene.ccbi");
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();

    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();

    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
