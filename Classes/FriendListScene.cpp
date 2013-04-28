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
    selectedindex = -1;
    
    bool bRet = false;
    do 
    {
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////

        CC_BREAK_IF(! CCLayer::init());
        
        mFriendList = CCArray::create(CCString::create("Li1"),CCString::create("张三"),CCString::create("Li3"),CCString::create("李四"),CCString::create("Li1653"),CCString::create("Li1qwe"),CCString::create("Li1"),CCString::create("Li1"),CCString::create("Li409"),CCString::create("Li134"),CCString::create("Li51"),CCString::create("Li18974523"),CCString::create("Li1"),CCString::create("Li1"),CCString::create("Li1"),CCString::create("Li1"),CCString::create("Li1"),CCString::create("Li124"),CCString::create("Li1998"),CCString::create("Li3561"),NULL);
        
        mFriendList->retain();

        bRet = true;
    } while (0);

    return bRet;
}

bool FriendListScene::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mTableViewFriend", CCTableView*, this->mTableViewFriend);
//    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mMainSceneTemp", MainSceneTemplate*, this->mMainSceneTemp);
    return true;
}

SEL_MenuHandler FriendListScene::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
//	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "menuBarBtnClicked:", FriendListScene::menuBarBtnClicked);
	return NULL;
}

SEL_CCControlHandler FriendListScene::onResolveCCBCCControlSelector(CCObject *pTarget, const char * pSelectorName) {
    
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "buttonClicked:", FriendListScene::buttonClicked);
	return NULL;
}

void FriendListScene::onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader)
{
    CCLOG("TEST");

    mTableViewFriend->setDirection(kCCScrollViewDirectionVertical);
    mTableViewFriend->setVerticalFillOrder(kCCTableViewFillTopDown);
    mTableViewFriend->setDataSource(this);
    mTableViewFriend->setViewSize(CCSizeMake(312, 280));
    mTableViewFriend->setDelegate(this);
    mTableViewFriend->reloadData();
}

void FriendListScene::tableCellHighlight(CCTableView* table, CCTableViewCell* cell)
{
    CCSprite *sSelected = (CCSprite*)cell->getChildByTag(121);
    sSelected->setVisible(true);
}

void FriendListScene::tableCellUnhighlight(CCTableView* table, CCTableViewCell* cell)
{
    CCSprite *sSelected = (CCSprite*)cell->getChildByTag(121);
    sSelected->setVisible(false);
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

unsigned int FriendListScene::numberOfCellsInTableView(CCTableView *table)
{
	return mFriendList->count();
}

CCSize FriendListScene::cellSizeForTable(CCTableView *table)
{
	return CCSizeMake(312, 50);
}

CCSize FriendListScene::cellSizeForIndex(CCTableView *table, unsigned int idx)
{
    if (selectedindex == idx ) {
        return CCSizeMake(312, 80);
    }
    return CCSizeMake(312, 44);
}

bool FriendListScene::hasFixedCellSize()
{
    return false;
}

CCTableViewCell* FriendListScene::tableCellAtIndex(CCTableView *table, unsigned int idx)
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

		CCLabelTTF *lblFriend = CCLabelTTF::create("生死不弃", "Arial", 14.0);
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
        
        int length = rand()%5;
        CCLayer *layer = CCLayer::create();
        layer->setTag(131);
        cell->addChild(layer);

        for (int i=0; i<length; i++) {
            CCSprite *sFriendheart = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("friends_love.png"));
            sFriendheart->setPosition(ccp(218 + CELL_LOVE_XGAP * i,size.height - CELL_ITEMS_Y - 15));
            sFriendheart->setAnchorPoint(CCPointZero);
            layer->addChild(sFriendheart);
        }
        
        CCControlButton * chatBtn = CCControlButton::create(CCScale9Sprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("friends_chat.png")));
        chatBtn->setPosition(ccp(30,size.height - CELL_ITEMS_Y - CELL_ITEMS_GAP));
        chatBtn->setAnchorPoint(CCPointZero);
        chatBtn->setTag(127);
        chatBtn->setVisible(selected);
        chatBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(FriendListScene::toolBarTouchDownAction), CCControlEventTouchUpInside);
        cell->addChild(chatBtn);
        
        CCControlButton * msgBtn = CCControlButton::create(CCScale9Sprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("friends_emailbtn.png")));
        msgBtn->setPosition(ccp(90,size.height - CELL_ITEMS_Y - CELL_ITEMS_GAP));
        msgBtn->setAnchorPoint(CCPointZero);
        msgBtn->setTag(128);
        msgBtn->setVisible(selected);
        msgBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(FriendListScene::toolBarTouchDownAction), CCControlEventTouchUpInside);
        cell->addChild(msgBtn);
        
        CCControlButton * formationBtn = CCControlButton::create(CCScale9Sprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("friends_formation.png")));
        formationBtn->setPosition(ccp(150,size.height - CELL_ITEMS_Y - CELL_ITEMS_GAP));
        formationBtn->setAnchorPoint(CCPointZero);
        formationBtn->setTag(129);
        formationBtn->setVisible(selected);
        formationBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(FriendListScene::toolBarTouchDownAction), CCControlEventTouchUpInside);
        cell->addChild(formationBtn);
        
        CCControlButton * deleteBtn = CCControlButton::create(CCScale9Sprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("friends_delete.png")));
        deleteBtn->setPosition(ccp(240,size.height - CELL_ITEMS_Y - CELL_ITEMS_GAP));
        deleteBtn->setAnchorPoint(CCPointZero);
        deleteBtn->setTag(130);
        deleteBtn->setVisible(selected);
        deleteBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(FriendListScene::toolBarTouchDownAction), CCControlEventTouchUpInside);
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

//    按下按钮事件回调
void FriendListScene::toolBarTouchDownAction(CCObject * sender , CCControlEvent controlEvent)
{
    CCLOG("CLICK");
    
    CCMessageDialog *box = CCMessageDialog::create();
    this->addChild(box);
}

void FriendListScene::buttonClicked(CCObject * sender , CCControlEvent controlEvent)
{
    CCLOG("SSSS");
    
//    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCLayer *addFriendLayer = (CCLayer *)this->GetLayer("AddFriendScene");
    MainGameScene *mainScene = (MainGameScene *)this->getParent();
    mainScene->PushLayer(addFriendLayer);
}


void FriendListScene::requestFinishedCallback(CCNode* pSender,void *data)
{

}

FriendListScene::FriendListScene()
{
    mTableViewFriend = NULL;
//    mMainSceneTemp = NULL;
    mFriendList = NULL;
}

FriendListScene::~FriendListScene()
{
//    mTableViewFriend->release();
//    mMainSceneTemp->release();
//    mFriendList->release();
}

