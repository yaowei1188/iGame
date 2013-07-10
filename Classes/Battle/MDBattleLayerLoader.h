//
//  MDBattleLayerLoader.h
//  cctest
//
//  Created by China Team on 4/9/13.
//
//

#ifndef mengdou_MDBattleLayerLoader_h
#define mengdou_MDBattleLayerLoader_h

#include <iostream>
#include "cocos2d.h"
#include "MDBattleLayer.h"

USING_NS_CC;

class MDBattleLayerLoader : public CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(MDBattleLayerLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(MDBattleLayer);
};

#endif
