//
//  MDHeroDetailLayerLoader.h
//  cctest
//
//  Created by China Team on 4/9/13.
//
//

#ifndef cctest_MDHeroDetailLayerLoader_h
#define cctest_MDHeroDetailLayerLoader_h

#include <iostream>
#include "cocos2d.h"
#include "MDHeroDetailLayer.h"

USING_NS_CC;

class MDHeroDetailLayerLoader : public CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(MDHeroDetailLayerLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(MDHeroDetailLayer);
};

#endif
