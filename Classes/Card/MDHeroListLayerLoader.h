//
//  MDHeroListLayerLoader.h
//  cctest
//
//  Created by China Team on 4/9/13.
//
//

#ifndef _MDHeroListLayerLoader_h
#define _MDHeroListLayerLoader_h

#include <iostream>
#include "cocos2d.h"
#include "MDHeroListLayer.h"

USING_NS_CC;

class MDHeroListLayerLoader : public CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(MDHeroListLayerLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(MDHeroListLayer);
};

#endif
