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
    mMainLayer = NULL;
    mblnIsHomePage = true;
}

MainGameScene::~MainGameScene()
{

}

void MainGameScene::onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader)
{
    this->mMainSceneTemp->setdelegate(this);
}

bool MainGameScene::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mMainSceneTemp", MainSceneTemplate*, this->mMainSceneTemp);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mMainLayer", CCLayer*, this->mMainLayer);
    
    return true;
}

void MainGameScene::toolBarBtnClicked(CCObject *pSender, CCControlEvent pCCControlEvent) {
    CCControlButton *button = (CCControlButton*) pSender;
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
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
            mblnIsHomePage = false;

            mSubLayer = (CCLayer *)this->GetLayer("FriendListScene");
            mSubLayer->setPosition(ccp(0 + winSize.width,38));
            this->addChild(mSubLayer);
            this->mSubLayer->runAction(CCMoveTo::create(0.2, ccp(0,38)));
            
            //this->mMainLayer->runAction(CCMoveBy::create(0.3, CCPointMake(-CCDirector::sharedDirector()->getWinSize().width,0)));
            this->mMainLayer->setVisible(false);
            this->mMainLayer->setPosition(CCPointMake(-CCDirector::sharedDirector()->getWinSize().width,this->mMainLayer->getPosition().y));
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
    

}

void MainGameScene::menuItemClicked(CCMenuItem *pItem)
{
    if (pItem->getTag() == MENUBAR_MAINPAGE_TAG) {
        if (mblnIsHomePage) {
            return;
        }
        
        if (mSubLayer!=NULL) {
            mSubLayer->removeFromParentAndCleanup(true);
            mSubLayer = NULL;
        }
        
        mMainLayer->setVisible(true);
        CCActionInterval *action1 = CCMoveTo::create(0.2, ccp(0,mMainLayer->getPosition().y));
        mMainLayer->runAction(action1);
        mblnIsHomePage = true;
        
    }
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
