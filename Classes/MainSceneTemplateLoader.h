//
//  MainSceneTemplateLoader.h
//  
//
//  Created by China Team on 4/9/13.
//
//

#ifndef __cctest__MainSceneTemplateLoader__
#define __cctest__MainSceneTemplateLoader__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "CCNodeLoader.h"
#include "MainSceneTemplate.h"

USING_NS_CC;
USING_NS_CC_EXT;

class MainSceneTemplateLoader : public CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(MainSceneTemplateLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(MainSceneTemplate);
};

#endif
