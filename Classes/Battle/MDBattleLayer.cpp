#include "MDBattleLayer.h"
#include "SharpLabelTTF.h"

CCScene* MDBattleLayer::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        MDBattleLayer *layer = MDBattleLayer::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MDBattleLayer::init()
{
    bool bRet = false;
    do 
    {
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////

        CC_BREAK_IF(! CCLayer::init());
        
		btnTouched = false;

		mArrayList= CCArray::create();
        mArrayList->retain();

        

        //CCLabelTTF *lblTest = SharpLabelTTF::create("TEST", "Arial", 30);
        SharpLabelTTF *pRet = new SharpLabelTTF();
        pRet->initWithString(CCString::create("姚伟\n伟")->getCString(), "Verdana-BoldItalic", 20);
        pRet->setDimensions(CCSizeMake(200, 100));
        this->addChild(pRet);
        pRet->setPosition(ccp(200, 200));
        pRet->setFontFillColor(ccc3(255,255,0));
//        pRet->enableStroke(ccc3(255, 0, 0), 0.3);
        pRet->enableShadow(CCSizeMake(0, 1), 0.5f, 5);

//        CC_SAFE_DELETE(pRet);

        
        
        bRet = true;
    } while (0);

    return bRet;
}

void MDBattleLayer::buttonClicked(CCObject *pSender,CCControlEvent event)
{
	CCLOG("i was clicked");
    
	MainGameScene *mainScene = (MainGameScene *)this->getParent();
	CCControlButton *button = (CCControlButton *)pSender;
	switch (button->getTag()) {
	case 101:
		CCLOG("11111");
		mainScene->PopLayer();
		break;
	case 102:
		mainScene->PopLayer();
		break;
	case 103:
		this->doSearchFriend();
		break;
	}
}

void MDBattleLayer::doSearchFriend()
{

	this->ShowLoadingIndicator("");

	CCHttpRequest *request = new CCHttpRequest();
	request->setRequestType(CCHttpRequest::kHttpGet);
	request->setResponseCallback(this,httpresponse_selector(MDBattleLayer::requestFinishedCallback));
	request->setTag("101");
    
	string _strUrl = CompleteUrl(URL_FRIEND_SEARCH);
	_strUrl.append(CCUserDefault::sharedUserDefault()->getStringForKey("userinfo"));
	_strUrl.append("/");
//	_strUrl.append(sSearchField);

	request->setUrl(_strUrl.c_str());

	CCHttpClient *client = CCHttpClient::getInstance();
	client->send(request);

	request->release();
}

void MDBattleLayer::addFriendRequest(std::string &targetUser)
{
	CCHttpRequest *request = new CCHttpRequest();
	request->setRequestType(CCHttpRequest::kHttpGet);
	request->setResponseCallback(this,httpresponse_selector(MDBattleLayer::requestFinishedCallback));
	request->setTag("102");
    
	string _strUrl = CompleteUrl(URL_FRIEND_ADD_NEW);
	_strUrl.append(CCUserDefault::sharedUserDefault()->getStringForKey("userinfo"));
	_strUrl.append("/" + targetUser);

	request->setUrl(_strUrl.c_str());

	CCHttpClient *client = CCHttpClient::getInstance();
	client->send(request);
    
	request->release();
}

void MDBattleLayer::requestFinishedCallback(CCHttpClient* client, CCHttpResponse* response)
{
//	if (!this->ValidateResponseData(client,response))
//	{
//		return;
//	}
//    
//    std::vector<char> *buffer = response->getResponseData();
//	std::string content(buffer->begin(),buffer->end());
//    
//	CCDictionary * dictionary = CCJSONConverter::sharedConverter()->dictionaryFrom(content.c_str());
//	int code = ((CCNumber *)dictionary->objectForKey("code"))->getIntValue();
//	if (code != 200) {
//		if (code == 121) {
//			 CCMessageBox(GlobalData::getLocalString("friend_add_exist")->getCString(),"Success");
//		}
//		
//		return;
//	}
//    
//    std::string requestTag(response->getHttpRequest()->getTag());
//    
//    if (requestTag == "101") {
//		mFriendList->removeAllObjects();
//		CCDictionary * friendDictionary = dynamic_cast<CCDictionary *>(dictionary->objectForKey("searchUserAccount"));
//		if (friendDictionary != NULL)
//		{
//			  mFriendList->addObject(friendDictionary);
//		}
//    } else if (requestTag == "102"){
//       CCMessageBox(GlobalData::getLocalString("friend_add_success")->getCString(),"Success");
//    }
}

void MDBattleLayer::onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader)
{

}

bool MDBattleLayer::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
//    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mTableViewFriend", CCTableView*, this->mTableViewFriend);
    return true;
}

void MDBattleLayer::toolBarTouchDownAction(CCObject *pSender, CCControlEvent pCCControlEvent) {
	CCControlButton *button = (CCControlButton *)pSender;
	if (pCCControlEvent==CCControlEventTouchDown)
	{
		btnTouched = true;
	}
	else if (pCCControlEvent==CCControlEventTouchUpInside)
	{
		switch (button->getTag()) {
		case 128:
			{
				btnTouched = false;
				MainGameScene *mainScene = (MainGameScene *)this->getParent();
				mainScene->PushLayer((CCLayer *)this->GetLayer("NewMailScene"));
			}
			break;
		case 129:
			{
				btnTouched = false;
				CCMessageDialog *box = CCMessageDialog::create();
				box->setTitle(GlobalData::getLocalString("friend_add_confirm")->getCString());
				box->setDelegate(this);
				this->addChild(box);
			}
			break;
		default:
			break;
		}
	}
}

void MDBattleLayer::didClickButton(CCMessageDialog* dialog,unsigned int index)
{
	if (index == 0)
	{

	}
}

SEL_MenuHandler MDBattleLayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
//	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "menuBarBtnClicked:", LoginScene::menuBarBtnClicked);
    
	return NULL;
}

SEL_CCControlHandler MDBattleLayer::onResolveCCBCCControlSelector(CCObject *pTarget, const char * pSelectorName) {
    
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "buttonClicked:", MDBattleLayer::buttonClicked);
	return NULL;
}

MDBattleLayer::MDBattleLayer()
{
    mArrayList = NULL;
}

MDBattleLayer::~MDBattleLayer()
{
    mArrayList->release();
}

