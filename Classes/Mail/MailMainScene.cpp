#include "MailMainScene.h"

using namespace cocos2d;

CCScene* MailMainScene::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        MailMainScene *layer = MailMainScene::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MailMainScene::init()
{
    selectedindex = -1;
    
    bool bRet = false;
    do 
    {

        CC_BREAK_IF(! CCLayer::init());
        
		//mFriendList =  CCArray::create();
        //mFriendList = CCArray::create(CCString::create("Li1"),CCString::create("张三"),CCString::create("Li3"),CCString::create("李四"),CCString::create("Li1653"),CCString::create("Li1qwe"),CCString::create("Li1"),CCString::create("Li1"),CCString::create("Li409"),CCString::create("Li134"),CCString::create("Li51"),CCString::create("Li18974523"),CCString::create("Li1"),CCString::create("Li1"),CCString::create("Li1"),CCString::create("Li1"),CCString::create("Li1"),CCString::create("Li124"),CCString::create("Li1998"),CCString::create("Li3561"),NULL);
        //mFriendList->retain();

        bRet = true;
    } while (0);

    return bRet;
}

//void MailMainScene::doSearchFriend()
//{
//	this->ShowLoadingIndicator("");
//
//	CCHttpRequest *request = new CCHttpRequest();
//	request->setRequestType(CCHttpRequest::kHttpGet);
//	request->setResponseCallback(this,httpresponse_selector(MailMainScene::requestFinishedCallback));
//	request->setTag("101");
//
//    string _strUrl = CompleteUrl(URL_FRIEND_LIST);
//    _strUrl.append(CCUserDefault::sharedUserDefault()->getStringForKey("userinfo"));
//
//	request->setUrl(_strUrl.c_str());
//
//	CCHttpClient *client = CCHttpClient::getInstance();
//	client->send(request);
//
//	request->release();
//}
//
//void MailMainScene::requestFinishedCallback(CCHttpClient* client, CCHttpResponse* response)
//{
//	if (!this->ValidateResponseData(client,response))
//	{
//		return;
//	}
//    
//	std::vector<char> *buffer = response->getResponseData();
//	std::string content(buffer->begin(),buffer->end());
//
//    CCDictionary * dictionary = CCJSONConverter::sharedConverter()->dictionaryFrom(content.c_str());
//	int code = ((CCNumber *)dictionary->objectForKey("code"))->getIntValue();
//    if (code != 200) {
//        CCMessageBox("invoke web api failed!","ERROR");
//        return;
//    }
//
//	std::string requestTag(response->getHttpRequest()->getTag());
//
//	if (requestTag == "101") {
//		mFriendList = dynamic_cast<CCArray *>(dictionary->objectForKey("friendList"));
//		if (mFriendList==NULL)
//		{
//			return;
//		}
//
//		selectedindex = -1;
//		//mTableView->reloadData();
//	} else if (requestTag == "102"){
//		this->doSearchFriend();
//		CCMessageBox("delete friend successfully","Success");
//	}
//}

bool MailMainScene::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{

    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_lblPage", CCLabelTTF*, this->m_lblPage);
    return true;
}

SEL_MenuHandler MailMainScene::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
	return NULL;
}

SEL_CCControlHandler MailMainScene::onResolveCCBCCControlSelector(CCObject *pTarget, const char * pSelectorName) {
    
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "buttonClicked:", MailMainScene::buttonClicked);
	return NULL;
}

void MailMainScene::onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader)
{
    this->setFntTitle(101);
    this->setFntTitle(102);
    this->setFntTitle(103);

	m_mailTab = new CCTabView(CCRectMake(0, 80, 320, 300));
	m_mailTab->autorelease();

	MailListScene * _layMail = MailListScene::create();
	_layMail->setTag(0);
	_layMail->retain();
	//CCLabelTTF * lbl = CCLabelTTF::create("tab1","Thonburi",18);
	//lbl->setPosition(ccp(50,50));
	//_layMail->addChild(lbl);

	SysMailListScene * _laySysMail = SysMailListScene::create();
	_laySysMail->setTag(1);
	_laySysMail->retain();
	//CCLabelTTF * lbl1 = CCLabelTTF::create("tab2","Thonburi",18);
	//lbl1->setPosition(ccp(50,50));
	//_laySysMail->addChild(lbl1);

	m_mailTab->addTab("tab1","mail_tab_secret.png","mail_tab_secret_selected.png", _layMail);
	m_mailTab->addTab("tab2","mail_tab_sys_mail.png","mail_tab_sys_mail_selected.png", _laySysMail);
	this->addChild(m_mailTab);
}

//void MailMainScene::didClickButton(CCMessageDialog* dialog,unsigned int index)
//{
//	if (index == 0)
//	{
//		CCDictionary *dict = (CCDictionary *)mFriendList->objectAtIndex(selectedindex);
//        string encryptedUserInfo(dict->valueForKey("encryptedUserInfo")->getCString());
//		this->deleteFriend(encryptedUserInfo);
//	}
//}

void MailMainScene::doDeleteAction()
{
	int selectedTab = m_mailTab->getSelectedTab();
	if (selectedTab==0) {
		MailListScene *mailLayer = (MailListScene *)m_mailTab->getSelectedLayer();
		mailLayer->deleteEntrys();
	} else if (selectedTab==1) {
		SysMailListScene *mailLayer = (SysMailListScene *)m_mailTab->getSelectedLayer();
		mailLayer->deleteEntrys();
	}
}

void MailMainScene::buttonClicked(CCObject * sender , CCControlEvent controlEvent)
{
	MainGameScene *mainScene = (MainGameScene *)this->getParent();
	CCControlButton *button = (CCControlButton *)sender;
	switch (button->getTag()) {
	case 101:
		{
			mainScene->PushLayer((CCLayer *)this->GetLayer("NewMailScene"));
			break;
		}
	case 102:
		{
			mainScene->PopLayer();
			break;
		}
	case 103:
		{
			this->doDeleteAction();
			break;
		}
	}
}

MailMainScene::MailMainScene()
{
    //mTableView = NULL;
    m_lblPage = NULL;
    mFriendList = NULL;
}

MailMainScene::~MailMainScene()
{
//    mTableViewFriend->release();
//    mMainSceneTemp->release();
//    mFriendList->release();
}

