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
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////

        CC_BREAK_IF(! CCLayer::init());

		mCardList = CCArray::create();
		mCardList->retain();

		mCardNameList = CCArray::create();
		mCardNameList->retain();

		mCardNameList->addObject(CCString::create("card_rulaifo.png"));
		mCardNameList->addObject(CCString::create("Card_Level5.png"));
		mCardNameList->addObject(CCString::create("Card_Level6.png"));
		mCardNameList->addObject(CCString::create("Card_Level3.png"));
		mCardNameList->addObject(CCString::create("Card_Level4.png"));


		selectedIndex = 0;
        
        bRet = true;
    } while (0);

    return bRet;
}

void CharacterScene::doSubmit()
{
	std::string sAccount(m_txtAccount->getText());

	if (trimRight(sAccount).empty() ) {
		CCMessageBox(GlobalData::getLocalString("character_name_empty")->getCString(),"ERROR");
		return;
	}

	 this->OpenNewScene("MainGameScene");

	//CCHttpRequest *request = new CCHttpRequest();
	//request->setRequestType(CCHttpRequest::kHttpGet);
	//request->setResponseCallback(this,callfuncND_selector(CharacterScene::requestFinishedCallback));
	//request->setTag("103");
 //   
	//string _strUrl = CompleteUrl(URL_FRIEND_DELETE);
	//_strUrl.append(CCUserDefault::sharedUserDefault()->getStringForKey("userinfo"));
 //   
	//request->setUrl(_strUrl.c_str());
 //   
	//CCHttpClient *client = CCHttpClient::getInstance();
	//client->send(request);
 //   
	//request->release();
}

void CharacterScene::requestFinishedCallback(CCNode* pSender,void *Rspdata)
{
	if (!this->ValidateResponseData(pSender,Rspdata))
	{
		return;
	}
    
	CCHttpResponse *response =  (CCHttpResponse*)Rspdata;
	std::vector<char> *buffer = response->getResponseData();
    
	std::string content(buffer->begin(),buffer->end());
	CCLog(content.c_str());
    
    CCDictionary * dictionary = CCJSONConverter::sharedConverter()->dictionaryFrom(content.c_str());
	int code = ((CCNumber *)dictionary->objectForKey("code"))->getIntValue();
    if (code != 200) {
        CCMessageBox("invoke web api failed!","ERROR");
        return;
    }
    
	std::string requestTag(response->getHttpRequest()->getTag());
    
	if (requestTag == "101") {
//		mArrayList = dynamic_cast<CCArray *>(dictionary->objectForKey("friendList"));
//		if (mArrayList==NULL)
//		{
//			return;
//		}
//        
//		selectedindex = -1;
//		mTableView->reloadData();
	}
}

void CharacterScene::onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader)
{
    m_txtAccount = CCEditBox::create(CCSizeMake(150, 34), CCScale9Sprite::create("transparent.png"));
    addChild(m_txtAccount);
    m_txtAccount->setFontColor(ccc3(255,255,153));
    m_txtAccount->setFont("Arial", 16);
    m_txtAccount->setPosition(ccp(148, 40));

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCObject *object;

	CCMenu *menu = CCMenu::create();
	menu->setPosition(0,0);
	this->addChild(menu);

	CCARRAY_FOREACH(mCardNameList,object)
	{
		CCString *strCardName = (CCString*)object; 
		CCSprite *fou = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(strCardName->getCString()));
		CCMenuItemSprite *spritCard = CCMenuItemSprite::create(fou, fou, fou, this, menu_selector(CharacterScene::menuItemCallback));
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
		if(low<0) {
			low = cardLength-1;
		}
		if (high>=cardLength)
		{
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

	float x = sprite->getPositionX();

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

