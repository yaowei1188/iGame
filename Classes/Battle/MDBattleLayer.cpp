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

        CC_BREAK_IF(! CCLayerColor::initWithColor(ccc4(254, 254, 254,255)));

		btnTouched = false;

//		mArrayList= CCArray::create();
//        mArrayList->retain();

//        CCSize s = CCDirector::sharedDirector()->getWinSize();
//        m_root = CCSprite::create("r1.png");
//        addChild(m_root, 1);
//        m_root->setPosition(ccp(s.width/2, s.height/2));
//
//        m_target = CCSprite::create("r1.png");
//        m_root->addChild(m_target);
//        m_target->setPosition(ccp(s.width/4, 0));
//
//        // create the streak object and add it to the scene
//        streak = CCMotionStreak::create(2, 3, 32, ccGREEN, "streak.png");
//        addChild(streak);
//        // schedule an update on each frame so we can syncronize the streak with the target
//        schedule(schedule_selector(MDBattleLayer::onUpdate));
//
//        CCActionInterval* a1 = CCRotateBy::create(2, 360);
//
//        CCAction* action1 = CCRepeatForever::create(a1);
//        CCActionInterval* motion = CCMoveBy::create(2, ccp(100,0) );
//        m_root->runAction( CCRepeatForever::create(CCSequence::create(motion, motion->reverse(), NULL) ) );
//        m_root->runAction( action1 );
//
//        CCActionInterval *colorAction = CCRepeatForever::create(CCSequence::create(
//                                                                                   CCTintTo::create(0.2f, 255, 0, 0),
//                                                                                   CCTintTo::create(0.2f, 0, 255, 0),
//                                                                                   CCTintTo::create(0.2f, 0, 0, 255),
//                                                                                   CCTintTo::create(0.2f, 0, 255, 255),
//                                                                                   CCTintTo::create(0.2f, 255, 255, 0),
//                                                                                   CCTintTo::create(0.2f, 255, 0, 255),
//                                                                                   CCTintTo::create(0.2f, 255, 255, 255),
//                                                                                   NULL));
//
//        streak->runAction(colorAction);


        SharpLabelTTF *pRet1 = new SharpLabelTTF();
        pRet1->initWithString(CCString::create("地")->getCString(), "JDJYCHAO.TTF", 50);
        pRet1->setDimensions(CCSizeMake(200, 180));
        this->addChild(pRet1);
        pRet1->setPosition(ccp(200, 300));
        pRet1->setFontFillColor(ccc3(255,255,205));
        pRet1->enableStroke(ccc3(50, 11, 1), 0.8);

        //CCLabelTTF *lblTest = SharpLabelTTF::create("TEST", "Arial", 30);
        SharpLabelTTF *pRet = new SharpLabelTTF();
        pRet->initWithString(CCString::create("地")->getCString(), "Verdana-BoldItalic", 50);
        pRet->setDimensions(CCSizeMake(200, 180));
        this->addChild(pRet);
        pRet->setPosition(ccp(200, 200));
        pRet->setFontFillColor(ccc3(255,255,205));
        pRet->enableStroke(ccc3(50, 11, 1), 0.8);
        //        pRet->enableShadow(CCSizeMake(0, 1), 0.5f, 5);

        SharpLabelTTF *pRet2 = new SharpLabelTTF();
        pRet2->initWithString(CCString::create("地")->getCString(), "Marker Felt.ttf", 50);
        pRet2->setDimensions(CCSizeMake(200, 180));
        this->addChild(pRet2);
        pRet2->setPosition(ccp(200, 100));
        pRet2->setFontFillColor(ccc3(255,255,205));
        pRet2->enableStroke(ccc3(50, 11, 1), 0.8);
        //        pRet1->enableShadow(CCSizeMake(0, 1), 0.5f, 2);

        SharpLabelTTF *pRet3 = new SharpLabelTTF();
        pRet3->initWithString(CCString::create("地")->getCString(), "simhei.ttf", 50);
        pRet3->setDimensions(CCSizeMake(200, 180));
        this->addChild(pRet3);
        pRet3->setPosition(ccp(200, 50));
        pRet3->setFontFillColor(ccc3(255,255,205));
        pRet3->enableStroke(ccc3(50, 11, 1), 0.8);

//        CC_SAFE_DELETE(pRet);

//        CCLabelTTF *lblTest2 = CCLabelTTF::create("姚伟", "Arial", 20);
//        lblTest2->setFontFillColor(ccc3(255,255,205));
//        lblTest2->setAnchorPoint(ccp(0.5,0.5));
//        lblTest2->setColor(ccc3(255,255,205));
//        lblTest2->setPosition(ccp(250, 300));
//
//        CCRenderTexture* stroke = this->createStroke(lblTest2, 1, ccc3(50, 11, 1));
//        this->addChild(lblTest2);
//        this->addChild(stroke);
        bRet = true;
    } while (0);

    return bRet;
}

