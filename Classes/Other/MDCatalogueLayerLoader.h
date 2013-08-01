//
//  MDCatalogueLayerLoader.h
//  cctest
//
//  Created by China Team on 4/9/13.
//
//

#ifndef _MDCatalogueLayerLoader_h
#define _MDCatalogueLayerLoader_h

#include <iostream>
#include "cocos2d.h"
#include "MDCatalogueLayer.h"

USING_NS_CC;

class MDCatalogueLayerLoader : public CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(MDCatalogueLayerLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(MDCatalogueLayer);
};

#endif
