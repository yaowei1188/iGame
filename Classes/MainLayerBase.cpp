//
//  MainLayerBase.cpp
//  iGame
//
//  Created by yao on 13-4-20.
//
//

#include "MainLayerBase.h"

void MainLayerBase::OpenNewScene(const char *pCCBFileName)
{
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    ccbReader->autorelease();
    
    CCScene *pScene = ccbReader->createSceneWithNodeGraphFromFile(pCCBFileName);
    CCDirector::sharedDirector()->replaceScene(CCTransitionMoveInR::create(0.3, pScene));
}

void MainLayerBase::PushScene(const char *pCCBFileName)
{
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    ccbReader->autorelease();
    
    CCScene *pScene = ccbReader->createSceneWithNodeGraphFromFile(pCCBFileName);
    CCDirector::sharedDirector()->pushScene(CCTransitionMoveInR::create(0.3, pScene));
}

CCNode* MainLayerBase::GetLayer(const char *pCCBFileName)
{
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    ccbReader->autorelease();
    
    return ccbReader->readNodeGraphFromFile(pCCBFileName);
}
