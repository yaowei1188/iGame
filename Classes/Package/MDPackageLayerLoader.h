//
//  MDPackageLayerLoader.h
//  cctest
//
//  Created by China Team on 4/9/13.
//
//

#ifndef _MDPackageLayerLoader_h
#define _MDPackageLayerLoader_h

#include <iostream>
#include "cocos2d.h"
#include "MDPackageLayer.h"

USING_NS_CC;

class MDPackageLayerLoader : public CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(MDPackageLayerLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(MDPackageLayer);
};

#endif
