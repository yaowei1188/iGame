#ifndef __MAIL_MAIN_SCENE_H__
#define __MAIL_MAIN_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"

#include "SimpleAudioEngine.h"
#include "XmlParser.h"

#include "MainGameScene.h"
#include "MainSceneTemplate.h"
#include "MainLayerBase.h"
#include "common.h"

using namespace cocos2d;
using namespace cocos2d::extension;
using namespace std;

class MailMainScene : public MainLayerBase,
public CCTableViewDataSource,
public CCTableViewDelegate,
public CCBSelectorResolver,
public CCNodeLoaderListener,
public CCBMemberVariableAssigner,
public CCMessageDialogDelegate
{
public:
    MailMainScene();
    ~MailMainScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void requestFinishedCallback(CCNode* pSender,void *p);
	void doSearchFriend();

    // implement the "static node()" method manually
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(MailMainScene,create);
    
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
	void deleteFriend(std::string &targetUser);
    CCTableView* mTableViewFriend;
//    MainSceneTemplate *mMainSceneTemp;
    unsigned int selectedindex;
    //CCTabView *tabView;
    CCArray *mFriendList;
};

#endif  // __HELLOWORLD_SCENE_H__