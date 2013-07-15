//
//  MDHerosFormationLayerLoader.h
//  cctest
//
//  Created by China Team on 4/9/13.
//
//

#ifndef cctest_MDHerosFormationLayerLoader_h
#define cctest_MDHerosFormationLayerLoader_h

#include <iostream>
#include "cocos2d.h"
#include "MDHerosFormationLayer.h"

USING_NS_CC;

class MDHerosFormationLayerLoader : public CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(MDHerosFormationLayerLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(MDHerosFormationLayer);
};

#endif
