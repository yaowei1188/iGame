//
//  MainMenuScene.h
//  cctest
//
//  Created by China Team on 4/9/13.
//
//

#ifndef __MainOuterLayer__
#define __MainOuterLayer__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "common.h"
#include "MainLayerBase.h"
#include "StringExt.h"
//#include "MDProgressBar.h"

using namespace cocos2d;
using namespace cocos2d::extension;

/**
 * Data source that governs table backend data.
 */
class MainOuterLayerDelegate
{
public:

    virtual void menuItemClickedCallBack(CCMenuItem *pItem) = 0;

};

class MainOuterLayer : public MainLayerBase,
  public CCBSelectorResolver,
  public CCBMemberVariableAssigner,
  public CCNodeLoaderListener
{
public:
    ~MainOuterLayer();
    MainOuterLayer();

    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(MainOuterLayer, create);
    CC_SYNTHESIZE(MainOuterLayerDelegate*, m_delegate, Delegate);
private:
    void menuBarBtnClicked(CCObject *pSender);
    void toolBarBtnClicked(CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent);
    
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
    
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);
    
    virtual bool init();

//	CCLabelTTF *mlblName;
//	CCLabelTTF *mlblHealth;
//	CCLabelTTF *mlblPower;
//
//	CCLabelTTF *mlblGold;
//	CCLabelTTF *mlblBronze;
//	CCLabelTTF *mlblGrade;
//	CCSprite   *m_sPlayerContainer;
//
//    MDProgressBar *hpBar;
//    MDProgressBar *expBar;
//public:
//    void updateUserInfo(int hp,int maxhp,int exp,int maxExp,int grade,int gold);
};

#endif
