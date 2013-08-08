#include "MDPackageLayer.h"

CCScene* MDPackageLayer::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        MDPackageLayer *layer = MDPackageLayer::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MDPackageLayer::init()
{
    selectedindex = -1;
    
    bool bRet = false;
    do 
    {
        CC_BREAK_IF(! CCLayer::init());

		btnTouched = false;
        
        mHeroList = CCArray::create(CCString::create("Li1"),CCString::create("张三"),CCString::create("Li3"),CCString::create("李四"),CCString::create("Li1653"),CCString::create("Li1qwe"),CCString::create("Li1"),CCString::create("Li1"),CCString::create("Li409"),CCString::create("Li134"),CCString::create("Li51"),CCString::create("Li18974523"),CCString::create("Li1"),CCString::create("Li1"),CCString::create("Li1"),CCString::create("Li1"),CCString::create("Li1"),CCString::create("Li124"),CCString::create("Li1998"),CCString::create("Li3561"),NULL);
        mHeroList->retain();

		vUserData = new int[mHeroList->count()]();
		memset(vUserData, sizeof(int) * mHeroList->count(), 0);

		this->reloadDataSource();

        bRet = true;
    } while (0);

    return bRet;
}

void MDPackageLayer::LoadHeros()
{
	this->ShowLoadingIndicator("");

	CCHttpRequest *request = new CCHttpRequest();
	request->setRequestType(CCHttpRequest::kHttpGet);
	request->setResponseCallback(this,httpresponse_selector(MDPackageLayer::requestFinishedCallback));
	request->setTag("101");

    string _strUrl = CompleteUrl(URL_FRIEND_LIST);
    _strUrl.append(CCUserDefault::sharedUserDefault()->getStringForKey("userinfo"));

	request->setUrl(_strUrl.c_str());

	CCHttpClient *client = CCHttpClient::getInstance();
	client->send(request);

	request->release();
}

void MDPackageLayer::requestFinishedCallback(CCHttpClient* client, CCHttpResponse* response)
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
		mHeroList = dynamic_cast<CCArray *>(dictionary->objectForKey("friendList"));
		if (mHeroList== NULL)
		{
			mHeroList = CCArray::create();
		}
        mHeroList->retain();
		selectedindex = -1;
		mTableView->reloadData();
	} else if (requestTag == "103"){
		this->LoadHeros();
		CCMessageBox("delete friend successfully","Success");
	}
}

bool MDPackageLayer::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    //CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mTableView", CCTableView*, this->mTableView);
    //CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_sTitle", CCSprite*, this->m_sTitle);
    return true;
}

SEL_MenuHandler MDPackageLayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
	return NULL;
}

SEL_CCControlHandler MDPackageLayer::onResolveCCBCCControlSelector(CCObject *pTarget, const char * pSelectorName) {
    
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "buttonClicked:", MDPackageLayer::buttonClicked);
	return NULL;
}

