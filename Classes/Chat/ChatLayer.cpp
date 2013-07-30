#include "ChatLayer.h"
#include "MainGameScene.h"

using namespace cocos2d;

ChatLayer::ChatLayer()
{
    m_txtAccount = NULL;
    m_txtPassword = NULL;
}

ChatLayer::~ChatLayer()
{
    
}

//CCScene* ChatLayer::scene()
//{
//    CCScene * scene = NULL;
//    do 
//    {
//        // 'scene' is an autorelease object
//        scene = CCScene::create();
//        CC_BREAK_IF(! scene);
//
//        // 'layer' is an autorelease object
//        ChatLayer *layer = ChatLayer::create();
//        CC_BREAK_IF(! layer);
//
//        // add layer as a child to scene
//        scene->addChild(layer);
//    } while (0);
//
//    // return the scene
//    return scene;
//}

// on "init" you need to initialize your instance
bool ChatLayer::init()
{
    bool bRet = false;
    do 
    {
        CC_BREAK_IF(! CCLayer::init());
        
        bRet = true;
    } while (0);

    return bRet;
}

//void ChatLayer::submitClicked(CCObject *pSender,CCControlEvent event)
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

void ChatLayer::doSubmit()
{
//	CCHttpRequest *request = new CCHttpRequest();
//	request->setRequestType(CCHttpRequest::kHttpPost);
//	request->setResponseCallback(this,callfuncND_selector(ChatLayer::requestFinishedCallback));
//	request->setTag("post testing!!!");
//	request->setUrl("http://223.4.10.91/andon_service/ANDON_EX_USER.asmx/GetList");
//
//	const char* postData = "cid=120000&date=";
//	request->setRequestData(postData,strlen(postData));
//	CCHttpClient *client = CCHttpClient::getInstance();
//	client->send(request);
//
//	request->release();
}

void ChatLayer::requestFinishedCallback(CCNode* pSender,void *data)
{
    CCHttpResponse *response =  (CCHttpResponse*)data;
	if(response==NULL)
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

	std::string content(buffer->begin(),buffer->end());

	XMLParser *xmlParser = XMLParser::parseWithString(content.c_str());
	CCLOG("%s",xmlParser->getString("content")->getCString());

//	parseJson();
}

//void ChatLayer::parseJson()
//{
//
//}

void ChatLayer::onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader)
{
    m_txtAccount = CCEditBox::create(CCSizeMake(134, 30), CCScale9Sprite::create("transparent.png"));
    this->addChild(m_txtAccount);
    m_txtAccount->setPosition(ccp(215, 24));
    m_txtAccount->setFontColor(ccc3(255,255,255));
    m_txtAccount->setFont("Arial", 16);
    
    CCMenu *menu = CCMenu::create();
    this->addChild(menu);
    menu->setPosition(ccp(33, 119));
    
//    CCLabelBMFont* lblName = CCLabelBMFont::create("阵营", "test.fnt");
    
    CCLabelTTF *lblShout = CCLabelTTF::create("喊话", FONT_VERDANA, FONT_SIZE_MEDIUM);
    lblShout->setColor(ccc3(197, 255, 255));
    lblShout->enableStroke(ccc3(69, 20, 21), 1);
	CCMenuItemLabel* menuShout = CCMenuItemLabel::create(lblShout, this, menu_selector(ChatLayer::menuCallback));
	menuShout->setPosition(ccp(4,80));
	menuShout->setTag(101);
	menu->addChild(menuShout);
    
    CCLabelTTF *lblWorld = CCLabelTTF::create("世界", FONT_VERDANA, FONT_SIZE_MEDIUM);
    lblWorld->setColor(ccc3(197, 255, 255));
    lblWorld->enableStroke(ccc3(69, 20, 21), 1);
	CCMenuItemLabel* menuWorld = CCMenuItemLabel::create(lblWorld, this, menu_selector(ChatLayer::menuCallback));
	menuWorld->setPosition(ccp(4,50));
	menuWorld->setTag(102);
	menu->addChild(menuWorld);
    
    CCLabelTTF *lblFaction = CCLabelTTF::create("阵营", FONT_VERDANA, FONT_SIZE_MEDIUM);
    lblFaction->setColor(ccc3(197, 255, 255));
    lblFaction->enableStroke(ccc3(69, 20, 21), 1);
	CCMenuItemLabel* menuFaction = CCMenuItemLabel::create(lblFaction, this, menu_selector(ChatLayer::menuCallback));
	menuFaction->setPosition(ccp(4,20));
	menuFaction->setTag(103);
	menu->addChild(menuFaction);
    
    CCLabelTTF *lblGroup = CCLabelTTF::create("公会", FONT_VERDANA, FONT_SIZE_MEDIUM);
    lblGroup->setColor(ccc3(197, 255, 255));
    lblGroup->enableStroke(ccc3(69, 20, 21), 1);
	CCMenuItemLabel* menuGroup = CCMenuItemLabel::create(lblGroup, this, menu_selector(ChatLayer::menuCallback));
	menuGroup->setPosition(ccp(4,-10));
	menuGroup->setTag(104);
	menu->addChild(menuGroup);
    
    CCLabelTTF *lblPrivate = CCLabelTTF::create("蜜语", FONT_VERDANA, FONT_SIZE_MEDIUM);
    lblPrivate->setColor(ccc3(197, 255, 255));
    lblPrivate->enableStroke(ccc3(69, 20, 21), 1);
	CCMenuItemLabel* menuPrivate = CCMenuItemLabel::create(lblPrivate, this, menu_selector(ChatLayer::menuCallback));
	menuPrivate->setPosition(ccp(4,-40));
	menuPrivate->setTag(105);
	menu->addChild(menuPrivate);

}

void ChatLayer::menuCallback(CCObject* sender)
{
//	MainGameScene *mainScene = (MainGameScene *)this->getParent();
	CCMenuItemFont *button = (CCMenuItemFont *)sender;
	switch (button->getTag()) {
        case 101:
		{

			break;
		}
        case 102:
		{
			break;
		}
	}
}

void ChatLayer::callbackSwitch(CCObject* pSender){
    
	CCMenuItemToggle* pSwitch = (CCMenuItemToggle*)pSender;
    
    if (pSwitch->getSelectedIndex()==0) {
        m_blnRememberMe = false;
    } else {
        m_blnRememberMe = true;
    }
}

bool ChatLayer::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
//    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_txtAccount", CCEditBox*, this->m_txtAccount);
//    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_txtPassword", CCEditBox*, this->m_txtPassword);
    return true;
}

void ChatLayer::buttonClicked(CCObject *pSender, CCControlEvent pCCControlEvent) {
    
    CCControlButton *button = (CCControlButton*) pSender;
    
    switch (button->getTag()) {
        case 1:
        {
            CCLOG("chat");
            MainGameScene *mainScene = (MainGameScene *)this->getParent();
            mainScene->RemoveChatLayer();
            break;
        }
        case 2:
        {
            CCLOG("face");
            break;
        }
    }
}

SEL_MenuHandler ChatLayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
	return NULL;
}

SEL_CCControlHandler ChatLayer::onResolveCCBCCControlSelector(CCObject *pTarget, const char * pSelectorName) {
    
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "buttonClicked:", ChatLayer::buttonClicked);
	return NULL;
}

