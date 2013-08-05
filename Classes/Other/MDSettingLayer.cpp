#include "MDSettingLayer.h"


CCScene* MDSettingLayer::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        MDSettingLayer *layer = MDSettingLayer::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MDSettingLayer::init()
{
    selectedindex = -1;
    
    bool bRet = false;
    do 
    {
        CC_BREAK_IF(! CCLayer::init());

		btnTouched = false;
        
        mHeroList = CCArray::createWithCapacity(7);
        mHeroList->retain();

		CCDictionary *dict0 = CCDictionary::create();
		dict0->setObject(CCString::create(""),"RowText");
		dict0->setObject(CCString::create("0"),"Row");
		dict0->setObject(CCString::create("1"),"Category");
		dict0->setObject(CCString::create("背景音乐"),"CategoryText");
		mHeroList->addObject(dict0);

		CCDictionary *dict1 = CCDictionary::create();
		dict1->setObject(CCString::create("1"),"Row");
		dict1->setObject(CCString::create("QQ账号"),"RowText");
		dict1->setObject(CCString::create("1"),"Category");
		dict1->setObject(CCString::create("账号绑定"),"CategoryText");
		mHeroList->addObject(dict1);

		CCDictionary *dict2 = CCDictionary::create();
		dict2->setObject(CCString::create("2"),"Row");
		dict2->setObject(CCString::create("新浪账号"),"RowText");
		dict2->setObject(CCString::create("1"),"Category");
		mHeroList->addObject(dict2);

		CCDictionary *dict3 = CCDictionary::create();
		dict3->setObject(CCString::create("3"),"Row");
		dict3->setObject(CCString::create("人人账号"),"RowText");
		dict3->setObject(CCString::create("1"),"Category");
		mHeroList->addObject(dict3);

		CCDictionary *dict4 = CCDictionary::create();
		dict4->setObject(CCString::create("4"),"Row");
		dict4->setObject(CCString::create("修改密码"),"RowText");
		dict4->setObject(CCString::create("2"),"Category");
		dict4->setObject(CCString::create("账号设置"),"CategoryText");
		mHeroList->addObject(dict4);

		CCDictionary *dict5 = CCDictionary::create();
		dict5->setObject(CCString::create("5"),"Row");
		dict5->setObject(CCString::create("意义反馈"),"RowText");
		dict5->setObject(CCString::create("2"),"Category");
		mHeroList->addObject(dict5);

		CCDictionary *dict6 = CCDictionary::create();
		dict6->setObject(CCString::create("6"),"Row");
		dict6->setObject(CCString::create("关于我们"),"RowText");
		dict6->setObject(CCString::create("2"),"Category");
		mHeroList->addObject(dict6);

		vUserData = new int[mHeroList->count()]();
		memset(vUserData, sizeof(int) * mHeroList->count(), 0);

        bRet = true;
    } while (0);

    return bRet;
}

void MDSettingLayer::LoadHeros()
{
	this->ShowLoadingIndicator("");

	CCHttpRequest *request = new CCHttpRequest();
	request->setRequestType(CCHttpRequest::kHttpGet);
	request->setResponseCallback(this,httpresponse_selector(MDSettingLayer::requestFinishedCallback));
	request->setTag("101");

    string _strUrl = CompleteUrl(URL_FRIEND_LIST);
    _strUrl.append(CCUserDefault::sharedUserDefault()->getStringForKey("userinfo"));

	request->setUrl(_strUrl.c_str());

	CCHttpClient *client = CCHttpClient::getInstance();
	client->send(request);

	request->release();
}

void MDSettingLayer::requestFinishedCallback(CCHttpClient* client, CCHttpResponse* response)
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

bool MDSettingLayer::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    //CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mTableView", CCTableView*, this->mTableView);
    return true;
}

SEL_MenuHandler MDSettingLayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
	return NULL;
}

SEL_CCControlHandler MDSettingLayer::onResolveCCBCCControlSelector(CCObject *pTarget, const char * pSelectorName) {
    
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "buttonClicked:", MDSettingLayer::buttonClicked);
	return NULL;
}

void MDSettingLayer::onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader)
{
	reloadDataSource();
}

void MDSettingLayer::reloadDataSource()
{
	mTableView = CCTableView::create(this,CCSizeMake(320,288),NULL);
	this->addChild(mTableView);
	mTableView->setPosition(ccp(0,90));
	mTableView->setDirection(kCCScrollViewDirectionVertical);
	mTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
	mTableView->setDataSource(this);
	mTableView->setViewSize(CCSizeMake(312, 314));
	mTableView->setDelegate(this);
	mTableView->reloadData();
}

void MDSettingLayer::tableCellHighlight(CCTableView* table, CCTableViewCell* cell)
{
    //CCSprite *sSelected = (CCSprite*)cell->getChildByTag(121);
    //sSelected->setVisible(true);
}

