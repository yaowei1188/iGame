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

}

MainInnerLayer::~MainInnerLayer()
{
    
}

void MainInnerLayer::onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader)
{
	mTableView->setDirection(kCCScrollViewDirectionHorizontal);
	mTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
	mTableView->setDataSource(this);
	mTableView->setViewSize(CCSizeMake(312, 60));
	mTableView->setDelegate(this);
}

bool MainInnerLayer::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mTableView", CCTableView*, this->mTableView);
    
    return true;
}

void MainInnerLayer::tableCellHighlight(CCTableView* table, CCTableViewCell* cell)
{
	//CCSprite *sSelected = (CCSprite*)cell->getChildByTag(121);
	//sSelected->setVisible(true);
}

void MainInnerLayer::tableCellUnhighlight(CCTableView* table, CCTableViewCell* cell)
{
	//CCSprite *sSelected = (CCSprite*)cell->getChildByTag(121);
	//sSelected->setVisible(false);
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
	return mFriendList->count();
}

CCSize MainInnerLayer::cellSizeForTable(CCTableView *table)
{
	return CCSizeMake(312, 50);
}

CCSize MainInnerLayer::cellSizeForIndex(CCTableView *table, unsigned int idx)
{
	if (selectedindex == idx ) {
		return CCSizeMake(312, 80);
	}
	return CCSizeMake(312, 44);
}

bool MainInnerLayer::hasFixedCellSize()
{
	return false;
}

