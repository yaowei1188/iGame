#include "MDBattleLayer.h"
#include "SharpLabelTTF.h"


#define CARD_MARGIN 20
#define CARD_WIDTH 64
#define CARD_H_MARGIN 30
#define CARD_V_MARGIN 30

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

void MDBattleLayer::startPuzzle()
{
//	    CCSize s = CCDirector::sharedDirector()->getWinSize();
//	    CCSprite *m_root = CCSprite::create("Icon.png");
//	    addChild(m_root, 1);
//	    m_root->setPosition(ccp(s.width/2, s.height/2));
//	
//	    // create the streak object and add it to the scene
//	    CCMotionStreak *streak = CCMotionStreak::create(2, 3, 32, ccGREEN, "particle-snow.png");
//	    addChild(streak);
//	    // schedule an update on each frame so we can syncronize the streak with the target
//	    //schedule(schedule_selector(MDBattleLayer::onUpdate));
//	
//	    //CCActionInterval* a1 = CCRotateBy::create(2, 360);
//	
//	    //CCAction* action1 = CCRepeatForever::create(a1);
//	    CCActionInterval* motion = CCMoveBy::create(2, ccp(100,0) );
//	    m_root->runAction( CCRepeatForever::create(CCSequence::create(motion, motion->reverse(), NULL) ) );
//	    //m_root->runAction( action1 );
//	
//	    CCActionInterval *colorAction = CCRepeatForever::create(CCSequence::create(
//	                                                                                CCTintTo::create(0.2f, 255, 0, 0),
//	                                                                                CCTintTo::create(0.2f, 0, 255, 0),
//	                                                                                CCTintTo::create(0.2f, 0, 0, 255),
//	                                                                                CCTintTo::create(0.2f, 0, 255, 255),
//	                                                                                CCTintTo::create(0.2f, 255, 255, 0),
//	                                                                                CCTintTo::create(0.2f, 255, 0, 255),
//	                                                                                CCTintTo::create(0.2f, 255, 255, 255),
//	                                                                                NULL));
//	
//	    streak->runAction(CCSpawn::create(colorAction, CCRepeatForever::create(CCSequence::create(motion, motion->reverse(), NULL) ),NULL));

        CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    CCLabelTTF *label0 = CCLabelTTF::create("方正行楷繁体0123456789","MarkerFelt-Wide",12);

    label0->setPosition(ccp( size.width /2 , size.height/2 + 100 ));
    label0->setColor(ccc3(250, 249, 198));
//    label0->setFontFillColor(ccc3(252, 250, 198));
    label0->enableStroke(ccc3(23, 12, 1), 0.3);
    this->addChild(label0);
    

//    CCLabelTTF *label1 = CCLabelTTF::create("方正行楷繁体0123456789","Arial",24);
//    label1->setPosition(ccp( size.width /2 , size.height/2 - 100 ));
//    this->addChild(label1);
//
//    CCLabelTTF *label2 = CCLabelTTF::create("方正行楷繁体0123456789","SimHei",24);
//    label2->setPosition(ccp( size.width /2 , size.height/2 ));
//    this->addChild(label2);
}

void MDBattleLayer::onUpdate(float time)
{

}

