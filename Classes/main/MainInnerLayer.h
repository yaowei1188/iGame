//
//  MainInnerLayer.h
//  cctest
//
//  Created by China Team on 4/9/13.
//
//

#ifndef __MainInnerLayer__
#define __MainInnerLayer__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "common.h"
#include "MainLayerBase.h"
#include "StringExt.h"

using namespace cocos2d;
using namespace cocos2d::extension;


class MainInnerLayerDelegate
{
public:

    virtual void toolBarButtonClickedCallBack(CCControlButton *pItem) = 0;

};

class MainInnerLayer : public MainLayerBase,
  public CCTableViewDataSource,
  public CCTableViewDelegate,
  public CCBSelectorResolver,
  public CCBMemberVariableAssigner,
  public CCNodeLoaderListener
{
public:
    ~MainInnerLayer();
    MainInnerLayer();
    
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(MainInnerLayer, create);
    CC_SYNTHESIZE(MainInnerLayerDelegate*, m_delegate, Delegate);
    
    void showTooBar(bool show);
    
    
private:
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
	virtual CCSize tableCellSizeForIndex(CCTableView *table, unsigned int idx);
	virtual void tableCellHighlight(CCTableView* table, CCTableViewCell* cell);
	virtual void tableCellUnhighlight(CCTableView* table, CCTableViewCell* cell);
    
    virtual bool init();
    
    void buttonClicked(CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent);
    void toolBarBtnClicked(CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent);
    
	unsigned int selectedindex;
	CCTableView* mTableView;
	CCArray *mCardList;
    CCLayer *m_layToolBar;

};

#endif
