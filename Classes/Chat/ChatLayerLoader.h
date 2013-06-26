//
//  ChatLayerLoader.h
//  cctest
//
//  Created by China Team on 4/9/13.
//
//

#ifndef cctest_ChatLayerLoader_h
#define cctest_ChatLayerLoader_h

#include <iostream>
#include "cocos2d.h"
#include "ChatLayer.h"

USING_NS_CC;

class ChatLayerLoader : public CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(ChatLayerLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(ChatLayer);
};

#endif
