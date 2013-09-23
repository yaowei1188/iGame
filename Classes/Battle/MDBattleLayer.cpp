#include "MDBattleLayer.h"
#include "SharpLabelTTF.h"


#define CARD_MARGIN 20
#define CARD_WIDTH 64
#define CARD_H_MARGIN 30
#define CARD_V_MARGIN 15
#define CARD_BOTTOM_MARGIN 10

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

        CC_BREAK_IF(! CCLayerColor::initWithColor(ccc4(0, 0, 0,255)));

		setTouchEnabled(true);

		m_intRound = -1;

		m_intWhoAttack = 0;

		//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("art_head.plist");

		mHeroCardList= CCArray::create();
		mHeroCardList->retain();

		mEnemyCardList= CCArray::create();
		mEnemyCardList->retain();
        
  //      mParticle = CCArray::create();
		//mParticle->retain();
  //      
  //      CCDictionary *dict = CCDictionary::create();
  //      dict->setObject(CCString::create("myAttack1.plist"), "pname");
  //      dict->setObject(CCString::create("0"), "target");
  //      dict->setObject(CCString::create("0"), "position");
  //      mParticle->addObject(dict);
  //      
  //      dict = CCDictionary::create();
  //      dict->setObject(CCString::create("galaxy"), "pname");
  //      dict->setObject(CCString::create("1"), "target");
  //      dict->setObject(CCString::create("1"), "position");
  //      mParticle->addObject(dict);
        
        intCurrentHeroCard = 0;
		intCurrentEnemyCard = 0;

		mHeroList = GlobalData::getAllCardProfile();
		mHeroList->retain();

		CCLOG("count=%d",mHeroList->count());

		mCardNameList= CCArray::create();
		CardQueryCriteria *query = new CardQueryCriteria();
		query->cardName = "ft001_2;ft003_2;ft004_2;ft005_2;ft006_2;ft017_2";
		mCardNameList= GlobalData::getAllCardProfile(query);
		//mCardNameList->addObject(CCString::create("head_rulaifo.png"));
		//mCardNameList->addObject(CCString::create("head_sunwukong.png"));
		//mCardNameList->addObject(CCString::create("head_erlangsheng.png"));
		//mCardNameList->addObject(CCString::create("head_sunwukong.png"));
		//mCardNameList->addObject(CCString::create("head_rulaifo.png"));
		//mCardNameList->addObject(CCString::create("head_erlangsheng.png"));
		mCardNameList->retain();

		prepareBackGround();

		prepareFormation();



//		startPuzzle();

        bRet = true;
    } while (0);

    return bRet;
}

void MDBattleLayer::playWinAction()
{
	CCSprite *sprite = CCSprite::create("base.png");
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	sprite->setPosition(ccp(winSize.width * 0.5,winSize.height * 0.5 - 20));
	this->addChild(sprite);

	CCFiniteTimeAction* _removeCallBack = CCCallFuncN::create(this, callfuncN_selector(MDBattleLayer::removeNodeCallBack));
	CCSequence *seq = CCSequence::create(CCRotateBy::create(3.0,360.0),_removeCallBack,NULL);

	sprite->runAction(seq);
}

void MDBattleLayer::removeNodeCallBack(CCNode* pNode)
{
	pNode->removeFromParentAndCleanup(true);
}

