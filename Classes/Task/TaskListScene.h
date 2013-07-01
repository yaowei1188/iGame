#ifndef __TASK_LIST_SCENE_H__
#define __TASK_LIST_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"

#include "SimpleAudioEngine.h"
#include "MainGameScene.h"
#include "MainSceneTemplate.h"
#include "MainLayerBase.h"
#include "SlidingMenu.h"

using namespace cocos2d;
using namespace cocos2d::extension;

class TaskListScene : public MainLayerBase,
//	public CCTableViewDataSource,
//	public CCTableViewDelegate,
	public CCBSelectorResolver,
	public CCNodeLoaderListener,
	public CCBMemberVariableAssigner,
	public CCMessageDialogDelegate
{
public:
	TaskListScene();
	~TaskListScene();

	virtual bool init();  

	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene();

	// a selector callback
	void requestFinishedCallback(CCHttpClient* client, CCHttpResponse* response);
	void retrieveCurrentTask();

	// implement the "static node()" method manually
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(TaskListScene,create);

	virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);

	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);

	void buttonClicked(CCObject * sender , CCControlEvent controlEvent);
	void didClickButton(CCMessageDialog* dialog,unsigned int index);
	void executeTask(std::string &targetUser);
    void showTaskLists();
    void menuItemCallback(CCObject* pSender);
	CCTableView* mTableView;
	unsigned int selectedindex;
    CCLabelTTF *m_lblTitle;
    SlidingMenuGrid* sliderMenu;
	CCArray *mArrayList;
    CCDictionary *mTaskDict;
};

#endif  // __TASK_LIST_SCENE_H__