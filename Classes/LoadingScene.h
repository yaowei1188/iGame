//
//  LoadingScene.h
//  cctest
//
//  Created by China Team on 4/9/13.
//
//

#ifndef __IGAME__LoadingScene__
#define __IGAME__LoadingScene__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"

using namespace cocos2d;
using namespace cocos2d::extension;

class LoadingScene : public cocos2d::CCLayer {
public:
    ~LoadingScene();
    LoadingScene();
    
    void buttonPressed(CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent);
    
    CREATE_FUNC(LoadingScene);
    
    virtual bool init();
    
};

#endif /* defined(__cctest__LoadingScene__) */
