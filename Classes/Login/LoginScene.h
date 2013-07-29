#ifndef __LOGINSCENE_SCENE_H__
#define __LOGINSCENE_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"

#include "XmlParser.h"
#include "MainLayerBase.h"
#include "MainSceneTemplate.h"

using namespace cocos2d;
using namespace cocos2d::extension;

class LoginScene : public MainLayerBase,
public CCBSelectorResolver,
public CCBMemberVariableAssigner,
public CCNodeLoaderListener
{
public:
    LoginScene();
    ~LoginScene();
    
    virtual bool init();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(LoginScene, create);

private:

    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
    
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);

    // a selector callback
    void requestFinishedCallback(CCHttpClient* client, CCHttpResponse* response);

    void menuBarBtnClicked(CCObject *pSender);
    void buttonClicked(CCObject *pSender, CCControlEvent pCCControlEvent);
    void switchCallback(CCObject* pSender);
	void doSubmit();

	CCEditBox *m_txtAccount;
	CCEditBox *m_txtPassword;
    
    bool m_blnRememberMe;
};

#endif  // __LOGINSCENE_SCENE_H__