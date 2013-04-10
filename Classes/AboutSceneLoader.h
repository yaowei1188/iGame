//
//  AboutSceneLoader.h
//  cctest
//
//  Created by China Team on 4/9/13.
//
//

#ifndef cctest_AboutSceneLoader_h
#define cctest_AboutSceneLoader_h

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "CCNodeLoader.h"
#include "AboutScene.h"

USING_NS_CC;
USING_NS_CC_EXT;

class AboutSceneLoader : public CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(AboutSceneLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(AboutScene);
};

#endif
