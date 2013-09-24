#include "CharacterScene.h"
//#include "JsonBox.h"

using namespace cocos2d;

#define ELLIPSE_WIDTH 90
#define ELLIPSE_HEIGHT 20
#define START_ANGLE 2 * M_PI * 3/4

CharacterScene::CharacterScene()
{
    m_txtAccount = NULL;
	m_sCharacterBelow = NULL;
    m_lblCharacterName = NULL;
    m_lblCharacterDesc = NULL;
    m_lblHp = NULL;
    m_lblDefence = NULL;
    m_lblAttack = NULL;
    m_lblAvoid = NULL;
    m_sValueBg = NULL;
}

CharacterScene::~CharacterScene()
{
	CC_SAFE_RELEASE(m_sCharacterBelow);
    CC_SAFE_RELEASE(m_lblCharacterName);
    CC_SAFE_RELEASE(m_lblCharacterDesc);
    CC_SAFE_RELEASE(m_lblHp);
    CC_SAFE_RELEASE(m_lblDefence);
    CC_SAFE_RELEASE(m_lblAttack);
    CC_SAFE_RELEASE(m_lblAvoid);
    CC_SAFE_RELEASE(m_sValueBg);
}

CCScene* CharacterScene::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        CharacterScene *layer = CharacterScene::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool CharacterScene::init()
{
    bool bRet = false;
    do 
    {
        CC_BREAK_IF(! CCLayer::init());

		mCardList = CCArray::create();
		mCardList->retain();

		mCardNameList = CCArray::create();
		mCardNameList->retain();

        /*CCArray *allCardArray = GlobalData::getAllCards("");*/
		CCArray *allCardArray = GlobalData::getCardProfile(-1);

        CCObject *obj = NULL;
        CCARRAY_FOREACH(allCardArray,obj)
        {
            CCDictionary *dict = (CCDictionary *)obj;
            mCardNameList->addObject(dict);
        }

		selectedIndex = 0;
        
        bRet = true;
    } while (0);

    return bRet;
}

void CharacterScene::doSubmit()
{
	std::string sAccount(trimRight(m_txtAccount->getText()));

	if (sAccount.empty() ) {
		CCMessageBox(GlobalData::getLocalString("character_name_empty")->getCString(),"ERROR");
		return;
	}
    if (sAccount.length()>16 ) {
		CCMessageBox(GlobalData::getLocalString("character_name_length")->getCString(),"ERROR");
		return;
	}

 //   this->OpenNewScene("MainGameScene");
	//return;

	this->ShowLoadingIndicator("");

	CCHttpRequest *request = new CCHttpRequest();
	request->setRequestType(CCHttpRequest::kHttpPost);
	request->setResponseCallback(this,httpresponse_selector(CharacterScene::requestFinishedCallback));
	request->setTag("101");

	std::string strPostData = "encryptedUserInfo=";
	strPostData.append(CCUserDefault::sharedUserDefault()->getStringForKey("userinfo"));
	strPostData.append("&gameRoleId=");

	CCDictionary *dict = (CCDictionary *)mCardNameList->objectAtIndex(selectedIndex);
	CCString *strCardId = (CCString *)dict->objectForKey("CardId");

	strPostData.append(strCardId->getCString());
	strPostData.append("&nickname=");
	strPostData.append(sAccount);

	request->setRequestData(strPostData.c_str(), strPostData.length()); 
	
	string _strUrl = CompleteUrl(URL_USER_CREATE_ROLE);
	request->setUrl(_strUrl.c_str());

	CCHttpClient *client = CCHttpClient::getInstance();
	client->send(request);

	request->release();
}

std::string CharacterScene::addReturnForName(CCString *cardName)
{
    std::string text = cardName->m_sString;
    std::string result;
    for(int i=0;i<text.length();i++)
    {
        result.append(1,text[i]);
        result.append("\n");
    }
    return result;
}

