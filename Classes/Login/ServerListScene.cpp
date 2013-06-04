#include "ServerListScene.h"

using namespace cocos2d;

CCScene* ServerListScene::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        ServerListScene *layer = ServerListScene::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool ServerListScene::init()
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
        mArrayList = CCArray::create(CCString::create("1区 花果山"),CCString::create("2区 齐天大圣"),CCString::create("3区 如来佛主"),NULL);
        mArrayList->retain();

        bRet = true;
    } while (0);

    return bRet;
}

void ServerListScene::doSearch()
{
	this->ShowLoadingIndicator("");

	CCHttpRequest *request = new CCHttpRequest();
	request->setRequestType(CCHttpRequest::kHttpGet);
	request->setResponseCallback(this,callfuncND_selector(ServerListScene::requestFinishedCallback));
	request->setTag("101");

    string _strUrl = CompleteUrl(URL_FRIEND_LIST);
    _strUrl.append(CCUserDefault::sharedUserDefault()->getStringForKey("userinfo"));

	request->setUrl(_strUrl.c_str());

	CCHttpClient *client = CCHttpClient::getInstance();
	client->send(request);

	request->release();
}

void ServerListScene::requestFinishedCallback(CCNode* pSender,void *Rspdata)
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
		mTableView->reloadData();
	} else if (requestTag == "102"){
		this->doSearch();
		CCMessageBox("delete friend successfully","Success");
	}
}

bool ServerListScene::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mTableView", CCTableView*, this->mTableView);
//    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mMainSceneTemp", MainSceneTemplate*, this->mMainSceneTemp);
    return true;
}

SEL_MenuHandler ServerListScene::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
//	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "menuBarBtnClicked:", ServerListScene::menuBarBtnClicked);
	return NULL;
}

SEL_CCControlHandler ServerListScene::onResolveCCBCCControlSelector(CCObject *pTarget, const char * pSelectorName) {
    
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "buttonClicked:", ServerListScene::buttonClicked);
	return NULL;
}

void ServerListScene::onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader)
{
    mTableView->setDirection(kCCScrollViewDirectionVertical);
    mTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
    mTableView->setDataSource(this);
    mTableView->setViewSize(CCSizeMake(290, 220));
    mTableView->setPosition(ccp(160, 120));
    mTableView->setDelegate(this);
    mTableView->reloadData();

	//doSearchFriend();
}

void ServerListScene::tableCellHighlight(CCTableView* table, CCTableViewCell* cell)
{
    CCSprite *sSelected = (CCSprite*)cell->getChildByTag(121);
    sSelected->setVisible(true);
}

void ServerListScene::tableCellUnhighlight(CCTableView* table, CCTableViewCell* cell)
{
    CCSprite *sSelected = (CCSprite*)cell->getChildByTag(121);
    sSelected->setVisible(false);
}

void ServerListScene::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
    CCLOG("cell touched at index: %i", cell->getIdx());
    if (selectedindex == cell->getIdx()) {
        
    } else {
        selectedindex = cell->getIdx();
    }

    table->reloadData();
}

unsigned int ServerListScene::numberOfCellsInTableView(CCTableView *table)
{
	return mArrayList->count();
}

CCSize ServerListScene::cellSizeForTable(CCTableView *table)
{
	return CCSizeMake(290, 40);
}

CCSize ServerListScene::cellSizeForIndex(CCTableView *table, unsigned int idx)
{
    return CCSizeMake(290, 40);
}

bool ServerListScene::hasFixedCellSize()
{
    return true;
}

