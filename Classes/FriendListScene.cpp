#include "FriendListScene.h"

using namespace cocos2d;

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
    
//    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
//    
//    mTableViewFriend->removeFromParentAndCleanup(true);
//        
//    mTableViewFriend = CCTableView::create(this, CCSizeMake(312, 250));
//    mTableViewFriend->setDirection(kCCScrollViewDirectionVertical);
//    mTableViewFriend->setPosition(ccp(0,winSize.height/2-30));
//    mTableViewFriend->setDelegate(this);
//    this->addChild(mTableViewFriend);
//    mTableViewFriend->reloadData();

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
}

CCSize FriendListScene::cellSizeForTable(CCTableView *table)
{
	return CCSizeMake(250, 60);
}

CCTableViewCell* FriendListScene::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
	CCString *string = CCString::createWithFormat("%d", idx);
	CCTableViewCell *cell = table->dequeueCell();
	if (!cell) {
		cell = new CCTableViewCell();
		cell->autorelease();
//		CCSprite *sprite = CCSprite::create("user_blue_32.png");
//		sprite->setAnchorPoint(CCPointZero);
//		sprite->setPosition(ccp(0, 0));
//		cell->addChild(sprite);

		CCLabelTTF *lblName = CCLabelTTF::create(string->getCString(), "Helvetica", 20.0);
		lblName->setPosition(CCPointZero);
		lblName->setAnchorPoint(CCPointZero);
		lblName->setTag(123);
		cell->addChild(lblName);

		CCLabelTTF *lblLevel = CCLabelTTF::create("Lv2", "Helvetica", 20.0);
		lblLevel->setPosition(ccp(60,10));
		lblLevel->setAnchorPoint(CCPointZero);
		lblLevel->setTag(124);
		cell->addChild(lblLevel);

		CCLabelTTF *lblFriend = CCLabelTTF::create("friends", "Helvetica", 20.0);
		lblFriend->setPosition(ccp(140,10));
		lblFriend->setAnchorPoint(CCPointZero);
		cell->addChild(lblFriend);

		CCLabelTTF *lblStatus = CCLabelTTF::create("Online", "Helvetica", 20.0);
		lblStatus->setPosition(ccp(220,10));
		lblStatus->setAnchorPoint(CCPointZero);
		cell->addChild(lblStatus);
	}
	else
	{
		CCLabelTTF *lblName = (CCLabelTTF*)cell->getChildByTag(123);
		lblName->setString(string->getCString());
	}

	return cell;
}

unsigned int FriendListScene::numberOfCellsInTableView(CCTableView *table)
{
	return 20;
}


void FriendListScene::requestFinishedCallback(CCNode* pSender,void *data)
{

}

