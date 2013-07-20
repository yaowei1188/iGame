#include "MDHerosFormationLayer.h"

#define TASK_COLUMN  3
#define TASK_ROW  3

CCScene* MDHerosFormationLayer::scene()
{
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		MDHerosFormationLayer *layer = MDHerosFormationLayer::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool MDHerosFormationLayer::init()
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

void MDHerosFormationLayer::doSearch()
{
	this->ShowLoadingIndicator("");

	CCHttpRequest *request = new CCHttpRequest();
	request->setRequestType(CCHttpRequest::kHttpGet);
	request->setResponseCallback(this,httpresponse_selector(MDHerosFormationLayer::requestFinishedCallback));
	request->setTag("101");

	string _strUrl = CompleteUrl(URL_FRIEND_LIST);
	_strUrl.append(CCUserDefault::sharedUserDefault()->getStringForKey("userinfo"));

	request->setUrl(_strUrl.c_str());

	CCHttpClient *client = CCHttpClient::getInstance();
	client->send(request);

	request->release();
}

void MDHerosFormationLayer::requestFinishedCallback(CCHttpClient* client, CCHttpResponse* response)
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

bool MDHerosFormationLayer::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_lblFightCapacity", CCLabelTTF*, this->m_lblFightCapacity);
	return true;
}

SEL_MenuHandler MDHerosFormationLayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
	return NULL;
}

SEL_CCControlHandler MDHerosFormationLayer::onResolveCCBCCControlSelector(CCObject *pTarget, const char * pSelectorName) {

	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "buttonClicked:", MDHerosFormationLayer::buttonClicked);
	return NULL;
}

void MDHerosFormationLayer::onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader)
{

}

void MDHerosFormationLayer::buttonClicked(CCObject * sender , CCControlEvent controlEvent)
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

MDHerosFormationLayer::MDHerosFormationLayer()
{
	m_lblFightCapacity = NULL;
}

MDHerosFormationLayer::~MDHerosFormationLayer()
{
	CC_SAFE_RELEASE(m_lblFightCapacity);
}

