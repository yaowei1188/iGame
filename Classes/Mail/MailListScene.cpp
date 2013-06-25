#include "MailListScene.h"

CCScene* MailListScene::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        MailListScene *layer = MailListScene::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MailListScene::init()
{
    selectedindex = -1;
    
    bool bRet = false;
    do 
    {
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////

        CC_BREAK_IF(! CCLayer::init());
        
		//mArrayList =  CCArray::create();
        mArrayList = CCArray::create(CCString::create("Li1"),CCString::create("张三"),CCString::create("Li3"),CCString::create("李四"),CCString::create("Li1653"),CCString::create("Li1qwe"),CCString::create("Li1"),CCString::create("Li1"),CCString::create("Li409"),CCString::create("Li134"),CCString::create("Li51"),CCString::create("Li18974523"),CCString::create("Li1"),CCString::create("Li1"),CCString::create("Li1"),CCString::create("Li1"),CCString::create("Li1"),CCString::create("Li124"),CCString::create("Li1998"),CCString::create("Li3561"),NULL);
        mArrayList->retain();

		CCSprite *mailListBg = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("mail_list_bg.png"));
		mailListBg->setAnchorPoint(CCPointZero);
		mailListBg->setPosition(CCPointZero);
		this->addChild(mailListBg);
        
        CCSprite *sFriend = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("mail_lblFriend.png"));
		sFriend->setAnchorPoint(CCPointMake(0, 0.5));
		sFriend->setPosition(CCPointMake(30, 275));
		this->addChild(sFriend);
        
        CCSprite *sSubject = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("mail_lblsubject.png"));
		sSubject->setAnchorPoint(CCPointMake(0, 0.5));
		sSubject->setPosition(CCPointMake(120, 275));
		this->addChild(sSubject);
        
        CCMenu *menu = this->generateCheckBox();
        menu->setAnchorPoint(CCPointMake(0, 0.5));
        menu->setPosition(CCPointMake(190, 275));

		mTableViewMail = CCTableView::create(this,CCSizeMake(300,240));
		mTableViewMail->setPosition(CCPointMake(0, 15));
		this->addChild(mTableViewMail);
		mTableViewMail->setDirection(kCCScrollViewDirectionVertical);
		mTableViewMail->setVerticalFillOrder(kCCTableViewFillTopDown);
		mTableViewMail->setDelegate(this);
//        mTableViewMail->setViewSize(CCSizeMake(300, 220));
		mTableViewMail->reloadData();

        bRet = true;
    } while (0);

    return bRet;
}

void MailListScene::doSearch()
{
	this->ShowLoadingIndicator("");

	CCHttpRequest *request = new CCHttpRequest();
	request->setRequestType(CCHttpRequest::kHttpGet);
	request->setResponseCallback(this,callfuncND_selector(MailListScene::requestFinishedCallback));
	request->setTag("101");

    string _strUrl = CompleteUrl(URL_FRIEND_LIST);
    _strUrl.append(CCUserDefault::sharedUserDefault()->getStringForKey("userinfo"));

	request->setUrl(_strUrl.c_str());

	CCHttpClient *client = CCHttpClient::getInstance();
	client->send(request);

	request->release();
}

void MailListScene::requestFinishedCallback(CCNode* pSender,void *Rspdata)
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
		mArrayList = dynamic_cast<CCArray *>(dictionary->objectForKey("friendList"));
		if (mArrayList==NULL)
		{
			return;
		}

		selectedindex = -1;
		mTableViewMail->reloadData();
	} else if (requestTag == "102"){
		this->doSearch();
		CCMessageBox("delete friend successfully","Success");
	}
}

void MailListScene::tableCellHighlight(CCTableView* table, CCTableViewCell* cell)
{
    CCSprite *sSelected = (CCSprite*)cell->getChildByTag(121);
    sSelected->setVisible(true);
}

void MailListScene::tableCellUnhighlight(CCTableView* table, CCTableViewCell* cell)
{
    CCSprite *sSelected = (CCSprite*)cell->getChildByTag(121);
    sSelected->setVisible(false);
}

void MailListScene::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
    CCLOG("cell touched at index: %i", cell->getIdx());
    if (selectedindex == cell->getIdx()) {
        selectedindex = -1;
    } else {
        selectedindex = cell->getIdx();
    }

    table->reloadData();
}

unsigned int MailListScene::numberOfCellsInTableView(CCTableView *table)
{
	return mArrayList->count();
}

CCSize MailListScene::cellSizeForTable(CCTableView *table)
{
	return CCSizeMake(312, 50);
}

CCSize MailListScene::cellSizeForIndex(CCTableView *table, unsigned int idx)
{
    return CCSizeMake(312, 50);
}

bool MailListScene::hasFixedCellSize()
{
    return false;
}

void MailListScene::callbackSwitch(CCObject* pSender){
    
	CCMenuItemToggle* pSwitch = (CCMenuItemToggle*)pSender;
    
    if (pSwitch->getSelectedIndex()==0) {
//        m_blnRememberMe = false;
    } else {
//        m_blnRememberMe = true;
    }
}

