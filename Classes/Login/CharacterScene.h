#ifndef __CharacterScene_SCENE_H__
#define __CharacterScene_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"

#include "SimpleAudioEngine.h"
#include "MainLayerBase.h"


using namespace cocos2d;
using namespace cocos2d::extension;
using namespace std;

class CharacterScene : public MainLayerBase,
public CCBSelectorResolver,
public CCBMemberVariableAssigner,
public CCNodeLoaderListener
{
public:
    CharacterScene();
    ~CharacterScene();
    
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void requestFinishedCallback(CCNode* pSender,void *p);

    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CharacterScene, create);
    
    void buttonClicked(CCObject *pSender, CCControlEvent pCCControlEvent);
    
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
    
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);

	void doSubmit();

	CCEditBox *m_txtAccount;
    CCSprite *m_ImgGroup;
};

#endif  // __CharacterScene_SCENE_H__