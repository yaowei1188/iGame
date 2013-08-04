#include "SysMailListScene.h"

CCScene* SysMailListScene::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        SysMailListScene *layer = SysMailListScene::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SysMailListScene::init()
{
    selectedindex = -1;
    
    bool bRet = false;
    do 
    {

        CC_BREAK_IF(! CCLayer::init());

		selectedindex = -1;
		btnTouched = false;

		//CCSprite *mailListBg = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("mail_list_bg.png"));
		//mailListBg->setAnchorPoint(CCPointZero);
		//mailListBg->setPosition(CCPointZero);
		//this->addChild(mailListBg);
        
  //      CCSprite *sFriend = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("mail_lblFriend.png"));
		//sFriend->setAnchorPoint(CCPointMake(0, 0.5));
		//sFriend->setPosition(CCPointMake(30, 275));
		//this->addChild(sFriend);
  //      
  //      CCSprite *sSubject = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("mail_lblsubject.png"));
		//sSubject->setAnchorPoint(CCPointMake(0, 0.5));
		//sSubject->setPosition(CCPointMake(120, 275));
		//this->addChild(sSubject);
        
        menuCheckAll = this->generateCheckBox();
        this->addChild(menuCheckAll);
        menuCheckAll->setAnchorPoint(CCPointMake(0, 0.5));
        menuCheckAll->setPosition(CCPointMake(280, 310));

		doSearch();

        bRet = true;
    } while (0);

    return bRet;
}

void SysMailListScene::loadTableView()
{
	//mArrayList =  CCArray::create();
	//mArrayList = CCArray::create(CCString::create("Li1"),CCString::create("张三"),CCString::create("Li3"),CCString::create("李四"),CCString::create("Li1653"),CCString::create("Li1qwe"),CCString::create("Li1"),CCString::create("Li1"),CCString::create("Li409"),CCString::create("Li134"),CCString::create("Li51"),CCString::create("Li18974523"),CCString::create("Li1"),CCString::create("Li1"),CCString::create("Li1"),CCString::create("Li1"),CCString::create("Li1"),CCString::create("Li124"),CCString::create("Li1998"),CCString::create("Li3561"),NULL);
	mArrayList->retain();

	vUserData = new int[mArrayList->count()]();
	memset(vUserData, sizeof(int) * mArrayList->count(), 0);

	if (mTableViewMail==NULL)
	{
		mTableViewMail = CCTableView::create(this,CCSizeMake(320,270));
		mTableViewMail->setPosition(CCPointMake(0, 15));
		this->addChild(mTableViewMail);
		mTableViewMail->setDirection(kCCScrollViewDirectionVertical);
		mTableViewMail->setVerticalFillOrder(kCCTableViewFillTopDown);
		mTableViewMail->setDelegate(this);
	}

	mTableViewMail->reloadData();
}

void SysMailListScene::deleteEntrys()
{

}


void SysMailListScene::doSearch()
{
	this->ShowLoadingIndicator("");

	CCHttpRequest *request = new CCHttpRequest();
	request->setRequestType(CCHttpRequest::kHttpGet);
	request->setResponseCallback(this,httpresponse_selector(SysMailListScene::requestFinishedCallback));
	request->setTag("101");

    string _strUrl = CompleteUrl(URL_FRIEND_INVITATION_LIST);
    _strUrl.append(CCUserDefault::sharedUserDefault()->getStringForKey("userinfo"));

	request->setUrl(_strUrl.c_str());

	CCHttpClient *client = CCHttpClient::getInstance();
	client->send(request);

	request->release();
}

