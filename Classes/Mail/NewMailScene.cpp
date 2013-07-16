#include "NewMailScene.h"
//#include "JsonBox.h"

using namespace cocos2d;

NewMailScene::NewMailScene()
{
    m_txtReceiver = NULL;
    m_txtSubject = NULL;
    m_txtContent = NULL;
}

NewMailScene::~NewMailScene()
{
    
}

CCScene* NewMailScene::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        NewMailScene *layer = NewMailScene::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool NewMailScene::init()
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

void NewMailScene::doSubmit()
{
    std::string sReceiver(m_txtReceiver->getText());
	std::string sSubject(m_txtSubject->getText());
    std::string sContent(m_txtContent->getText());
    
    if (trimRight(sReceiver).empty() || trimRight(sSubject).empty() || trimRight(sContent).empty()) {
        CCMessageBox("field can not be empty","ERROR");
        return;
    }
    
    this->ShowLoadingIndicator("");
    
	CCHttpRequest *request = new CCHttpRequest();
	request->setRequestType(CCHttpRequest::kHttpGet);
	request->setResponseCallback(this,httpresponse_selector(NewMailScene::requestFinishedCallback));
	request->setTag("1");
    
    char url[150] = {0};
    sprintf(url,"%s/user/login/%s/%s/%s",API_URL,sReceiver.c_str(),sSubject.c_str(),sContent.c_str());
	request->setUrl(url);
    
	CCHttpClient *client = CCHttpClient::getInstance();
	client->send(request);
    
	request->release();
}

void NewMailScene::requestFinishedCallback(CCHttpClient* client, CCHttpResponse* response)
{
	if (!this->ValidateResponseData(client,response))
	{
		return;
	}

	int statusCode = response->getResponseCode();
	char statusString[64] = {};
	CCLOG(statusString, "HTTP Status Code: %d, tag = %s", statusCode, response->getHttpRequest()->getTag());

	if (!response->isSucceed())   
	{  
		CCLog("response failed");  
		CCLog("error buffer: %s", response->getErrorBuffer());
        CCMessageBox("ERROR", "Response failed");
		return;  
	}
	std::vector<char> *buffer = response->getResponseData(); 

	std::string content(buffer->begin(),buffer->end());

	parseJson(content);
}

void NewMailScene::parseJson(std::string &content)
{
//    JsonBox::Value v2;
//	v2.loadFromString(content);
//    
//    int code = v2["code"].getInt();
//    if (code!=200) {
//        
//        CCMessageBox("invoke web api failed!","ERROR");
//        return;
//    }else {
//    	CCLOG("douzhan:login successfully!");
//    }
//    
//    CCUserDefault::sharedUserDefault()->setStringForKey("username", v2["username"].getString());
//    CCUserDefault::sharedUserDefault()->setStringForKey("userinfo", v2["encryptedUserInfo"].getString());
}

void NewMailScene::onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader)
{
    CCLOG("TEST");
    
    m_txtReceiver = CCEditBox::create(CCSizeMake(200, 35), CCScale9Sprite::create("transparent.png"));
    this->addChild(m_txtReceiver);
    m_txtReceiver->setPosition(ccp(187, 343));
    m_txtReceiver->setFontColor(ccc3(251,255,33));
    m_txtReceiver->setFont("Arial", 14);
 
    m_txtSubject = CCEditBox::create(CCSizeMake(200, 35), CCScale9Sprite::create("transparent.png"));
    this->addChild(m_txtSubject);
    m_txtSubject->setPosition(ccp(187, 297));
    m_txtSubject->setFontColor(ccc3(251,255,33));
    m_txtSubject->setFont("Arial", 14);
    
    m_txtContent = CCEditBox::create(CCSizeMake(200, 35), CCScale9Sprite::create("transparent.png"));
    this->addChild(m_txtContent);
    m_txtContent->setPosition(ccp(187, 248));
    m_txtContent->setFontColor(ccc3(251,255,33));
    m_txtContent->setFont("Arial", 14);
//    m_txtContent->setContentSize(CCSizeMake(200, 85));
//    m_txtContent->setPreferredSize(CCSizeMake(200, 85));
}

bool NewMailScene::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
//    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_txtReceiver", CCEditBox*, this->m_txtReceiver);
//    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_txtSubject", CCEditBox*, this->m_txtSubject);
//    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_txtContent", CCEditBox*, this->m_txtContent);
    
    return true;
}

void NewMailScene::buttonClicked(CCObject *pSender, CCControlEvent pCCControlEvent) {
    
    CCControlButton *button = (CCControlButton*) pSender;
    
    switch (button->getTag()) {
        case 101:
        {
			this->doSubmit();
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

SEL_MenuHandler NewMailScene::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
	return NULL;
}

SEL_CCControlHandler NewMailScene::onResolveCCBCCControlSelector(CCObject *pTarget, const char * pSelectorName) {
    
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "buttonClicked:", NewMailScene::buttonClicked);
	return NULL;
}

