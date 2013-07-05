#include "LoginScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

LoginScene::LoginScene()
{
    m_txtAccount = NULL;
    m_txtPassword = NULL;
    m_blnRememberMe = false;
}

LoginScene::~LoginScene()
{
    
}

CCScene* LoginScene::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        LoginScene *layer = LoginScene::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool LoginScene::init()
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

//void LoginScene::doSubmit()
//{
//	CCHttpRequest *request = new CCHttpRequest();
//	request->setRequestType(CCHttpRequest::kHttpPost);
//	request->setResponseCallback(this,httpresponse_selector(LoginScene::requestFinishedCallback));
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

void LoginScene::doSubmit()
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
    request->setResponseCallback(this,httpresponse_selector(LoginScene::requestFinishedCallback));
	request->setTag("1");

	string _strUrl = CompleteUrl(URL_USER_LOGIN);
	_strUrl.append(sAccount + "/");
	_strUrl.append(sPassword);
	request->setUrl(_strUrl.c_str());
    
	CCHttpClient *client = CCHttpClient::getInstance();
	client->send(request);
    
	request->release();
}

void LoginScene::requestFinishedCallback(CCHttpClient* client, CCHttpResponse* response)
{
    this->HideLoadingIndicator();

	if (!this->ValidateResponseData(client,response))
	{
		return;
	}

	std::vector<char> *buffer = response->getResponseData();
	std::string content(buffer->begin(),buffer->end());

	CCDictionary * dictionary = CCJSONConverter::sharedConverter()->dictionaryFrom(content.c_str());
	int code = ((CCNumber *)dictionary->objectForKey("code"))->getIntValue();
	if (code != 200) {
		if (code == 112) {
			CCMessageBox(GlobalData::getLocalString("login_wrongnameorpassword")->getCString(),"");
		} else {
			CCMessageBox(response->getErrorBuffer(),"error");
		}
		return;
	}

	std::string requestTag(response->getHttpRequest()->getTag());

	if (requestTag == "1") {
		CCString *strEncryptedUser = (CCString *)dictionary->objectForKey("encryptedUserInfo");
		CCString *strName = (CCString *)dictionary->objectForKey("username");
		if(strEncryptedUser->length() > 0)
		{
			CCDictionary *userInfo = CCDictionary::create();
			userInfo->setObject(CCNumber::create(1),"fraction");
			GlobalData::setUserinfo(userInfo);

			CCUserDefault::sharedUserDefault()->setStringForKey("userinfo", strEncryptedUser->getCString());
			CCUserDefault::sharedUserDefault()->setStringForKey("username", strName->getCString());

//			string selectedServer = CCUserDefault::sharedUserDefault()->getStringForKey("SelectedServer");
//			if (selectedServer.length()>0) {
//				this->OpenNewScene("MainGameScene");
//			} else {
//				this->OpenNewScene("ServerListScene");
//			}

            this->OpenNewScene("ServerListScene");
		}
	}
}

void LoginScene::onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader)
{
    CCLOG("TEST");
    
    m_txtAccount = CCEditBox::create(CCSizeMake(200, 35), CCScale9Sprite::create("transparent.png"));
    m_txtAccount->setText("yaowei");
    m_txtAccount->setPosition(ccp(177, 247));
    m_txtAccount->setFontColor(ccc3(0,0,0));
    m_txtAccount->setFont(FONT_LOGIN, 16);
    this->addChild(m_txtAccount);

    m_txtPassword = CCEditBox::create(CCSizeMake(200, 35), CCScale9Sprite::create("transparent.png"));
    m_txtPassword->setText("123456");
    this->addChild(m_txtPassword);
    m_txtPassword->setPosition(ccp(177, 201));
    m_txtPassword->setInputFlag(kEditBoxInputFlagPassword);
    m_txtPassword->setFontColor(ccc3(0,0,0));
    m_txtPassword->setFont(FONT_LOGIN, 16);
    
	CCSprite *spriteOn = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("gou_1.png"));
	CCSprite *spriteOff = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("gou_2.png"));
    
    CCMenu* m_auto_op_menu = CCMenu::create();
    CCMenuItemSprite* auto_op_btn = CCMenuItemSprite::create(spriteOff, NULL);
    CCMenuItemSprite* auto_op_btn2 = CCMenuItemSprite::create(spriteOn, NULL);
    CCMenuItemToggle* item = CCMenuItemToggle::createWithTarget(this, menu_selector(LoginScene::callbackSwitch),auto_op_btn,auto_op_btn2,NULL);
    
    m_auto_op_menu->addChild(item);
    m_auto_op_menu->setPosition(ccp(85, 148));
    this->addChild(m_auto_op_menu);
}

void LoginScene::callbackSwitch(CCObject* pSender){

	CCMenuItemToggle* pSwitch = (CCMenuItemToggle*)pSender;
    
    if (pSwitch->getSelectedIndex()==0) {
        m_blnRememberMe = false;
    } else {
        m_blnRememberMe = true;
    }
}

bool LoginScene::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
//    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_txtAccount", CCEditBox*, this->m_txtAccount);
//    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_txtPassword", CCEditBox*, this->m_txtPassword);
    
    return true;
}

void LoginScene::buttonClicked(CCObject *pSender, CCControlEvent pCCControlEvent) {
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	    //SimpleAudioEngine::sharedEngine()->playEffect( EFFECT_FILE );
    #endif

    CCControlButton *button = (CCControlButton*) pSender;
    
    if (pCCControlEvent==CCControlEventTouchUpInside) {
        switch (button->getTag()) {
            case LOGIN_BUTTON_ACTION_SIGNIN_TAG:
                CCLOG("signin");
                this->doSubmit();
                break;
            case LOGIN_BUTTON_ACTION_SIGNUP_TAG:
                CCLOG("signup");
                this->PushScene("RegisterScene");
                break;
            case LOGIN_BUTTON_ACTION_TOURIST_TAG:
                CCLOG("tourist");
                this->doSubmit();
                break;
            case LOGIN_BUTTON_ACTION_FORGOT_PWD_TAG:
                CCLOG("fotgot pwd");
                break;
        }
    }
}

void LoginScene::menuBarBtnClicked(CCObject *pSender)
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
    
    this->PushScene("ThirdLoginScene.ccbi");
}

SEL_MenuHandler LoginScene::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "menuBarBtnClicked:", LoginScene::menuBarBtnClicked);
	return NULL;
}

SEL_CCControlHandler LoginScene::onResolveCCBCCControlSelector(CCObject *pTarget, const char * pSelectorName) {
    
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "buttonClicked:", LoginScene::buttonClicked);
	return NULL;
}

