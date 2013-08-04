#ifndef __HERO_LIST_SCENE_H__
#define __HERO_LIST_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"

#include "SimpleAudioEngine.h"
//#include "CCMessageDialog.h"
#include "MainGameScene.h"
#include "MainLayerBase.h"

using namespace cocos2d;
using namespace cocos2d::extension;
using namespace std;

class MDHeroListLayerDelegate
{
public:
	virtual void didSelectedItems(CCArray *pItems) = 0;
};

typedef enum _MD_HEROLIST_CATEGORY {
    MD_HEROLIST_DEFAULT,
    MD_HEROLIST_CHOOSE
} MDHeroListCategory;

class MDHeroListLayer : public MainLayerBase,
public CCTableViewDataSource,
public CCTableViewDelegate,
public CCBSelectorResolver,
public CCNodeLoaderListener,
public CCBMemberVariableAssigner,
public CCMessageDialogDelegate
{
public:
    MDHeroListLayer();
    ~MDHeroListLayer();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();

    // implement the "static node()" method manually
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(MDHeroListLayer,create);
	CC_SYNTHESIZE(MDHeroListLayerDelegate*, m_delegate, Delegate);

	void reloadDataSource();

private:
    
    virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view) {};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view) {}
    
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, CCTableViewCell* cell);
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
    virtual CCSize tableCellSizeForIndex(CCTableView *table, unsigned int idx);

	virtual CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(CCTableView *table);
    
    virtual void tableCellHighlight(CCTableView* table, CCTableViewCell* cell);
    virtual void tableCellUnhighlight(CCTableView* table, CCTableViewCell* cell);
    
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
    
	// a selector callback
	void requestFinishedCallback(CCHttpClient* client, CCHttpResponse* response);

//    void toolBarTouchDownAction(CCObject * sender , CCControlEvent controlEvent);
    void buttonClicked(CCObject * sender , CCControlEvent controlEvent);
	void didClickButton(CCMessageDialog* dialog,unsigned int index);
    void LoadHeros();
	void callbackSwitch(CCObject* pSender);

//	void deleteFriend(std::string &targetUser);
private:
    CCTableView* mTableView;
    unsigned int selectedindex;
    CCSprite *m_sTitle;
    CCArray *mHeroList;
	bool btnTouched;
    int *vUserData;
    CCControlButton *m_btnLeft;
    CCControlButton *m_btnRight;
public:
    MDHeroListCategory category;
};

#endif  // __HERO_LIST_SCENE_H__