//
//  MainGameScene.cpp
//  cctest
//
//  Created by China Team on 4/9/13.
//
//

#include "MainSceneTemplate.h"


MainSceneTemplate::MainSceneTemplate()
{
    this->mlblName = NULL;
}

MainSceneTemplate::~MainSceneTemplate()
{
    
}

void MainSceneTemplate::onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader)
{
    this->mlblName->setString("sunwukong");
    
    CCSprite *lCap = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("x1.png"));
	CCScale9Sprite *mCap = CCScale9Sprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("x2.png"));
    CCSprite *rCap = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("x3.png"));
    lCap->setPosition(ccp(47,399));
//    mCap->setPosition(ccp(52,399));
//    mCap->setAnchorPoint(ccp(0,0.5));
//    mCap->setContentSize(CCSizeMake(60, 9));
    rCap->setPosition(ccp(102,399));
    
    this->addChild(lCap);
//    this->addChild(mCap);
    this->addChild(rCap);
}

bool MainSceneTemplate::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mlblName", CCLabelTTF*, this->mlblName);
    
    return true;
}

void MainSceneTemplate::toolBarBtnClicked(CCObject *pSender, CCControlEvent pCCControlEvent) {
	CCLOG("button clicked");
}

void MainSceneTemplate::menuBarBtnClicked(CCObject *pSender)
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
            break;
    }
}

SEL_MenuHandler MainSceneTemplate::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "menuBarBtnClicked:", MainSceneTemplate::menuBarBtnClicked);
    
	return NULL;
}

SEL_CCControlHandler MainSceneTemplate::onResolveCCBCCControlSelector(CCObject *pTarget, const char * pSelectorName) {
    
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "toolBarBtnClicked:", MainSceneTemplate::toolBarBtnClicked);
    
	return NULL;
}

bool MainSceneTemplate::init()
{
    return true;
}

CCScene* MainSceneTemplate::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // add layer as a child to scene
    CCLayer* layer = new MainSceneTemplate();
    scene->addChild(layer);
    layer->release();
    
    return scene;
}