void MDBattleLayer::prepareBackGround()
{
	/*CCSprite* background = CCSprite::create("background.jpeg");*/
	CCSprite* background = CCSprite::create("transparent.png");

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

	/*CCLabelBMFont* label = CCLabelBMFont::create("Leave", "test.fnt");*/
	CCLabelTTF *leaveLabel = CCLabelTTF::create("逃跑","Arial",20);
	CCMenuItemLabel* menuFont = CCMenuItemLabel::create(leaveLabel, this, menu_selector(MDBattleLayer::menuCallback));
	menuFont->setPosition( -100,-40);
	menuFont->setTag(101);
	menu->addChild(menuFont);

	//CCLabelBMFont* MoveLabel = CCLabelBMFont::create("前进", "test.fnt");
	CCLabelTTF *MoveLabel = CCLabelTTF::create("前进","Arial",20);
	CCMenuItemLabel* menuMove = CCMenuItemLabel::create(MoveLabel, this, menu_selector(MDBattleLayer::menuCallback));
	menuMove->setPosition(0,-40);
	menuMove->setTag(102);
	menu->addChild(menuMove);

	//CCSprite *sprite = CCSprite::create("di.jpg");
	//this->setPosition(ccp(winSize.width * 0.5,winSize.height * 0.5));
	//this->addChild(sprite);
    
 //   CCLabelBMFont* lblFightLabel = CCLabelBMFont::create("Fight", "test.fnt");
	//CCMenuItemLabel* menuFight = CCMenuItemLabel::create(lblFightLabel, this, menu_selector(MDBattleLayer::menuCallback));
	//menuFight->setPosition(winSize.width * 0.5 - 60, -40);
	//menuFight->setTag(103);
	//menu->addChild(menuFight);
}

void MDBattleLayer::showRoundInfo() 
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	if (m_lblRoundInfo==NULL)
	{
		m_lblRoundInfo = CCLabelTTF::create("","Marker Felt",30);
		this->addChild(m_lblRoundInfo);
	}
	m_lblRoundInfo->setVisible(true);
	m_lblRoundInfo->setPosition(ccp(0,size.height * 0.5 - 30));
	if (m_intRound==0) {
		m_lblRoundInfo->setString("第一波敌人来袭！");
	} else if(m_intRound == 1) {
		m_lblRoundInfo->setString("第二波敌人来袭！");
	} else if(m_intRound == 2) {
		m_lblRoundInfo->setString("BOSS");
	}
	
	CCMoveBy *_moveRight= CCMoveBy::create(0.3,ccp(size.width * 0.5,0));
	CCDelayTime *_delayTime1 = CCDelayTime::create(1.0);
	CCMoveBy *_moveRight1= CCMoveBy::create(0.3,ccp(size.width * 0.5,0));
	CCHide *_hideAction = CCHide::create();
	m_lblRoundInfo->runAction(CCSequence::create(_moveRight,_delayTime1,_moveRight1,_hideAction,NULL));
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

			//for(int i=0;i<mEnemyCardList->count();i++)
			//{
			//	MDCardPlayer *cardPlayer = (MDCardPlayer *)mEnemyCardList->objectAtIndex(i);

			//	cardPlayer->m_sCardPlayer->setVisible(false);
			//}

			this->backgroundMoveForward();
			this->cardMoveForward();
			break;
		}
    //case 103:
    //    {
    //        this->playHeroAction();
    //        break;
    //    }
	}
}

void MDBattleLayer::prepareMoveForward()
{
	CCMenu *menu = (CCMenu *)this->getChildByTag(2);
	CCMenuItemFont *menuLeave = (CCMenuItemFont *)menu->getChildByTag(101);
	menuLeave->setVisible(true);
	CCMenuItemFont *menuMove = (CCMenuItemFont *)menu->getChildByTag(102);
	menuMove->setVisible(true);

	for(int i=0;i<mEnemyCardList->count();i++)
	{
		MDCardPlayer *cardPlayer = (MDCardPlayer *)mEnemyCardList->objectAtIndex(i);

		cardPlayer->m_sCardPlayer->setVisible(false);
	}
}

int MDBattleLayer::getNextVictim(CCArray *array)
{
	CCArray *randomArray =  CCArray::create();
	for(int i=0;i<array->count();i++)
	{
		MDCardPlayer *player = (MDCardPlayer *)array->objectAtIndex(i);
		if (player->isDead)
		{
			continue;
		}
		randomArray->addObject(CCNumber::create(i));
	}
	if (randomArray->count()==0)
	{
		return -1;
	}
	srand(time(NULL));
	int num = rand()%randomArray->count();
	return ((CCNumber *)randomArray->objectAtIndex(num))->getIntValue();
}

