#include "ThirdLoginScene.h"
//#include "JsonBox.h"

using namespace cocos2d;

ThirdLoginScene::ThirdLoginScene()
{
    m_txtAccount = NULL;
    m_txtPassword = NULL;
}

ThirdLoginScene::~ThirdLoginScene()
{
    
}

CCScene* ThirdLoginScene::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        ThirdLoginScene *layer = ThirdLoginScene::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool ThirdLoginScene::init()
{
    bool bRet = false;
    do 
    {
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////

        CC_BREAK_IF(! CCLayer::init());

        ////////////////////////////////////////////////////////////////////////////
        //// add your codes below...
        ////////////////////////////////////////////////////////////////////////////
        
        bRet = true;
    } while (0);

    return bRet;
}

//void ThirdLoginScene::submitClicked(CCObject *pSender,CCControlEvent event)
//{
//	CCLOG("i was clicked");
//	char sAccount[20];
//	char sPassword[20];
//	sprintf(sAccount,m_txtAccount->getText());
//	sprintf(sPassword,m_txtAccount->getText());
//
//	//this->doSubmit();
//    
//    
////    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
////    //ccNodeLoaderLibrary->registerCCNodeLoader("AboutScene", AboutSceneLoader::loader());
////    
////    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
////    ccbReader->autorelease();
////    
////    CCScene *pScene = ccbReader->createSceneWithNodeGraphFromFile("MainGameScene.ccbi");
////    CCDirector::sharedDirector()->replaceScene(CCTransitionFlipAngular::create(1.0, pScene));
//
//}

void ThirdLoginScene::doSubmit()
{
	CCHttpRequest *request = new CCHttpRequest();
	request->setRequestType(CCHttpRequest::kHttpPost);
	request->setResponseCallback(this,httpresponse_selector(ThirdLoginScene::requestFinishedCallback));
	request->setTag("post testing!!!");
	request->setUrl("http://223.4.10.91/andon_service/ANDON_EX_USER.asmx/GetList");

	const char* postData = "cid=120000&date=";
	request->setRequestData(postData,strlen(postData));
	CCHttpClient *client = CCHttpClient::getInstance();
	client->send(request);

	request->release();
}

void ThirdLoginScene::requestFinishedCallback(CCHttpClient* client, CCHttpResponse* response)
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
		return;  
	}
	std::vector<char> *buffer = response->getResponseData(); 

	//for (unsigned int i = 0; i < buffer->size(); i++)  
	//{
	//	CCLog("%c", (*buffer)[i]);
	//}
	std::string content(buffer->begin(),buffer->end());
	//CCLog(content.c_str());

	XMLParser *xmlParser = XMLParser::parseWithString(content.c_str());
	//xmlParser->getString("content");
	//CCString *content = CCString::create(xmlParser->getString("content")->getCString());
	CCLOG("%s",xmlParser->getString("content")->getCString());

	parseJson();
}

void ThirdLoginScene::parseJson()
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
}

void ThirdLoginScene::onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader)
{
    m_txtAccount = CCEditBox::create(CCSizeMake(200, 35), CCScale9Sprite::create("transparent.png"));
    this->addChild(m_txtAccount);
    m_txtAccount->setPosition(ccp(177, 368));
    
    m_txtPassword = CCEditBox::create(CCSizeMake(200, 35), CCScale9Sprite::create("transparent.png"));
    this->addChild(m_txtPassword);
    m_txtPassword->setPosition(ccp(177, 320));
    
    m_txtAccount->setFontColor(ccc3(0,0,0));
    m_txtAccount->setFont("Arial", 16);
    m_txtPassword->setInputFlag(kEditBoxInputFlagPassword);
    m_txtPassword->setFontColor(ccc3(0,0,0));
    m_txtPassword->setFont("Arial", 16);
    
	CCSprite *spriteOn = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("gou_1.png"));
	CCSprite *spriteOff = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("gou_2.png"));
    
    CCMenu* m_auto_op_menu = CCMenu::create();
    CCMenuItemSprite* auto_op_btn = CCMenuItemSprite::create(spriteOn, NULL);
    CCMenuItemSprite* auto_op_btn2 = CCMenuItemSprite::create(spriteOff, NULL);
    CCMenuItemToggle* item = CCMenuItemToggle::createWithTarget(this, menu_selector(ThirdLoginScene::callbackSwitch),auto_op_btn,auto_op_btn2,NULL);
    
    m_auto_op_menu->addChild(item);
    m_auto_op_menu->setPosition(ccp(116, 268));
    this->addChild(m_auto_op_menu);
}

void ThirdLoginScene::callbackSwitch(CCObject* pSender){
    
	CCMenuItemToggle* pSwitch = (CCMenuItemToggle*)pSender;
    
    if (pSwitch->getSelectedIndex()==0) {
        m_blnRememberMe = false;
    } else {
        m_blnRememberMe = true;
    }
}

bool ThirdLoginScene::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
//    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_txtAccount", CCEditBox*, this->m_txtAccount);
//    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_txtPassword", CCEditBox*, this->m_txtPassword);
    return true;
}

void ThirdLoginScene::buttonClicked(CCObject *pSender, CCControlEvent pCCControlEvent) {
    
    CCControlButton *button = (CCControlButton*) pSender;
//	char sAccount[20];
//	char sPassword[20];
//	sprintf(sAccount,m_txtAccount->getText());
//	sprintf(sPassword,m_txtAccount->getText());
    
    switch (button->getTag()) {
        case LOGIN_BUTTON_ACTION_SIGNIN_TAG:
            CCLOG("signin");
            break;
        case LOGIN_BUTTON_ACTION_SIGNUP_TAG:
            CCLOG("signup");
            break;
            break;
    }
    
    CCDirector::sharedDirector()->popScene();
}

SEL_MenuHandler ThirdLoginScene::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
	return NULL;
}

SEL_CCControlHandler ThirdLoginScene::onResolveCCBCCControlSelector(CCObject *pTarget, const char * pSelectorName) {
    
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "buttonClicked:", ThirdLoginScene::buttonClicked);
	return NULL;
}

