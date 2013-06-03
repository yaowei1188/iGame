//
//  AddFriendSceneLoader.h
//  cctest
//
//  Created by China Team on 4/9/13.
//
//

#ifndef cctest_AddFriendSceneLoader_h
#define cctest_AddFriendSceneLoader_h

#include <iostream>
#include "cocos2d.h"
#include "AddFriendScene.h"

USING_NS_CC;

class AddFriendSceneLoader : public CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(AddFriendSceneLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(AddFriendScene);
};

#endif
