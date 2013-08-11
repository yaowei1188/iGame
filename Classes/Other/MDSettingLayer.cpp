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

		m_blnMusic = CCUserDefault::sharedUserDefault()->getBoolForKey("IsSound",true);
		m_blnEffect = CCUserDefault::sharedUserDefault()->getBoolForKey("IsEffect",true);
        
        mSettingList = CCArray::createWithCapacity(7);
        mSettingList->retain();

		CCDictionary *dict0 = CCDictionary::create();
		dict0->setObject(CCString::create(""),"RowText");
		dict0->setObject(CCString::create("0"),"Row");
		dict0->setObject(CCString::create("0"),"Category");
		dict0->setObject(CCString::create("背景音乐"),"CategoryText");
		mSettingList->addObject(dict0);

		CCDictionary *dict1 = CCDictionary::create();
		dict1->setObject(CCString::create("1"),"Row");
		dict1->setObject(CCString::create("QQ账号"),"RowText");
		dict1->setObject(CCString::create("1"),"Category");
		dict1->setObject(CCString::create("账号绑定"),"CategoryText");
		mSettingList->addObject(dict1);

		CCDictionary *dict2 = CCDictionary::create();
		dict2->setObject(CCString::create("2"),"Row");
		dict2->setObject(CCString::create("新浪账号"),"RowText");
		dict2->setObject(CCString::create("1"),"Category");
//        dict2->setObject(CCString::create(""),"CategoryText");
		mSettingList->addObject(dict2);

		CCDictionary *dict3 = CCDictionary::create();
		dict3->setObject(CCString::create("3"),"Row");
		dict3->setObject(CCString::create("人人账号"),"RowText");
		dict3->setObject(CCString::create("1"),"Category");
//        dict3->setObject(CCString::create(""),"CategoryText");
		mSettingList->addObject(dict3);

		CCDictionary *dict4 = CCDictionary::create();
		dict4->setObject(CCString::create("4"),"Row");
		dict4->setObject(CCString::create("修改密码"),"RowText");
		dict4->setObject(CCString::create("2"),"Category");
		dict4->setObject(CCString::create("账号设置"),"CategoryText");
		mSettingList->addObject(dict4);

		CCDictionary *dict5 = CCDictionary::create();
		dict5->setObject(CCString::create("5"),"Row");
		dict5->setObject(CCString::create("意义反馈"),"RowText");
		dict5->setObject(CCString::create("2"),"Category");
//        dict5->setObject(CCString::create(""),"CategoryText");
		mSettingList->addObject(dict5);

		CCDictionary *dict6 = CCDictionary::create();
		dict6->setObject(CCString::create("6"),"Row");
		dict6->setObject(CCString::create("关于我们"),"RowText");
		dict6->setObject(CCString::create("2"),"Category");
//        dict6->setObject(CCString::create(""),"CategoryText");
		mSettingList->addObject(dict6);

		//vUserData = new int[mSettingList->count()]();
		//memset(vUserData, sizeof(int) * mSettingList->count(), 0);

        bRet = true;
    } while (0);

    return bRet;
}

//void MDSettingLayer::LoadHeros()
//{
//	this->ShowLoadingIndicator("");
//
//	CCHttpRequest *request = new CCHttpRequest();
//	request->setRequestType(CCHttpRequest::kHttpGet);
//	request->setResponseCallback(this,httpresponse_selector(MDSettingLayer::requestFinishedCallback));
//	request->setTag("101");
//
//    string _strUrl = CompleteUrl(URL_FRIEND_LIST);
//    _strUrl.append(CCUserDefault::sharedUserDefault()->getStringForKey("userinfo"));
//
//	request->setUrl(_strUrl.c_str());
//
//	CCHttpClient *client = CCHttpClient::getInstance();
//	client->send(request);
//
//	request->release();
//}

