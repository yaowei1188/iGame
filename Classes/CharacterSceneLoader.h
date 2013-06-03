//
//  AboutSceneLoader.h
//  cctest
//
//  Created by China Team on 4/9/13.
//
//

#ifndef cctest_CharacterSceneLoader_h
#define cctest_CharacterSceneLoader_h

#include <iostream>
#include "cocos2d.h"
#include "CharacterScene.h"

USING_NS_CC;

class CharacterSceneLoader : public CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CharacterSceneLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CharacterScene);
};

#endif
