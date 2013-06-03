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
#include "NewMailSceneLoader.h"
#include "MailMainScene.h"

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
    
    CCSize screenSize = CCEGLView::sharedOpenGLView()->getFrameSize();
    
    CCSize designSize = CCSizeMake(320, 480);
    CCSize resourceSize = CCSizeMake(320, 480);
    
    std::vector<std::string> searchPaths;
    std::vector<std::string> resDirOrders;
    
    TargetPlatform platform = CCApplication::sharedApplication()->getTargetPlatform();
    if (platform == kTargetIphone || platform == kTargetIpad)
    {
        searchPaths.push_back("Image");
        //searchPaths.push_back("ccbResources");
        CCFileUtils::sharedFileUtils()->setSearchPaths(searchPaths);
        
        if (screenSize.height > 480)
        {
            resourceSize = CCSizeMake(640, 960);
            resDirOrders.push_back("resources-iphonehd");
        }
        else
        {
            resDirOrders.push_back("resources-iphone");
        }
        
        CCFileUtils::sharedFileUtils()->setSearchResolutionsOrder(resDirOrders);
    }
    else if (platform == kTargetAndroid)
    {
		searchPaths.push_back("Image");
		//searchPaths.push_back("ccbResources");
		CCFileUtils::sharedFileUtils()->setSearchPaths(searchPaths);

		if (screenSize.height > 960)
		{
			resourceSize = CCSizeMake(640, 960);
			resDirOrders.push_back("resources-iphonehd");
		}
		else if (screenSize.height > 480)
		{
			resourceSize = CCSizeMake(640, 960);
			resDirOrders.push_back("resources-iphonehd");
		}
		else
		{
			resDirOrders.push_back("resources-iphone");
		}

		CCFileUtils::sharedFileUtils()->setSearchResolutionsOrder(resDirOrders);
    }
	else if (platform == kTargetWindows)
	{
		searchPaths.push_back("Image");
		//searchPaths.push_back("ccbResources");
		CCFileUtils::sharedFileUtils()->setSearchPaths(searchPaths);

		//resourceSize = CCSizeMake(640, 960);
		//resDirOrders.push_back("resources-iphonehd");
		if (screenSize.height > 480)
		{
			resourceSize = CCSizeMake(640, 960);
			resDirOrders.push_back("resources-iphonehd");
		}
		else
		{
			resDirOrders.push_back("resources-iphone");
		}

		CCFileUtils::sharedFileUtils()->setSearchResolutionsOrder(resDirOrders);
	}
    
    pDirector->setContentScaleFactor(resourceSize.width/designSize.width);
    
    CCEGLView::sharedOpenGLView()->setDesignResolutionSize(designSize.width, designSize.height, kResolutionShowAll);
    
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
    ccNodeLoaderLibrary->registerCCNodeLoader("NewMailScene", NewMailSceneLoader::loader());

    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    ccbReader->autorelease();
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("login.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("main.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("friends.plist");
    
    CCScene *pScene = ccbReader->createSceneWithNodeGraphFromFile("LoginScene.ccbi");

	//CCScene *pScene = MailMainScene::scene();
//    CCScene *pScene = ccbReader->createSceneWithNodeGraphFromFile("ivantest.ccbi");
//    CCScene *pScene = ccbReader->createSceneWithNodeGraphFromFile("MainGameScene.ccbi");
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
