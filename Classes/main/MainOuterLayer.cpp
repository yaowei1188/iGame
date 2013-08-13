//
//  MainGameScene.cpp
//  cctest
//
//  Created by China Team on 4/9/13.
//
//

#include "MainOuterLayer.h"

MainOuterLayer::MainOuterLayer()
{
    this->m_scrollLabel = NULL;
}

MainOuterLayer::~MainOuterLayer()
{
//    CC_SAFE_RELEASE(mlblName);
}


void MainOuterLayer::onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader)
{
    m_scrollLabel = MDScrollLabel::create("this is a test word this is a test word this is a test word this is a test word this is a test word this is a test word this is a test word this is a test word this is a test word!!!", CCSizeMake(320, 40), "Arial", 14);
//    m_scrollLabel->autoScroll();
    this->addChild(m_scrollLabel);
    m_scrollLabel->setPosition(ccp(160,457));

}

bool MainOuterLayer::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
//    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mlblName", CCLabelTTF*, this->mlblName);
    
    return true;
}

void MainOuterLayer::toolBarBtnClicked(CCObject *pSender, CCControlEvent pCCControlEvent) {
	CCLOG("button clicked");
}

void MainOuterLayer::menuBarBtnClicked(CCObject *pSender)
{
    CCMenuItem *button = (CCMenuItem*) pSender;
    if(m_delegate != NULL) {
        m_delegate->menuItemClickedCallBack(button);
    }
}

SEL_MenuHandler MainOuterLayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "menuBarBtnClicked:", MainOuterLayer::menuBarBtnClicked);
	return NULL;
}

SEL_CCControlHandler MainOuterLayer::onResolveCCBCCControlSelector(CCObject *pTarget, const char * pSelectorName) {
    
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "toolBarBtnClicked:", MainOuterLayer::toolBarBtnClicked);
	return NULL;
}

bool MainOuterLayer::init()
{
    return true;
}