int MDBattleLayer::getNextPresenter(CCArray *array,int *num)
{
	MDCardPlayer *player = (MDCardPlayer *)array->objectAtIndex(*num);
	while(player->isDead) {
		*num = *num + 1;
		if (*num == array->count()) {
			*num = 0;
		}
		player = (MDCardPlayer *)array->objectAtIndex(*num);
	}
	int returnNum = *num;
	*num = returnNum + 1;
	if (*num == array->count()) {
		*num = 0;
	}
	return returnNum;
}

void MDBattleLayer::playEnemyAction()
{
	int num = getNextVictim(mHeroCardList);
	if (num==-1)
	{
		return;
	}
	int attackCategory = rand()%3;
	MDCardPlayer *heroCardPlayer = (MDCardPlayer *)mHeroCardList->objectAtIndex(num);

	int presenterNum = this->getNextPresenter(mEnemyCardList,&intCurrentEnemyCard);
	MDCardPlayer *enemyCardPlayer = (MDCardPlayer *)mEnemyCardList->objectAtIndex(presenterNum);
	CCDictionary *dictFormation = enemyCardPlayer->getFormation();
	CardCategory category = (CardCategory)((CCString *)dictFormation->objectForKey("Category"))->intValue();

	switch	(category) {
	case CardCategoryAttack:
		{
			switch (attackCategory) {
			case 0:
				{
					enemyCardPlayer->playMeteorEffect(heroCardPlayer);
					break;
				}
			case 1:
				{
					enemyCardPlayer->playFireEffect(heroCardPlayer);
					break;
				}
			case 2:
				{
					enemyCardPlayer->playAttackAnnimateFrame(heroCardPlayer);
					break;
				}
			//case 3:
			//	{
			//		enemyCardPlayer->playRainAnnimation(mHeroCardList);
			//		break;
			//	}
			default:
				break;
			}
			break;
		}
	case CardCategoryDefence:
		{
			int enemyCardNum = getNextVictim(mEnemyCardList);
			MDCardPlayer *randomEnemyCardPlayer = (MDCardPlayer *)mEnemyCardList->objectAtIndex(enemyCardNum);
			enemyCardPlayer->playEcllipseEffect(randomEnemyCardPlayer);
			break;
		}
	case CardCategoryAssist:
		{
			int enemyCardNum = getNextVictim(mEnemyCardList);
			MDCardPlayer *randomEnemyCardPlayer = (MDCardPlayer *)mEnemyCardList->objectAtIndex(enemyCardNum);
			enemyCardPlayer->playAssistAnnimateFrame(randomEnemyCardPlayer);
			break;
		}
	default:
		break;
	}

	actionFinished = false;
}

void MDBattleLayer::playHeroAction()
{
	int num = getNextVictim(mEnemyCardList);
	if (num==-1)
	{
		return;
	}

    int attackCategory = rand()%5;
    MDCardPlayer *enmeyCardPlayer = (MDCardPlayer *)mEnemyCardList->objectAtIndex(num);
    
	int presenterNum = this->getNextPresenter(mHeroCardList,&intCurrentHeroCard);

    MDCardPlayer *cardPlayer = (MDCardPlayer *)mHeroCardList->objectAtIndex(presenterNum);
    switch (attackCategory) {
        case 0:
			{
				cardPlayer->playMeteorEffect(enmeyCardPlayer);
				break;
			}
        case 1:
			{
				cardPlayer->playFireEffect(enmeyCardPlayer);
				break;
			}
        case 2:
			{
				int myCardNum = getNextVictim(mHeroCardList);
				MDCardPlayer *myCardPlayer = (MDCardPlayer *)mHeroCardList->objectAtIndex(myCardNum);
				cardPlayer->playEcllipseEffect(myCardPlayer);
				break;
			}
		case 3:
			{

				cardPlayer->playAttackAnnimateFrame(enmeyCardPlayer);
				break;
			}
		case 4:
			{
				int myCardNum = getNextVictim(mHeroCardList);
				MDCardPlayer *myCardPlayer = (MDCardPlayer *)mHeroCardList->objectAtIndex(myCardNum);
				cardPlayer->playAssistAnnimateFrame(myCardPlayer);
				break;
			}
		//case 5:
		//	{
		//		cardPlayer->playRainAnnimation(mEnemyCardList);
		//		break;
		//	}
        default:
            break;
    }
    
    if (intCurrentHeroCard == mHeroCardList->count()) {
        intCurrentHeroCard = 0;
    }

	actionFinished = false;
}