//void MDSettingLayer::requestFinishedCallback(CCHttpClient* client, CCHttpResponse* response)
//{
//	if (!this->ValidateResponseData(client,response))
//	{
//		return;
//	}
//
//	std::vector<char> *buffer = response->getResponseData();
//	std::string content(buffer->begin(),buffer->end());
//
//    CCDictionary * dictionary = CCJSONConverter::sharedConverter()->dictionaryFrom(content.c_str());
//	int code = ((CCNumber *)dictionary->objectForKey("code"))->getIntValue();
//    if (code != 200) {
//        CCMessageBox("invoke web api failed!","ERROR");
//        return;
//    }
//
//	std::string requestTag(response->getHttpRequest()->getTag());
//
//	if (requestTag == "101") {
//		mSettingList = dynamic_cast<CCArray *>(dictionary->objectForKey("friendList"));
//		if (mSettingList== NULL)
//		{
//			mSettingList = CCArray::create();
//		}
//        mSettingList->retain();
//		selectedindex = -1;
//		mTableView->reloadData();
//	} else if (requestTag == "103"){
//		this->LoadHeros();
//		CCMessageBox("delete friend successfully","Success");
//	}
//}

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
    this->setFntTitle(101);
	reloadDataSource();
}

void MDSettingLayer::reloadDataSource()
{
	mTableView = CCTableView::create(this,CCSizeMake(320,288),NULL);
	this->addChild(mTableView);
	mTableView->setPosition(ccp(0,60));
	mTableView->setDirection(kCCScrollViewDirectionVertical);
	mTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
	mTableView->setDataSource(this);
	mTableView->setViewSize(CCSizeMake(320, 314));
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


	//CCDictionary *dict = (CCDictionary *)mSettingList->objectAtIndex(cell->getIdx());
	//if (dict->objectForKey(""))
	//{
	//}
	selectedindex = cell->getIdx();
	switch (selectedindex)
	{
	case 1:
		//qq
		break;
	case 2:
		//weibo
		break;
	case 3:
		//renren
		break;
	case 4:
		//password
		break;
	case 5:
		//feedback
		break;
	case 6:
		//MainGameScene *mainScene = (MainGameScene *)this->getParent();
		//mainScene->PushLayer((CCLayer *)this->GetLayer("MDHeroDetailLayer"));
		//about
		break;
	}
}

unsigned int MDSettingLayer::numberOfCellsInTableView(CCTableView *table)
{
	return mSettingList->count();
}

CCSize MDSettingLayer::cellSizeForTable(CCTableView *table)
{
	return CCSizeMake(312, 80);
}

CCSize MDSettingLayer::tableCellSizeForIndex(CCTableView *table, unsigned int idx)
{
    return CCSizeMake(312, 80);
}

void MDSettingLayer::radioButtonCallback(CCObject* pSender)
{
	CCMenuItemToggle* pSwitch = (CCMenuItemToggle*)pSender;
	CCMenu *menu = (CCMenu *)pSwitch->getParent();

	if (menu->getTag()==120)
	{
		if (pSwitch->getSelectedIndex()==0) {
			 CCUserDefault::sharedUserDefault()->setBoolForKey("IsSound",false);
			 MDSoundManager::stopBackgroundMusic();
		} else {
			CCUserDefault::sharedUserDefault()->setBoolForKey("IsSound",true);
			MDSoundManager::playBackgroundMusic();
		}
	} else if (menu->getTag()==121) {
		if (pSwitch->getSelectedIndex()==0) {
			CCUserDefault::sharedUserDefault()->setBoolForKey("IsEffect",false);
		} else {
			CCUserDefault::sharedUserDefault()->setBoolForKey("IsEffect",true);
		}
	}
}

CCMenu* MDSettingLayer::generateRadioButton(const char *menuName)
{
	CCSprite *spriteOff = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("setting_checkbox_off.png"));
	CCSprite *spriteOn = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("setting_checkbox_on.png"));

	CCMenu* m_auto_op_menu = CCMenu::create();
	CCMenuItemSprite* menuOff = CCMenuItemSprite::create(spriteOff, NULL);
	CCMenuItemSprite* menuOn = CCMenuItemSprite::create(spriteOn, NULL);
	CCMenuItemToggle* item = CCMenuItemToggle::createWithTarget(this, menu_selector(MDSettingLayer::radioButtonCallback),menuOff,menuOn,NULL);
    CCLabelTTF *lblMenuName = CCLabelTTF::create(menuName, FONT_VERDANA, FONT_SIZE_BIG);
    lblMenuName->setPosition(ccp(-24,item->getContentSize().height * 0.5));
    lblMenuName->setColor(ccc3(254, 203, 27));
    item->addChild(lblMenuName);

	m_auto_op_menu->addChild(item);

	return m_auto_op_menu;
}

