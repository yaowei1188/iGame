//
//  MainMenuSceneLoader.h
//  cctest
//
//  Created by China Team on 4/9/13.
//
//

#ifndef __MainGameSceneLoader__
#define __MainGameSceneLoader__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "MainGameScene.h"

USING_NS_CC;
USING_NS_CC_EXT;

class MainGameSceneLoader : public CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(MainGameSceneLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(MainGameScene);
};

#endif /* defined(__MainGameSceneLoader__) */
