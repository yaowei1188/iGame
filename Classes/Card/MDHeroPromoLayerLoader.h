//
//  MDHeroPromoLayerLoader.h
//  cctest
//
//  Created by China Team on 4/9/13.
//
//

#ifndef cctest_MDHeroPromoLayerLoader_h
#define cctest_MDHeroPromoLayerLoader_h

#include <iostream>
#include "cocos2d.h"
#include "MDHeroPromoLayer.h"

USING_NS_CC;

class MDHeroPromoLayerLoader : public CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(MDHeroPromoLayerLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(MDHeroPromoLayer);
};

#endif