void SysMailListScene::requestFinishedCallback(CCHttpClient* client, CCHttpResponse* response)
{
	if (!this->ValidateResponseData(client,response))
	{
		return;
	}

	std::vector<char> *buffer = response->getResponseData();
	std::string content(buffer->begin(),buffer->end());

    CCDictionary * dictionary = CCJSONConverter::sharedConverter()->dictionaryFrom(content.c_str());
	int code = ((CCNumber *)dictionary->objectForKey("code"))->getIntValue();
    if (code != 200) {
        CCMessageBox("invoke web api failed!","ERROR");
        return;
    }

	std::string requestTag(response->getHttpRequest()->getTag());

	if (requestTag == "101") {
		mArrayList = dynamic_cast<CCArray *>(dictionary->objectForKey("friendInvitationList"));
		if (mArrayList==NULL)
		{
			return;
		}

		selectedindex = -1;

		loadTableView();

	} else if (requestTag == "103"){
		this->doSearch();
	}
}

void SysMailListScene::tableCellHighlight(CCTableView* table, CCTableViewCell* cell)
{
	CCSprite *sSelected = (CCSprite*)cell->getChildByTag(119);
	sSelected->setVisible(true);
}

void SysMailListScene::tableCellUnhighlight(CCTableView* table, CCTableViewCell* cell)
{
    CCSprite *sSelected = (CCSprite*)cell->getChildByTag(119);
    sSelected->setVisible(false);
}

void SysMailListScene::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
	CCLOG("cell touched at index: %i", cell->getIdx());
	if (btnTouched)
	{
		return;
	}
	if (selectedindex == cell->getIdx()) {
		selectedindex = -1;
	} else {
		selectedindex = cell->getIdx();
	}

	table->refreshData();
}

unsigned int SysMailListScene::numberOfCellsInTableView(CCTableView *table)
{
	return mArrayList->count();
}

CCSize SysMailListScene::cellSizeForTable(CCTableView *table)
{
	return CCSizeMake(320, 50);
}

CCSize SysMailListScene::tableCellSizeForIndex(CCTableView *table, unsigned int idx)
{
    return CCSizeMake(320, 50);
}

void SysMailListScene::callbackSwitch(CCObject* pSender){
    
	CCMenuItemToggle* pSwitch = (CCMenuItemToggle*)pSender;
	
	int *idx = (int *)pSwitch->getUserData();
	if (idx==NULL)
	{
		if (pSwitch->getSelectedIndex()==0) {
			for(int i=0;i<mArrayList->count();i++)
			{
				vUserData[i]=0;
			}
		} else {
			for(int i=0;i<mArrayList->count();i++)
			{
				vUserData[i]=1;
			}
		}
		mTableViewMail->refreshData();
	}
	else
	{
		if (pSwitch->getSelectedIndex()==0) {
			*idx = 0;
		} else {
			*idx = 1;
		}
	}
}

