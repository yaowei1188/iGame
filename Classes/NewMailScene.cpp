#include "NewMailScene.h"
#include "json/json.h"

using namespace cocos2d;

NewMailScene::NewMailScene()
{
    m_txtReceiver = NULL;
    m_txtSubject = NULL;
    m_txtContent = false;
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
	request->setResponseCallback(this,callfuncND_selector(NewMailScene::requestFinishedCallback));
	request->setTag("1");
    
    char url[150] = {0};
    sprintf(url,"%s/user/login/%s/%s/%s",API_URL,sReceiver.c_str(),sSubject.c_str(),sContent.c_str());
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
    
    m_txtReceiver->setFontColor(ccc3(251,255,33));
    m_txtReceiver->setFont("Arial", 14);
 
    m_txtSubject->setFontColor(ccc3(251,255,33));
    m_txtSubject->setFont("Arial", 14);
    
    m_txtContent->setFontColor(ccc3(251,255,33));
    m_txtContent->setFont("Arial", 14);
    m_txtContent->setContentSize(CCSizeMake(200, 85));
    m_txtContent->setPreferredSize(CCSizeMake(200, 85));
}

bool NewMailScene::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_txtReceiver", CCEditBox*, this->m_txtReceiver);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_txtSubject", CCEditBox*, this->m_txtSubject);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_txtContent", CCEditBox*, this->m_txtContent);
    
    return true;
}

void NewMailScene::buttonClicked(CCObject *pSender, CCControlEvent pCCControlEvent) {
    
    CCControlButton *button = (CCControlButton*) pSender;
    
    switch (button->getTag()) {
        case 101:
        {
            MainGameScene *mainScene = (MainGameScene *)this->getParent();
            mainScene->PopLayer();
        }
            break;
        case 102:
        {
            CCLOG("popup");
            this->doSubmit();
        }
            break;
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

