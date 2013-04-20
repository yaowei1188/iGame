//
//  MainLayerBase.h
//  iGame
//
//  Created by yao on 13-4-20.
//
//

#ifndef __iGame__MainLayerBase__
#define __iGame__MainLayerBase__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"

using namespace cocos2d;
using namespace cocos2d::extension;

class MainLayerBase : public cocos2d::CCLayer
{
protected:
    void OpenNewScene(const char *pCCBFileName);
    void PushScene(const char *pCCBFileName);
    CCNode* GetLayer(const char *pCCBFileName);
};

#endif /* defined(__iGame__MainLayerBase__) */
