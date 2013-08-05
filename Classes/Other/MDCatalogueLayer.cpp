#include "MDCatalogueLayer.h"

CCScene* MDCatalogueLayer::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        MDCatalogueLayer *layer = MDCatalogueLayer::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MDCatalogueLayer::init()
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

void MDCatalogueLayer::LoadHeros()
{
	this->ShowLoadingIndicator("");

	CCHttpRequest *request = new CCHttpRequest();
	request->setRequestType(CCHttpRequest::kHttpGet);
	request->setResponseCallback(this,httpresponse_selector(MDCatalogueLayer::requestFinishedCallback));
	request->setTag("101");

    string _strUrl = CompleteUrl(URL_FRIEND_LIST);
    _strUrl.append(CCUserDefault::sharedUserDefault()->getStringForKey("userinfo"));

	request->setUrl(_strUrl.c_str());

	CCHttpClient *client = CCHttpClient::getInstance();
	client->send(request);

	request->release();
}

void MDCatalogueLayer::requestFinishedCallback(CCHttpClient* client, CCHttpResponse* response)
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

bool MDCatalogueLayer::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
//    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mTableView", CCMultiColumnTableView*, this->mTableView);
    return true;
}

SEL_MenuHandler MDCatalogueLayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
	return NULL;
}

SEL_CCControlHandler MDCatalogueLayer::onResolveCCBCCControlSelector(CCObject *pTarget, const char * pSelectorName) {
    
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "buttonClicked:", MDCatalogueLayer::buttonClicked);
	return NULL;
}

void MDCatalogueLayer::onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader)
{
    this->setFntTitle(101);

    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCMenu *menuTab = CCMenu::create();
    menuTab->setPosition(ccp(winSize.width * 0.5, 355));
    this->addChild(menuTab);

    CCMenuItemSprite* itemFairy = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("catalogue_tab_bg.png"),CCSprite::createWithSpriteFrameName("catalogue_tab_bg_selected.png"),NULL,this,menu_selector(MDCatalogueLayer::switchCallback));
    CCSize itemSize = itemFairy->getContentSize();
    
    CCSprite *_sFairy = CCSprite::createWithSpriteFrameName("catalogue_tab_dairy.png");
    itemFairy->addChild(_sFairy);
    _sFairy->setPosition(ccp(itemSize.width * 0.5,itemSize.height * 0.5));
    menuTab->addChild(itemFairy);
    itemFairy->setPosition(ccp(-itemSize.width, 0));
    itemFairy->selected();
    _preSelectedTab = itemFairy;

    CCMenuItemSprite* itemBuddha = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("catalogue_tab_bg.png"),CCSprite::createWithSpriteFrameName("catalogue_tab_bg_selected.png"),NULL,this,menu_selector(MDCatalogueLayer::switchCallback));
    CCSprite *_sBuhhda = CCSprite::createWithSpriteFrameName("catalogue_tab_fo.png");
    itemBuddha->addChild(_sBuhhda);
    _sBuhhda->setPosition(ccp(itemSize.width * 0.5,itemSize.height * 0.5));
    menuTab->addChild(itemBuddha);
    itemBuddha->setPosition(ccp(0, 0));

    CCMenuItemSprite* itemDemon = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("catalogue_tab_bg.png"),CCSprite::createWithSpriteFrameName("catalogue_tab_bg_selected.png"),NULL,this,menu_selector(MDCatalogueLayer::switchCallback));
    CCSprite *_sDemon = CCSprite::createWithSpriteFrameName("catalogue_tab_damon.png");
    itemDemon->addChild(_sDemon);
    _sDemon->setPosition(ccp(itemSize.width * 0.5,itemSize.height * 0.5));
    menuTab->addChild(itemDemon);
    itemDemon->setPosition(ccp(itemSize.width, 0));

    this->reloadDataSource();
}

