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
    this->mlblHealth = NULL;
    this->mlblPower = NULL;
    this->mlblGold = NULL;
    this->mlblBronze = NULL;
    this->mlblGrade = NULL;
}

MainSceneTemplate::~MainSceneTemplate()
{
    
}

void MainSceneTemplate::onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader)
{
	//wstring ss = L"TEST";
	std::string text = ShowString("你好世界");
	/*std::string text = WStrToUTF8(L"你好世界");*/
	//CCLabelTTF* pLabel = CCLabelTTF::labelWithString(text.c_str(), "Arial", 24);

    this->mlblName->setString(text.c_str());
    this->mlblHealth->setZOrder(20);
    this->mlblPower->setZOrder(10);
    
    CCSpriteBatchNode *batchNode = CCSpriteBatchNode::create("main.png");
    this->addChild(batchNode);
    
    CCSprite *lhCap = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("x1.png"));
	CCScale9Sprite *mhCap = CCScale9Sprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("x2.png"));
    CCSprite *rhCap = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("x3.png"));
    lhCap->setAnchorPoint(ccp(0,0.5));
    lhCap->setPosition(ccp(43,399));
    mhCap->setPosition(ccp(48,399));
    mhCap->setAnchorPoint(ccp(0,0.5));
    mhCap->setContentSize(CCSizeMake(82, 9));
    rhCap->setAnchorPoint(ccp(0,0.5));
    rhCap->setPosition(ccp(130,399));
    
    batchNode->addChild(lhCap);
    this->addChild(mhCap);
    batchNode->addChild(rhCap);
    
    CCSprite *lpCap = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("t1.png"));
	CCScale9Sprite *mpCap = CCScale9Sprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("t2.png"));
    CCSprite *rpCap = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("t3.png"));
    lpCap->setAnchorPoint(ccp(0,0.5));
    lpCap->setPosition(ccp(201,399));
    mpCap->setPosition(ccp(206,399));
    mpCap->setAnchorPoint(ccp(0,0.5));
    mpCap->setContentSize(CCSizeMake(83, 9));
    rpCap->setAnchorPoint(ccp(0,0.5));
    rpCap->setPosition(ccp(289,399));
    
    batchNode->addChild(lpCap);
    this->addChild(mpCap);
    batchNode->addChild(rpCap);
    
//    this->createStroke(mlblHealth, 2, ccc3(255,0,0));
}

bool MainSceneTemplate::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mlblName", CCLabelTTF*, this->mlblName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mlblHealth", CCLabelTTF*, this->mlblHealth);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mlblPower", CCLabelTTF*, this->mlblPower);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mlblBronze", CCLabelTTF*, this->mlblBronze);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mlblGold", CCLabelTTF*, this->mlblGold);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mlblGrade", CCLabelTTF*, this->mlblGrade);
    
    return true;
}

void MainSceneTemplate::toolBarBtnClicked(CCObject *pSender, CCControlEvent pCCControlEvent) {
	CCLOG("button clicked");
}

void MainSceneTemplate::menuBarBtnClicked(CCObject *pSender)
{
    CCMenuItem *button = (CCMenuItem*) pSender;
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
    if(m_delegate != NULL) {
        m_delegate->menuItemClicked(button);
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
