//
//  MainGameScene.cpp
//  cctest
//
//  Created by China Team on 4/9/13.
//
//

#include "MainGameScene.h"
#include "AboutSceneLoader.h"

#define PLAY_BUTTON_TAG 1
#define OPTIONS_BUTTON_TAG 2
#define ABOUT_BUTTON_TAG 3

MainGameScene::MainGameScene()
{
    
}

MainGameScene::~MainGameScene()
{
    //this->cat->release();
}

void MainGameScene::onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader)
{
    //cat->setString("thank you");
}

bool MainGameScene::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
//    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "cat", CCLabelTTF*, this->cat);
    
    return true;
}

void MainGameScene::bottomBtnClicked(CCObject *pSender, CCControlEvent pCCControlEvent)
{
    CCControlButton *button = (CCControlButton*) pSender;
    switch (button->getTag()) {
        case PLAY_BUTTON_TAG:
            CCLOG("11111111111111111");
            
            cat->setString("fuck you");
//            [[CCDirector sharedDirector] replaceScene:[CCTransitionCrossFade transitionWithDuration:1.0 scene:[CCBReader sceneWithNodeGraphFromFile:@"GameScene.ccbi"]]];
            break;
        case OPTIONS_BUTTON_TAG:
//            [[CCDirector sharedDirector] replaceScene:[CCTransitionFlipAngular transitionWithDuration:1.0 scene:[CCBReader sceneWithNodeGraphFromFile:@"OptionsScene.ccbi"]]];
            CCLOG("222222222222222222");
            break;
        case ABOUT_BUTTON_TAG:
//            [[CCDirector sharedDirector] replaceScene:[CCTransitionCrossFade transitionWithDuration:1.0 scene:[CCBReader sceneWithNodeGraphFromFile:@"AboutScene.ccbi"]]];
            CCLOG("3333333333333333333");
            
            //[[CCDirector sharedDirector] replaceScene:[CCTransitionFlipAngular transitionWithDuration:1.0 scene:[CCBReader sceneWithNodeGraphFromFile:@"AboutScene.ccbi"]]];
            //CCDirector::sharedDirector()->replaceScene()
            
            CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
            ccNodeLoaderLibrary->registerCCNodeLoader("AboutScene", AboutSceneLoader::loader());
            
            cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
            ccbReader->autorelease();
            
            CCScene *pScene = ccbReader->createSceneWithNodeGraphFromFile("AboutScene.ccbi");
            CCDirector::sharedDirector()->replaceScene(CCTransitionFlipAngular::create(1.0, pScene));
            break;
    }
}

SEL_MenuHandler MainGameScene::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
	//CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "appleClicked", MainGameScene::appleClicked);
    
	return NULL;
}

void MainGameScene::appleClicked(CCObject *pSender, CCControlEvent pCCControlEvent) {
	CCLOG("button clicked");
}

SEL_CCControlHandler MainGameScene::onResolveCCBCCControlSelector(CCObject *pTarget, const char * pSelectorName) {
    
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "bottomBtnClicked:", MainGameScene::bottomBtnClicked);
    
	return NULL;
}

bool MainGameScene::init()
{
    return true;
}

CCScene* MainGameScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // add layer as a child to scene
    CCLayer* layer = new MainGameScene();
    scene->addChild(layer);
    layer->release();
    
    return scene;
}
