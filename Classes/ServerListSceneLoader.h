//
//  ServerListSceneLoader.h
//  cctest
//
//  Created by China Team on 4/9/13.
//
//

#ifndef cctest_ServerListSceneLoader_h
#define cctest_ServerListSceneLoader_h

#include <iostream>
#include "cocos2d.h"
#include "ServerListScene.h"

USING_NS_CC;

class ServerListSceneLoader : public CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(ServerListSceneLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(ServerListScene);
};

#endif
