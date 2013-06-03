#include "LoginScene.h"
//#include "json/json.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

LoginScene::LoginScene()
{
//    // preload background music and effect
//    SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic( MUSIC_FILE );
//    SimpleAudioEngine::sharedEngine()->preloadEffect( EFFECT_FILE );
//    
//    // set default volume
//    SimpleAudioEngine::sharedEngine()->setEffectsVolume(0.5);
//    SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.5);
    
    m_txtAccount = NULL;
    m_txtPassword = NULL;
    mCloud = NULL;
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
    
        
//        SimpleAudioEngine::sharedEngine()->playBackgroundMusic(MUSIC_FILE, true);
        
        bRet = true;
    } while (0);

    return bRet;
}

//void LoginScene::doSubmit()
//{
//	CCHttpRequest *request = new CCHttpRequest();
//	request->setRequestType(CCHttpRequest::kHttpPost);
//	request->setResponseCallback(this,callfuncND_selector(LoginScene::requestFinishedCallback));
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
        CCMessageBox("用户名密码不能为空！","ERROR");
        return;
    }
    
    
    this->ShowLoadingIndicator("");
    
	CCHttpRequest *request = new CCHttpRequest();
	request->setRequestType(CCHttpRequest::kHttpGet);
	request->setResponseCallback(this,callfuncND_selector(LoginScene::requestFinishedCallback));
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

void LoginScene::requestFinishedCallback(CCNode* pSender,void *data)
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

void LoginScene::parseJson(std::string &content)
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
    
    JsonBox::Value val;
	val.loadFromString(content);
    
    int code = val["code"].getInt();
    if (code!=200) {
        
        CCMessageBox("invoke web api failed!","ERROR");
        return;
    }else {
    	CCLOG("douzhan:login successfully!");
    }

    CCUserDefault::sharedUserDefault()->setStringForKey("username", val["username"].getString());
    CCUserDefault::sharedUserDefault()->setStringForKey("userinfo", val["encryptedUserInfo"].getString());
    
//    CCUserDefault::sharedUserDefault()->setStringForKey("username", root["username"].asString());
//    CCUserDefault::sharedUserDefault()->setStringForKey("userinfo", root["encryptedUserInfo"].asString());
    
    this->OpenNewScene("MainGameScene");
}

void LoginScene::onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader)
{
    CCLOG("TEST");
    
    m_txtAccount->setText("yaowei");
    m_txtPassword->setText("123456");
    
    m_txtAccount->setFontColor(ccc3(0,0,0));
    m_txtAccount->setFont("Arial", 16);
    m_txtPassword->setInputFlag(kEditBoxInputFlagPassword);
    m_txtPassword->setFontColor(ccc3(0,0,0));
    m_txtPassword->setFont("Arial", 16);
    
	CCSprite *spriteOn = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("gou_1.png"));
	CCSprite *spriteOff = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("gou_2.png"));
    
    CCMenu* m_auto_op_menu = CCMenu::create();
    CCMenuItemSprite* auto_op_btn = CCMenuItemSprite::create(spriteOff, NULL);
    CCMenuItemSprite* auto_op_btn2 = CCMenuItemSprite::create(spriteOn, NULL);
    CCMenuItemToggle* item = CCMenuItemToggle::createWithTarget(this, menu_selector(LoginScene::callbackSwitch),auto_op_btn,auto_op_btn2,NULL);
    
    m_auto_op_menu->addChild(item);
    m_auto_op_menu->setPosition(ccp(116, 148));
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
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_txtAccount", CCEditBox*, this->m_txtAccount);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_txtPassword", CCEditBox*, this->m_txtPassword);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mCloud", CCSprite*, this->mCloud);
    
    return true;
}

void LoginScene::buttonClicked(CCObject *pSender, CCControlEvent pCCControlEvent) {
    
//    SimpleAudioEngine::sharedEngine()->playEffect( EFFECT_FILE );
    CCControlButton *button = (CCControlButton*) pSender;
    
    if (pCCControlEvent==CCControlEventTouchUpInside) {
        switch (button->getTag()) {
            case LOGIN_BUTTON_ACTION_SIGNIN_TAG:
                CCLOG("signin");
                this->doSubmit();
                break;
            case LOGIN_BUTTON_ACTION_SIGNUP_TAG:
                CCLOG("signup");
                break;
            case LOGIN_BUTTON_ACTION_TOURIST_TAG:
                CCLOG("tourist");
                break;
            case LOGIN_BUTTON_ACTION_FORGOT_PWD_TAG:
                CCLOG("fotgot pwd");
                break;
        }
    } else if (pCCControlEvent==CCControlEventTouchDown) {
        mCloud->runAction(CCMoveTo::create(0.1, button->getPosition()));
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