void MDPackageLayer::onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader)
{
    this->setFntTitle(101);
    this->setFntTitle(102);

    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCMenu *menuTab = CCMenu::create();
    menuTab->setPosition(ccp(winSize.width * 0.5, 366));
    this->addChild(menuTab);
    
    CCMenuItemSprite* itemFairy = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("package_tab_normal.png"),CCSprite::createWithSpriteFrameName("package_tab_selected.png"),NULL,this,menu_selector(MDPackageLayer::switchCallback));
    CCSize itemSize = itemFairy->getContentSize();
    
    CCLabelBMFont *lblPackage1 = CCLabelBMFont::create("背包一", "btn.fnt");
    itemFairy->addChild(lblPackage1);
    lblPackage1->setPosition(ccp(itemSize.width * 0.5,itemSize.height * 0.5));
    menuTab->addChild(itemFairy);
    itemFairy->setPosition(ccp(-itemSize.width - 4, 0));
    itemFairy->selected();
    _preSelectedTab = itemFairy;
    
    CCMenuItemSprite* itemBuddha = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("package_tab_normal.png"),CCSprite::createWithSpriteFrameName("package_tab_selected.png"),NULL,this,menu_selector(MDPackageLayer::switchCallback));
    CCLabelBMFont *lblPackage2 = CCLabelBMFont::create("背包二", "btn.fnt");
    itemBuddha->addChild(lblPackage2);
    lblPackage2->setPosition(ccp(itemSize.width * 0.5,itemSize.height * 0.5));
    menuTab->addChild(itemBuddha);
    itemBuddha->setPosition(ccp(0, 0));
    
    CCMenuItemSprite* itemDemon = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("package_tab_normal.png"),CCSprite::createWithSpriteFrameName("package_tab_selected.png"),NULL,this,menu_selector(MDPackageLayer::switchCallback));
    CCLabelBMFont *lblPackage3 = CCLabelBMFont::create("背包三", "btn.fnt");
    itemDemon->addChild(lblPackage3);
    lblPackage3->setPosition(ccp(itemSize.width * 0.5,itemSize.height * 0.5));
    menuTab->addChild(itemDemon);
    itemDemon->setPosition(ccp(itemSize.width + 4, 0));
    
    this->reloadDataSource();
}

void MDPackageLayer::switchCallback(CCObject* pSender){
    
	CCMenuItemSprite * pItem = dynamic_cast<CCMenuItemSprite*>(pSender);
    
    if ( pItem != _preSelectedTab ) {
        if ( _preSelectedTab != NULL )
		{
			_preSelectedTab->unselected();
		}
        
        pItem->selected();
        
        _preSelectedTab = pItem;
    } else {
        pItem->selected();
    }
}

void MDPackageLayer::reloadDataSource()
{
	mTableView = CCMultiColumnTableView::create(this,CCSizeMake(320,270),NULL);
	this->addChild(mTableView);
	mTableView->setPosition(ccp(0,80));
	mTableView->setDirection(kCCScrollViewDirectionVertical);
	mTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
	mTableView->setDataSource(this);
	mTableView->setDelegate(this);
	mTableView->setColCount(5);
	mTableView->reloadData();
}

void MDPackageLayer::tableCellHighlight(CCTableView* table, CCTableViewCell* cell)
{
//    CCSprite *sSelected = (CCSprite*)cell->getChildByTag(121);
//    sSelected->setVisible(true);
}

void MDPackageLayer::tableCellUnhighlight(CCTableView* table, CCTableViewCell* cell)
{
//    CCSprite *sSelected = (CCSprite*)cell->getChildByTag(121);
//    sSelected->setVisible(false);
}

void MDPackageLayer::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
//    CCLOG("cell touched at index: %i", cell->getIdx());
//	if (btnTouched)
//	{
//		return;
//	}
//    if (selectedindex == cell->getIdx()) {
//        selectedindex = -1;
//    } else {
//        selectedindex = cell->getIdx();
//    }
//
//    table->refreshData();
    //MainGameScene *mainScene = (MainGameScene *)this->getParent();
    //mainScene->PushLayer((CCLayer *)this->GetLayer("MDHeroDetailLayer"));
}

unsigned int MDPackageLayer::numberOfCellsInTableView(CCTableView *table)
{
	return mHeroList->count();
}

CCSize MDPackageLayer::cellSizeForTable(CCTableView *table)
{
	return CCSizeMake(62, 64);
}

CCSize MDPackageLayer::tableCellSizeForIndex(CCTableView *table, unsigned int idx)
{
    return CCSizeMake(62, 64);
}