void CharacterScene::requestFinishedCallback(CCHttpClient* client, CCHttpResponse* response)
{
	if (!this->ValidateResponseData(client,response))
	{
		return;
	}
    
	std::vector<char> *buffer = response->getResponseData();
	std::string content(buffer->begin(),buffer->end());
    
    CCDictionary * dictionary = CCJSONConverter::sharedConverter()->dictionaryFrom(content.c_str());
	int code = ((CCNumber *)dictionary->objectForKey("code"))->getIntValue();
    if (code != 200) {
		if (code == 103) {
			CCMessageBox("exist nickname","ERROR");
		}
		else if (code == 104) {
			CCMessageBox("invalid nickname","ERROR");
		}
        return;
    }
    
	std::string requestTag(response->getHttpRequest()->getTag());
    
	if (requestTag == "101") {
		CCNumber *strGameRoleId = (CCNumber *)dictionary->objectForKey("gameRoleId");
		//CCString *strNickName = (CCString *)dict->objectForKey("nickName");
		//CCNumber *strUserId = (CCNumber *)dict->objectForKey("userId");

		char gameRoleid[10];
		//char UserId[10];

		sprintf(gameRoleid,"%d",strGameRoleId->getIntValue());
		//sprintf(UserId,"%d",strUserId->getIntValue());

		std::string sAccount(m_txtAccount->getText());

		//CCUserDefault::sharedUserDefault()->setStringForKey("userId", UserId);
		CCUserDefault::sharedUserDefault()->setStringForKey("gameRoleId", gameRoleid);
		CCUserDefault::sharedUserDefault()->setStringForKey("nickName", m_txtAccount->getText());

		this->OpenNewScene("MainGameScene");
	}
}

void CharacterScene::onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader)
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

    this->setFntTitle(101);
    
    m_txtAccount = CCEditBox::create(CCSizeMake(150, 34), CCScale9Sprite::create("transparent.png"));
    addChild(m_txtAccount);
    m_txtAccount->setFontColor(ccc3(255,255,153));
    m_txtAccount->setFont("Arial", 16);
    m_txtAccount->setPosition(ccp(148, 40));
    
	m_lblCharacterName->setFontName("Courier-Bold");
	m_lblCharacterName->setFontSize(20);
	m_lblCharacterName->setFontFillColor(ccc3(255, 255, 205));
	//    m_lblCharacterName->enableShadow(CCSizeMake(-1, -1), 1.0, 0.5,true);
	m_lblCharacterName->enableStroke(ccc3(50, 11, 1), 0.8);

	m_lblCharacterDesc->setHorizontalAlignment(kCCTextAlignmentLeft);
	m_lblCharacterDesc->setVerticalAlignment(kCCVerticalTextAlignmentTop);
    m_lblCharacterDesc->setDimensions(CCSizeMake(280, 50));
	m_lblCharacterDesc->setPosition(ccp(winSize.width * 0.5,120));
	m_lblCharacterDesc->setFontSize(12);

	//ccFontDefinition fontDef;
	//fontDef.m_fontFillColor = ccc3(255, 255, 205);
	////fontDef.m_fontName = "Courier";
	//fontDef.m_fontSize = 12;
	//fontDef.m_alignment = kCCTextAlignmentLeft;

	//ccFontStroke fontStroke;
	//fontStroke.m_strokeColor = ccc3(50, 11, 1);
	//fontStroke.m_strokeEnabled = true;
	//fontStroke.m_strokeSize = 0.5;
	//fontDef.m_stroke = fontStroke;

	//m_lblCharacterDesc->setTextDefinition(&fontDef);

	CCObject *object;

	CCMenu *menu = CCMenu::create();
	menu->setPosition(0,0);
	this->addChild(menu);

	CCARRAY_FOREACH(mCardNameList,object)
	{
        CCDictionary *dict = (CCDictionary *)object;
        
        CCSprite *sCardBg = CCSprite::create("Card_Level4.png");
        CCSize bgSize = sCardBg->getContentSize();
        
        CCString *strCardName = (CCString *)dict->objectForKey("CardName");
//        std::string strCardName1 = this->addReturnForName(strCardName);
        
        //CCLabelTTF *lblCardName = CCLabelTTF::create(strCardName->getCString(), "Arial", 14.0);
        //lblCardName->setAnchorPoint(ccp(1,1));
        //lblCardName->setPosition(ccp(bgSize.width - 10,bgSize.height - 50));

        CCLabelTTF *lblCardLevel = CCLabelTTF::create(((CCString *)dict->objectForKey("StarGrade"))->getCString(), "Arial", 14.0);
        lblCardLevel->setAnchorPoint(ccp(0,1));
        lblCardLevel->setPosition(ccp(10,bgSize.height - 10));

        std::string strGroup = determineGroup((CCString *)dict->objectForKey("formation"));
        CCSprite *sCardGroup = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(strGroup.c_str()));
        sCardGroup->setAnchorPoint(ccp(1,1));
        sCardGroup->setPosition(ccp(bgSize.width - 5,bgSize.height - 10));

		CCSprite *sCard = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(((CCString *)dict->objectForKey("CardImage"))->getCString()));
        
        sCardBg->addChild(sCard);
        //sCardBg->addChild(lblCardName);
        sCardBg->addChild(lblCardLevel);
        sCardBg->addChild(sCardGroup);
        
        sCard->setPosition(ccp(bgSize.width * 0.5,bgSize.height * 0.5));
		CCMenuItemSprite *spritCard = CCMenuItemSprite::create(sCardBg, sCardBg, sCardBg, this, menu_selector(CharacterScene::menuItemCallback));
		mCardList->addObject(spritCard);
		menu->addChild(spritCard);
	}

	m_configs = new std::vector<lrEllipseConfig*>();
	int cardLength = mCardList->count();

	for(int i=0;i<cardLength;i++)
	{
		CCMenuItemSprite *sprite = (CCMenuItemSprite *)mCardList->objectAtIndex(i);
		sprite->setTag(i);

		lrEllipseConfig *config = new lrEllipseConfig();

		config->aLength = ELLIPSE_WIDTH;
		config->cLength = ELLIPSE_HEIGHT;
		angleStep = 2 * M_PI / cardLength;
		config->step = 2 * M_PI / cardLength;
		config->startAngle = START_ANGLE + i * config->step;
		config->centerPosition = ccp(winSize.width * 0.5,300);

		CCPoint position = ccpAdd(config->centerPosition,ccp(getEllipseX(config->aLength,config->cLength,config->startAngle,0.0),getEllipseY(config->aLength,config->cLength,config->startAngle,0.0)));
		sprite->setPosition(position);
		sprite->setScale(0.9);
		m_configs->push_back(config);
	}

	resetZorder();

	for(int i=0;i<cardLength;i++)
	{
		lrEllipseConfig* config = m_configs->at(i);
		CCMenuItemSprite *sprite = (CCMenuItemSprite *)mCardList->objectAtIndex(i);
		sprite->setScale(config->scale);
	}
    
    setValueByIndex();
    
    m_sValueBg->setZOrder(99);
    m_lblAttack->setZOrder(98);
    m_lblDefence->setZOrder(98);
    m_lblAvoid->setZOrder(98);
    m_lblHp->setZOrder(98);
}