// on "init" you need to initialize your instance
bool MDBattleLayer::init()
{
    bool bRet = false;
    do 
    {

        CC_BREAK_IF(! CCLayerColor::initWithColor(ccc4(255, 255, 255,255)));

		setTouchEnabled(true);

		mCardList= CCArray::create();
		mCardList->retain();

		mEnemyCardList= CCArray::create();
		mEnemyCardList->retain();
        
        mParticle = CCArray::create();
		mParticle->retain();
        
        CCDictionary *dict = CCDictionary::create();
        dict->setObject(CCString::create("myAttack1.plist"), "pname");
        dict->setObject(CCString::create("0"), "target");
        dict->setObject(CCString::create("0"), "position");
        mParticle->addObject(dict);
        
        dict = CCDictionary::create();
        dict->setObject(CCString::create("galaxy"), "pname");
        dict->setObject(CCString::create("1"), "target");
        dict->setObject(CCString::create("1"), "position");
        mParticle->addObject(dict);
        
        intCurrentCard = 0;

		mCardNameList= CCArray::create();
		mCardNameList->addObject(CCString::create("head_rulaifo.png"));
		mCardNameList->addObject(CCString::create("head_sunwukong.png"));
		mCardNameList->addObject(CCString::create("head_erlangsheng.png"));
		mCardNameList->addObject(CCString::create("head_sunwukong.png"));
		mCardNameList->addObject(CCString::create("head_rulaifo.png"));
		mCardNameList->addObject(CCString::create("head_erlangsheng.png"));
		mCardNameList->retain();

		mEnemyCardNameList = CCArray::create();
		mEnemyCardNameList->addObject(CCString::create("head_rulaifo.png"));
		mEnemyCardNameList->addObject(CCString::create("head_sunwukong.png"));
		mEnemyCardNameList->addObject(CCString::create("head_erlangsheng.png"));
		mEnemyCardNameList->addObject(CCString::create("head_rulaifo.png"));
		mEnemyCardNameList->addObject(CCString::create("head_sunwukong.png"));
		mEnemyCardNameList->addObject(CCString::create("head_erlangsheng.png"));
		mEnemyCardNameList->retain();

		prepareBackGround();

		prepareFormation();
        
        prepareEnemyFormation();

//		startPuzzle();

        bRet = true;
    } while (0);

    return bRet;
}

void MDBattleLayer::prepareBackGround()
{
	CCSprite* background = CCSprite::create("background.jpeg");

//	background->setScale( 1.5f );
	background->setAnchorPoint(ccp(0.5,0));

	CCParallaxNode* backgroundNode = CCParallaxNode::create();
	backgroundNode->setTag(103);
	backgroundNode->addChild(background, -1, ccp(0.0f,2.0f), ccp(0,-78));
	addChild( backgroundNode );

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	CCMenu *menu = CCMenu::create();
	menu->setTag(2);
	this->addChild(menu);

	//CCMenuItemFont *menuFont = CCMenuItemFont::create("逃跑",this,menu_selector(MDBattleLayer::menuCallback));
	CCLabelBMFont* label = CCLabelBMFont::create("Leave", "test.fnt");
	CCMenuItemLabel* menuFont = CCMenuItemLabel::create(label, this, menu_selector(MDBattleLayer::menuCallback));
	menuFont->setPosition(winSize.width * 0.5 - 60,winSize.height * 0.5 - 60);
	menuFont->setTag(101);
	menu->addChild(menuFont);

	CCLabelBMFont* MoveLabel = CCLabelBMFont::create("Move", "test.fnt");
	CCMenuItemLabel* menuMove = CCMenuItemLabel::create(MoveLabel, this, menu_selector(MDBattleLayer::menuCallback));
	menuMove->setPosition(0,-40);
	menuMove->setTag(102);
	menu->addChild(menuMove);
    
    CCLabelBMFont* lblFightLabel = CCLabelBMFont::create("Fight", "test.fnt");
	CCMenuItemLabel* menuFight = CCMenuItemLabel::create(lblFightLabel, this, menu_selector(MDBattleLayer::menuCallback));
	menuFight->setPosition(winSize.width * 0.5 - 60,0-winSize.height * 0.5 - 12);
	menuFight->setTag(103);
	menu->addChild(menuFight);
}

void MDBattleLayer::menuCallback(CCObject* sender) 
{
	MainGameScene *mainScene = (MainGameScene *)this->getParent();
	CCMenuItemFont *button = (CCMenuItemFont *)sender;
	switch (button->getTag()) {
	case 101:
		{
			mainScene->returnToMainLayer();
			break;
		}
	case 102:
		{
			CCMenu *menu = (CCMenu *)this->getChildByTag(2);
			CCMenuItemFont *menuLeave = (CCMenuItemFont *)menu->getChildByTag(101);
			menuLeave->setVisible(false);
			CCMenuItemFont *menuMove = (CCMenuItemFont *)menu->getChildByTag(102);
			menuMove->setVisible(false);

			for(int i=0;i<mEnemyCardList->count();i++)
			{
				MDCardPlayer *cardPlayer = (MDCardPlayer *)mEnemyCardList->objectAtIndex(i);

				cardPlayer->m_sCardPlayer->setVisible(false);
			}

			this->backgroundMoveForward();
			this->cardMoveForward();
			break;
		}
    case 103:
        {
            this->AttackEnemy();
            break;
        }
	}
}

