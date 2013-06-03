//
//  LoadingScene.cpp
//  cctest
//
//  Created by China Team on 4/9/13.
//
//

#include "LoadingScene.h"

LoadingScene::LoadingScene()
{

}

LoadingScene::~LoadingScene()
{
    
}

void LoadingScene::buttonPressed(CCObject *pSender, CCControlEvent pCCControlEvent)
{

}

bool LoadingScene::init()
{
    bool bRet = false;
    do
    {
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////
        
        CC_BREAK_IF(! CCLayer::init());
        
        CCSize s = CCDirector::sharedDirector()->getWinSize();
        
        CCProgressTo *to1 = CCProgressTo::create(1, 100);
        
        CCProgressTimer *left = CCProgressTimer::create(CCSprite::create("Icon.png"));
        left->setType( kCCProgressTimerTypeRadial );
        addChild(left);
        left->setPosition(ccp(s.width/2, s.height/2));
        left->runAction( CCRepeatForever::create(to1));
        
        bRet = true;
    } while (0);
    
    return bRet;
}
