//
//  MainInnerLayer.cpp
//  cctest
//
//  Created by China Team on 4/9/13.
//
//

#include "MainInnerLayer.h"


MainInnerLayer::MainInnerLayer()
{
    mTableView = NULL;
     
    mCardList =  CCArray::create();
    mCardList->addObject(CCString::create("head_rulaifo.png"));
    mCardList->addObject(CCString::create("head_sunwukong.png"));
    mCardList->addObject(CCString::create("head_erlangsheng.png"));
//    mCardList->addObject(CCString::create("test3"));
//    mCardList->addObject(CCString::create("test"));
//    mCardList->addObject(CCString::create("test1"));
//    mCardList->addObject(CCString::create("test2"));
//    mCardList->addObject(CCString::create("test3"));
//    mCardList->addObject(CCString::create("test"));
//    mCardList->addObject(CCString::create("test1"));
//    mCardList->addObject(CCString::create("test2"));
//    mCardList->addObject(CCString::create("test3"));
//    mCardList->addObject(CCString::create("test"));
//    mCardList->addObject(CCString::create("test1"));
//    mCardList->addObject(CCString::create("test2"));
//    mCardList->addObject(CCString::create("test3"));
//    mCardList->addObject(CCString::create("test"));
//    mCardList->addObject(CCString::create("test1"));
//    mCardList->addObject(CCString::create("test2"));
//    mCardList->addObject(CCString::create("test3"));
//    mCardList->addObject(CCString::create("test"));
//    mCardList->addObject(CCString::create("test1"));
//    mCardList->addObject(CCString::create("test2"));
//    mCardList->addObject(CCString::create("test3"));
//    mCardList->addObject(CCString::create("test"));
//    mCardList->addObject(CCString::create("test1"));
//    mCardList->addObject(CCString::create("test2"));
//    mCardList->addObject(CCString::create("test3"));
//    mCardList->addObject(CCString::create("test"));
//    mCardList->addObject(CCString::create("test1"));
//    mCardList->addObject(CCString::create("test2"));
//    mCardList->addObject(CCString::create("test3"));
    mCardList->retain();

}

MainInnerLayer::~MainInnerLayer()
{
    CC_SAFE_RELEASE(mTableView);
}

void MainInnerLayer::onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader)
{
	mTableView->setDirection(kCCScrollViewDirectionHorizontal);
	mTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
	mTableView->setDataSource(this);
	mTableView->setViewSize(CCSizeMake(262, 65));
	mTableView->setDelegate(this);
    
    mTableView->reloadData();
}

bool MainInnerLayer::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mTableView", CCTableView*, this->mTableView);
    
    return true;
}

void MainInnerLayer::tableCellHighlight(CCTableView* table, CCTableViewCell* cell)
{
    CCSprite *sSelected = (CCSprite*)cell->getChildByTag(121);
    sSelected->setVisible(true);
}

void MainInnerLayer::tableCellUnhighlight(CCTableView* table, CCTableViewCell* cell)
{
    CCSprite *sSelected = (CCSprite*)cell->getChildByTag(121);
    sSelected->setVisible(false);
}

void MainInnerLayer::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
	CCLOG("cell touched at index: %i", cell->getIdx());
	//if (selectedindex == cell->getIdx()) {
	//	selectedindex = -1;
	//} else {
	//	selectedindex = cell->getIdx();
	//}

	//table->reloadData();
}

unsigned int MainInnerLayer::numberOfCellsInTableView(CCTableView *table)
{
	return mCardList->count();
}

CCSize MainInnerLayer::cellSizeForTable(CCTableView *table)
{
	return CCSizeMake(66.5, 65);
}

CCSize MainInnerLayer::cellSizeForIndex(CCTableView *table, unsigned int idx)
{
	return CCSizeMake(66.5, 65);
}

bool MainInnerLayer::hasFixedCellSize()
{
	return true;
}

CCTableViewCell* MainInnerLayer::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
	CCString *string = (CCString *)mCardList->objectAtIndex(idx);
	bool selected = (idx==selectedindex);
    CCSprite *sCard = NULL;
    CCSprite *sSelected = NULL;
	CCTableViewCell *cell = table->dequeueCell();
	if (!cell) {
		cell = new CCTableViewCell();
		cell->autorelease();

//		CCSize size = this->cellSizeForIndex(table, idx);

		sSelected = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("card_selected.png"));
		sSelected->setVisible(false);
		sSelected->setTag(121);
		sSelected->setPosition(ccp(2,0));
		sSelected->setAnchorPoint(CCPointZero);
		cell->addChild(sSelected);

		sCard = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(string->getCString()));
		sCard->setTag(122);
		sCard->setPosition(ccp(2,0));
		sCard->setAnchorPoint(CCPointZero);
		cell->addChild(sCard);
	}
	else
	{
		sCard = (CCSprite*)cell->getChildByTag(122);
        sCard->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(string->getCString()));
	}


	return cell;
}

void MainInnerLayer::toolBarBtnClicked(CCObject *pSender, CCControlEvent pCCControlEvent) {
	CCLOG("button clicked");
    
    CCControlButton *button = (CCControlButton*) pSender;
    if(m_delegate != NULL) {
        m_delegate->toolBarButtonClickedCallBack(button);
    }
}

void MainInnerLayer::buttonClicked(CCObject *pSender, CCControlEvent pCCControlEvent) {
	CCLOG("button clicked");
}

SEL_MenuHandler MainInnerLayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
	return NULL;
}

SEL_CCControlHandler MainInnerLayer::onResolveCCBCCControlSelector(CCObject *pTarget, const char * pSelectorName) {
    
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "toolBarBtnClicked:", MainInnerLayer::toolBarBtnClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "buttonClicked:", MainInnerLayer::buttonClicked);
    
	return NULL;
}

bool MainInnerLayer::init()
{
    return true;
}
