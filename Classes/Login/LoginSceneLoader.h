//
//  AboutSceneLoader.h
//  cctest
//
//  Created by China Team on 4/9/13.
//
//

#ifndef cctest_LoginSceneLoader_h
#define cctest_LoginSceneLoader_h

#include <iostream>
#include "cocos2d.h"
#include "LoginScene.h"

USING_NS_CC;

class LoginSceneLoader : public CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(LoginSceneLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(LoginScene);
};

#endif