CCTableViewCell* MDPackageLayer::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
	CCDictionary *dict = (CCDictionary *)mHeroList->objectAtIndex(idx);
	bool selected = (idx==selectedindex);
	CCTableViewCell *cell = table->dequeueCell();
    CCSize size = this->tableCellSizeForIndex(table, idx);
	if (!cell) {
		cell = new CCTableViewCell();
		cell->autorelease();
        
//		CCSprite *sSelected = CCSprite::createWithSpriteFrameName("card_selected.png");
//		sSelected->setVisible(false);
//		sSelected->setTag(121);
//		sSelected->setPosition(ccp(size.width * 0.5,size.height * 0.5));
//		sSelected->setAnchorPoint(ccp(0.5, 0.5));
//		cell->addChild(sSelected);

		CCSprite *sHead = CCSprite::createWithSpriteFrameName("package_cell_bg.png");
		sHead->setTag(122);
		sHead->setPosition(ccp(size.width * 0.5,size.height * 0.5));
		sHead->setAnchorPoint(ccp(0.5, 0.5));
		cell->addChild(sHead);

//		CCLabelTTF *lblName = CCLabelTTF::create("rulaifo", FONT_VERDANA, FONT_SIZE_BIG);
//		lblName->setPosition(ccp(80,size.height - CELL_ITEMS_Y));
//		lblName->setAnchorPoint(ccp(0, 0.5));
//        lblName->setColor(ccc3(235, 234, 181));
//        lblName->enableStroke(ccc3(16, 6, 9), 0.8);
//		lblName->setTag(123);
//		cell->addChild(lblName);

		//CCLabelTTF *lblLevel = CCLabelTTF::create("LV. 3", FONT_VERDANA, FONT_SIZE_MEDIUM);
		//lblLevel->setPosition(ccp(80,size.height - 2 * CELL_ITEMS_Y));
		//lblLevel->setAnchorPoint(ccp(0, 0.5));
  //      lblLevel->setColor(ccc3(235, 234, 181));
  //      lblLevel->enableStroke(ccc3(16, 6, 9), 0.8);
		//lblLevel->setTag(124);
		//cell->addChild(lblLevel);
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
        
        CCSprite *sHead = (CCSprite*)cell->getChildByTag(122);
        
//		CCLabelTTF *lblName = (CCLabelTTF*)cell->getChildByTag(123);
//		lblName->setString("weiweiyao");
        
        //CCLabelTTF *lblLevel = (CCLabelTTF*)cell->getChildByTag(124);
		//lblLevel->setString(string->getCString());
	}

	return cell;
}

//    按下按钮事件回调
void MDPackageLayer::toolBarTouchDownAction(CCObject * sender , CCControlEvent pCCControlEvent)
{
	CCControlButton *button = (CCControlButton *)sender;
	if (pCCControlEvent==CCControlEventTouchDown)
	{
		btnTouched = true;
	}
	else if (pCCControlEvent==CCControlEventTouchUpInside)
	{
		switch (button->getTag()) 
		{
		case 127:
			{
				btnTouched = false;
				break;
			}
		case 128:
			{
				btnTouched = false;
				MainGameScene *mainScene = (MainGameScene *)this->getParent();
				mainScene->PushLayer((CCLayer *)this->GetLayer("NewMailScene"));
				break;
			}
		case 129:
			{
				btnTouched = false;
				break;
			}
		case 130:
			{
				btnTouched = false;
				//CCMessageDialog *box = CCMessageDialog::create();
				//box->setTitle(GlobalData::getLocalString("friend_delete_confirm")->getCString());
				//box->setDelegate(this);
				//this->addChild(box);

				break;
			}
		}
	}
}

void MDPackageLayer::buttonClicked(CCObject * sender , CCControlEvent controlEvent)
{
	MainGameScene *mainScene = (MainGameScene *)this->getParent();
	CCControlButton *button = (CCControlButton *)sender;
	switch (button->getTag()) {
	case 101:
        {
            mainScene->PushLayer((CCLayer *)this->GetLayer("MDHeroDetailLayer"));
            break;
        }
	case 102:
        {

            mainScene->PopLayer();
            break;
        }
	}
}

MDPackageLayer::MDPackageLayer()
{
    mTableView = NULL;
    mHeroList = NULL;
    //m_sTitle = NULL;
}

MDPackageLayer::~MDPackageLayer()
{
    //CC_SAFE_RELEASE(mTableView);
    //CC_SAFE_RELEASE(m_sTitle);
}

