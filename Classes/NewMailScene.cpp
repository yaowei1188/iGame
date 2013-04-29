#include "NewMailScene.h"
#include "json/json.h"

using namespace cocos2d;

NewMailScene::NewMailScene()
{
    m_txtAccount = NULL;
    m_txtPassword = NULL;
    mCloud = NULL;
    m_blnRememberMe = false;
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
    std::string sAccount(m_txtAccount->getText());
	std::string sPassword(m_txtPassword->getText());
    
    if (trimRight(sAccount).empty() || trimRight(sPassword).empty()) {
        CCMessageBox("用户名密码不能为空！","ERROR");
        return;
    }
    
    
    this->ShowLoadingIndicator("");
    
	CCHttpRequest *request = new CCHttpRequest();
	request->setRequestType(CCHttpRequest::kHttpGet);
	request->setResponseCallback(this,callfuncND_selector(NewMailScene::requestFinishedCallback));
	request->setTag("1");
    
    char url[150] = {0};
    sprintf(url,"%s/user/login/%s/%s",API_URL,sAccount.c_str(),sPassword.c_str());
    CCLOG(url);
	request->setUrl(url);
    
	CCHttpClient *client = CCHttpClient::getInstance();
	client->send(request);
    
	request->release();
}

void NewMailScene::requestFinishedCallback(CCNode* pSender,void *data)
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

void NewMailScene::parseJson(std::string &content)
{
	Json::Reader reader;  
	Json::Value root; 

	const char* str = content.c_str();
	if (!reader.parse(str, root))
	{
        CCMessageBox("Parse failed","ERROR");
		return;
	}
    int code = root["code"].asInt();
    if (code!=200) {
        
        CCMessageBox("登陆失败,用户名或者密码错误！","ERROR");
        return;
    }

    CCUserDefault::sharedUserDefault()->setStringForKey("username", root["username"].asString());
    CCUserDefault::sharedUserDefault()->setStringForKey("userinfo", root["encryptedUserInfo"].asString());
    
    this->OpenNewScene("MainGameScene");
}

void NewMailScene::onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader)
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
    CCMenuItemToggle* item = CCMenuItemToggle::createWithTarget(this, menu_selector(NewMailScene::callbackSwitch),auto_op_btn,auto_op_btn2,NULL);
    
    m_auto_op_menu->addChild(item);
    m_auto_op_menu->setPosition(ccp(116, 148));
    this->addChild(m_auto_op_menu);
}

void NewMailScene::callbackSwitch(CCObject* pSender){

	CCMenuItemToggle* pSwitch = (CCMenuItemToggle*)pSender;
    
    if (pSwitch->getSelectedIndex()==0) {
        m_blnRememberMe = false;
    } else {
        m_blnRememberMe = true;
    }
}

bool NewMailScene::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_txtAccount", CCEditBox*, this->m_txtAccount);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_txtPassword", CCEditBox*, this->m_txtPassword);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mCloud", CCSprite*, this->mCloud);
    
    return true;
}

void NewMailScene::buttonClicked(CCObject *pSender, CCControlEvent pCCControlEvent) {
    
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

void NewMailScene::menuBarBtnClicked(CCObject *pSender)
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

SEL_MenuHandler NewMailScene::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "menuBarBtnClicked:", NewMailScene::menuBarBtnClicked);
	return NULL;
}

SEL_CCControlHandler NewMailScene::onResolveCCBCCControlSelector(CCObject *pTarget, const char * pSelectorName) {
    
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "buttonClicked:", NewMailScene::buttonClicked);
	return NULL;
}

