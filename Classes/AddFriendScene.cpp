#include "AddFriendScene.h"
#include "json/json.h"

using namespace cocos2d;

CCScene* AddFriendScene::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        AddFriendScene *layer = AddFriendScene::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool AddFriendScene::init()
{
    bool bRet = false;
    do 
    {
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////

        CC_BREAK_IF(! CCLayer::init());
        
        selectedindex = -1;

        mFriendList = CCArray::create(CCString::create("Li1"),CCString::create("Li2"),CCString::create("Li3"),CCString::create("Li1"),CCString::create("Li1653"),CCString::create("Li1qwe"),CCString::create("Li1"),CCString::create("Li1"),CCString::create("Li409"),CCString::create("Li134"),CCString::create("Li51"),CCString::create("Li18974523"),CCString::create("Li1"),CCString::create("Li1"),CCString::create("Li1"),CCString::create("Li1"),CCString::create("Li1"),CCString::create("Li124"),CCString::create("Li1998"),CCString::create("Li3561"),NULL);
        mFriendList->retain();
        
        bRet = true;
    } while (0);

    return bRet;
}

void AddFriendScene::buttonClicked(CCObject *pSender,CCControlEvent event)
{
	CCLOG("i was clicked");
	char sSearchText[20];
	sprintf(sSearchText,"%s",m_txtSearchField->getText());
    
    CCControlButton *button = (CCControlButton *)pSender;
    
    if (button->getTag()==2) {

        MainGameScene *mainScene = (MainGameScene *)this->getParent();
        mainScene->PopLayer();
        
    } else if(button->getTag()==2) {
        this->doSearchFriend();
    }
}

void AddFriendScene::doSearchFriend()
{
	CCHttpRequest *request = new CCHttpRequest();
	request->setRequestType(CCHttpRequest::kHttpGet);
	request->setResponseCallback(this,callfuncND_selector(AddFriendScene::requestFinishedCallback));
	request->setTag("101");
    
    char url[150] = {0};
    //sprintf(url,"%s/friend/addFriend/%s/%s",API_URL,CCUserDefault::sharedUserDefault()->getStringForKey("userinfo").c_str(),userinfo.c_str());
    CCLOG(url);
	request->setUrl(url);

	CCHttpClient *client = CCHttpClient::getInstance();
	client->send(request);

	request->release();
}

void AddFriendScene::addFriendRequest(std::string &userinfo)
{
	CCHttpRequest *request = new CCHttpRequest();
	request->setRequestType(CCHttpRequest::kHttpGet);
	request->setResponseCallback(this,callfuncND_selector(AddFriendScene::requestFinishedCallback));
	request->setTag("102");
    
    char url[150] = {0};
    sprintf(url,"%s/friend/addFriend/%s/%s",API_URL,CCUserDefault::sharedUserDefault()->getStringForKey("userinfo").c_str(),userinfo.c_str());
    CCLOG(url);
	request->setUrl(url);

	CCHttpClient *client = CCHttpClient::getInstance();
	client->send(request);
    
	request->release();
}

void AddFriendScene::requestFinishedCallback(CCNode* pSender,void *data)
{
    CCHttpResponse *response =  (CCHttpResponse*)data;
    
	if (!response->isSucceed())
	{
		CCLog("response failed");
		CCLog("error buffer: %s", response->getErrorBuffer());
        CCMessageBox("ERROR", "Response failed");
		return;
	}
    
    std::vector<char> *buffer = response->getResponseData();
	std::string content(buffer->begin(),buffer->end());
    
    Json::Reader reader;
	Json::Value root;
    
    const char* str = content.c_str();
	if (!reader.parse(str, root))
	{
        CCMessageBox("Parse failed","ERROR");
		return;
	}
    
    std::string requestTag(response->getHttpRequest()->getTag());
    
    if (requestTag == "101") {
        std::string a(root["username"].asString());
    } else if (requestTag == "102"){
        std::string a(root["username"].asString());
    }
}

void AddFriendScene::onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader)
{
    CCLOG("TEST");
    
    m_txtSearchField->setPlaceHolder("please input search field");
    
    mTableViewFriend->setDirection(kCCScrollViewDirectionVertical);
    mTableViewFriend->setVerticalFillOrder(kCCTableViewFillTopDown);
    mTableViewFriend->setDataSource(this);
    mTableViewFriend->setViewSize(CCSizeMake(312, 260));
    mTableViewFriend->setDelegate(this);
    mTableViewFriend->reloadData();

}

bool AddFriendScene::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_txtSearchField", CCEditBox*, this->m_txtSearchField);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mTableViewFriend", CCTableView*, this->mTableViewFriend);
    return true;
}

void AddFriendScene::toolBarBtnClicked(CCObject *pSender, CCControlEvent pCCControlEvent) {
	CCControlButton *button = (CCControlButton *)pSender;
    switch (button->getTag()) {
        case 127:
            std::string userinfo = "6a5f0245b228a6c6f464fd300304857e";
            this->addFriendRequest(userinfo);
            break;
//        case 128:
//            
//            break;
//        case 129:
//            
//            break;
//        case 130:
//            
//            break;
//        default:
//            break;
    }
}