CCTableViewCell* MDSettingLayer::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
	CCDictionary *dict = (CCDictionary *)mSettingList->objectAtIndex(idx);
	bool selected = (idx==selectedindex);
	CCTableViewCell *cell = table->dequeueCell();
	CCString *strCategory = (CCString *)dict->objectForKey("Category");
	CCString *strCategoryText = (CCString *)dict->objectForKey("CategoryText");
	CCString *strRowText = (CCString *)dict->objectForKey("RowText");
    CCSize size = this->tableCellSizeForIndex(table, idx);
	if (!cell) {
		cell = new CCTableViewCell();
		cell->autorelease();

        CCLabelTTF *lblName = NULL;

        if (strCategory->compare("0")==0) {
            CCMenu *menuMusic = generateRadioButton("音乐");
            menuMusic->setTag(120);
            menuMusic->setPosition(120,size.height * 0.5 - 5);
            cell->addChild(menuMusic);
			CCMenuItemToggle *itemMusic =  (CCMenuItemToggle *)menuMusic->getChildren()->objectAtIndex(0);
			if (m_blnMusic)
			{
				itemMusic->setSelectedIndex(1);
			} else {
				itemMusic->setSelectedIndex(0);
			}

            CCMenu *menuEffect = generateRadioButton("音效");
            menuEffect->setTag(121);
            menuEffect->setPosition(220,size.height * 0.5 - 5);
            cell->addChild(menuEffect);
			CCMenuItemToggle *itemEffect =  (CCMenuItemToggle *)menuEffect->getChildren()->objectAtIndex(0);
			if (m_blnEffect)
			{
				itemEffect->setSelectedIndex(1);
			} else {
				itemEffect->setSelectedIndex(0);
			}
        } else {
            CCLabelTTF *lblName = CCLabelTTF::create(strRowText->getCString(), FONT_VERDANA, FONT_SIZE_MEDIUM);
            lblName->setColor(ccc3(254, 203, 27));
            //		lblName->enableStroke(ccc3(16, 6, 9), 0.8);
            lblName->setTag(123);
            cell->addChild(lblName);
            lblName->setPosition(ccp(size.width * 0.5,size.height * 0.5 -10));
        }
        
        if (strCategoryText!=NULL && strCategoryText->length()>0) {
            CCScale9Sprite *sSectionLine = CCScale9Sprite::createWithSpriteFrameName("setting_cell_seperator.png");
            sSectionLine->setPreferredSize(CCSizeMake(320, 18));
            sSectionLine->setPosition(ccp(0,size.height));
            sSectionLine->setAnchorPoint(ccp(0,1));
            sSectionLine->setTag(124);
            cell->addChild(sSectionLine);

            CCLabelTTF *lblCategoryText = CCLabelTTF::create(strCategoryText->getCString(), FONT_VERDANA, FONT_SIZE_BIG);
            lblCategoryText->setPosition(ccp(size.width * 0.5,size.height));
            lblCategoryText->setAnchorPoint(ccp(0.5, 1));
            lblCategoryText->setColor(ccc3(255, 144, 27));
//            lblCategoryText->enableStroke(ccc3(16, 6, 9), 0.8);
            lblCategoryText->setTag(125);
            cell->addChild(lblCategoryText);

        } else {
            CCScale9Sprite *sline = CCScale9Sprite::createWithSpriteFrameName("setting_cell_line.png");
            sline->setPreferredSize(CCSizeMake(320, 1));
            sline->setPosition(ccp(0,size.height));
            sline->setAnchorPoint(ccp(0, 1));
            sline->setTag(122);
            cell->addChild(sline);
        }
	}
	else
	{    
		CCLabelTTF *lblName = (CCLabelTTF*)cell->getChildByTag(123);
		lblName->setString(strRowText->getCString());

        CCScale9Sprite *sSectionLine = (CCScale9Sprite *)cell->getChildByTag(124);
        CCLabelTTF *lblCategoryText = (CCLabelTTF*)cell->getChildByTag(125);;
        CCScale9Sprite *sline =  (CCScale9Sprite *)cell->getChildByTag(122);

        CCMenu *menuMusic = (CCMenu *)cell->getChildByTag(120);
        CCMenu *menuEffect = (CCMenu *)cell->getChildByTag(121);

        if (strCategory->compare("0")==0) {
            if (menuMusic == NULL) {
                menuMusic = generateRadioButton("音乐");
                menuMusic->setTag(120);
                menuMusic->setPosition(120,size.height * 0.5 - 5);
                cell->addChild(menuMusic);
				CCMenuItemToggle *itemMusic =  (CCMenuItemToggle *)menuMusic->getChildren()->objectAtIndex(0);
				if (m_blnMusic)
				{
					itemMusic->setSelectedIndex(1);
				} else {
					itemMusic->setSelectedIndex(0);
				}
            }
            
            if (menuEffect == NULL) {
                menuEffect = generateRadioButton("音效");
                menuEffect->setTag(121);
                menuEffect->setPosition(220,size.height * 0.5 - 5);
                cell->addChild(menuEffect);

				CCMenuItemToggle *itemEffect =  (CCMenuItemToggle *)menuEffect->getChildren()->objectAtIndex(0);
				if (m_blnEffect)
				{
					itemEffect->setSelectedIndex(1);
				} else {
					itemEffect->setSelectedIndex(0);
				}
            }
        } else {
            if (menuMusic != NULL) {
                menuMusic->removeFromParentAndCleanup(true);
            }
            if (menuEffect != NULL) {
                menuEffect->removeFromParentAndCleanup(true);
            }
        }

        if (strCategoryText!=NULL && strCategoryText->length()>0) {
            if (sSectionLine==NULL) {
                sSectionLine = CCScale9Sprite::createWithSpriteFrameName("setting_cell_seperator.png");
                sSectionLine->setPreferredSize(CCSizeMake(320, 18));
                sSectionLine->setPosition(ccp(0,size.height));
                sSectionLine->setAnchorPoint(ccp(0,1));
                sSectionLine->setTag(124);
                cell->addChild(sSectionLine);
            }

            if (lblCategoryText==NULL) {
                lblCategoryText = CCLabelTTF::create(strCategoryText->getCString(), FONT_VERDANA, FONT_SIZE_BIG);
                lblCategoryText->setPosition(ccp(size.width * 0.5,size.height));
                lblCategoryText->setAnchorPoint(ccp(0.5, 1));
                lblCategoryText->setColor(ccc3(255, 144, 27));
//                lblCategoryText->enableStroke(ccc3(16, 6, 9), 0.8);
                lblCategoryText->setTag(125);
                cell->addChild(lblCategoryText);
            } else {
                lblCategoryText->setString(strCategoryText->getCString());
            }

            if (sline!=NULL) {
                sline->removeFromParentAndCleanup(true);
            }

            lblName->setPosition(ccp(size.width * 0.5,size.height * 0.5 - 10));

        } else {
            if (sline==NULL) {
                sline = CCScale9Sprite::createWithSpriteFrameName("setting_cell_line.png");
                sline->setPreferredSize(CCSizeMake(320, 1));
                sline->setPosition(ccp(0,size.height));
                sline->setAnchorPoint(ccp(0, 1));
                sline->setTag(122);
                cell->addChild(sline);
            }

            if (sSectionLine!=NULL) {
                sSectionLine->removeFromParentAndCleanup(true);
            }

            if (lblCategoryText!=NULL) {
                lblCategoryText->removeFromParentAndCleanup(true);
            }

            lblName->setPosition(ccp(size.width * 0.5,size.height * 0.5));

        }
	}

	return cell;
}

//    按下按钮事件回调
//void MDSettingLayer::toolBarTouchDownAction(CCObject * sender , CCControlEvent pCCControlEvent)
//{
//	CCControlButton *button = (CCControlButton *)sender;
//	if (pCCControlEvent==CCControlEventTouchDown)
//	{
//		btnTouched = true;
//	}
//	else if (pCCControlEvent==CCControlEventTouchUpInside)
//	{
//		switch (button->getTag()) 
//		{
//		case 128:
//			{
//				btnTouched = false;
//				MainGameScene *mainScene = (MainGameScene *)this->getParent();
//				mainScene->PushLayer((CCLayer *)this->GetLayer("NewMailScene"));
//				break;
//			}
//		}
//	}
//}

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
    mSettingList = NULL;
}

MDSettingLayer::~MDSettingLayer()
{
    //CC_SAFE_RELEASE(mTableView);
}

