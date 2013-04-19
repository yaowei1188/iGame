//
//  AboutSceneLoader.h
//  cctest
//
//  Created by China Team on 4/9/13.
//
//

#ifndef cctest_ThirdLoginSceneLoader_h
#define cctest_ThirdLoginSceneLoader_h

#include <iostream>
#include "cocos2d.h"
#include "ThirdLoginScene.h"

USING_NS_CC;

class ThirdLoginSceneLoader : public CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(ThirdLoginSceneLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(ThirdLoginScene);
};

#endif
