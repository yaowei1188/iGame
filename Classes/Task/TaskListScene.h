#ifndef __TASK_LIST_SCENE_H__
#define __TASK_LIST_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"

#include "SimpleAudioEngine.h"
#include "XmlParser.h"
//#include "CCTableView.h"
//#include "CustomCCTableViewCell.h"

using namespace cocos2d;
using namespace cocos2d::extension;

class TaskListScene : public cocos2d::CCLayer,
public CCTableViewDataSource,
public CCTableViewDelegate,
public CCNodeLoaderListener,
public CCBMemberVariableAssigner
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void requestFinishedCallback(CCNode* pSender,void *p);

    // implement the "static node()" method manually
//    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(TaskListScene,create);
    
    virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    
    CCTableView* mTableViewFriend;
    
//    virtual unsigned int numberOfRowsInSection(unsigned int mSection,CCTableView * mTableView);
//	virtual unsigned int numberOfSectionsInCCTableView(CCTableView * mTableView){return 1;}
//	virtual void ccTableViewCommitCellEditingStyleForRowAtIndexPath(CCTableView * mTableView,CCTableViewCellEditingStyle mCellEditStyle,CCIndexPath &mIndexPath){}
	/*cell was set to anchor point(0.5,0.5)*/
//	virtual CCTableViewCell * cellForRowAtIndexPath(CCIndexPath &mIndexPath,CCTableView * mTableView);
//    float cellHeightForRowAtIndexPath(CCIndexPath & mIndexPath,CCTableView * mTableView);
};

#endif  // __HELLOWORLD_SCENE_H__