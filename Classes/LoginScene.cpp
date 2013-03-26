#include "HelloWorldScene.h"
#include "json/json.h"

using namespace cocos2d;

CCScene* HelloWorld::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        HelloWorld *layer = HelloWorld::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
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

        //// 1. Add a menu item with "X" image, which is clicked to quit the program.

        //// Create a "close" menu item with close icon, it's an auto release object.
        //CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
        //    "CloseNormal.png",
        //    "CloseSelected.png",
        //    this,
        //    menu_selector(HelloWorld::menuCloseCallback));
        //CC_BREAK_IF(! pCloseItem);

        //// Place the menu item bottom-right conner.
        //pCloseItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20));

        //// Create a menu with the "close" menu item, it's an auto release object.
        //CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
        //pMenu->setPosition(CCPointZero);
        //CC_BREAK_IF(! pMenu);

        //// Add the menu to HelloWorld layer as a child layer.
        //this->addChild(pMenu, 1);

        //// 2. Add a label shows "Hello World".

        //// Create a label and initialize with string "Hello World".
        //CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", 24);
        //CC_BREAK_IF(! pLabel);

        //// Get window size and place the label upper. 
        //CCSize size = CCDirector::sharedDirector()->getWinSize();
        //pLabel->setPosition(ccp(size.width / 2, size.height - 50));

        //// Add the label to HelloWorld layer as a child layer.
        //this->addChild(pLabel, 1);

        //// 3. Add add a splash screen, show the cocos2d splash image.
        //CCSprite* pSprite = CCSprite::create("HelloWorld.png");
        //CC_BREAK_IF(! pSprite);

        //// Place the sprite on the center of the screen
        //pSprite->setPosition(ccp(size.width/2, size.height/2));

        //// Add the sprite to HelloWorld layer as a child layer.
        //this->addChild(pSprite, 0);

		CCSize winSize = CCDirector::sharedDirector()->getWinSize();

		lblAccount = CCLabelTTF::create("Account:","Arial",25);
		lblAccount->setPosition(CCPointMake(100,winSize.height - 50));
		//lblAccount->SET(CCTextAlignment::kCCTextAlignmentLeft);
		addChild(lblAccount);

		m_txtAccount = CCEditBox::create(CCSizeMake(400,50),CCScale9Sprite::create("account.png"));
		m_txtAccount->setPosition(CCPointMake(250,winSize.height - 100));
		m_txtAccount->setPlaceHolder("this is account");
		addChild(m_txtAccount);

		lblPassword = CCLabelTTF::create("Password:","Arial",25);
		lblPassword->setPosition(CCPointMake(100,winSize.height - 150));
		addChild(lblPassword);

		m_txtPassword = CCEditBox::create(CCSizeMake(400,50),CCScale9Sprite::create("account.png"));
		m_txtPassword->setInputFlag(kEditBoxInputFlagPassword);
		m_txtPassword->setPosition(CCPointMake(250,winSize.height - 200));
		m_txtPassword->setPlaceHolder("this is password");
		addChild(m_txtPassword);

		CCScale9Sprite* btnNormal = CCScale9Sprite::create("btnSubmit.png");  
		CCLabelTTF *title = CCLabelTTF::create("Touch Me!", "Arial", 30);  

		btnSubmit = CCControlButton::create(title,btnNormal);
		btnSubmit->setPosition(CCPointMake(winSize.width/2,winSize.height - 290));
		btnSubmit->addTargetWithActionForControlEvents(this,cccontrol_selector(HelloWorld::submitClicked),CCControlEventTouchDown);
		addChild(btnSubmit);

        bRet = true;
    } while (0);

    return bRet;
}

void HelloWorld::submitClicked(CCObject *pSender,CCControlEvent event)
{
	CCLOG("i was clicked");
	char sAccount[20];
	char sPassword[20];
	sprintf(sAccount,m_txtAccount->getText());
	sprintf(sPassword,m_txtAccount->getText());

	this->doSubmit();


}

void HelloWorld::doSubmit()
{
	CCHttpRequest *request = new CCHttpRequest();
	request->setRequestType(CCHttpRequest::kHttpPost);
	request->setResponseCallback(this,callfuncND_selector(HelloWorld::requestFinishedCallback));
	request->setTag("post testing!!!");
	request->setUrl("http://223.4.10.91/andon_service/ANDON_EX_USER.asmx/GetList");

	const char* postData = "cid=120000&date=";
	request->setRequestData(postData,strlen(postData));
	CCHttpClient *client = CCHttpClient::getInstance();
	client->send(request);

	request->release();
}

void HelloWorld::requestFinishedCallback(CCNode* pSender,void *data)
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

void HelloWorld::parseJson()
{
	Json::Reader reader;  
	Json::Value root; 

	const char* str = "{\"uploadid\": \"UP000000\",\"code\": 100,\"msg\": \"\",\"files\": \"\"}";  
	if (reader.parse(str, root)) 
	{  
		std::string upload_id = root["uploadid"].asString();
		int code = root["code"].asInt();
	}
}

