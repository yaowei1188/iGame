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
    mlayArray = CCArray::create();
    mlayArray->retain();
}

MainGameScene::~MainGameScene()
{
    mlayArray->release();
}

void MainGameScene::onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader)
{
    this->mMainSceneTemp->setdelegate(this);
    this->mlayArray->addObject(mMainLayer);
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
            this->PushLayer((CCLayer *)this->GetLayer("FriendListScene"));
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

void MainGameScene::PushLayer(CCLayer *subLayer)
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCLayer *prevLayer = (CCLayer *)mlayArray->objectAtIndex(mlayArray->count()-1);
    
    CCSequence *sequence = CCSequence::create(CCMoveBy::create(0.2, CCPointMake(-CCDirector::sharedDirector()->getWinSize().width,0)),CCCallFuncN::create(this, callfuncN_selector(MainGameScene::removeNodeCallBack)),NULL);
    
    prevLayer->runAction(sequence);
    
    subLayer->setPosition(ccp(0 + winSize.width,38));
    this->addChild(subLayer);
    subLayer->runAction(CCMoveTo::create(0.2, ccp(0,38)));

    this->mlayArray->addObject(subLayer);
}

void MainGameScene::removeNodeCallBack(CCNode* pNode)
{
    pNode->removeFromParent();
}

void MainGameScene::removeAndCleanNodeCallBack(CCNode* pNode)
{
    pNode->removeFromParentAndCleanup(true);
    mlayArray->removeLastObject();
}

void MainGameScene::PopToRoot()
{
    if (mlayArray->count()<=1) {
        return;
    }
    
    for (int i=mlayArray->count()-2; i>=1; i--) {
        CCLayer *layer = (CCLayer *)mlayArray->objectAtIndex(i);
        layer->removeFromParentAndCleanup(true);
        mlayArray->removeObjectAtIndex(i);
    }
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCLayer *current = (CCLayer *)mlayArray->objectAtIndex(mlayArray->count()-1);
    
    CCSequence *sequence = CCSequence::create(CCMoveBy::create(0.2, CCPointMake(winSize.width,0)),CCCallFuncN::create(this, callfuncN_selector(MainGameScene::removeAndCleanNodeCallBack)),NULL);
    
    current->runAction(sequence);
    
    CCLayer *root = (CCLayer *)mlayArray->objectAtIndex(0);
    
    root->setPosition(ccp(-320, root->getPosition().y));
    this->addChild(root);
    root->runAction(CCMoveTo::create(0.2, ccp(0,root->getPosition().y)));
}

void MainGameScene::PopLayer()
{
    if (mlayArray->count()<=1) {
        return;
    }
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCLayer *current = (CCLayer *)mlayArray->objectAtIndex(mlayArray->count()-1);
    
    CCSequence *sequence = CCSequence::create(CCMoveBy::create(0.2, CCPointMake(winSize.width,0)),CCCallFuncN::create(this, callfuncN_selector(MainGameScene::removeAndCleanNodeCallBack)),NULL);
    
    current->runAction(sequence);
    
    CCLayer *prev = (CCLayer *)mlayArray->objectAtIndex(mlayArray->count()-2);
    prev->setPosition(ccp(-160, prev->getPosition().y));
    this->addChild(prev);
    prev->runAction(CCMoveTo::create(0.2, ccp(0,prev->getPosition().y)));
}

void MainGameScene::menuItemClicked(CCMenuItem *pItem)
{
    if (pItem->getTag() == MENUBAR_MAINPAGE_TAG) {
//        if (mblnIsHomePage) {
//            return;
//        }
//        
//        if (mSubLayer!=NULL) {
//            mSubLayer->removeFromParentAndCleanup(true);
//            mSubLayer = NULL;
//        }
//
//        mMainLayer->setVisible(true);
//        CCActionInterval *action1 = CCMoveTo::create(0.2, ccp(0,mMainLayer->getPosition().y));
//        mMainLayer->runAction(action1);
//        mblnIsHomePage = true;
        this->PopToRoot();
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
