#ifndef __CHAT_LAYER_H__
#define __CHAT_LAYER_H__

#include "cocos2d.h"
#include "cocos-ext.h"

#include "common.h"
#include "MainLayerBase.h"
//#include "MainGameScene.h"

using namespace cocos2d;
using namespace cocos2d::extension;

class ChatLayer : public MainLayerBase,
public CCBSelectorResolver,
public CCBMemberVariableAssigner,
public CCNodeLoaderListener
{
public:
    ChatLayer();
    ~ChatLayer();
    
    virtual bool init();  

//    static cocos2d::CCScene* scene();
    
    // a selector callback


    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(ChatLayer, create);
    

//	void parseJson();
private:
    
    void requestFinishedCallback(CCNode* pSender,void *p);
    
    void buttonClicked(CCObject *pSender, CCControlEvent pCCControlEvent);
    
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
    
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);
    void callbackSwitch(CCObject* pSender);
    
	void doSubmit();
    
    void menuCallback(CCObject* sender);

	CCEditBox *m_txtAccount;
	CCEditBox *m_txtPassword;

    bool m_blnRememberMe;
};

#endif  // __CHAT_LAYER_H__
