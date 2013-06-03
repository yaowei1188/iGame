//
//  MailListSceneLoader.h
//  cctest
//
//  Created by China Team on 4/9/13.
//
//

#ifndef cctest_MailListSceneLoader_h
#define cctest_MailListSceneLoader_h

#include <iostream>
#include "cocos2d.h"
#include "MailListScene.h"

USING_NS_CC;

class MailListSceneLoader : public CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(MailListSceneLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(MailListScene);
};

#endif