void MDBattleLayer::didActionFinished(MDCardPlayer* player)
{
	CCLOG("didActionFinished");
	if (actionFinished)
	{
		return;
	}
	actionFinished = true;

	this->doBattle();
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

		CCDictionary *dictHero = (CCDictionary *)mCardNameList->objectAtIndex(i);
		//std::string strCardHeadName(((CCString *)dictHero->objectForKey("cardHeadImg"))->getCString());
		//strCardHeadName.append(".png");

		std::string strCardHeadName("art/art_head/");
		strCardHeadName.append(((CCString *)dictHero->objectForKey("cardHeadImg"))->getCString());
		strCardHeadName.append(".png");

		MDCardPlayer *cardPlayer = MDCardPlayer::create(strCardHeadName);
		mHeroCardList->addObject(cardPlayer);
		cardPlayer->setCardData(dictHero);
		cardPlayer->side = 0;
		this->addChild(cardPlayer->m_sCardPlayer);
		cardPlayer->m_location = ccp(leftcap + CARD_H_MARGIN * col + col * CARD_WIDTH + CARD_WIDTH * 0.5,CARD_BOTTOM_MARGIN + CARD_V_MARGIN * row + row * CARD_WIDTH + CARD_WIDTH * 0.5);
		cardPlayer->m_sCardPlayer->setPosition(cardPlayer->m_location);
		cardPlayer->setDelegate(this);
	}
}

void MDBattleLayer::prepareEnemyFormation()
{
	CCArray *allEnemyFormation = GlobalData::getEnemyFormation(-1);
	CCDictionary *dictFormation = (CCDictionary *)allEnemyFormation->objectAtIndex(m_intRound);
	CCArray *enemyFormation  = (CCArray *)dictFormation->objectForKey("Formation");

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	float leftcap = (winSize.width - 3 * CARD_WIDTH - 2 * CARD_H_MARGIN) * 0.5;
	int row,col;

	m_intEnemyCount = enemyFormation->count();

	srand(time(NULL));

	for(int i=0;i< m_intEnemyCount;i++)
	{
		CCDictionary *dictFormation = (CCDictionary *)enemyFormation->objectAtIndex(i);
		int position = ((CCString *)dictFormation->objectForKey("Position"))->intValue();

		row = position / 3;
		col = position % 3;

		int idx = rand()%(mHeroList->count());
		CCDictionary *dictHero = (CCDictionary *)mHeroList->objectAtIndex(idx);

		//std::string strCardHeadName(((CCString *)dictHero->objectForKey("cardHeadImg"))->getCString());
		//strCardHeadName.append(".png");


		std::string strCardHeadName("art/art_head/");
		strCardHeadName.append(((CCString *)dictHero->objectForKey("cardHeadImg"))->getCString());
		strCardHeadName.append(".png");

		MDCardPlayer *cardPlayer = MDCardPlayer::create(strCardHeadName);
		mEnemyCardList->addObject(cardPlayer);
		cardPlayer->setFormation(dictFormation);
		cardPlayer->setCardData(dictHero);
		cardPlayer->side = 1;

		this->addChild(cardPlayer->m_sCardPlayer);
		cardPlayer->m_location = ccp(leftcap + CARD_H_MARGIN * col + col * CARD_WIDTH + CARD_WIDTH * 0.5,winSize.height - CARD_BOTTOM_MARGIN - CARD_V_MARGIN * row - row * CARD_WIDTH - CARD_WIDTH * 0.5);
		cardPlayer->m_sCardPlayer->setPosition(cardPlayer->m_location);
		cardPlayer->setDelegate(this);
	}
}

