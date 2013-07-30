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
	//CCLOG("items:%d",pItems->count());
	CCControlButton *btn = (CCControlButton *)this->getChildByTag(selectedButton);
	CCSpriteFrame *sHeadFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("head_rulaifo.png");
	btn->setBackgroundSpriteFrameForState(sHeadFrame,CCControlStateNormal);
	btn->setBackgroundSpriteFrameForState(sHeadFrame,CCControlStateHighlighted);
}

bool MDCardAlchemyLayer::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
//	  CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_sCard", CCSprite*, this->m_sCard);
//    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_lblTitle", CCLabelTTF*, this->m_lblTitle);
//    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_lblLife", CCLabelTTF*, this->m_lblLife);
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
    remainTime -=dt;
    string stime(secondsToString((int)(remainTime + 0.5)));
    lblTime->setString(stime.c_str());
    barFront->setPercent(remainTime/waitTime);
    if (remainTime<=0) {
        this->unschedule(schedule_selector(MDCardAlchemyLayer::step));
    }
}

void MDCardAlchemyLayer::startAlchemy()
{
    if (lblTime==NULL) {
        CCLabelBMFont* lblTimeTile = CCLabelBMFont::create("Remain", "test.fnt");
        this->addChild(lblTimeTile);
        lblTimeTile->setPosition(ccp(50, 70));

        lblTime = CCLabelBMFont::create("", "test.fnt");
        this->addChild(lblTime);
        lblTime->setPosition(ccp(150, 70));

        barBg = MDProgressBar::create("lod_1_03.png","lod_1_04.png","lod_1_05.png",290,1.0);
        barBg->setPosition(ccp(10, 50));
        this->addChild(barBg);

        barFront = MDProgressBar::create("lod_2_03.png","lod_2_04.png","lod_2_05.png",290,1.0);
        barFront->setPosition(ccp(10, 50));
        this->addChild(barFront);
    }
    
    waitTime = 60.0;
    remainTime = 60.0;
    lblTime->setString(secondsToString(waitTime).c_str());
    this->schedule(schedule_selector(MDCardAlchemyLayer::step), 1.0f);
}

void MDCardAlchemyLayer::onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader)
{
	//doSearchFriend();



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
			_heroListLayer->category=1;
			_heroListLayer->setDelegate(this);
			_heroListLayer->reloadDataSource();
			mainScene->PushLayer(_heroListLayer);
			break;
		}
	}
}

MDCardAlchemyLayer::MDCardAlchemyLayer()
{
	lblTime = NULL;
	//    mMainSceneTemp = NULL;
	mTaskList = NULL;
//    m_lblTitle = NULL;
//    m_sCard = NULL;
//    m_lblLife = NULL;
}

MDCardAlchemyLayer::~MDCardAlchemyLayer()
{
//	m_sCard->release();
//	m_lblTitle->release();
//	mTaskList->release();
//    m_lblLife->release();
}

