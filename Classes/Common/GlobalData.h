//
//  GlobalData.h
//  mengdou
//
//  Created by ivan on 6/3/13.
//
//

#ifndef __mengdou__GlobalData__
#define __mengdou__GlobalData__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"

using namespace std;
using namespace cocos2d;
using namespace cocos2d::extension;

class GlobalData
{
public:
    static CCString* getLocalString(std::string name);
    
    static CCDictionary* getTasks(std::string name);
};

#endif /* defined(__mengdou__GlobalData__) */