void MDBattleLayer::cardMoveFinished(CCNode* sender)
{
	CCMenu *menu = (CCMenu *)this->getChildByTag(2);

	CCMenuItemFont *menuLeave = (CCMenuItemFont *)menu->getChildByTag(101);
	if (menuLeave->isVisible())
	{
		return;
	}
	menuLeave->setVisible(false);
	CCMenuItemFont *menuMove = (CCMenuItemFont *)menu->getChildByTag(102);
	menuMove->setVisible(false);

	m_intRound ++;

	//this->showRoundInfo(NULL);

	//this->prepareEnemyFormation();

	//this->doBattle();
}

void MDBattleLayer::doBattle()
{
	BattleWinerSide winner = determineWinner();

	if (winner == BattleWinner_Heros)
	{
		if (m_intRound < 2)
		{
			prepareMoveForward();
		}
		else
		{
			playWinAction();
		}

		return;
	}

	if (winner == BattleWinner_Enemy)
	{
		return;
	}

	if (m_intWhoAttack==0)
	{
		this->playHeroAction();
		m_intWhoAttack = 1;
	} 
	else if(m_intWhoAttack==1) 
	{
		this->playEnemyAction();
		m_intWhoAttack = 0;
	}
}

BattleWinerSide MDBattleLayer::determineWinner()
{
	bool haveSurvive = false;
	for(int i=0;i<mEnemyCardList->count();i++)
	{
		MDCardPlayer *cardPlayer = (MDCardPlayer *)mEnemyCardList->objectAtIndex(i);

		if (!cardPlayer->isDead)
		{
			haveSurvive = true;
			break;;
		}
	}

	if (!haveSurvive)
	{
		return BattleWinner_Heros;
	}

	haveSurvive = false;
	for(int i=0;i<mHeroCardList->count();i++)
	{
		MDCardPlayer *cardPlayer = (MDCardPlayer *)mHeroCardList->objectAtIndex(i);

		if (!cardPlayer->isDead)
		{
			haveSurvive = true;
			break;;
		}
	}

	if (!haveSurvive)
	{
		return BattleWinner_Enemy;
	}

	return BattleWinner_None;
}

void MDBattleLayer::backgroundMoveForward()
{
	CCParallaxNode* backgroundNode = (CCParallaxNode*)this->getChildByTag(103);
	CCActionInterval* goUp = CCMoveBy::create(2.0, ccp(0,-40) );
	CCDelayTime *_delayTime = CCDelayTime::create(1.0);
	CCDelayTime *_delayTime1 = CCDelayTime::create(2.0);

	CCFiniteTimeAction* _showRoundInfoAction = CCCallFunc::create(this,callfunc_selector(MDBattleLayer::showRoundInfo));

	CCFiniteTimeAction* _prepareEnemyFormationAction = CCCallFunc::create(this,callfunc_selector(MDBattleLayer::prepareEnemyFormation));

	CCFiniteTimeAction* actionMoveDone = CCCallFuncN::create( this, callfuncN_selector(MDBattleLayer::cardMoveFinished));

	CCFiniteTimeAction* _doBattleAction = CCCallFunc::create(this,callfunc_selector(MDBattleLayer::doBattle));

	CCSequence* seq = CCSequence::create(goUp, _delayTime,actionMoveDone,_showRoundInfoAction,_delayTime,_prepareEnemyFormationAction,_delayTime1,_doBattleAction,NULL);
	backgroundNode->runAction(seq);
}

void MDBattleLayer::cardMoveForward()
{
	for(int i=0;i<mHeroCardList->count();i++)
	{
		MDCardPlayer *cardPlayer = (MDCardPlayer *)mHeroCardList->objectAtIndex(i);
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

	for(int i=0;i<mHeroCardList->count();i++)
	{
		MDCardPlayer *cardPlayer = (MDCardPlayer *)mHeroCardList->objectAtIndex(i);
		
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

		for(int i=0;i<mHeroCardList->count();i++)
		{
			MDCardPlayer *_eachCardPlayer = (MDCardPlayer *)mHeroCardList->objectAtIndex(i);
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
	m_lblRoundInfo = NULL;
}

MDBattleLayer::~MDBattleLayer()
{
    //mCardNameList->release();
}

