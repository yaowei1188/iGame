//
//  CCControlSwitchLoader.h
//  cctest
//
//  Created by China Team on 4/9/13.
//
//

#ifndef cctest_CCControlSwitchLoader_h
#define cctest_CCControlSwitchLoader_h

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
using namespace cocos2d::extension;

class CCControlSwitchLoader : public CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CCControlSwitchLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CCControlSwitch);
};

#endif
