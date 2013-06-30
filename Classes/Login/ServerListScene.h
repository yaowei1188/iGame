#ifndef __SERVER_LIST_SCENE_H__
#define __SERVER_LIST_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"

#include "SimpleAudioEngine.h"
#include "MainGameScene.h"
#include "MainSceneTemplate.h"
#include "MainLayerBase.h"

using namespace cocos2d;
using namespace cocos2d::extension;
using namespace std;

class ServerListScene : public MainLayerBase,
public CCTableViewDataSource,
public CCTableViewDelegate,
public CCBSelectorResolver,
public CCNodeLoaderListener,
public CCBMemberVariableAssigner
{
public:
    ServerListScene();
    ~ServerListScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void requestFinishedCallback(CCHttpClient* client, CCHttpResponse* response);
	void retrieveUserGameRole();

    // implement the "static node()" method manually
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(ServerListScene,create);
    
    virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view) {};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view) {}
    
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, CCTableViewCell* cell);
	virtual CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(CCTableView *table);
    virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
    virtual CCSize tableCellSizeForIndex(CCTableView *table, unsigned int idx);
    //virtual void tableCellHighlight(CCTableView* table, CCTableViewCell* cell);
    //virtual void tableCellUnhighlight(CCTableView* table, CCTableViewCell* cell);
    
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
    
    void buttonClicked(CCObject * sender , CCControlEvent controlEvent);
	void submitSelectedServer();
    CCTableView* mTableView;
    unsigned int selectedindex;
    CCArray *mArrayList;
	bool mHasCreatedRole;
};

#endif  // __MAIL_LIST_SCENE_H__