#ifndef __ADDFRIENDSCENE_SCENE_H__
#define __ADDFRIENDSCENE_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"

#include "SimpleAudioEngine.h"
#include "XmlParser.h"
#include "MainGameScene.h"
#include "MainSceneTemplate.h"
#include "common.h"

using namespace cocos2d;
using namespace cocos2d::extension;

class AddFriendScene : public cocos2d::CCLayer,
public CCTableViewDataSource,
public CCTableViewDelegate,
public CCBSelectorResolver,
public CCNodeLoaderListener,
public CCBMemberVariableAssigner
{
public:
    AddFriendScene();
    ~AddFriendScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void requestFinishedCallback(CCNode* pSender,void *p);
    void doSearchFriend();
	void parseJson();

    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(AddFriendScene, create);
    
	void buttonClicked(CCObject *pSender,CCControlEvent event);
    
    void toolBarBtnClicked(CCObject *pSender, CCControlEvent pCCControlEvent);
    
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
    
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);
    
    virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view) {};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view) {}
    
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, CCTableViewCell* cell);
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(CCTableView *table);
    virtual bool hasFixedCellSize();
    virtual CCSize cellSizeForIndex(CCTableView *table, unsigned int idx);
    virtual void tableCellHighlight(CCTableView* table, CCTableViewCell* cell);

	CCEditBox *m_txtSearchField;
    CCTableView* mTableViewFriend;
    unsigned int selectedindex;
    CCArray *mFriendList;
};

#endif  // __LOGINSCENE_SCENE_H__