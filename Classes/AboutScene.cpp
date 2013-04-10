//
//  AboutScene.cpp
//  cctest
//
//  Created by China Team on 4/9/13.
//
//

#include "AboutScene.h"

AboutScene::AboutScene()
{
    
}

AboutScene::~AboutScene()
{
    
}

void AboutScene::buttonPressed(CCObject *pSender, CCControlEvent pCCControlEvent)
{

}

SEL_MenuHandler AboutScene::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
	//CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "appleClicked", MainMenuScene::appleClicked);
    
	return NULL;
}

void AboutScene::appleClicked(CCObject *pSender, CCControlEvent pCCControlEvent) {
	CCLOG("button clicked");
}

SEL_CCControlHandler AboutScene::onResolveCCBCCControlSelector(CCObject *pTarget, const char * pSelectorName) {
    
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "buttonPressed:", AboutScene::buttonPressed);
    
	return NULL;
}

bool AboutScene::init()
{
    return true;
}

CCScene* AboutScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // add layer as a child to scene
    CCLayer* layer = new AboutScene();
    scene->addChild(layer);
    layer->release();
    
    return scene;
}