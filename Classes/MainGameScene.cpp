//
//  MainGameScene.cpp
//  cctest
//
//  Created by China Team on 4/9/13.
//
//

#include "MainGameScene.h"

MainGameScene::MainGameScene()
{
    mMainSceneTemp = NULL;
    mLayer = NULL;
}

MainGameScene::~MainGameScene()
{

}

void MainGameScene::onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader)
{

}

bool MainGameScene::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mMainSceneTemp", MainSceneTemplate*, this->mMainSceneTemp);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLayer", CCLayer*, this->mLayer);
    
    return true;
}

void MainGameScene::toolBarBtnClicked(CCObject *pSender, CCControlEvent pCCControlEvent) {
    CCControlButton *button = (CCControlButton*) pSender;
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    switch (button->getTag()) {
        case TOOLBAR_BTN_COMPETITION_TAG:
            CCLOG("11111");
            this->mLayer->runAction(CCMoveBy::create(0.5, ccp(-CCDirector::sharedDirector()->getWinSize().width,0)));
            
            break;
        case TOOLBAR_BTN_GOD_DEMON_TAG:
            CCLOG("22222");
            break;
        case TOOLBAR_BTN_RANKLIST_TAG:
            CCLOG("33333");
            break;
        case TOOLBAR_BTN_FRIENDS_TAG:
            CCLOG("44444");
            this->PushScene("FriendListScene");
            break;
        case TOOLBAR_BTN_ITEMS_TAG:
            CCLOG("55555");
            break;
        case TOOLBAR_BTN_MAIL_TAG:
            CCLOG("66666");
            break;
        case TOOLBAR_BTN_SETTING_TAG:
            CCLOG("77777");
            break;
    }
    
    CCLayer *layer = (CCLayer *)this->GetLayer("FriendListScene");
    layer->setPosition(ccp(0,38));
    this->addChild(layer);
}

SEL_MenuHandler MainGameScene::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
//	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "menuBarBtnClicked:", MainGameScene::menuBarBtnClicked);
//    
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