CCRenderTexture* MDBattleLayer::createStroke(cocos2d::CCLabelTTF *label, float size, cocos2d::ccColor3B color)
{
    float x=label->getTexture()->getContentSize().width+size*2;
    float y=label->getTexture()->getContentSize().height+size*2;
    CCRenderTexture *rt=CCRenderTexture::create(x, y);
    CCPoint originalPos=label->getPosition();
    ccColor3B originalColor=label->getColor();
    label->setColor(color);
    ccBlendFunc originalBlend=label->getBlendFunc();
    label->setBlendFunc((ccBlendFunc){GL_SRC_ALPHA,GL_ONE});
//    CCPoint center=ccp(x/2+size, y/2+size);

    CCPoint bottomLeft = ccp(label->getTexture()->getContentSize().width * label->getAnchorPoint().x + size, label->getTexture()->getContentSize().height * label->getAnchorPoint().y + size);
    CCPoint positionOffset = ccp(label->getTexture()->getContentSize().width * label->getAnchorPoint().x - label->getTexture()->getContentSize().width/2,label->getTexture()->getContentSize().height * label->getAnchorPoint().y - label->getTexture()->getContentSize().height/2);
    CCPoint position = ccpSub(originalPos, positionOffset);

    rt->begin();
    for (int i=0; i<360; i+=30) {
        float _x=bottomLeft.x+sin(CC_DEGREES_TO_RADIANS(i))*size;
        float _y=bottomLeft.y+cos(CC_DEGREES_TO_RADIANS(i))*size;

        label->setPosition(ccp(_x, _y));
        label->visit();

    }
    rt->end();
    label->setPosition(originalPos);
    label->setColor(originalColor);
    label->setBlendFunc(originalBlend);
//    float rtX=originalPos.x-size;
//    float rtY=originalPos.y-size;

    rt->setPosition(position);

    return rt;
}

void MDBattleLayer::onUpdate(float delta)
{
    streak->setPosition( m_target->convertToWorldSpace(CCPointZero) );
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

//	this->ShowLoadingIndicator("");
//
//	CCHttpRequest *request = new CCHttpRequest();
//	request->setRequestType(CCHttpRequest::kHttpGet);
//	request->setResponseCallback(this,httpresponse_selector(MDBattleLayer::requestFinishedCallback));
//	request->setTag("101");
//    
//	string _strUrl = CompleteUrl(URL_FRIEND_SEARCH);
//	_strUrl.append(CCUserDefault::sharedUserDefault()->getStringForKey("userinfo"));
//	_strUrl.append("/");
////	_strUrl.append(sSearchField);
//
//	request->setUrl(_strUrl.c_str());
//
//	CCHttpClient *client = CCHttpClient::getInstance();
//	client->send(request);
//
//	request->release();
}

void MDBattleLayer::addFriendRequest(std::string &targetUser)
{
//	CCHttpRequest *request = new CCHttpRequest();
//	request->setRequestType(CCHttpRequest::kHttpGet);
//	request->setResponseCallback(this,httpresponse_selector(MDBattleLayer::requestFinishedCallback));
//	request->setTag("102");
//    
//	string _strUrl = CompleteUrl(URL_FRIEND_ADD_NEW);
//	_strUrl.append(CCUserDefault::sharedUserDefault()->getStringForKey("userinfo"));
//	_strUrl.append("/" + targetUser);
//
//	request->setUrl(_strUrl.c_str());
//
//	CCHttpClient *client = CCHttpClient::getInstance();
//	client->send(request);
//    
//	request->release();
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
//	CCControlButton *button = (CCControlButton *)pSender;
//	if (pCCControlEvent==CCControlEventTouchDown)
//	{
//		btnTouched = true;
//	}
//	else if (pCCControlEvent==CCControlEventTouchUpInside)
//	{
//		switch (button->getTag()) {
//		case 128:
//			{
//				btnTouched = false;
//				MainGameScene *mainScene = (MainGameScene *)this->getParent();
//				mainScene->PushLayer((CCLayer *)this->GetLayer("NewMailScene"));
//			}
//			break;
//		case 129:
//			{
//				btnTouched = false;
//				CCMessageDialog *box = CCMessageDialog::create();
//				box->setTitle(GlobalData::getLocalString("friend_add_confirm")->getCString());
//				box->setDelegate(this);
//				this->addChild(box);
//			}
//			break;
//		default:
//			break;
//		}
//	}
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

