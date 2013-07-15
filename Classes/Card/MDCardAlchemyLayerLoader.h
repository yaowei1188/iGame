//
//  MDCardAlchemyLayerLoader.h
//  cctest
//
//  Created by China Team on 4/9/13.
//
//

#ifndef cctest_MDCardAlchemyLayerLoader_h
#define cctest_MDCardAlchemyLayerLoader_h

#include <iostream>
#include "cocos2d.h"
#include "MDCardAlchemyLayer.h"

USING_NS_CC;

class MDCardAlchemyLayerLoader : public CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(MDCardAlchemyLayerLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(MDCardAlchemyLayer);
};

#endif
