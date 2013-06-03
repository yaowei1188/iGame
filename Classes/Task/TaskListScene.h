#ifndef __TASK_LIST_SCENE_H__
#define __TASK_LIST_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"

#include "SimpleAudioEngine.h"
#include "MainGameScene.h"
#include "MainSceneTemplate.h"
#include "MainLayerBase.h"

using namespace cocos2d;
using namespace cocos2d::extension;

class TaskListScene : public MainLayerBase,
	public CCTableViewDataSource,
	public CCTableViewDelegate,
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
	void requestFinishedCallback(CCNode* pSender,void *p);
	void doSearch();

	// implement the "static node()" method manually
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(TaskListScene,create);

	virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);

	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view) {};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view) {}

	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, CCTableViewCell* cell);
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(CCTableView *table);
	virtual bool hasFixedCellSize();
	virtual CCSize cellSizeForIndex(CCTableView *table, unsigned int idx);
	virtual void tableCellHighlight(CCTableView* table, CCTableViewCell* cell);
	virtual void tableCellUnhighlight(CCTableView* table, CCTableViewCell* cell);

	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);

	void toolBarTouchDownAction(CCObject * sender , CCControlEvent controlEvent);
	void buttonClicked(CCObject * sender , CCControlEvent controlEvent);
	void didClickButton(CCMessageDialog* dialog,unsigned int index);
	void deleteEntry(std::string &targetUser);
	CCTableView* mTableViewMail;
	//    MainSceneTemplate *mMainSceneTemp;
	unsigned int selectedindex;

	CCArray *mArrayList;
};

#endif  // __TASK_LIST_SCENE_H__