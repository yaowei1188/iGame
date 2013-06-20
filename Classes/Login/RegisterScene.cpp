#include "RegisterScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

RegisterScene::RegisterScene()
{
    m_txtAccount = NULL;
    m_txtPassword = NULL;
}

RegisterScene::~RegisterScene()
{
    
}

CCScene* RegisterScene::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        RegisterScene *layer = RegisterScene::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool RegisterScene::init()
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

//void RegisterScene::doSubmit()
//{
//	CCHttpRequest *request = new CCHttpRequest();
//	request->setRequestType(CCHttpRequest::kHttpPost);
//	request->setResponseCallback(this,callfuncND_selector(RegisterScene::requestFinishedCallback));
//	request->setTag("post testing!!!");
//	request->setUrl("http://223.4.10.91/andon_service/ANDON_EX_USER.asmx/GetList");
//
//	const char* postData = "cid=120000&date=";
//	request->setRequestData(postData,strlen(postData));
//	CCHttpClient *client = CCHttpClient::getInstance();
//	client->send(request);
//
//	request->release();
//}

void RegisterScene::doSubmit()
{
    std::string sAccount(m_txtAccount->getText());
	std::string sPassword(m_txtPassword->getText());
    
    if (trimRight(sAccount).empty() || trimRight(sPassword).empty()) {
        CCMessageBox(GlobalData::getLocalString("account_pwd_empty")->getCString(),"ERROR");
        return;
    }
    
    this->ShowLoadingIndicator("");
    
	CCHttpRequest *request = new CCHttpRequest();
	request->setRequestType(CCHttpRequest::kHttpGet);
	request->setResponseCallback(this,callfuncND_selector(RegisterScene::requestFinishedCallback));
	request->setTag("1");

	string _strUrl = CompleteUrl(URL_USER_LOGIN);
	_strUrl.append(sAccount + "/");
	_strUrl.append(sPassword);
	request->setUrl(_strUrl.c_str());
    
 //   char url[150] = {0};
 //   sprintf(url,"%s/user/login/%s/%s",API_URL,sAccount.c_str(),sPassword.c_str());
 //   CCLOG(url);
	//request->setUrl(url);
    
	CCHttpClient *client = CCHttpClient::getInstance();
	client->send(request);
    
	request->release();
}

void RegisterScene::requestFinishedCallback(CCNode* pSender,void *data)
{
    this->HideLoadingIndicator();
    
    CCHttpResponse *response =  (CCHttpResponse*)data;
	if(response == NULL)
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
	CCLog(content.c_str());

	parseJson(content);
}

void RegisterScene::parseJson(std::string &content)
{
//	Json::Reader reader;  
//	Json::Value root; 
//
//	const char* str = content.c_str();
//	if (!reader.parse(str, root))
//	{
//        CCMessageBox("Parse failed","ERROR");
//		return;
//	}
//    int code = root["code"].asInt();
//    if (code!=200) {
//        
//        CCMessageBox("登陆失败,用户名或者密码错误！","ERROR");
//        return;
//    }
    
//    JsonBox::Value val;
//	val.loadFromString(content);
//
//    int code = val["code"].getInt();
//    if (code!=200) {
//
//        CCMessageBox("invoke web api failed!","ERROR");
//        return;
//    }else {
//    	CCLOG("douzhan:login successfully!");
//    }

//    CCUserDefault::sharedUserDefault()->setStringForKey("username", val["username"].getString());
//    CCUserDefault::sharedUserDefault()->setStringForKey("userinfo", val["encryptedUserInfo"].getString());
    
//    CCUserDefault::sharedUserDefault()->setStringForKey("username", root["username"].asString());
//    CCUserDefault::sharedUserDefault()->setStringForKey("userinfo", root["encryptedUserInfo"].asString());
    
    string selectedServer = CCUserDefault::sharedUserDefault()->getStringForKey("SelectedServer");
    if (selectedServer.length()>0) {
         this->OpenNewScene("MainGameScene");
    } else {
        this->OpenNewScene("ServerListScene");
    }
}

void RegisterScene::onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader)
{
    CCLOG("TEST");
    
    m_txtAccount = CCEditBox::create(CCSizeMake(200, 35), CCScale9Sprite::create("transparent.png"));
    this->addChild(m_txtAccount);
    m_txtAccount->setPosition(ccp(177, 247));
    
    m_txtPassword = CCEditBox::create(CCSizeMake(200, 35), CCScale9Sprite::create("transparent.png"));
    this->addChild(m_txtPassword);
    m_txtPassword->setPosition(ccp(177, 201));
    
    m_txtAccount->setFontColor(ccc3(0,0,0));
    m_txtAccount->setFont(FONT_LOGIN, 16);

    m_txtPassword->setInputFlag(kEditBoxInputFlagPassword);
    m_txtPassword->setFontColor(ccc3(0,0,0));
    m_txtPassword->setFont(FONT_LOGIN, 16);

//	m_txtAccount->setText("yaowei");
//	m_txtPassword->setText("123456");
}

bool RegisterScene::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
//    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_txtAccount", CCEditBox*, this->m_txtAccount);
//    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_txtPassword", CCEditBox*, this->m_txtPassword);
    
    return true;
}

void RegisterScene::buttonClicked(CCObject *pSender, CCControlEvent pCCControlEvent) {
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	    //SimpleAudioEngine::sharedEngine()->playEffect( EFFECT_FILE );
    #endif

    CCControlButton *button = (CCControlButton*) pSender;
    
    if (pCCControlEvent==CCControlEventTouchUpInside) {
        switch (button->getTag()) {
            case LOGIN_BUTTON_ACTION_SIGNUP_TAG:
                CCLOG("signup");
                break;
            case LOGIN_BUTTON_ACTION_TOURIST_TAG:
                CCDirector::sharedDirector()->popScene();
                break;
        }
    }
}

void RegisterScene::menuBarBtnClicked(CCObject *pSender)
{
    CCMenuItem *menuItem = (CCMenuItem*) pSender;
    switch (menuItem->getTag()) {
        case LOGIN_MENU_BAR_QQ_TAG:
            CCLOG("qq");
            break;
        case LOGIN_MENU_BAR_SINA_TAG:
            CCLOG("sina");
            break;
        case LOGIN_MENU_BAR_RENREN_TAG:
            CCLOG("renren");
            break;
    }
    
    this->PushScene("ThirdRegisterScene.ccbi");
}

SEL_MenuHandler RegisterScene::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "menuBarBtnClicked:", RegisterScene::menuBarBtnClicked);
	return NULL;
}

SEL_CCControlHandler RegisterScene::onResolveCCBCCControlSelector(CCObject *pTarget, const char * pSelectorName) {
    
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "buttonClicked:", RegisterScene::buttonClicked);
	return NULL;
}