void MDBattleLayer::AttackEnemy()
{
    srand(time(NULL));
    int enemyNum = rand()%6;
    int attackCategory = 4;//;rand()%5;
    MDCardPlayer *enmeyCardPlayer = (MDCardPlayer *)mEnemyCardList->objectAtIndex(enemyNum);
    
    MDCardPlayer *cardPlayer = (MDCardPlayer *)mCardList->objectAtIndex(intCurrentCard++);
    switch (attackCategory) {
        case 0:
        {
            cardPlayer->playMeteorEffect(enmeyCardPlayer);
            break;
        }
        case 1:
        {
            cardPlayer->playAttackAnnimation(mEnemyCardList);
            break;
        }
        case 2:
        {
            cardPlayer->playFireEffect(enmeyCardPlayer);
            break;
        }
        case 3:
        {
            cardPlayer->playEcllipseEffect(enmeyCardPlayer);
            break;
        }
		case 4:
			{
				enmeyCardPlayer->playAnnimateFrame("2200",18);
				break;
			}
        default:
            break;
    }
    
    if (intCurrentCard==6) {
        intCurrentCard = 0;
    }
}

void MDBattleLayer::prepareFormation()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	float leftcap = (winSize.width - 3 * CARD_WIDTH - 2 * CARD_H_MARGIN) * 0.5;
	int row,col;
	
	for(int i=0;i<mCardNameList->count();i++)
	{
		row = i / 3;
		col = i % 3;
		CCString *strCardName = (CCString *)mCardNameList->objectAtIndex(i);
		MDCardPlayer *cardPlayer = MDCardPlayer::create(strCardName->getCString());
		mCardList->addObject(cardPlayer);
		this->addChild(cardPlayer->m_sCardPlayer);
		cardPlayer->m_location = ccp(leftcap + CARD_H_MARGIN * col + col * CARD_WIDTH + CARD_WIDTH * 0.5,0 + CARD_MARGIN * row + row * CARD_WIDTH + CARD_WIDTH * 0.5);
		cardPlayer->m_sCardPlayer->setPosition(cardPlayer->m_location);
	}
}

void MDBattleLayer::prepareEnemyFormation()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	float leftcap = (winSize.width - 3 * CARD_WIDTH - 2 * CARD_H_MARGIN) * 0.5;
	int row,col;

	if (mEnemyCardList->count()>0)
	{
		for(int i=0;i<mEnemyCardList->count();i++)
		{
			MDCardPlayer *cardPlayer = (MDCardPlayer *)mEnemyCardList->objectAtIndex(i);

			cardPlayer->m_sCardPlayer->setVisible(true);
		}
		return;
	}

	for(int i=0;i<mEnemyCardNameList->count();i++)
	{
		row = i / 3;
		col = i % 3;
		CCString *strCardName = (CCString *)mEnemyCardNameList->objectAtIndex(i);
		if(strCardName->length()==0)
		{
			continue;
		}
		MDCardPlayer *cardPlayer = MDCardPlayer::create(strCardName->getCString());
		mEnemyCardList->addObject(cardPlayer);
		this->addChild(cardPlayer->m_sCardPlayer);
		cardPlayer->m_location = ccp(leftcap + CARD_H_MARGIN * col + col * CARD_WIDTH + CARD_WIDTH * 0.5,250 + CARD_MARGIN * row + row * CARD_WIDTH + CARD_WIDTH * 0.5);
		cardPlayer->m_sCardPlayer->setPosition(cardPlayer->m_location);
	}
}

void MDBattleLayer::cardMoveFinished(CCNode* sender)
{
//	CCSprite *sprite = (CCSprite *)sender;

	CCMenu *menu = (CCMenu *)this->getChildByTag(2);

	CCMenuItemFont *menuLeave = (CCMenuItemFont *)menu->getChildByTag(101);
	if (menuLeave->isVisible())
	{
		return;
	}
	menuLeave->setVisible(true);
	CCMenuItemFont *menuMove = (CCMenuItemFont *)menu->getChildByTag(102);
	menuMove->setVisible(true);

	this->prepareEnemyFormation();

	for(int i=0;i<mCardList->count();i++)
	{
		MDCardPlayer *cardPlayer = (MDCardPlayer *)mCardList->objectAtIndex(i);

		cardPlayer->stopAllAction();
	}
}

