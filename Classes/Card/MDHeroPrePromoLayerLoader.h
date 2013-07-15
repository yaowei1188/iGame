//
//  MDHeroPrePromoLayerLoader.h
//  cctest
//
//  Created by China Team on 4/9/13.
//
//

#ifndef cctest_MDHeroPrePromoLayerLoader_h
#define cctest_MDHeroPrePromoLayerLoader_h

#include <iostream>
#include "cocos2d.h"
#include "MDHeroPrePromoLayer.h"

USING_NS_CC;

class MDHeroPrePromoLayerLoader : public CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(MDHeroPrePromoLayerLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(MDHeroPrePromoLayer);
};

#endif
