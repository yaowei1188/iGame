//
//  AboutSceneLoader.h
//  cctest
//
//  Created by China Team on 4/9/13.
//
//

#ifndef cctest_RegisterSceneLoader_h
#define cctest_RegisterSceneLoader_h

#include <iostream>
#include "cocos2d.h"
#include "RegisterScene.h"

USING_NS_CC;

class RegisterSceneLoader : public CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(RegisterSceneLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(RegisterScene);
};

#endif