CCTableViewCell* SysMailListScene::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
	CCDictionary *dict = (CCDictionary *)mArrayList->objectAtIndex(idx);
	bool selected = (idx==selectedindex);
    CCSize size = this->tableCellSizeForIndex(table, idx);
	CCTableViewCell *cell = table->dequeueCell();
	if (!cell) {
		cell = new CCTableViewCell();
		cell->autorelease();

		CCSprite *sSelected = CCSprite::createWithSpriteFrameName("friends_cellhighlight.png");
		sSelected->setVisible(false);
		sSelected->setTag(119);
		sSelected->setPosition(ccp(2,5));
		sSelected->setAnchorPoint(CCPointZero);
		cell->addChild(sSelected);

		CCSprite *sState = CCSprite::createWithSpriteFrameName("mail_state_read.png");
		sState->setAnchorPoint(CCPointMake(0, 0.5));
		sState->setPosition(ccp(10,size.height * 0.5));
		sState->setTag(120);
		cell->addChild(sState);

		CCLabelTTF *lblFriendName = CCLabelTTF::create(((CCString *)dict->objectForKey("username"))->getCString(), "Arial", 14.0);
		lblFriendName->setPosition(ccp(65,size.height - CELL_ITEMS_Y));
        lblFriendName->setColor(ccc3(255, 255, 204));
		lblFriendName->setTag(121);
        //lblFriendName->enableStroke(ccc3(51, 0, 0), 0.6);
		cell->addChild(lblFriendName);

		CCLabelTTF *lblSubject = CCLabelTTF::create(GlobalData::getLocalString("friend_request_add")->getCString(), "Arial", 14.0);
		lblSubject->setPosition(ccp(130,size.height - CELL_ITEMS_Y));
        lblSubject->setColor(ccc3(255, 255, 204));
        lblSubject->setTag(122);
        //lblSubject->enableStroke(ccc3(51, 0, 0), 0.6);
		cell->addChild(lblSubject);
        
        CCScale9Sprite *sline = CCScale9Sprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("mail_line.png"));
        sline->setPreferredSize(CCSizeMake(285, 1));
        sline->setPosition(ccp(0,size.height-2));
        sline->setAnchorPoint(CCPointZero);
        cell->addChild(sline);
        
        CCMenu *menuCheck = this->generateCheckBox();
        cell->addChild(menuCheck);
        CCMenuItemToggle *toggle= (CCMenuItemToggle *)menuCheck->getChildByTag(1);
        toggle->setUserData(&vUserData[idx]);
		if (vUserData[idx] == 1) {
			toggle->setSelectedIndex(1);
		} else {
			toggle->setSelectedIndex(0);
		}

        menuCheck->setTag(123);
        menuCheck->setAnchorPoint(CCPointMake(0, 0.5));
        menuCheck->setPosition(CCPointMake(280, size.height * 0.5));

		CCControlButton * approveBtn =  CCControlButton::create(CCScale9Sprite::createWithSpriteFrameName("btn_bg.png"));
		approveBtn->setTitleBMFontForState("btn.fnt", CCControlStateNormal);
		approveBtn->setTitleForState(CCString::create("同意"),CCControlStateNormal);
		approveBtn->setPosition(CCPointMake(140, size.height * 0.5));
		approveBtn->setAnchorPoint(ccp(0,0.5));
		approveBtn->setTag(129);
		approveBtn->setPreferredSize(CCSizeMake(75,35));
		approveBtn->setVisible(selected);
		approveBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(SysMailListScene::toolBarTouchDownAction), CCControlEventTouchDown);
		approveBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(SysMailListScene::toolBarTouchDownAction), CCControlEventTouchUpInside);
		cell->addChild(approveBtn);

		CCControlButton * declineBtn =  CCControlButton::create(CCScale9Sprite::createWithSpriteFrameName("btn_bg.png"));
		declineBtn->setTitleBMFontForState("btn.fnt", CCControlStateNormal);
		declineBtn->setTitleForState(CCString::create("拒绝"),CCControlStateNormal);
		declineBtn->setPosition(CCPointMake(225, size.height * 0.5));
		declineBtn->setAnchorPoint(ccp(0,0.5));
		declineBtn->setTag(130);
		declineBtn->setPreferredSize(CCSizeMake(75,35));
		declineBtn->setVisible(selected);
		declineBtn->setTouchPriority(100);
		declineBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(SysMailListScene::toolBarTouchDownAction), CCControlEventTouchDown);
		declineBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(SysMailListScene::toolBarTouchDownAction), CCControlEventTouchUpInside);
		cell->addChild(declineBtn);
	}
	else
	{
		CCLabelTTF *lblFriendName = (CCLabelTTF*)cell->getChildByTag(121);
		lblFriendName->setString(((CCString *)dict->objectForKey("username"))->getCString());
        
        CCLabelTTF *lblSubject = (CCLabelTTF*)cell->getChildByTag(122);
		lblSubject->setString(GlobalData::getLocalString("friend_request_add")->getCString());

		CCMenu *menuCheck = (CCMenu *)cell->getChildByTag(123);
		CCMenuItemToggle *toggle= (CCMenuItemToggle *)menuCheck->getChildByTag(1);
		toggle->setUserData(&vUserData[idx]);

		if (vUserData[idx] == 1) {
			toggle->setSelectedIndex(1);
		} else {
			toggle->setSelectedIndex(0);
		}

		CCControlButton *approveBtn = (CCControlButton *)cell->getChildByTag(129);
		//approveBtn->setPosition(ccp(approveBtn->getPosition().x,size.height - CELL_ITEMS_Y - CELL_ITEMS_GAP));
		approveBtn->setVisible(selected);

		CCControlButton *declineBtn = (CCControlButton *)cell->getChildByTag(130);
		//declineBtn->setPosition(ccp(declineBtn->getPosition().x,size.height - CELL_ITEMS_Y - CELL_ITEMS_GAP));
		declineBtn->setVisible(selected);
	}

	return cell;
}

