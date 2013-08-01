//
//  MDSettingLayerLoader.h
//  cctest
//
//  Created by China Team on 4/9/13.
//
//

#ifndef _MDSettingLayerLoader_h
#define _MDSettingLayerLoader_h

#include <iostream>
#include "cocos2d.h"
#include "MDSettingLayer.h"

USING_NS_CC;

class MDSettingLayerLoader : public CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(MDSettingLayerLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(MDSettingLayer);
};

#endif
