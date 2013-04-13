//
//  FriendListSceneLoader.h
//  cctest
//
//  Created by China Team on 4/9/13.
//
//

#ifndef cctest_FriendListSceneLoader_h
#define cctest_FriendListSceneLoader_h

#include <iostream>
#include "cocos2d.h"
#include "FriendListScene.h"

USING_NS_CC;

class FriendListSceneLoader : public CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(FriendListSceneLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(FriendListScene);
};

#endif
