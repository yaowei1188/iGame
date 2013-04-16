//
//  CCTableViewLoader.h
//  cctest
//
//  Created by China Team on 4/9/13.
//
//

#ifndef cctest_CCTableViewLoader_h
#define cctest_CCTableViewLoader_h

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "CCTableView.h"

USING_NS_CC;
using namespace cocos2d::extension;

class CCTableViewLoader : public CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CCTableViewLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CCTableView);
};

#endif