CCTableViewCell* MainInnerLayer::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
	CCString *string = (CCString *)mFriendList->objectAtIndex(idx);
	bool selected = (idx==selectedindex);
	CCTableViewCell *cell = table->dequeueCell();
	if (!cell) {
		cell = new CCTableViewCell();
		cell->autorelease();

		CCSize size = this->cellSizeForIndex(table, idx);

		CCSprite *sSelected = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("friends_cellhighlight.png"));
		sSelected->setVisible(false);
		sSelected->setTag(121);
		sSelected->setPosition(ccp(13,size.height - 39));
		sSelected->setAnchorPoint(CCPointZero);
		cell->addChild(sSelected);

		CCSprite *sGroup = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("friends_dairy.png"));
		sGroup->setTag(122);
		sGroup->setPosition(ccp(11,size.height - CELL_ITEMS_Y - 10));
		sGroup->setAnchorPoint(CCPointZero);
		cell->addChild(sGroup);

		CCLabelTTF *lblName = CCLabelTTF::create(string->getCString(), "Arial", 14.0);
		lblName->setPosition(ccp(51,size.height - CELL_ITEMS_Y));
		lblName->setAnchorPoint(CCPointZero);
		lblName->setColor(ccc3(248, 255, 38));
		lblName->setTag(123);
		cell->addChild(lblName);

		CCLabelTTF *lblLevel = CCLabelTTF::create("LV. 3", "Arial", 14.0);
		lblLevel->setPosition(ccp(165,size.height - CELL_ITEMS_Y));
		lblLevel->setAnchorPoint(CCPointZero);
		lblLevel->setColor(ccc3(248, 255, 38));
		lblLevel->setTag(124);
		cell->addChild(lblLevel);

		CCLabelTTF *lblFriend = CCLabelTTF::create("ÉúËÀ²»Æú", "Arial", 14.0);
		lblFriend->setPosition(ccp(218,size.height - CELL_ITEMS_Y));
		lblFriend->setAnchorPoint(CCPointZero);
		lblFriend->setColor(ccc3(248, 255, 38));
		lblFriend->setTag(125);
		cell->addChild(lblFriend);

		CCLabelTTF *lblStatus = CCLabelTTF::create("100", "Arial", 14.0);
		lblStatus->setPosition(ccp(283,size.height - CELL_ITEMS_Y));
		lblStatus->setAnchorPoint(CCPointZero);
		lblStatus->setColor(ccc3(248, 255, 38));
		lblStatus->setTag(126);
		cell->addChild(lblStatus);

		CCScale9Sprite *sline = CCScale9Sprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("line.png"));
		sline->setPreferredSize(CCSizeMake(290, 1));
		sline->setPosition(ccp(15,size.height - CELL_ITEMS_Y - 20));
		sline->setAnchorPoint(CCPointZero);
		cell->addChild(sline);

		int length = rand()%5;
		CCLayer *layer = CCLayer::create();
		layer->setTag(131);
		cell->addChild(layer);

		for (int i=0; i<5; i++) {
			CCSprite *sFriendheart = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("friends_love.png"));
			sFriendheart->setPosition(ccp(218 + CELL_LOVE_XGAP * i,size.height - CELL_ITEMS_Y - 15));
			sFriendheart->setAnchorPoint(CCPointZero);
			layer->addChild(sFriendheart);
		}


		CCControlButton * chatBtn = CCControlButton::create(CCScale9Sprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("friends_chat.png")));
		chatBtn->setPosition(ccp(4,size.height - CELL_ITEMS_Y - CELL_ITEMS_GAP));
		chatBtn->setAnchorPoint(ccp(0,0.5));
		chatBtn->setTag(127);
		chatBtn->setVisible(selected);
		chatBtn->setPreferredSize(CCSizeMake(74,34));
		//chatBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(MainInnerLayer::toolBarTouchDownAction), CCControlEventTouchUpInside);
		cell->addChild(chatBtn);

		CCControlButton * msgBtn = CCControlButton::create(CCScale9Sprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("friends_emailbtn.png")));
		msgBtn->setPosition(ccp(81,size.height - CELL_ITEMS_Y - CELL_ITEMS_GAP));
		msgBtn->setAnchorPoint(ccp(0,0.5));
		msgBtn->setTag(128);
		msgBtn->setPreferredSize(CCSizeMake(74,34));
		msgBtn->setVisible(selected);
		//msgBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(MainInnerLayer::toolBarTouchDownAction), CCControlEventTouchUpInside);
		cell->addChild(msgBtn);

		CCControlButton * formationBtn = CCControlButton::create(CCScale9Sprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("friends_formation.png")));
		formationBtn->setPosition(ccp(158,size.height - CELL_ITEMS_Y - CELL_ITEMS_GAP));
		formationBtn->setAnchorPoint(ccp(0,0.5));
		formationBtn->setTag(129);
		formationBtn->setPreferredSize(CCSizeMake(74,34));
		formationBtn->setVisible(selected);
		//formationBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(MainInnerLayer::toolBarTouchDownAction), CCControlEventTouchUpInside);
		cell->addChild(formationBtn);

		CCControlButton * deleteBtn = CCControlButton::create(CCScale9Sprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("friends_delete.png")));
		deleteBtn->setPosition(ccp(235,size.height - CELL_ITEMS_Y - CELL_ITEMS_GAP));
		deleteBtn->setAnchorPoint(ccp(0,0.5));
		deleteBtn->setTag(130);
		deleteBtn->setPreferredSize(CCSizeMake(74,34));
		deleteBtn->setVisible(selected);
		//deleteBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(MainInnerLayer::toolBarTouchDownAction), CCControlEventTouchUpInside);
		cell->addChild(deleteBtn);
	}
	else
	{
		CCSize size = this->cellSizeForIndex(table, idx);

		CCSprite *sSelected = (CCSprite*)cell->getChildByTag(121);
		sSelected->setPosition(ccp(13,size.height - 39));
		if (selectedindex == idx ) {
			sSelected->setVisible(true);
		} else {
			sSelected->setVisible(false);
		}

		CCSprite *sGroup = (CCSprite*)cell->getChildByTag(122);
		sGroup->setPosition(ccp(sGroup->getPosition().x,size.height - CELL_ITEMS_Y - 10));

		CCLabelTTF *lblName = (CCLabelTTF*)cell->getChildByTag(123);
		lblName->setString(string->getCString());
		lblName->setPosition(ccp(lblName->getPosition().x,size.height - CELL_ITEMS_Y));

		CCLabelTTF *lblLevel = (CCLabelTTF*)cell->getChildByTag(124);
		//lblLevel->setString(string->getCString());
		lblLevel->setPosition(ccp(lblLevel->getPosition().x,size.height - CELL_ITEMS_Y));

		CCLabelTTF *lblFriend = (CCLabelTTF*)cell->getChildByTag(125);
		//		lblFriend->setString(string->getCString());
		lblFriend->setPosition(ccp(lblFriend->getPosition().x,size.height - CELL_ITEMS_Y));

		CCLabelTTF *lblStatus = (CCLabelTTF*)cell->getChildByTag(126);
		//		lblStatus->setString(string->getCString());
		lblStatus->setPosition(ccp(lblStatus->getPosition().x,size.height - CELL_ITEMS_Y));

		//        CCScale9Sprite *background = (CCScale9Sprite *)cell->getChildByTag(121);
		//        background->setContentSize(size);

		CCControlButton *chatBtn = (CCControlButton *)cell->getChildByTag(127);
		chatBtn->setPosition(ccp(chatBtn->getPosition().x,size.height - CELL_ITEMS_Y - CELL_ITEMS_GAP));
		chatBtn->setVisible(selected);

		CCControlButton *msgBtn = (CCControlButton *)cell->getChildByTag(128);
		msgBtn->setPosition(ccp(msgBtn->getPosition().x,size.height - CELL_ITEMS_Y - CELL_ITEMS_GAP));
		msgBtn->setVisible(selected);

		CCControlButton *formationBtn = (CCControlButton *)cell->getChildByTag(129);
		formationBtn->setPosition(ccp(formationBtn->getPosition().x,size.height - CELL_ITEMS_Y - CELL_ITEMS_GAP));
		formationBtn->setVisible(selected);

		CCControlButton *deleteBtn = (CCControlButton *)cell->getChildByTag(130);
		deleteBtn->setPosition(ccp(deleteBtn->getPosition().x,size.height - CELL_ITEMS_Y - CELL_ITEMS_GAP));
		deleteBtn->setVisible(selected);

		CCLayer *heartLayer = (CCLayer *)cell->getChildByTag(131);
		CCArray *array = heartLayer->getChildren();
		if (array!=NULL) {
			for (int i=0; i<array->count(); i++) {
				CCSprite *sprite = (CCSprite *)array->objectAtIndex(i);
				sprite->setPosition(ccp(sprite->getPosition().x,size.height - CELL_ITEMS_Y - 15));
			}
		}
	}

	return cell;
}

void MainInnerLayer::toolBarBtnClicked(CCObject *pSender, CCControlEvent pCCControlEvent) {
	CCLOG("button clicked");
}

void MainInnerLayer::menuBarBtnClicked(CCObject *pSender)
{
    CCMenuItem *button = (CCMenuItem*) pSender;
    //if(m_delegate != NULL) {
    //    m_delegate->menuItemClicked(button);
    //}
}

SEL_MenuHandler MainInnerLayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "menuBarBtnClicked:", MainInnerLayer::menuBarBtnClicked);
    
	return NULL;
}

SEL_CCControlHandler MainInnerLayer::onResolveCCBCCControlSelector(CCObject *pTarget, const char * pSelectorName) {
    
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "toolBarBtnClicked:", MainInnerLayer::toolBarBtnClicked);
    
	return NULL;
}

bool MainInnerLayer::init()
{
    return true;
}
