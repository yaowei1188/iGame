#include "MDHeroMainLayer.h"
#include "MainGameScene.h"

using namespace cocos2d;

MDHeroMainLayer::MDHeroMainLayer()
{

}

MDHeroMainLayer::~MDHeroMainLayer()
{
    
}

CCScene* MDHeroMainLayer::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        MDHeroMainLayer *layer = MDHeroMainLayer::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MDHeroMainLayer::init()
{
    bool bRet = false;
    do 
    {
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////

        CC_BREAK_IF(! CCLayer::init());

        ////////////////////////////////////////////////////////////////////////////
        //// add your codes below...
        ////////////////////////////////////////////////////////////////////////////
        
        bRet = true;
    } while (0);

    return bRet;
}

void MDHeroMainLayer::doSubmit()
{

}

void MDHeroMainLayer::requestFinishedCallback(CCNode* pSender,void *data)
{

}

void MDHeroMainLayer::onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader)
{
}

bool MDHeroMainLayer::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    return true;
}

void MDHeroMainLayer::buttonClicked(CCObject *pSender, CCControlEvent pCCControlEvent) {
    
    CCControlButton *button = (CCControlButton*) pSender;
    
    switch (button->getTag()) {
        case 101:
        {
            CCLOG("hunji");
            break;
        }
        case 102:
        {
            CCLOG("buzhen");
            break;
        }
        case 103:
        {
            CCLOG("yingxiongdian");
            MainGameScene *mainScene = (MainGameScene *)this->getParent();
            mainScene->PushLayer((CCLayer *)this->GetLayer("MDHeroListLayer"));
            break;
        }
        case 104:
        {
            CCLOG("ronghetang");
            break;
        }
        case 105:
        {
            CCLOG("feishengge");
            break;
        }
    }
}

SEL_MenuHandler MDHeroMainLayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
	return NULL;
}

SEL_CCControlHandler MDHeroMainLayer::onResolveCCBCCControlSelector(CCObject *pTarget, const char * pSelectorName) {
    
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "buttonClicked:", MDHeroMainLayer::buttonClicked);
	return NULL;
}

