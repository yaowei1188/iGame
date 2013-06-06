//
//  TaskRewardSceneLoader.h
//  cctest
//
//  Created by China Team on 4/9/13.
//
//

#ifndef cctest_TaskRewardSceneLoader_h
#define cctest_TaskRewardSceneLoader_h

#include <iostream>
#include "cocos2d.h"
#include "TaskRewardScene.h"

USING_NS_CC;

class TaskRewardSceneLoader : public CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(TaskRewardSceneLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(TaskRewardScene);
};

#endif
