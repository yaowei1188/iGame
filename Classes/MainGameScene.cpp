//
//  MainGameScene.cpp
//  cctest
//
//  Created by China Team on 4/9/13.
//
//

#include "MainGameScene.h"
#include "AboutSceneLoader.h"

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

MainGameScene::MainGameScene()
{
    
}

MainGameScene::~MainGameScene()
{
    this->mlblName->release();
}

void MainGameScene::onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader)
{
    this->mlblName->setString("孙悟空");
}

bool MainGameScene::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mlblName", CCLabelTTF*, this->mlblName);
    
    return true;
}

void MainGameScene::toolBarBtnClicked(CCObject *pSender, CCControlEvent pCCControlEvent) {
	CCLOG("button clicked");
}

void MainGameScene::menuBarBtnClicked(CCObject *pSender, CCControlEvent pCCControlEvent)
{
    CCControlButton *button = (CCControlButton*) pSender;
    switch (button->getTag()) {
        case TOOLBAR_BTN_COMPETITION_TAG:
            CCLOG("11111");
            break;
        case TOOLBAR_BTN_GOD_DEMON_TAG:
            CCLOG("22222");
            break;
        case TOOLBAR_BTN_RANKLIST_TAG:
            CCLOG("33333");
            break;
        case TOOLBAR_BTN_FRIENDS_TAG:
            CCLOG("44444");
            break;
        case TOOLBAR_BTN_ITEMS_TAG:
            CCLOG("55555");
            break;
        case TOOLBAR_BTN_MAIL_TAG:
            CCLOG("66666");
            break;
        case TOOLBAR_BTN_SETTING_TAG:
            CCLOG("77777");
            
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
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "menuBarBtnClicked:", MainGameScene::menuBarBtnClicked);
    
	return NULL;
}

SEL_CCControlHandler MainGameScene::onResolveCCBCCControlSelector(CCObject *pTarget, const char * pSelectorName) {
    
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "toolBarBtnClicked:", MainGameScene::toolBarBtnClicked);
    
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
