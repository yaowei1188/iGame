//
//  MDTaskBoxLayerLoader.h
//  cctest
//
//  Created by China Team on 4/9/13.
//
//

#ifndef _MDTaskBoxLayerLoader_h
#define _MDTaskBoxLayerLoader_h

#include <iostream>
#include "cocos2d.h"
#include "MDTaskBoxLayer.h"

USING_NS_CC;

class MDTaskBoxLayerLoader : public CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(MDTaskBoxLayerLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(MDTaskBoxLayer);
};

#endif
