//
//  MainOuterLayerLoader.h
//  
//
//  Created by China Team on 4/9/13.
//
//

#ifndef __MainOuterLayerLoader__
#define __MainOuterLayerLoader__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
//#include "CCNodeLoader.h"
#include "MainOuterLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

class MainOuterLayerLoader : public CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(MainOuterLayerLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(MainOuterLayer);
};

#endif
