//
//  TaskDetailSceneLoader.h
//  cctest
//
//  Created by China Team on 4/9/13.
//
//

#ifndef cctest_TaskDetailSceneLoader_h
#define cctest_TaskDetailSceneLoader_h

#include <iostream>
#include "cocos2d.h"
#include "TaskDetailScene.h"

USING_NS_CC;

class TaskDetailSceneLoader : public CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(TaskDetailSceneLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(TaskDetailScene);
};

#endif
