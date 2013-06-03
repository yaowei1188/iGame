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
        
		//mFriendList =  CCArray::create();
        mFriendList = CCArray::create(CCString::create("Li1"),CCString::create("张三"),CCString::create("Li3"),CCString::create("李四"),CCString::create("Li1653"),CCString::create("Li1qwe"),CCString::create("Li1"),CCString::create("Li1"),CCString::create("Li409"),CCString::create("Li134"),CCString::create("Li51"),CCString::create("Li18974523"),CCString::create("Li1"),CCString::create("Li1"),CCString::create("Li1"),CCString::create("Li1"),CCString::create("Li1"),CCString::create("Li124"),CCString::create("Li1998"),CCString::create("Li3561"),NULL);
        mFriendList->retain();

        bRet = true;
    } while (0);

    return bRet;
}

void FriendListScene::doSearchFriend()
{
	this->ShowLoadingIndicator("");

	CCHttpRequest *request = new CCHttpRequest();
	request->setRequestType(CCHttpRequest::kHttpGet);
	request->setResponseCallback(this,callfuncND_selector(FriendListScene::requestFinishedCallback));
	request->setTag("101");

    string _strUrl = CompleteUrl(URL_FRIEND_LIST);
    _strUrl.append(CCUserDefault::sharedUserDefault()->getStringForKey("userinfo"));

	request->setUrl(_strUrl.c_str());

	CCHttpClient *client = CCHttpClient::getInstance();
	client->send(request);

	request->release();
}

void FriendListScene::requestFinishedCallback(CCNode* pSender,void *Rspdata)
{
	if (!this->ValidateResponseData(pSender,Rspdata))
	{
		return;
	}

	CCHttpResponse *response =  (CCHttpResponse*)Rspdata;
	std::vector<char> *buffer = response->getResponseData();

	std::string content(buffer->begin(),buffer->end());
	CCLog(content.c_str());

    CCDictionary * dictionary = CCJSONConverter::sharedConverter()->dictionaryFrom(content.c_str());
	int code = ((CCNumber *)dictionary->objectForKey("code"))->getIntValue();
    if (code != 200) {
        CCMessageBox("invoke web api failed!","ERROR");
        return;
    }

	std::string requestTag(response->getHttpRequest()->getTag());

	if (requestTag == "101") {
		mFriendList = dynamic_cast<CCArray *>(dictionary->objectForKey("friendList"));
		if (mFriendList==NULL)
		{
			return;
		}

		selectedindex = -1;
		mTableViewFriend->reloadData();
	} else if (requestTag == "102"){
		this->doSearchFriend();
		CCMessageBox("delete friend successfully","Success");
	}
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
    mTableViewFriend->setDirection(kCCScrollViewDirectionVertical);
    mTableViewFriend->setVerticalFillOrder(kCCTableViewFillTopDown);
    mTableViewFriend->setDataSource(this);
    mTableViewFriend->setViewSize(CCSizeMake(312, 300));
    mTableViewFriend->setDelegate(this);
    mTableViewFriend->reloadData();

	//doSearchFriend();
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
        chatBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(FriendListScene::toolBarTouchDownAction), CCControlEventTouchUpInside);
        cell->addChild(chatBtn);
        
        CCControlButton * msgBtn = CCControlButton::create(CCScale9Sprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("friends_emailbtn.png")));
        msgBtn->setPosition(ccp(81,size.height - CELL_ITEMS_Y - CELL_ITEMS_GAP));
        msgBtn->setAnchorPoint(ccp(0,0.5));
        msgBtn->setTag(128);
		msgBtn->setPreferredSize(CCSizeMake(74,34));
        msgBtn->setVisible(selected);
        msgBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(FriendListScene::toolBarTouchDownAction), CCControlEventTouchUpInside);
        cell->addChild(msgBtn);
        
        CCControlButton * formationBtn = CCControlButton::create(CCScale9Sprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("friends_formation.png")));
        formationBtn->setPosition(ccp(158,size.height - CELL_ITEMS_Y - CELL_ITEMS_GAP));
        formationBtn->setAnchorPoint(ccp(0,0.5));
        formationBtn->setTag(129);
		formationBtn->setPreferredSize(CCSizeMake(74,34));
        formationBtn->setVisible(selected);
        formationBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(FriendListScene::toolBarTouchDownAction), CCControlEventTouchUpInside);
        cell->addChild(formationBtn);
        
        CCControlButton * deleteBtn = CCControlButton::create(CCScale9Sprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("friends_delete.png")));
        deleteBtn->setPosition(ccp(235,size.height - CELL_ITEMS_Y - CELL_ITEMS_GAP));
        deleteBtn->setAnchorPoint(ccp(0,0.5));
        deleteBtn->setTag(130);
		deleteBtn->setPreferredSize(CCSizeMake(74,34));
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
	CCControlButton *button = (CCControlButton *)sender;
	switch (button->getTag()) 
	{
	case 127:
		{
			break;
		}
	case 128:
		{
			MainGameScene *mainScene = (MainGameScene *)this->getParent();
			mainScene->PushLayer((CCLayer *)this->GetLayer("NewMailScene"));
			break;
		}
	case 129:
		{
			break;
		}
	case 130:
		{
			CCMessageDialog *box = CCMessageDialog::create();
			box->setTitle("Are you sure add this guy as your friends?");
			box->setDelegate(this);
			this->addChild(box);

			break;
		}
	}
}

void FriendListScene::didClickButton(CCMessageDialog* dialog,unsigned int index)
{
	if (index == 0)
	{
		CCDictionary *dict = (CCDictionary *)mFriendList->objectAtIndex(selectedindex);
        string encryptedUserInfo(dict->valueForKey("encryptedUserInfo")->getCString());
		this->deleteFriend(encryptedUserInfo);
	}
}

void FriendListScene::deleteFriend(std::string &targetUser)
{
	CCHttpRequest *request = new CCHttpRequest();
	request->setRequestType(CCHttpRequest::kHttpGet);
	request->setResponseCallback(this,callfuncND_selector(FriendListScene::requestFinishedCallback));
	request->setTag("103");

	string _strUrl = CompleteUrl(URL_FRIEND_DELETE);
	_strUrl.append(CCUserDefault::sharedUserDefault()->getStringForKey("userinfo"));
	_strUrl.append("/" + targetUser);

	request->setUrl(_strUrl.c_str());

	CCHttpClient *client = CCHttpClient::getInstance();
	client->send(request);

	request->release();
}

void FriendListScene::buttonClicked(CCObject * sender , CCControlEvent controlEvent)
{
	MainGameScene *mainScene = (MainGameScene *)this->getParent();
	CCControlButton *button = (CCControlButton *)sender;
	switch (button->getTag()) {
	case 101:
		CCLOG("11111");
		mainScene->PopLayer();
		break;
	case 102:
		CCLOG("22222");
		mainScene->PushLayer((CCLayer *)this->GetLayer("AddFriendScene"));
		break;
	case 103:
		CCLOG("33333");
		break;
	}
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