CCTableViewCell* ServerListScene::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
	CCString *string = (CCString *)mArrayList->objectAtIndex(idx);
    bool selected = (idx==selectedindex);
	CCTableViewCell *cell = table->dequeueCell();
    CCSize size = this->cellSizeForIndex(table, idx);
	if (!cell) {
		cell = new CCTableViewCell();
		cell->autorelease();
        
        CCSprite *sbackground = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("server_cell_bg.png"));
        sbackground->setTag(120);
		sbackground->setPosition(ccp(size.width/2,size.height/2));
		cell->addChild(sbackground);
        
        CCSprite *sSelected = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("yuan.png"));
        sSelected->setTag(121);
		sSelected->setPosition(ccp(50,size.height/2));
		cell->addChild(sSelected);
        
        if (selected ) {
            sSelected->setVisible(true);
        } else {
            sSelected->setVisible(false);
        }

		CCLabelTTF *lblName = CCLabelTTF::create(string->getCString(), "Arial", 12.0);
		lblName->setPosition(ccp(130,size.height/2));
        lblName->setVerticalAlignment(kCCVerticalTextAlignmentCenter);
        lblName->setColor(ccc3(0, 0, 0));
		lblName->setTag(123);
		cell->addChild(lblName);

//		CCLabelTTF *lblLevel = CCLabelTTF::create("2区", "Arial", 14.0);
//		lblLevel->setPosition(ccp(165,18));
////		lblLevel->setAnchorPoint(CCPointZero);
//        lblLevel->setColor(ccc3(248, 255, 38));
//		lblLevel->setTag(124);
//		cell->addChild(lblLevel);

		CCLabelTTF *lblFriend = CCLabelTTF::create("良好", "Arial", 11.0);
		lblFriend->setPosition(ccp(218,size.height/2));
        lblFriend->setVerticalAlignment(kCCVerticalTextAlignmentCenter);
        lblFriend->setColor(ccc3(51, 153, 00));
        lblFriend->setTag(125);
		cell->addChild(lblFriend);
    }
	else
	{
        CCSprite *sSelected = (CCSprite*)cell->getChildByTag(121);
        if (selectedindex == idx ) {
            sSelected->setVisible(true);
        } else {
            sSelected->setVisible(false);
        }
        
		CCLabelTTF *lblName = (CCLabelTTF*)cell->getChildByTag(123);
		lblName->setString(string->getCString());
        
//        CCLabelTTF *lblLevel = (CCLabelTTF*)cell->getChildByTag(124);
		//lblLevel->setString(string->getCString());
        
//        CCLabelTTF *lblFriend = (CCLabelTTF*)cell->getChildByTag(125);
//		lblFriend->setString(string->getCString());
	}

	return cell;
}

void ServerListScene::submitSelectedServer(std::string &targetUser)
{
    if (selectedindex == -1) {
        CCMessageBox(GlobalData::getLocalString("account_pwd_empty")->getCString(),"ERROR");
        return;
    }
    
	CCHttpRequest *request = new CCHttpRequest();
	request->setRequestType(CCHttpRequest::kHttpGet);
	request->setResponseCallback(this,callfuncND_selector(ServerListScene::requestFinishedCallback));
	request->setTag("103");

	string _strUrl = CompleteUrl(URL_FRIEND_DELETE);
	_strUrl.append(CCUserDefault::sharedUserDefault()->getStringForKey("userinfo"));
	_strUrl.append("/" + targetUser);

	request->setUrl(_strUrl.c_str());

	CCHttpClient *client = CCHttpClient::getInstance();
	client->send(request);

	request->release();
}

void ServerListScene::buttonClicked(CCObject * sender , CCControlEvent controlEvent)
{
	MainGameScene *mainScene = (MainGameScene *)this->getParent();
	CCControlButton *button = (CCControlButton *)sender;
	switch (button->getTag()) {
	case 101:
		CCLOG("11111");
		mainScene->PopLayer();
		break;
	case 102:
		this->OpenNewScene("MainGameScene");
		break;
	}
}

ServerListScene::ServerListScene()
{
    mTableView = NULL;
//    mMainSceneTemp = NULL;
    mArrayList = NULL;
}

ServerListScene::~ServerListScene()
{
//    mTableViewMail->release();
//    mMainSceneTemp->release();
//    mArrayList->release();
}

