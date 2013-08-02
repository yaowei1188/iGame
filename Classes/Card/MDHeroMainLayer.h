#ifndef __HERO_MAIN_LAYER_H__
#define __HERO_MAIN_LAYER_H__

#include "cocos2d.h"
#include "cocos-ext.h"


#include "common.h"
#include "MainGameScene.h"
#include "MainLayerBase.h"

using namespace cocos2d;
using namespace cocos2d::extension;

class MDHeroMainLayer : public MainLayerBase,
public CCBSelectorResolver,
public CCBMemberVariableAssigner,
public CCNodeLoaderListener
{
public:
    MDHeroMainLayer();
    ~MDHeroMainLayer();
    
    virtual bool init();  

    static cocos2d::CCScene* scene();
    
    // a selector callback
    void requestFinishedCallback(CCNode* pSender,void *p);

    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(MDHeroMainLayer, create);
    
    void buttonClicked(CCObject *pSender, CCControlEvent pCCControlEvent);
    
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
    
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);

	void doSubmit();
};

#endif  // __HERO_MAIN_LAYER_H__
