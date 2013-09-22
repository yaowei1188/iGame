#include "MDCardAlchemyLayer.h"

#define TASK_COLUMN  3
#define TASK_ROW  3

CCScene* MDCardAlchemyLayer::scene()
{
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		MDCardAlchemyLayer *layer = MDCardAlchemyLayer::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool MDCardAlchemyLayer::init()
{
	selectedindex = 0;

	bool bRet = false;
	do 
	{

		CC_BREAK_IF(! CCLayer::init());

		bRet = true;
	} while (0);

	return bRet;
}

void MDCardAlchemyLayer::doSearch()
{
	this->ShowLoadingIndicator("");

	CCHttpRequest *request = new CCHttpRequest();
	request->setRequestType(CCHttpRequest::kHttpGet);
	request->setResponseCallback(this,httpresponse_selector(MDCardAlchemyLayer::requestFinishedCallback));
	request->setTag("101");

	string _strUrl = CompleteUrl(URL_FRIEND_LIST);
	_strUrl.append(CCUserDefault::sharedUserDefault()->getStringForKey("userinfo"));

	request->setUrl(_strUrl.c_str());

	CCHttpClient *client = CCHttpClient::getInstance();
	client->send(request);

	request->release();
}

void MDCardAlchemyLayer::requestFinishedCallback(CCHttpClient* client, CCHttpResponse* response)
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
//		mArrayList = dynamic_cast<CCArray *>(dictionary->objectForKey("friendList"));
//		if (mArrayList==NULL)
//		{
//			return;
//		}
//
//		selectedindex = -1;
//		mTableView->reloadData();
	} else if (requestTag == "102"){
		this->doSearch();
		CCMessageBox("delete friend successfully","Success");
	}
}

void MDCardAlchemyLayer::didSelectedItems(CCArray *pItems)
{
	if (pItems==NULL || pItems->count()==0)
	{
		return;
	}
	//CCLOG("items:%d",pItems->count());
	CCDictionary *dict = (CCDictionary *)pItems->objectAtIndex(0);
	std::string strCardHeadImg(((CCString *)dict->objectForKey("cardHeadImg"))->getCString());
	strCardHeadImg.append(".png");

	CCControlButton *btn = (CCControlButton *)this->getChildByTag(selectedButton);
	CCSpriteFrame *sHeadFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(strCardHeadImg.c_str());
	btn->setBackgroundSpriteFrameForState(sHeadFrame,CCControlStateNormal);
	btn->setBackgroundSpriteFrameForState(sHeadFrame,CCControlStateHighlighted);
}

bool MDCardAlchemyLayer::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_btnLeft", CCControlButton*, this->m_btnLeft);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_btnRight", CCControlButton*, this->m_btnRight);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_btnDone", CCControlButton*, this->m_btnDone);
	return true;
}

SEL_MenuHandler MDCardAlchemyLayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
	return NULL;
}

SEL_CCControlHandler MDCardAlchemyLayer::onResolveCCBCCControlSelector(CCObject *pTarget, const char * pSelectorName) {

	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "buttonClicked:", MDCardAlchemyLayer::buttonClicked);
	return NULL;
}

void MDCardAlchemyLayer::step(float dt)
{
    remainTime -= dt;
    string stime(secondsToString((int)(remainTime + 0.5)));
    lblTime->setString(stime.c_str());
    barFront->setPercent(remainTime/waitTime);
    if (remainTime<=0) {
        this->finishAlchemy();
    }
}

void MDCardAlchemyLayer::cancelAlchemy()
{
    this->unschedule(schedule_selector(MDCardAlchemyLayer::step));
    barFront->removeFromParentAndCleanup(true);
    barBg->removeFromParentAndCleanup(true);
    lblTimeTitle->removeFromParentAndCleanup(true);
    lblTime->removeFromParentAndCleanup(true);
    lblTime = NULL;
    
    m_btnLeft->setTitleForState(CCString::create(LITERAL_STRING_START), CCControlStateNormal);
//    m_btnLeft->setBackgroundSpriteFrameForState(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("card_btn_start.png"), CCControlStateNormal);
//    m_btnLeft->setBackgroundSpriteFrameForState(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("card_btn_start_highlight.png"), CCControlStateHighlighted);
    m_btnLeft->setTag(101);
    m_btnRight->setVisible(true);
    m_btnDone->setVisible(false);
}

