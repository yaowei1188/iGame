//
//  MainInnerLayerLoader.h
//  
//
//  Created by China Team on 4/9/13.
//
//

#ifndef __cctest__MainInnerLayerLoader__
#define __cctest__MainInnerLayerLoader__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
//#include "CCNodeLoader.h"
#include "MainInnerLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

class MainInnerLayerLoader : public CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(MainInnerLayerLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(MainInnerLayer);
};

#endif
