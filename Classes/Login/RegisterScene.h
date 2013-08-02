#ifndef __RegisterScene_SCENE_H__
#define __RegisterScene_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"

#include "XmlParser.h"
#include "MainLayerBase.h"

using namespace cocos2d;
using namespace cocos2d::extension;

class RegisterScene : public MainLayerBase,
public CCBSelectorResolver,
public CCBMemberVariableAssigner,
public CCNodeLoaderListener
{
public:
    RegisterScene();
    ~RegisterScene();
    
    virtual bool init();  

    static cocos2d::CCScene* scene();
    
    // a selector callback
    void requestFinishedCallback(CCHttpClient* client, CCHttpResponse* response);

    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(RegisterScene, create);
    
    void menuBarBtnClicked(CCObject *pSender);
    void buttonClicked(CCObject *pSender, CCControlEvent pCCControlEvent);
    
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
    
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);

	void doSubmit();
	void parseJson(std::string& content);

	CCEditBox *m_txtAccount;
	CCEditBox *m_txtPassword;
    
};

#endif  // __RegisterScene_SCENE_H__