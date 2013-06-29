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
//	request->setResponseCallback(this,httpresponse_selector(RegisterScene::requestFinishedCallback));
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
	request->setResponseCallback(this,httpresponse_selector(RegisterScene::requestFinishedCallback));
	request->setTag("101");

	string _strUrl = CompleteUrl(URL_USER_REGISTER);
	_strUrl.append(sAccount + "/");
	_strUrl.append(sPassword);
	request->setUrl(_strUrl.c_str());
    
	CCHttpClient *client = CCHttpClient::getInstance();
	client->send(request);
    
	request->release();
}

void RegisterScene::requestFinishedCallback(CCHttpClient* client, CCHttpResponse* response)
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
        if (code == 105) {
            CCMessageBox(GlobalData::getLocalString("register_have_sameuser")->getCString(),"");
        }
        return;
    }
	
    
    std::string requestTag(response->getHttpRequest()->getTag());
    
    if (requestTag == "101") {
        CCString *strEncryptedUser = (CCString *)dictionary->objectForKey("encryptedUserInfo");
        if(strEncryptedUser->length() > 0)
        {
            CCMessageBox(GlobalData::getLocalString("register_successfully")->getCString(),"");
            CCDirector::sharedDirector()->popScene();
        }
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
                this->doSubmit();
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