CCMenu* MailListScene::generateCheckBox()
{
    CCSprite *spriteOn = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("gou_1.png"));
	CCSprite *spriteOff = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("gou_2.png"));
    
    CCMenu* m_auto_op_menu = CCMenu::create();
    CCMenuItemSprite* auto_op_btn = CCMenuItemSprite::create(spriteOff, NULL);
    CCMenuItemSprite* auto_op_btn2 = CCMenuItemSprite::create(spriteOn, NULL);
    CCMenuItemToggle* item = CCMenuItemToggle::createWithTarget(this, menu_selector(MailListScene::callbackSwitch),auto_op_btn,auto_op_btn2,NULL);
    
    m_auto_op_menu->addChild(item);
//    m_auto_op_menu->autorelease();
    
    return m_auto_op_menu;
}

CCTableViewCell* MailListScene::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
	CCString *string = (CCString *)mArrayList->objectAtIndex(idx);
    CCSize size = this->cellSizeForIndex(table, idx);
	CCTableViewCell *cell = table->dequeueCell();
	if (!cell) {
		cell = new CCTableViewCell();
		cell->autorelease();
        
        
        
//        CCSprite *sSelected = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("friends_cellhighlight.png"));
//        sSelected->setVisible(false);
//        sSelected->setTag(121);
//		sSelected->setPosition(ccp(13,size.height - 39));
//		sSelected->setAnchorPoint(CCPointZero);
//		cell->addChild(sSelected);

		CCLabelTTF *lblFriendName = CCLabelTTF::create(string->getCString(), "Arial", 14.0);
		lblFriendName->setPosition(ccp(40,size.height * 0.5));
        lblFriendName->setColor(ccc3(255, 255, 204));
		lblFriendName->setTag(121);
        lblFriendName->setString(string->getCString());
		cell->addChild(lblFriendName);

		CCLabelTTF *lblSubject = CCLabelTTF::create("100", "Arial", 14.0);
		lblSubject->setPosition(ccp(130,size.height * 0.5));
        lblSubject->setColor(ccc3(255, 255, 204));
        lblSubject->setTag(122);
        lblSubject->setString(string->getCString());
		cell->addChild(lblSubject);
        
        CCScale9Sprite *sline = CCScale9Sprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("mail_line.png"));
        sline->setPreferredSize(CCSizeMake(290, 1));
        sline->setPosition(ccp(5,size.height-2));
        sline->setAnchorPoint(CCPointZero);
        cell->addChild(sline);
	}
	else
	{
//        CCSprite *sSelected = (CCSprite*)cell->getChildByTag(121);
//        sSelected->setPosition(ccp(13,size.height - 39));
//        if (selectedindex == idx ) {
//            sSelected->setVisible(true);
//        } else {
//            sSelected->setVisible(false);
//        }
        
		CCLabelTTF *lblFriendName = (CCLabelTTF*)cell->getChildByTag(121);
		lblFriendName->setString(string->getCString());
        
        CCLabelTTF *lblSubject = (CCLabelTTF*)cell->getChildByTag(122);
		lblSubject->setString(string->getCString());
	}

	return cell;
}

//    按下按钮事件回调
void MailListScene::toolBarTouchDownAction(CCObject * sender , CCControlEvent controlEvent)
{
	CCControlButton *button = (CCControlButton *)sender;
	switch (button->getTag()) 
	{
	case 128:
		{
			MainGameScene *mainScene = (MainGameScene *)this->getParent();
			mainScene->PushLayer((CCLayer *)this->GetLayer("NewMailScene"));
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

void MailListScene::didClickButton(CCMessageDialog* dialog,unsigned int index)
{
	if (index == 0)
	{
		CCDictionary *dict = (CCDictionary *)mArrayList->objectAtIndex(selectedindex);
        string encryptedUserInfo(dict->valueForKey("encryptedUserInfo")->getCString());
		this->deleteEntry(encryptedUserInfo);
	}
}

void MailListScene::deleteEntry(std::string &targetUser)
{
	CCHttpRequest *request = new CCHttpRequest();
	request->setRequestType(CCHttpRequest::kHttpGet);
	request->setResponseCallback(this,callfuncND_selector(MailListScene::requestFinishedCallback));
	request->setTag("103");

	string _strUrl = CompleteUrl(URL_FRIEND_DELETE);
	_strUrl.append(CCUserDefault::sharedUserDefault()->getStringForKey("userinfo"));
	_strUrl.append("/" + targetUser);

	request->setUrl(_strUrl.c_str());

	CCHttpClient *client = CCHttpClient::getInstance();
	client->send(request);

	request->release();
}

void MailListScene::buttonClicked(CCObject * sender , CCControlEvent controlEvent)
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

MailListScene::MailListScene()
{
    //mTableViewMail = NULL;
//    mMainSceneTemp = NULL;
    mArrayList = NULL;
}

MailListScene::~MailListScene()
{
//    mTableViewMail->release();
//    mMainSceneTemp->release();
//    mArrayList->release();
}

