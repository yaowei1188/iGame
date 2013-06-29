#ifndef __ThirdLoginScene_SCENE_H__
#define __ThirdLoginScene_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"

#include "MainGameScene.h"
#include "MainSceneTemplate.h"
#include "MainLayerBase.h"

using namespace cocos2d;
using namespace cocos2d::extension;

class ThirdLoginScene : public MainLayerBase,
public CCBSelectorResolver,
public CCBMemberVariableAssigner,
public CCNodeLoaderListener
{
public:
    ThirdLoginScene();
    ~ThirdLoginScene();
    
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void requestFinishedCallback(CCHttpClient* client, CCHttpResponse* response);

    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(ThirdLoginScene, create);
    
    void buttonClicked(CCObject *pSender, CCControlEvent pCCControlEvent);
    
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
    
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);
    void callbackSwitch(CCObject* pSender);

	void doSubmit();
	void parseJson();

	CCEditBox *m_txtAccount;
	CCEditBox *m_txtPassword;

    bool m_blnRememberMe;
};

#endif  // __ThirdLoginScene_SCENE_H__