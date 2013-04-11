//
//  CCEditBoxLoader.h
//  cctest
//
//  Created by China Team on 4/9/13.
//
//

#ifndef cctest_CCEditBoxLoader_h
#define cctest_CCEditBoxLoader_h

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
using namespace cocos2d::extension;

class CCEditBoxLoader : public CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CCEditBoxLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CCEditBox);
};

#endif
