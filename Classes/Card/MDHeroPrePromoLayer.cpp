#include "MDHeroPrePromoLayer.h"

#define TASK_COLUMN  3
#define TASK_ROW  3

CCScene* MDHeroPrePromoLayer::scene()
{
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		MDHeroPrePromoLayer *layer = MDHeroPrePromoLayer::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool MDHeroPrePromoLayer::init()
{
	selectedindex = 0;

	bool bRet = false;
	do 
	{
		//////////////////////////////////////////////////////////////////////////
		// super init first
		//////////////////////////////////////////////////////////////////////////

		CC_BREAK_IF(! CCLayer::init());

		//mArrayList =  CCArray::create();
//		mTaskList = CCArray::create(CCString::create("Li1"),CCString::create("’≈»˝"),CCString::create("Li3"),CCString::create("¿ÓÀƒ"),CCString::create("Li1653"),CCString::create("Li1qwe"),CCString::create("Li1"),CCString::create("Li1"),CCString::create("Li409"),CCString::create("Li134"),CCString::create("Li51"),CCString::create("Li18974523"),CCString::create("Li1"),CCString::create("Li1"),CCString::create("Li1"),CCString::create("Li1"),CCString::create("Li1"),CCString::create("Li124"),CCString::create("Li1998"),CCString::create("Li3561"),NULL);
//		mTaskList->retain();

		bRet = true;
	} while (0);

	return bRet;
}

void MDHeroPrePromoLayer::showTaskInfo()
{
	this->ShowLoadingIndicator("");

	CCHttpRequest *request = new CCHttpRequest();
	request->setRequestType(CCHttpRequest::kHttpGet);
	request->setResponseCallback(this,httpresponse_selector(MDHeroPrePromoLayer::requestFinishedCallback));
	request->setTag("101");

	string _strUrl = CompleteUrl(URL_FRIEND_LIST);
	_strUrl.append(CCUserDefault::sharedUserDefault()->getStringForKey("userinfo"));

	request->setUrl(_strUrl.c_str());

	CCHttpClient *client = CCHttpClient::getInstance();
	client->send(request);

	request->release();
}

void MDHeroPrePromoLayer::requestFinishedCallback(CCHttpClient* client, CCHttpResponse* response)
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
	} else if (requestTag == "102"){
	}
}

bool MDHeroPrePromoLayer::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_lblPreQuality", CCLabelTTF*, this->m_lblPreQuality);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_lblAftQuality", CCLabelTTF*, this->m_lblAftQuality);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_lblCardName", CCLabelTTF*, this->m_lblCardName);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_lblRank", CCLabelTTF*, this->m_lblRank);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_lbExp", CCLabelTTF*, this->m_lbExp);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_lbHP", CCLabelTTF*, this->m_lbHP);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_lblAttack", CCLabelTTF*, this->m_lblAttack);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_lblDefence", CCLabelTTF*, this->m_lblDefence);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_lblSuper", CCLabelTTF*, this->m_lblSuper);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_lblAftRank", CCLabelTTF*, this->m_lblAftRank);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_lbAftExp", CCLabelTTF*, this->m_lbAftExp);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_lbAftHP", CCLabelTTF*, this->m_lbAftHP);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_lblAftAttack", CCLabelTTF*, this->m_lblAftAttack);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_lblAftDefence", CCLabelTTF*, this->m_lblAftDefence);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_lblAftSuper", CCLabelTTF*, this->m_lblAftSuper);
	return true;
}

SEL_MenuHandler MDHeroPrePromoLayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
	return NULL;
}

SEL_CCControlHandler MDHeroPrePromoLayer::onResolveCCBCCControlSelector(CCObject *pTarget, const char * pSelectorName) {

	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "buttonClicked:", MDHeroPrePromoLayer::buttonClicked);
	return NULL;
}

void MDHeroPrePromoLayer::onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader)
{
//    mTaskList = GlobalData::getTasks("");
//    mTaskList->retain();
    
//    showTaskInfo();
}

void MDHeroPrePromoLayer::buttonClicked(CCObject * sender , CCControlEvent controlEvent)
{
	MainGameScene *mainScene = (MainGameScene *)this->getParent();
	CCControlButton *button = (CCControlButton *)sender;
	switch (button->getTag()) {
	case 101:
        {
//            mainScene->PopLayer();
            break;
        }
	case 102:
        {
            mainScene->PopLayer();
            break;
        }
		break;
	}
}

MDHeroPrePromoLayer::MDHeroPrePromoLayer()
{
	mTaskList = NULL;
    
    m_lblPreQuality = NULL;
    m_lblAftQuality = NULL;
    m_lblCardName = NULL;
    
    m_lblRank = NULL;
    m_lbExp = NULL;
    m_lbHP = NULL;
    m_lblAttack = NULL;
    m_lblDefence = NULL;
    m_lblSuper = NULL;
    
    m_lblAftRank = NULL;
    m_lbAftExp = NULL;
    m_lbAftHP = NULL;
    m_lblAftAttack = NULL;
    m_lblAftDefence = NULL;
    m_lblAftSuper = NULL;

    m_sCardBefore = NULL;
    m_sCardAfter = NULL;
}

MDHeroPrePromoLayer::~MDHeroPrePromoLayer()
{
	CC_SAFE_RELEASE(m_lblPreQuality);
    CC_SAFE_RELEASE(m_lblAftQuality);
    CC_SAFE_RELEASE(m_lblCardName);
    
    CC_SAFE_RELEASE(m_lblRank);
    CC_SAFE_RELEASE(m_lbExp);
    CC_SAFE_RELEASE(m_lbHP);
    CC_SAFE_RELEASE(m_lblAttack);
    CC_SAFE_RELEASE(m_lblDefence);
    CC_SAFE_RELEASE(m_lblSuper);
    
    CC_SAFE_RELEASE(m_lblAftRank);
    CC_SAFE_RELEASE(m_lbAftExp);
    CC_SAFE_RELEASE(m_lbAftHP);
    CC_SAFE_RELEASE(m_lblAftAttack);
    CC_SAFE_RELEASE(m_lblDefence);
    CC_SAFE_RELEASE(m_lblAftSuper);
}