void CharacterScene::resetZorder()
{
	lrEllipseConfig* config = m_configs->at(selectedIndex);
	CCMenuItemSprite *currentSprite = (CCMenuItemSprite *)mCardList->objectAtIndex(selectedIndex);
	int cardLength = mCardList->count();

	int number = 0;
	int maxZorder = 2 * cardLength;

	for(int i=selectedIndex-1;i>=0;i--)
	{
		CCMenuItemSprite *sprite = (CCMenuItemSprite *)mCardList->objectAtIndex(i);
		if (config->step>0)
		{
			sprite->setZOrder(maxZorder - cardLength + number++);
		}
		else
		{
			sprite->setZOrder(--maxZorder);
		}
	}
	number = 0;
	maxZorder = 2 * cardLength;

	currentSprite->setZOrder(maxZorder);
//    currentSprite->setTouchPriority(-129);

	for(int i=selectedIndex+1;i<cardLength;i++)
	{
		CCMenuItemSprite *sprite = (CCMenuItemSprite *)mCardList->objectAtIndex(i);
		if (config->step>0)
		{
			sprite->setZOrder(--maxZorder);
		}
		else
		{
			sprite->setZOrder(maxZorder - cardLength +  ++number);
		}
	}

	float maxScale = 0.9;
	float minScale = 0.8;
	
	number = (cardLength-1)/2 + (cardLength-1)%2;
	float scaleStep = (maxScale-minScale)/number;
	config->scale = maxScale;
	int low = selectedIndex-1;
	int high = selectedIndex+1;

	for(int i=1;i<=number;i++)
	{
		if(low < 0) {
			low = cardLength-1;
		}
		if (high >= cardLength) {
			high = 0;
		}

		lrEllipseConfig* config1 = m_configs->at(low);
		lrEllipseConfig* config2 = m_configs->at(high);

		config1->scale = maxScale- number * scaleStep;
		config2->scale = maxScale- number * scaleStep;

		low--;
		high++;
	}
}

