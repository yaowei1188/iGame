#ifndef __MAIL_LIST_SCENE_H__
#define __MAIL_LIST_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"

#include "SimpleAudioEngine.h"
#include "XmlParser.h"

//#include "CCMessageDialog.h"
#include "MainGameScene.h"
#include "MainLayerBase.h"

using namespace cocos2d;
using namespace cocos2d::extension;
using namespace std;

class MailListScene : public MainLayerBase,
public CCTableViewDataSource,
public CCTableViewDelegate,
//public CCBSelectorResolver,
//public CCNodeLoaderListener,
//public CCBMemberVariableAssigner,
public CCMessageDialogDelegate
{
public:
    MailListScene();
    ~MailListScene();
    
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();

	// implement the "static node()" method manually
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(MailListScene,create);

	void deleteEntrys();

private:
    
    // a selector callback
    void requestFinishedCallback(CCHttpClient* client, CCHttpResponse* response);
	void doSearch();
    
    void callbackSwitch(CCObject* pSender);
    
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view) {};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view) {}
    
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, CCTableViewCell* cell);
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(CCTableView *table);
    virtual CCSize tableCellSizeForIndex(CCTableView *table, unsigned int idx);
    virtual void tableCellHighlight(CCTableView* table, CCTableViewCell* cell);
    virtual void tableCellUnhighlight(CCTableView* table, CCTableViewCell* cell);
    
    //virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    //virtual SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
    
    void toolBarTouchDownAction(CCObject * sender , CCControlEvent controlEvent);
    //void buttonClicked(CCObject * sender , CCControlEvent controlEvent);
	void didClickButton(CCMessageDialog* dialog,unsigned int index);

	void loadTableView();
	CCTableView* mTableViewMail;
    unsigned int selectedindex;
    CCMenu *menuCheckAll;
    CCArray *mArrayList;
    int *vUserData;
};

#endif