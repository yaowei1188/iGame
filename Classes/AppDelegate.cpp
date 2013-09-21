#include "cocos2d.h"
#include "CCEGLView.h"
#include "AppDelegate.h"

#include "CCTableViewLoader.h"

#include "TaskListSceneLoader.h"
#include "TaskDetailSceneLoader.h"
#include "TaskRewardSceneLoader.h"
#include "MDTaskBoxLayerLoader.h"

#include "FriendListSceneLoader.h"
#include "AddFriendSceneLoader.h"

#include "MainGameSceneLoader.h"
#include "MainOuterLayerLoader.h"
#include "MainInnerLayerLoader.h"
#include "ChatLayerLoader.h"

#include "MDCatalogueLayerLoader.h"
#include "MDCatalogueDetailLayerLoader.h"
#include "MDPackageLayerLoader.h"
#include "MDSettingLayerLoader.h"

#include "LoginSceneLoader.h"
#include "ThirdLoginSceneLoader.h"
#include "RegisterSceneLoader.h"
#include "CharacterSceneLoader.h"
#include "ServerListSceneLoader.h"

#include "NewMailSceneLoader.h"
#include "MailMainSceneLoader.h"


#include "MDCardAlchemyLayerLoader.h"
#include "MDHeroDetailLayerLoader.h"
#include "MDHeroListLayerLoader.h"
#include "MDHeroMainLayerLoader.h"
#include "MDHeroPromoLayerLoader.h"
#include "MDHeroPrePromoLayerLoader.h"
#include "MDHerosFormationLayerLoader.h"

#include "MDSoundManager.h"

//#include "MDBattleLayer.h"

USING_NS_CC;

AppDelegate::AppDelegate()
{
	MDSoundManager::preLoadSound();
}

AppDelegate::~AppDelegate()
{
	MDSoundManager::end();
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

    // turn on display FPS
    pDirector->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);
    
    CCSize screenSize = CCEGLView::sharedOpenGLView()->getFrameSize();
    
    CCSize designSize = CCSizeMake(320, 480);
    CCSize resourceSize = CCSizeMake(320, 480);
    
    std::vector<std::string> searchPaths;
    std::vector<std::string> resDirOrders;
    
	searchPaths.push_back("Task");
	searchPaths.push_back("language");
	searchPaths.push_back("Image");
	searchPaths.push_back("sound");
    searchPaths.push_back("particle");
	searchPaths.push_back("scene");
    searchPaths.push_back("font");
    searchPaths.push_back("data");

    TargetPlatform platform = CCApplication::sharedApplication()->getTargetPlatform();
    if (platform == kTargetIphone || platform == kTargetIpad)
    {
        if (screenSize.height > 480)
        {
            resourceSize = CCSizeMake(640, 960);
            resDirOrders.push_back("resources-iphonehd");
        }
        else
        {
            resDirOrders.push_back("resources-iphone");
        }
    }
    else if (platform == kTargetAndroid)
    {
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
    }
	else if (platform == kTargetWindows)
	{
		if (screenSize.height > 480)
		{
			resourceSize = CCSizeMake(640, 960);
			resDirOrders.push_back("resources-iphonehd");
		}
		else
		{
			resDirOrders.push_back("resources-iphone");
		}
	}

	CCFileUtils::sharedFileUtils()->setSearchPaths(searchPaths);
	CCFileUtils::sharedFileUtils()->setSearchResolutionsOrder(resDirOrders);
    
    pDirector->setContentScaleFactor(resourceSize.width/designSize.width);
    
    CCEGLView::sharedOpenGLView()->setDesignResolutionSize(designSize.width, designSize.height, kResolutionShowAll);
    
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    ccNodeLoaderLibrary->registerCCNodeLoader("MainGameScene", MainGameSceneLoader::loader());
    ccNodeLoaderLibrary->registerCCNodeLoader("LoginScene", LoginSceneLoader::loader());
    ccNodeLoaderLibrary->registerCCNodeLoader("CCTableView", CCTableViewLoader::loader());
