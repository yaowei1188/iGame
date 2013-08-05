//
//  MDCatalogueDetailLayerLoader.h
//  cctest
//
//  Created by China Team on 4/9/13.
//
//

#ifndef cctest_MDCatalogueDetailLayerLoader_h
#define cctest_MDCatalogueDetailLayerLoader_h

#include <iostream>
#include "cocos2d.h"
#include "MDCatalogueDetailLayer.h"

USING_NS_CC;

class MDCatalogueDetailLayerLoader : public CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(MDCatalogueDetailLayerLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(MDCatalogueDetailLayer);
};

#endif