void CharacterScene::setValueByIndex()
{
    CCDictionary *dict = (CCDictionary *)mCardNameList->objectAtIndex(selectedIndex);
    
    m_lblCharacterName->setString(((CCString *)dict->objectForKey("CardName"))->getCString());
    
    CCString *strDesc = (CCString *)dict->objectForKey("Desc");
    std::string desc = strDesc->m_sString;

    m_lblCharacterDesc->setString(desc.c_str());

    
    m_lblHp->setString(((CCString *)dict->objectForKey("Hp"))->getCString());
    m_lblHp->setColor(ccc3(255,255,255));
    m_lblHp->setFontFillColor(ccc3(255,255,255));
    m_lblHp->enableStroke(ccc3(50, 11, 1), 0.8);
    
    m_lblDefence->setString(((CCString *)dict->objectForKey("Dp"))->getCString());
	m_lblDefence->setColor(ccc3(255,255,255));
	m_lblDefence->setFontFillColor(ccc3(255,255,255));
    m_lblDefence->enableStroke(ccc3(51, 11, 1), 0.7);
    
    m_lblAttack->setString(((CCString *)dict->objectForKey("Ap"))->getCString());
	m_lblAttack->setColor(ccc3(255,255,255));
	m_lblAttack->setFontFillColor(ccc3(255,255,255));
    m_lblAttack->enableStroke(ccc3(51, 11, 1), 0.6);
    
    m_lblAvoid->setString(((CCString *)dict->objectForKey("Dd"))->getCString());
	m_lblAvoid->setColor(ccc3(255,255,255));
	m_lblAvoid->setFontFillColor(ccc3(255,255,255));
    m_lblAvoid->enableStroke(ccc3(51, 11, 1), 0.5);
}

void CharacterScene::doEllipse()
{
	int cardLength = mCardList->count();
	for(int i=0;i<cardLength;i++)
	{
		CCMenuItemSprite *sprite = (CCMenuItemSprite *)mCardList->objectAtIndex(i);
		lrEllipseConfig* config = m_configs->at(i);

		EllipseActionInterval *ellipseInterval = EllipseActionInterval::actionWithDuration(0.6,*config);
		CCActionInterval *scaleInvertval = CCScaleTo::create(0.6,config->scale,config->scale);

		CCSpawn *action = CCSpawn::createWithTwoActions(ellipseInterval,scaleInvertval);

		CCSequence *sequence = CCSequence::create(action,CCCallFuncN::create(this, callfuncN_selector(CharacterScene::animateEndCallBack)),NULL);
		sequence->setTag(1);
		sprite->runAction(sequence);
	}
}

bool CharacterScene::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{

    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_sCharacterBelow", CCSprite*, this->m_sCharacterBelow);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_sValueBg", CCSprite*, this->m_sValueBg);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_lblCharacterName", CCLabelTTF*, this->m_lblCharacterName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_lblCharacterDesc", CCLabelTTF*, this->m_lblCharacterDesc);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_lblHp", CCLabelTTF*, this->m_lblHp);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_lblDefence", CCLabelTTF*, this->m_lblDefence);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_lblAttack", CCLabelTTF*, this->m_lblAttack);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_lblAvoid", CCLabelTTF*, this->m_lblAvoid);
    return true;
}

void CharacterScene::menuItemCallback(CCObject* pSender)
{
	CCMenuItemSprite *sprite = (CCMenuItemSprite*)pSender;

	CCAction *action = sprite->getActionByTag(1);
	if (action!=NULL && !action->isDone())
	{
		return;
	}

	if (selectedIndex == sprite->getTag())
	{
		return;
	}

	int cardLength = mCardList->count();
	for(int i=0;i<cardLength;i++)
	{
		lrEllipseConfig* config = m_configs->at(i);

		int gap  = selectedIndex - sprite->getTag();
		if (abs(gap) > cardLength/2)
		{
			if (gap>0)
			{
				config->step = angleStep * ((cardLength-gap) * -1);
			}
			else
			{
				config->step = angleStep * ((cardLength+gap));
			}
		}
		else
		{
			config->step = angleStep * gap;
		}
		
	}

	selectedIndex = sprite->getTag();

	this->resetZorder();
	this->doEllipse();
    
    this->setValueByIndex();
}

void CharacterScene::animateEndCallBack(CCNode *node)
{
    CCSprite *sprite = (CCSprite *)node;
	lrEllipseConfig* config = m_configs->at(sprite->getTag());

	config->startAngle += config->step;
	config->startAngle = fmod((double)config->startAngle,2 * M_PI);
}

void CharacterScene::buttonClicked(CCObject *pSender, CCControlEvent pCCControlEvent) {
    
    CCControlButton *button = (CCControlButton*) pSender;
	
    if (pCCControlEvent==CCControlEventTouchUpInside) {
        switch (button->getTag()) {
            case 101:
                this->doSubmit();
                break;
        }
    } else if (pCCControlEvent==CCControlEventTouchDown) {
        CCPoint point = button->getPosition();
        m_sCharacterBelow->runAction(CCMoveTo::create(0.5, point));
    }
}

SEL_MenuHandler CharacterScene::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
	return NULL;
}

SEL_CCControlHandler CharacterScene::onResolveCCBCCControlSelector(CCObject *pTarget, const char * pSelectorName) {
    
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "buttonClicked:", CharacterScene::buttonClicked);
	return NULL;
}