//    ccNodeLoaderLibrary->registerCCNodeLoader("MainOuterLayer", MainOuterLayerLoader::loader());
    ccNodeLoaderLibrary->registerCCNodeLoader("MainInnerLayer", MainInnerLayerLoader::loader());
    ccNodeLoaderLibrary->registerCCNodeLoader("MainOuterLayer", MainOuterLayerLoader::loader());   
    ccNodeLoaderLibrary->registerCCNodeLoader("FriendListScene", FriendListSceneLoader::loader());
    ccNodeLoaderLibrary->registerCCNodeLoader("AddFriendScene", AddFriendSceneLoader::loader());
    ccNodeLoaderLibrary->registerCCNodeLoader("ThirdLoginScene", ThirdLoginSceneLoader::loader());
    ccNodeLoaderLibrary->registerCCNodeLoader("NewMailScene", NewMailSceneLoader::loader());
	ccNodeLoaderLibrary->registerCCNodeLoader("ServerListScene", ServerListSceneLoader::loader());
	ccNodeLoaderLibrary->registerCCNodeLoader("CharacterScene", CharacterSceneLoader::loader());
    ccNodeLoaderLibrary->registerCCNodeLoader("TaskListScene", TaskListSceneLoader::loader());
    ccNodeLoaderLibrary->registerCCNodeLoader("TaskDetailScene", TaskDetailSceneLoader::loader());
    ccNodeLoaderLibrary->registerCCNodeLoader("TaskRewardScene", TaskRewardSceneLoader::loader());
    ccNodeLoaderLibrary->registerCCNodeLoader("RegisterScene", RegisterSceneLoader::loader());
    ccNodeLoaderLibrary->registerCCNodeLoader("MailMainScene", MailMainSceneLoader::loader());
    ccNodeLoaderLibrary->registerCCNodeLoader("ChatLayer", ChatLayerLoader::loader());
    ccNodeLoaderLibrary->registerCCNodeLoader("MDCardAlchemyLayer", MDCardAlchemyLayerLoader::loader());
	ccNodeLoaderLibrary->registerCCNodeLoader("MDHeroDetailLayer", MDHeroDetailLayerLoader::loader());
    ccNodeLoaderLibrary->registerCCNodeLoader("MDHeroListLayer", MDHeroListLayerLoader::loader());
    ccNodeLoaderLibrary->registerCCNodeLoader("MDHeroMainLayer", MDHeroMainLayerLoader::loader());
    ccNodeLoaderLibrary->registerCCNodeLoader("MDHeroPromoLayer", MDHeroPromoLayerLoader::loader());
    ccNodeLoaderLibrary->registerCCNodeLoader("MDHeroPrePromoLayer", MDHeroPrePromoLayerLoader::loader());
    ccNodeLoaderLibrary->registerCCNodeLoader("MDHerosFormationLayer", MDHerosFormationLayerLoader::loader());

    ccNodeLoaderLibrary->registerCCNodeLoader("MDPackageLayer", MDPackageLayerLoader::loader());
    ccNodeLoaderLibrary->registerCCNodeLoader("MDCatalogueDetailLayer", MDCatalogueDetailLayerLoader::loader());
    ccNodeLoaderLibrary->registerCCNodeLoader("MDCatalogueLayer", MDCatalogueLayerLoader::loader());
    ccNodeLoaderLibrary->registerCCNodeLoader("MDSettingLayer", MDSettingLayerLoader::loader());
    ccNodeLoaderLibrary->registerCCNodeLoader("MDTaskBoxLayer", MDTaskBoxLayerLoader::loader());

    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    ccbReader->autorelease();
    
//    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("login.plist");
//    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("main.plist");
//    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("friends.plist");
//    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("card.plist");

	//SimpleAudioEngine::sharedEngine()->playBackgroundMusic(MUSIC_FILE, true);
	MDSoundManager::playBackgroundMusic();
    
    CCScene *pScene = ccbReader->createSceneWithNodeGraphFromFile("LoginScene.ccbi");


//	CCScene *pScene = MDBattleLayer::scene();
	//CCScene *pScene = MailListScene::scene();
//    CCScene *pScene = ccbReader->createSceneWithNodeGraphFromFile("MDHeroPrePromoLayer.ccbi");
    //CCScene *pScene = ccbReader->createSceneWithNodeGraphFromFile("CharacterScene.ccbi");
//    CCScene *pScene = ccbReader->createSceneWithNodeGraphFromFile("TaskListScene.ccbi");
//    CCScene *pScene = ccbReader->createSceneWithNodeGraphFromFile("MainGameScene.ccbi");
//    CCScene *pScene = ccbReader->createSceneWithNodeGraphFromFile("MDHerosFormationLayer");
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();

	MDSoundManager::pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();

    MDSoundManager::resumeBackgroundMusic();
}
