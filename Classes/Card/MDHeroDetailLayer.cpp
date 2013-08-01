#include "MDHeroDetailLayer.h"

#define TASK_COLUMN  3
#define TASK_ROW  3

CCScene* MDHeroDetailLayer::scene()
{
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		MDHeroDetailLayer *layer = MDHeroDetailLayer::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool MDHeroDetailLayer::init()
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

void MDHeroDetailLayer::doPromotion()
{
    MainGameScene *mainScene = (MainGameScene *)this->getParent();
    mainScene->PushLayer((CCLayer *)this->GetLayer("MDHeroPrePromoLayer"));
    
//	this->ShowLoadingIndicator("");
//
//	CCHttpRequest *request = new CCHttpRequest();
//	request->setRequestType(CCHttpRequest::kHttpGet);
//	request->setResponseCallback(this,httpresponse_selector(MDHeroDetailLayer::requestFinishedCallback));
//	request->setTag("101");
//
//	string _strUrl = CompleteUrl(URL_FRIEND_LIST);
//	_strUrl.append(CCUserDefault::sharedUserDefault()->getStringForKey("userinfo"));
//
//	request->setUrl(_strUrl.c_str());
//
//	CCHttpClient *client = CCHttpClient::getInstance();
//	client->send(request);
//
//	request->release();
}

void MDHeroDetailLayer::requestFinishedCallback(CCHttpClient* client, CCHttpResponse* response)
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

	}
}

bool MDHeroDetailLayer::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_sCard", CCSprite*, this->m_sCard);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_lblCardName", CCLabelTTF*, this->m_lblCardName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_lblLevel", CCLabelTTF*, this->m_lblLevel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_lblHeroName", CCLabelTTF*, this->m_lblHeroName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_lblHp", CCLabelTTF*, this->m_lblHp);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_lblDefence", CCLabelTTF*, this->m_lblDefence);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_lblAttack", CCLabelTTF*, this->m_lblAttack);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_lblAvoid", CCLabelTTF*, this->m_lblAvoid);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_lblDesc", CCLabelTTF*, this->m_lblDesc);
	return true;
}

SEL_MenuHandler MDHeroDetailLayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
	return NULL;
}

SEL_CCControlHandler MDHeroDetailLayer::onResolveCCBCCControlSelector(CCObject *pTarget, const char * pSelectorName) {

	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "buttonClicked:", MDHeroDetailLayer::buttonClicked);
	return NULL;
}

void MDHeroDetailLayer::onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader)
{
    this->setFntTitle(101);
    this->setFntTitle(102);
    
    CCSize bgSize = m_sCard->getContentSize();

    std::string strGroup = determineGroup(CCString::create("1"));
    CCSprite *sCardGroup = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(strGroup.c_str()));
    sCardGroup->setAnchorPoint(ccp(1,1));
    sCardGroup->setPosition(ccp(bgSize.width - 5,bgSize.height - 10));
    m_sCard->addChild(sCardGroup);

    CCSprite *sPeople = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("character_rulaifo.png"));
    sPeople->setPosition(ccp(bgSize.width * 0.5,bgSize.height * 0.5));
    m_sCard->addChild(sPeople);

    m_lblDesc->setColor(ccc3(0, 255, 0));
}

void MDHeroDetailLayer::buttonClicked(CCObject * sender , CCControlEvent controlEvent)
{
	CCControlButton *button = (CCControlButton *)sender;
	switch (button->getTag()) {
	case 101:
        {
            doPromotion();
            break;
        }
	case 102:
        {
            MainGameScene *mainScene = (MainGameScene *)this->getParent();
            mainScene->PopLayer();
            break;
        }
	}
}

MDHeroDetailLayer::MDHeroDetailLayer()
{
	mTaskList = NULL;
    m_sCard = NULL;
    m_lblLevel = NULL;
    m_lblCardName = NULL;
    m_lblHeroName = NULL;
    
    m_lblHp = NULL;
    m_lblDefence = NULL;
    m_lblAttack = NULL;
    m_lblAvoid = NULL;
    m_lblDesc = NULL;
}

MDHeroDetailLayer::~MDHeroDetailLayer()
{
	CC_SAFE_RELEASE(m_sCard);
    CC_SAFE_RELEASE(m_lblLevel);
    CC_SAFE_RELEASE(m_lblCardName);
    CC_SAFE_RELEASE(m_lblHeroName);
    CC_SAFE_RELEASE(m_lblHp);
    CC_SAFE_RELEASE(m_lblDefence);
    CC_SAFE_RELEASE(m_lblAttack);
    CC_SAFE_RELEASE(m_lblAvoid);
    CC_SAFE_RELEASE(m_lblDesc);
}

