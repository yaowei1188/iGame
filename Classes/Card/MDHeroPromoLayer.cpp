#include "MDHeroPromoLayer.h"

#define TASK_COLUMN  3
#define TASK_ROW  3

CCScene* MDHeroPromoLayer::scene()
{
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		MDHeroPromoLayer *layer = MDHeroPromoLayer::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool MDHeroPromoLayer::init()
{
	bool bRet = false;
	do 
	{
		//////////////////////////////////////////////////////////////////////////
		// super init first
		//////////////////////////////////////////////////////////////////////////

		CC_BREAK_IF(! CCLayer::init());

		bRet = true;
	} while (0);

	return bRet;
}

void MDHeroPromoLayer::doSearch()
{
	this->ShowLoadingIndicator("");

	CCHttpRequest *request = new CCHttpRequest();
	request->setRequestType(CCHttpRequest::kHttpGet);
	request->setResponseCallback(this,httpresponse_selector(MDHeroPromoLayer::requestFinishedCallback));
	request->setTag("101");

	string _strUrl = CompleteUrl(URL_FRIEND_LIST);
	_strUrl.append(CCUserDefault::sharedUserDefault()->getStringForKey("userinfo"));

	request->setUrl(_strUrl.c_str());

	CCHttpClient *client = CCHttpClient::getInstance();
	client->send(request);

	request->release();
}

void MDHeroPromoLayer::requestFinishedCallback(CCHttpClient* client, CCHttpResponse* response)
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

bool MDHeroPromoLayer::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_lblWindNum", CCLabelTTF*, this->m_lblWindNum);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_lblWindStr", CCLabelTTF*, this->m_lblWindStr);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_lblFireNum", CCLabelTTF*, this->m_lblFireNum);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_lblFireStr", CCLabelTTF*, this->m_lblFireStr);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_lblWaterNum", CCLabelTTF*, this->m_lblWaterNum);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_lblWaterStr", CCLabelTTF*, this->m_lblWaterStr);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_lblStoneNum", CCLabelTTF*, this->m_lblStoneNum);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_lblStoneStr", CCLabelTTF*, this->m_lblStoneStr);
	return true;
}

SEL_MenuHandler MDHeroPromoLayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
	return NULL;
}

SEL_CCControlHandler MDHeroPromoLayer::onResolveCCBCCControlSelector(CCObject *pTarget, const char * pSelectorName) {

	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "buttonClicked:", MDHeroPromoLayer::buttonClicked);
	return NULL;
}

void MDHeroPromoLayer::onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader)
{
//    mTaskList = GlobalData::getTasks("");
//    mTaskList->retain();
//    
//    doSearch();
}

void MDHeroPromoLayer::buttonClicked(CCObject * sender , CCControlEvent controlEvent)
{
	MainGameScene *mainScene = (MainGameScene *)this->getParent();
	CCControlButton *button = (CCControlButton *)sender;
	switch (button->getTag()) {
        case 101:
        {
            mainScene->PopLayer();
            break;
        }
        case 102:
        {

        }
        case 103:
        {
            
        }
        case 104:
        {
            
        }
        case 105:
        {
            
        }
        case 106:
        {
            
        }
    }
}

MDHeroPromoLayer::MDHeroPromoLayer()
{
	mTaskList = NULL;
    m_lblWindNum = NULL;
    m_lblWindStr = NULL;
    m_lblFireNum = NULL;
    m_lblFireStr = NULL;
    m_lblWaterNum = NULL;
    m_lblWaterStr = NULL;
    m_lblStoneNum = NULL;
    m_lblStoneStr = NULL;
}

MDHeroPromoLayer::~MDHeroPromoLayer()
{
	CC_SAFE_RELEASE(m_lblWindNum);
    CC_SAFE_RELEASE(m_lblWindStr);
    CC_SAFE_RELEASE(m_lblFireNum);
    CC_SAFE_RELEASE(m_lblFireStr);
    CC_SAFE_RELEASE(m_lblWaterNum);
    CC_SAFE_RELEASE(m_lblWaterStr);
    CC_SAFE_RELEASE(m_lblStoneNum);
    CC_SAFE_RELEASE(m_lblStoneStr);
}

