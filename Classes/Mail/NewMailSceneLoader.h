//
//  NewMailScene loader.h
//  cctest
//
//  Created by China Team on 4/9/13.
//
//

#ifndef cctest_NewMailSceneLoader_h
#define cctest_NewMailSceneLoader_h

#include <iostream>
#include "cocos2d.h"
#include "NewMailScene.h"

USING_NS_CC;

class NewMailSceneLoader : public CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(NewMailSceneLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(NewMailScene);
};

#endif
