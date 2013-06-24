//
//  MailMainSceneLoader.h
//  cctest
//
//  Created by China Team on 4/9/13.
//
//

#ifndef cctest_MailMainSceneLoader_h
#define cctest_MailMainSceneLoader_h

#include <iostream>
#include "cocos2d.h"
#include "MailMainScene.h"

USING_NS_CC;

class MailMainSceneLoader : public CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(MailMainSceneLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(MailMainScene);
};

#endif