void MDCatalogueLayer::switchCallback(CCObject* pSender){

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

void MDCatalogueLayer::reloadDataSource()
{
	mTableView = CCMultiColumnTableView::create(this,CCSizeMake(320,288),NULL);
	this->addChild(mTableView);
	mTableView->setPosition(ccp(0,50));
	mTableView->setDirection(kCCScrollViewDirectionVertical);
	mTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
	mTableView->setDataSource(this);
	mTableView->setDelegate(this);
	mTableView->setColCount(4);
	mTableView->reloadData();

}

void MDCatalogueLayer::tableCellHighlight(CCTableView* table, CCTableViewCell* cell)
{
    CCSprite *sSelected = (CCSprite*)cell->getChildByTag(121);
    sSelected->setVisible(true);
}

void MDCatalogueLayer::tableCellUnhighlight(CCTableView* table, CCTableViewCell* cell)
{
	CCSprite *sSelected = (CCSprite*)cell->getChildByTag(121);
	sSelected->setVisible(false);
}

void MDCatalogueLayer::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
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
	MainGameScene *mainScene = (MainGameScene *)this->getParent();
	mainScene->PushLayer((CCLayer *)this->GetLayer("MDCatalogueDetailLayer"));
}

unsigned int MDCatalogueLayer::numberOfCellsInTableView(CCTableView *table)
{
	return mHeroList->count();
}

CCSize MDCatalogueLayer::cellSizeForTable(CCTableView *table)
{
	return CCSizeMake(68, 72);
}

CCSize MDCatalogueLayer::tableCellSizeForIndex(CCTableView *table, unsigned int idx)
{
    return CCSizeMake(68, 72);
}

CCTableViewCell* MDCatalogueLayer::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
	CCTableViewCell *cell = table->dequeueCell();
    CCSize size = this->tableCellSizeForIndex(table, idx);
	if (!cell) {
		cell = new CCTableViewCell();
		cell->autorelease();
        
		CCSprite *sSelected = CCSprite::createWithSpriteFrameName("card_selected.png");
		sSelected->setVisible(false);
		sSelected->setTag(121);
		sSelected->setPosition(ccp(size.width * 0.5,size.height * 1.0 - 2));
		sSelected->setAnchorPoint(ccp(0.5, 1.0));
		cell->addChild(sSelected);
        
        CCSprite *sHead = CCSprite::createWithSpriteFrameName("head_rulaifo.png");
        sHead->setTag(122);
        sHead->setPosition(ccp(size.width * 0.5,size.height * 1.0 - 2));
		sHead->setAnchorPoint(ccp(0.5, 1));
		cell->addChild(sHead);

        CCSprite *sLine = CCSprite::createWithSpriteFrameName("catalogue_row_line.png");
        sLine->setPosition(ccp(0,0));
		sLine->setAnchorPoint(ccp(0, 0));
		cell->addChild(sLine);

		/*CCLabelTTF *lblName = CCLabelTTF::create("rulaifo", FONT_VERDANA, FONT_SIZE_BIG);
		lblName->setPosition(ccp(80,size.height - CELL_ITEMS_Y));
		lblName->setAnchorPoint(ccp(0, 0.5));
		lblName->setColor(ccc3(235, 234, 181));
		lblName->enableStroke(ccc3(16, 6, 9), 0.8);
		lblName->setTag(123);
		cell->addChild(lblName);

		}*/
	}
	else
	{
        CCSprite *sSelected = (CCSprite*)cell->getChildByTag(121);
//        sSelected->setPosition(ccp(13,size.height - 39));
        if (selectedindex == idx ) {
            sSelected->setVisible(true);
        } else {
            sSelected->setVisible(false);
        }
        
        CCSprite *sHead = (CCSprite*)cell->getChildByTag(122);
        
		//CCLabelTTF *lblName = (CCLabelTTF*)cell->getChildByTag(123);
		//lblName->setString("weiweiyao");
	}

	return cell;
}

void MDCatalogueLayer::buttonClicked(CCObject * sender , CCControlEvent controlEvent)
{
	MainGameScene *mainScene = (MainGameScene *)this->getParent();
	CCControlButton *button = (CCControlButton *)sender;
	switch (button->getTag()) {
	case 101:
        {
            mainScene->PopLayer();
            break;
        }
	}
}

MDCatalogueLayer::MDCatalogueLayer()
{
    mTableView = NULL;
    mHeroList = NULL;
    _preSelectedTab = NULL;
}

MDCatalogueLayer::~MDCatalogueLayer()
{
//    CC_SAFE_RELEASE(mTableView);
}