void MDCardAlchemyLayer::startAlchemy()
{
    if (lblTime == NULL) {
        
        lblTimeTitle = CCLabelBMFont::create("Remain", "test.fnt");
        this->addChild(lblTimeTitle);
        lblTimeTitle->setPosition(ccp(50, 70));

        lblTime = CCLabelBMFont::create("", "test.fnt");
        this->addChild(lblTime);
        lblTime->setPosition(ccp(150, 70));

        barBg = MDProgressBar::create("lod_1_03.png","lod_1_04.png","lod_1_05.png",290,1.0);
        barBg->setPosition(ccp(10, 50));
        this->addChild(barBg);

        barFront = MDProgressBar::create("lod_2_03.png","lod_2_04.png","lod_2_05.png",290,1.0);
        barFront->setPosition(ccp(10, 50));
        this->addChild(barFront);

//        m_btnLeft->setBackgroundSpriteFrameForState(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("no_1.png"), CCControlStateNormal);
//        m_btnLeft->setBackgroundSpriteFrameForState(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("no_2.png"), CCControlStateHighlighted);
    }
    
    m_btnLeft->setTitleForState(CCString::create("取消"), CCControlStateNormal);
    m_btnLeft->setTag(109);
    
    m_btnRight->setVisible(false);
    m_btnDone->setVisible(true);
    
    waitTime = 60.0;
    remainTime = 60.0;
    lblTime->setString(secondsToString(waitTime).c_str());
    this->schedule(schedule_selector(MDCardAlchemyLayer::step), 1.0f);
}

void MDCardAlchemyLayer::absorb()
{
    
}

void MDCardAlchemyLayer::finishAlchemy()
{
    this->unschedule(schedule_selector(MDCardAlchemyLayer::step));
    barFront->removeFromParentAndCleanup(true);
    barBg->removeFromParentAndCleanup(true);
    lblTimeTitle->removeFromParentAndCleanup(true);
    lblTime->removeFromParentAndCleanup(true);
    lblTime = NULL;

    m_btnDone->setVisible(false);
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    m_spriteSuccess = CCSprite::createWithSpriteFrameName("card_title_success.png");
    this->addChild(m_spriteSuccess);
    m_spriteSuccess->setPosition(ccp(winSize.width * 0.5,130));

    CCLabelTTF *lblName = CCLabelTTF::create("yuan", "Arial", 14);
    this->addChild(lblName);
    lblName->setColor(ccc3(255, 255, 0));
    lblName->setPosition(ccp(winSize.width * 0.5,winSize.height * 0.5 + 40));

    CCLabelTTF *lblDesc = CCLabelTTF::create("xi", "Arial", 14);
    this->addChild(lblDesc);
    lblDesc->setColor(ccc3(255, 255, 255));
    lblDesc->setPosition(ccp(winSize.width * 0.5,winSize.height * 0.5 + 20));

    m_spriteResult = CCSprite::create("jingyandan.png");
    this->addChild(m_spriteResult);
    m_spriteResult->setPosition(ccp(winSize.width * 0.5,winSize.height * 0.5 - 30));

    m_btnLeft->setTitleForState(CCString::create("吸收"), CCControlStateNormal);
    m_btnLeft->setTag(111);
}

void MDCardAlchemyLayer::onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader)
{
    this->setFntTitle(101);
    this->setFntTitle(102);
    this->setFntTitle(110);
}

void MDCardAlchemyLayer::buttonClicked(CCObject * sender , CCControlEvent controlEvent)
{
	MainGameScene *mainScene = (MainGameScene *)this->getParent();
	CCControlButton *button = (CCControlButton *)sender;
	switch (button->getTag()) {
        case 101:
        {
            this->startAlchemy();
            break;
        }
        case 102:
        {
            mainScene->PopLayer();
            break;
        }
        case 103:
        case 104:
        case 105:
        case 106:
        case 107:
        case 108:
		{
			selectedButton = button->getTag();
			MDHeroListLayer *_heroListLayer = (MDHeroListLayer *)this->GetLayer("MDHeroListLayer");
			_heroListLayer->category = MD_HEROLIST_CHOOSE;
			_heroListLayer->setDelegate(this);
			_heroListLayer->reloadDataSource();
			mainScene->PushLayer(_heroListLayer);
			break;
		}
        case 109:
        {
            this->cancelAlchemy();
            break;
        }
        case 110:
        {
            this->finishAlchemy();
            break;
        }
        case 111:
        {
            this->absorb();
            break;
        }
	}
}

MDCardAlchemyLayer::MDCardAlchemyLayer()
{
	lblTime = NULL;
	mTaskList = NULL;
    m_btnLeft = NULL;
    m_btnRight = NULL;
    m_btnDone = NULL;
}

MDCardAlchemyLayer::~MDCardAlchemyLayer()
{
    CC_SAFE_RELEASE(m_btnLeft);
    CC_SAFE_RELEASE(m_btnRight);
    CC_SAFE_RELEASE(m_btnDone);
}