void MDSettingLayer::tableCellUnhighlight(CCTableView* table, CCTableViewCell* cell)
{
    //CCSprite *sSelected = (CCSprite*)cell->getChildByTag(121);
    //sSelected->setVisible(false);
}

void MDSettingLayer::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
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

unsigned int MDSettingLayer::numberOfCellsInTableView(CCTableView *table)
{
	return mHeroList->count();
}

CCSize MDSettingLayer::cellSizeForTable(CCTableView *table)
{
	return CCSizeMake(312, 80);
}

CCSize MDSettingLayer::tableCellSizeForIndex(CCTableView *table, unsigned int idx)
{
    return CCSizeMake(312, 80);
}

CCTableViewCell* MDSettingLayer::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
	CCDictionary *dict = (CCDictionary *)mHeroList->objectAtIndex(idx);
	bool selected = (idx==selectedindex);
	CCTableViewCell *cell = table->dequeueCell();
	CCString *strCategory = (CCString *)dict->objectForKey("Category");
	//CCString *strCategoryText = (CCString *)dict->objectForKey("CategoryText");
	CCString *strRowText = (CCString *)dict->objectForKey("RowText");
    CCSize size = this->tableCellSizeForIndex(table, idx);
	if (!cell) {
		cell = new CCTableViewCell();
		cell->autorelease();
        
  //      CCSprite *sSelected = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("friends_cellhighlight.png"));
  //      sSelected->setVisible(false);
  //      sSelected->setTag(121);
		//sSelected->setPosition(ccp(13,size.height - 39));
		//sSelected->setAnchorPoint(CCPointZero);
		//cell->addChild(sSelected);
  //      
  //      CCSprite *sHead = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("head_rulaifo.png"));
  //      sHead->setTag(122);
  //      sHead->setPosition(ccp(10,size.height * 0.5));
		//sHead->setAnchorPoint(ccp(0, 0.5));
		//cell->addChild(sHead);

		CCLabelTTF *lblName = CCLabelTTF::create(strRowText->getCString(), FONT_VERDANA, FONT_SIZE_BIG);
		lblName->setPosition(ccp(80,size.height - CELL_ITEMS_Y));
		lblName->setAnchorPoint(ccp(0, 0.5));
		lblName->setColor(ccc3(235, 234, 181));
		lblName->enableStroke(ccc3(16, 6, 9), 0.8);
		lblName->setTag(123);
		cell->addChild(lblName);

		//CCLabelTTF *lblLevel = CCLabelTTF::create("LV. 3", FONT_VERDANA, FONT_SIZE_MEDIUM);
		//lblLevel->setPosition(ccp(80,size.height - 2 * CELL_ITEMS_Y));
		//lblLevel->setAnchorPoint(ccp(0, 0.5));
  //      lblLevel->setColor(ccc3(235, 234, 181));
  //      lblLevel->enableStroke(ccc3(16, 6, 9), 0.8);
		//lblLevel->setTag(124);
		//cell->addChild(lblLevel);

		CCScale9Sprite *sline = CCScale9Sprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("setting_cell_line.png"));
		sline->setPreferredSize(CCSizeMake(290, 1));
		sline->setPosition(ccp(15,size.height));
		sline->setAnchorPoint(CCPointZero);
		cell->addChild(sline);
        
		//CCPoint point = ccp(218 ,size.height * 0.5);

  //      CCSprite *sStarGrade = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("card_l_star5.png"));
  //      sStarGrade->setPosition(point);
		//lblLevel->setTag(125);
  //      sStarGrade->setAnchorPoint(ccp(0, 0.5));
  //      cell->addChild(sStarGrade);
	}
	else
	{
  //      CCSprite *sSelected = (CCSprite*)cell->getChildByTag(121);
  //      sSelected->setPosition(ccp(13,size.height - 39));
  //      if (selectedindex == idx ) {
  //          sSelected->setVisible(true);
  //      } else {
  //          sSelected->setVisible(false);
  //      }
  //      
  //      CCSprite *sHead = (CCSprite*)cell->getChildByTag(122);
  //      
		CCLabelTTF *lblName = (CCLabelTTF*)cell->getChildByTag(123);
		lblName->setString(strRowText->getCString());
  //      
  //      CCLabelTTF *lblLevel = (CCLabelTTF*)cell->getChildByTag(124);
		//lblLevel->setString(string->getCString());
        
//        CCScale9Sprite *background = (CCScale9Sprite *)cell->getChildByTag(121);
//        background->setContentSize(size);
	}

	return cell;
}

//    按下按钮事件回调
void MDSettingLayer::toolBarTouchDownAction(CCObject * sender , CCControlEvent pCCControlEvent)
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

void MDSettingLayer::buttonClicked(CCObject * sender , CCControlEvent controlEvent)
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

MDSettingLayer::MDSettingLayer()
{
    //mTableView = NULL;
    mHeroList = NULL;
}

MDSettingLayer::~MDSettingLayer()
{
    //CC_SAFE_RELEASE(mTableView);
}

