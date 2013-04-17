#include "FriendListScene.h"

using namespace cocos2d;

#define CELL_ITEMS_Y 30

CCScene* FriendListScene::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        FriendListScene *layer = FriendListScene::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool FriendListScene::init()
{
    selectedindex = -1;
    
    bool bRet = false;
    do 
    {
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////

        CC_BREAK_IF(! CCLayer::init());

        bRet = true;
    } while (0);

    return bRet;
}

bool FriendListScene::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mTableViewFriend", CCTableView*, this->mTableViewFriend);
    return true;
}

void FriendListScene::onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader)
{
    CCLOG("TEST");

    mTableViewFriend->setDirection(kCCScrollViewDirectionVertical);
    mTableViewFriend->setVerticalFillOrder(kCCTableViewFillTopDown);
    mTableViewFriend->setDataSource(this);
    mTableViewFriend->setDelegate(this);
    mTableViewFriend->reloadData();
}

void FriendListScene::tableCellHighlight(CCTableView* table, CCTableViewCell* cell)
{
    
}

void FriendListScene::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
    CCLOG("cell touched at index: %i", cell->getIdx());
    if (selectedindex == cell->getIdx()) {
        selectedindex = -1;
    } else {
        selectedindex = cell->getIdx();
    }

    table->reloadData();
}

CCSize FriendListScene::cellSizeForTable(CCTableView *table)
{
	return CCSizeMake(250, 50);
}

CCSize FriendListScene::cellSizeForIndex(CCTableView *table, unsigned int idx)
{
    if (selectedindex == idx ) {
        return CCSizeMake(320, 80);
    }
    return CCSizeMake(320, 50);
}

bool FriendListScene::hasFixedCellSize()
{
    return false;
}

CCTableViewCell* FriendListScene::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
	CCString *string = CCString::createWithFormat("%d", idx);
	CCTableViewCell *cell = table->dequeueCell();
	if (!cell) {
		cell = new CCTableViewCell();
		cell->autorelease();
        
        CCSize size = this->cellSizeForIndex(table, idx);
    
        CCScale9Sprite *background = CCScale9Sprite::create("account.png", CCRectMake(0, 0, size.width, size.height));
        background->setAnchorPoint(CCPointZero);
        background->setTag(121);
        cell->addChild(background);
        
//		CCSprite *sprite = CCSprite::create("user_blue_32.png");
//		sprite->setPosition(ccp(40,10));
//		sprite->setAnchorPoint(CCPointZero);
//		cell->addChild(sprite);

		CCLabelTTF *lblName = CCLabelTTF::create(string->getCString(), "Helvetica", 20.0);
		lblName->setPosition(ccp(15,size.height - CELL_ITEMS_Y));
		lblName->setAnchorPoint(CCPointZero);
		lblName->setTag(123);
		cell->addChild(lblName);

		CCLabelTTF *lblLevel = CCLabelTTF::create("Lv2", "Helvetica", 20.0);
		lblLevel->setPosition(ccp(90,size.height - CELL_ITEMS_Y));
		lblLevel->setAnchorPoint(CCPointZero);
		lblLevel->setTag(124);
		cell->addChild(lblLevel);

		CCLabelTTF *lblFriend = CCLabelTTF::create("friends", "Helvetica", 20.0);
		lblFriend->setPosition(ccp(160,size.height - CELL_ITEMS_Y));
		lblFriend->setAnchorPoint(CCPointZero);
        lblFriend->setTag(125);
		cell->addChild(lblFriend);

		CCLabelTTF *lblStatus = CCLabelTTF::create("Online", "Helvetica", 20.0);
		lblStatus->setPosition(ccp(240,size.height - CELL_ITEMS_Y));
		lblStatus->setAnchorPoint(CCPointZero);
        lblStatus->setTag(126);
		cell->addChild(lblStatus);
        
        CCControlButton * button = CCControlButton::create("Chat", "Helvetica", 15);
        button->setPosition(ccp(60,size.height - CELL_ITEMS_Y * 2));
        button->setAnchorPoint(CCPointZero);
        button->setTag(127);
//        button->setBackgroundSprite(CCScale9Sprite::create("btnSubmit.png"));
        button->addTargetWithActionForControlEvents(this, cccontrol_selector(FriendListScene::toolBarTouchDownAction), CCControlEventTouchDown);
        cell->addChild(button);
	}
	else
	{
        CCSize size = this->cellSizeForIndex(table, idx);
        
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
        
        CCScale9Sprite *background = (CCScale9Sprite *)cell->getChildByTag(121);
        background->setContentSize(size);
	}

	return cell;
}

//    按下按钮事件回调
void FriendListScene::toolBarTouchDownAction(CCObject * sender , CCControlEvent * controlEvent)
{
//    CCLabelTTF  * label = (CCLabelTTF*) this ->getChildByTag(923);
//    label->setString(CCString::createWithFormat("按下")->getCString());
    CCLOG("CLICK");
}

unsigned int FriendListScene::numberOfCellsInTableView(CCTableView *table)
{
	return 20;
}


void FriendListScene::requestFinishedCallback(CCNode* pSender,void *data)
{

}