SEL_MenuHandler AddFriendScene::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
//	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "menuBarBtnClicked:", LoginScene::menuBarBtnClicked);
    
	return NULL;
}

SEL_CCControlHandler AddFriendScene::onResolveCCBCCControlSelector(CCObject *pTarget, const char * pSelectorName) {
    
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "buttonClicked:", AddFriendScene::buttonClicked);
	return NULL;
}

void AddFriendScene::tableCellHighlight(CCTableView* table, CCTableViewCell* cell)
{
    
}

void AddFriendScene::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
    CCLOG("cell touched at index: %i", cell->getIdx());
    if (selectedindex == cell->getIdx()) {
        selectedindex = -1;
    } else {
        selectedindex = cell->getIdx();
    }
    
    table->reloadData();
}

unsigned int AddFriendScene::numberOfCellsInTableView(CCTableView *table)
{
	return mFriendList->count();
}

CCSize AddFriendScene::cellSizeForTable(CCTableView *table)
{
	return CCSizeMake(312, 50);
}

CCSize AddFriendScene::cellSizeForIndex(CCTableView *table, unsigned int idx)
{
    if (selectedindex == idx ) {
        return CCSizeMake(312, 80);
    }
    return CCSizeMake(312, 50);
}

bool AddFriendScene::hasFixedCellSize()
{
    return false;
}

CCTableViewCell* AddFriendScene::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
	CCString *string = (CCString *)mFriendList->objectAtIndex(idx);
    bool selected = (idx==selectedindex);
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
        
		CCLabelTTF *lblName = CCLabelTTF::create(string->getCString(), "Helvetica", 15.0);
		lblName->setPosition(ccp(15,size.height - CELL_ITEMS_Y));
		lblName->setAnchorPoint(CCPointZero);
		lblName->setTag(123);
		cell->addChild(lblName);
        
		CCLabelTTF *lblLevel = CCLabelTTF::create("Lv2", "Helvetica", 15.0);
		lblLevel->setPosition(ccp(90,size.height - CELL_ITEMS_Y));
		lblLevel->setAnchorPoint(CCPointZero);
		lblLevel->setTag(124);
		cell->addChild(lblLevel);
        
		CCLabelTTF *lblFriend = CCLabelTTF::create("friends", "Helvetica", 15.0);
		lblFriend->setPosition(ccp(160,size.height - CELL_ITEMS_Y));
		lblFriend->setAnchorPoint(CCPointZero);
        lblFriend->setTag(125);
		cell->addChild(lblFriend);
        
		CCLabelTTF *lblStatus = CCLabelTTF::create("Online", "Helvetica", 15.0);
		lblStatus->setPosition(ccp(240,size.height - CELL_ITEMS_Y));
		lblStatus->setAnchorPoint(CCPointZero);
        lblStatus->setTag(126);
		cell->addChild(lblStatus);
        
        CCControlButton * chatBtn = CCControlButton::create("Chat", "Helvetica", 15);
        chatBtn->setPosition(ccp(30,size.height - CELL_ITEMS_Y - CELL_ITEMS_GAP));
        chatBtn->setAnchorPoint(CCPointZero);
        chatBtn->setTag(127);
        chatBtn->setVisible(selected);
        chatBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(AddFriendScene::toolBarBtnClicked), CCControlEventTouchUpInside);
        cell->addChild(chatBtn);
        
        CCControlButton * msgBtn = CCControlButton::create("message", "Helvetica", 15);
        msgBtn->setPosition(ccp(90,size.height - CELL_ITEMS_Y - CELL_ITEMS_GAP));
        msgBtn->setAnchorPoint(CCPointZero);
        msgBtn->setTag(128);
        msgBtn->setVisible(selected);
        msgBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(AddFriendScene::toolBarBtnClicked), CCControlEventTouchUpInside);
        cell->addChild(msgBtn);
        
        CCControlButton * formationBtn = CCControlButton::create("formation", "Helvetica", 15);
        formationBtn->setPosition(ccp(150,size.height - CELL_ITEMS_Y - CELL_ITEMS_GAP));
        formationBtn->setAnchorPoint(CCPointZero);
        formationBtn->setTag(129);
        formationBtn->setVisible(selected);
        formationBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(AddFriendScene::toolBarBtnClicked), CCControlEventTouchUpInside);
        cell->addChild(formationBtn);
        
        CCControlButton * deleteBtn = CCControlButton::create("Delete", "Helvetica", 15);
        deleteBtn->setPosition(ccp(240,size.height - CELL_ITEMS_Y - CELL_ITEMS_GAP));
        deleteBtn->setAnchorPoint(CCPointZero);
        deleteBtn->setTag(130);
        deleteBtn->setVisible(selected);
        deleteBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(AddFriendScene::toolBarBtnClicked), CCControlEventTouchUpInside);
        cell->addChild(deleteBtn);
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
	}
    
	return cell;
}

AddFriendScene::AddFriendScene()
{
    mTableViewFriend = NULL;
    mFriendList = NULL;
    m_txtSearchField = NULL;
}

AddFriendScene::~AddFriendScene()
{
//    mTableViewFriend->release();
//    mMainSceneTemp->release();
    mFriendList->release();
//    m_txtSearchField->release();
}