void MDBattleLayer::backgroundMoveForward()
{
	CCParallaxNode* backgroundNode = (CCParallaxNode*)this->getChildByTag(103);
	CCActionInterval* goUp = CCMoveBy::create(4, ccp(0,-80) );

	CCFiniteTimeAction* actionMoveDone = CCCallFuncN::create( this, callfuncN_selector(MDBattleLayer::cardMoveFinished));

	CCSequence* seq = CCSequence::create(goUp, actionMoveDone,NULL);
	backgroundNode->runAction(seq);
}

void MDBattleLayer::cardMoveForward()
{
	for(int i=0;i<mCardList->count();i++)
	{
		MDCardPlayer *cardPlayer = (MDCardPlayer *)mCardList->objectAtIndex(i);

		cardPlayer->playParadeAnnimation();
	}
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

void MDBattleLayer::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,10,true);
}

void MDBattleLayer::panForTranslation(CCPoint translation )
{
	if (m_sSelectedSprite) {
		CCPoint newPos = ccpAdd(m_sSelectedSprite->getPosition(), translation);
		m_sSelectedSprite->setPosition(newPos);
	}
}

void MDBattleLayer::selectSpriteForTouch(CCPoint touchLocation)
{
	CCSprite * newSprite = NULL;

	for(int i=0;i<mCardList->count();i++)
	{
		MDCardPlayer *cardPlayer = (MDCardPlayer *)mCardList->objectAtIndex(i);
		
		if (cardPlayer->m_sCardPlayer->boundingBox().containsPoint(touchLocation))
		{
			newSprite = cardPlayer->m_sCardPlayer;
			newSprite->setZOrder(11);
			//break;
		}
		else
		{
			cardPlayer->m_sCardPlayer->setZOrder(10);
		}
	}

	if (newSprite != m_sSelectedSprite)
	{
		m_sSelectedSprite = newSprite;
	}
}

bool MDBattleLayer::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	CCPoint touchLocation = this->convertTouchToNodeSpace(touch);
	this->selectSpriteForTouch(touchLocation);

	return true;
}

void MDBattleLayer::ccTouchCancelled(CCTouch* touch, CCEvent* event)
{

}

void MDBattleLayer::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
	if (m_sSelectedSprite) 
	{
		CCPoint touchLocation = this->convertTouchToNodeSpace(touch);
		CCPoint oldTouchLocation = touch->getPreviousLocationInView();
		oldTouchLocation = CCDirector::sharedDirector()->convertToGL(oldTouchLocation);
		oldTouchLocation = this->convertToNodeSpace(oldTouchLocation);

		CCPoint translation = ccpSub(touchLocation, oldTouchLocation);    
		this->panForTranslation(translation);   
	}
}

void MDBattleLayer::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	if (m_sSelectedSprite) 
	{
		CCPoint touchLocation = m_sSelectedSprite->getPosition();
		MDCardPlayer *_cardPlayer = (MDCardPlayer *)m_sSelectedSprite->getUserObject();
		MDCardPlayer *_nearCardPlayer = NULL;

		for(int i=0;i<mCardList->count();i++)
		{
			MDCardPlayer *_eachCardPlayer = (MDCardPlayer *)mCardList->objectAtIndex(i);
			if (_eachCardPlayer==_cardPlayer)
			{
				continue;
			}
			float length = fabs(ccpDistance(_eachCardPlayer->m_location,touchLocation));
			if (length<CARD_MARGIN)
			{
				_nearCardPlayer= _eachCardPlayer;
				break;
			}
		}

		if (_nearCardPlayer==NULL)
		{
			_cardPlayer->MoveToPosition();
			return;
		}

		this->exchangeCard(_cardPlayer,_nearCardPlayer);

		_cardPlayer->MoveToPosition();
		_nearCardPlayer->MoveToPosition();
	}
}

void MDBattleLayer::exchangeCard(MDCardPlayer *p_cardOne,MDCardPlayer *p_cardTwo)
{
	CCPoint _temp = p_cardOne->m_location;
	p_cardOne->m_location = p_cardTwo->m_location;
	p_cardTwo->m_location = _temp;

	int position = p_cardOne->position;
	p_cardOne->position = p_cardTwo->position;
	p_cardTwo->position = position;
}

MDBattleLayer::MDBattleLayer()
{
    mCardNameList = NULL;
}

MDBattleLayer::~MDBattleLayer()
{
    //mCardNameList->release();
}