//    按下按钮事件回调
void SysMailListScene::toolBarTouchDownAction(CCObject * sender , CCControlEvent controlEvent)
{
	CCControlButton *button = (CCControlButton *)sender;
	if (controlEvent==CCControlEventTouchDown)
	{
		btnTouched = true;
	}
	else if (controlEvent==CCControlEventTouchUpInside)
	{
		switch (button->getTag()) 
		{
		case 129:
			{
				CCDictionary *dict = (CCDictionary *)mArrayList->objectAtIndex(selectedindex);
				string encryptedUserInfo(dict->valueForKey("encryptedUserInfo")->getCString());
				this->confirmRequest(encryptedUserInfo,true);

				btnTouched = false;
				break;
			}
		case 130:
			{
				CCMessageDialog *box = CCMessageDialog::create();
				box->setTitle(GlobalData::getLocalString("friend_delete_confirm")->getCString());
				box->setDelegate(this);
				this->addChild(box);

				btnTouched = false;
				break;
			}
		}
	}
}

void SysMailListScene::didClickButton(CCMessageDialog* dialog,unsigned int index)
{
	CCDictionary *dict = (CCDictionary *)mArrayList->objectAtIndex(selectedindex);
	string encryptedUserInfo(dict->valueForKey("encryptedUserInfo")->getCString());
	if (index == 0)
	{
		this->confirmRequest(encryptedUserInfo,false);
	}
}

void SysMailListScene::confirmRequest(std::string &targetUser,bool accept)
{
	CCHttpRequest *request = new CCHttpRequest();
	request->setRequestType(CCHttpRequest::kHttpGet);
	request->setResponseCallback(this,httpresponse_selector(SysMailListScene::requestFinishedCallback));
	request->setTag("103");

	string _strUrl = CompleteUrl(URL_FRIEND_CONFIRM);
	_strUrl.append(CCUserDefault::sharedUserDefault()->getStringForKey("userinfo"));
	_strUrl.append("/" + targetUser);
	if (accept)
	{
		_strUrl.append("/true");
	}
	else 
	{
		_strUrl.append("/false");
	}

	request->setUrl(_strUrl.c_str());

	CCHttpClient *client = CCHttpClient::getInstance();
	client->send(request);

	request->release();
}

//void SysMailListScene::buttonClicked(CCObject * sender , CCControlEvent controlEvent)
//{
//	MainGameScene *mainScene = (MainGameScene *)this->getParent();
//	CCControlButton *button = (CCControlButton *)sender;
//	switch (button->getTag()) {
//	case 101:
//		CCLOG("11111");
//		mainScene->PopLayer();
//		break;
//	case 102:
//		CCLOG("22222");
//		mainScene->PushLayer((CCLayer *)this->GetLayer("AddFriendScene"));
//		break;
//	case 103:
//		CCLOG("33333");
//		break;
//	}
//}

SysMailListScene::SysMailListScene()
{
    mTableViewMail = NULL;
//    mMainSceneTemp = NULL;
    mArrayList = NULL;
}

SysMailListScene::~SysMailListScene()
{
//    mTableViewMail->release();
//    mMainSceneTemp->release();
//    mArrayList->release();
}

