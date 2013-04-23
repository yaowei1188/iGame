//
//  MainMenuScene.h
//  cctest
//
//  Created by China Team on 4/9/13.
//
//

#ifndef __cctest__MainGameScene__
#define __cctest__MainGameScene__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "MainSceneTemplate.h"
#include "MainLayerBase.h"
#include "MainSceneTemplate.h"
#include "common.h"

using namespace cocos2d;
using namespace cocos2d::extension;

class MainGameScene : public MainLayerBase,
  public CCBSelectorResolver,
  public CCBMemberVariableAssigner,
  public CCNodeLoaderListener,
  public MainSceneTemplateDelegate
{
public:
    ~MainGameScene();
    MainGameScene();
    
    // returns a Scene that contains the HelloWorld as the only child
    static cocos2d::CCScene* scene();
    
    void toolBarBtnClicked(CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent);
    
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
    
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    
    virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);
    
    virtual bool init();
    
    MainSceneTemplate *mMainSceneTemp;
    
    CCLayer *mMainLayer;
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(MainGameScene, create);
    bool mblnIsHomePage;
    virtual void menuItemClicked(CCMenuItem *pItem);
    void removeNodeCallBack(CCNode *pNode);
    void removeAndCleanNodeCallBack(CCNode *pNode);
    
public:
    void PushLayer(CCLayer *layer);
    void PopLayer();
    void PopToRoot();
private:
    CCArray *mlayArray;
};

#endif /* defined(__cctest__MainMenuScene__) */
