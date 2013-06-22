#include "CharacterScene.h"
//#include "JsonBox.h"

using namespace cocos2d;

#define ELLIPSE_WIDTH 90
#define ELLIPSE_HEIGHT 20

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

        CCSize winSize = CCDirector::sharedDirector()->getWinSize();

		config1.aLength = ELLIPSE_WIDTH;
		config1.cLength = ELLIPSE_HEIGHT;
		config1.startAngle = 2 * M_PI * 3/4;
		config1.step = 1;
		config1.centerPosition = ccp(winSize.width * 0.5,300);

        config2.aLength = ELLIPSE_WIDTH;
		config2.cLength = ELLIPSE_HEIGHT;
		config2.startAngle = 2 * M_PI * 1/12;
		config2.step = 1;
		config2.centerPosition = ccp(winSize.width * 0.5,300);

        config3.aLength = ELLIPSE_WIDTH;
		config3.cLength = ELLIPSE_HEIGHT;
		config3.startAngle = 2 * M_PI * 5/12;
		config3.step = 1;
		config3.centerPosition = ccp(winSize.width * 0.5,300);
        
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
    
	CCSprite *fou = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("fou.png"));
	spritFou = CCMenuItemSprite::create(fou, fou, fou, this, menu_selector(CharacterScene::menuItemCallback));

	CCSprite *xian = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("xian.png"));
	spriteXian = CCMenuItemSprite::create(xian, xian, xian, this, menu_selector(CharacterScene::menuItemCallback));

	CCSprite *yao = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("yao.png"));
	spriteYao = CCMenuItemSprite::create(yao, yao, yao, this, menu_selector(CharacterScene::menuItemCallback));

	CCMenu *menu = CCMenu::create(spritFou,spriteYao,spriteXian,NULL);
	menu->setPosition(0,0);
	this->addChild(menu);

	spritFou->setUserData(&config1);
    spriteXian->setUserData(&config2);
    spriteYao->setUserData(&config3);

	CCPoint point1 = ccpAdd(config1.centerPosition,ccp(getEllipseX(config1.aLength,config1.cLength,config1.startAngle,0.0),getEllipseY(config1.aLength,config1.cLength,config1.startAngle,0.0)));
	CCPoint point2 = ccpAdd(config2.centerPosition,ccp(getEllipseX(config2.aLength,config2.cLength,config2.startAngle,0.0),getEllipseY(config2.aLength,config2.cLength,config2.startAngle,0.0)));
	CCPoint point3 = ccpAdd(config3.centerPosition,ccp(getEllipseX(config3.aLength,config3.cLength,config3.startAngle,0.0),getEllipseY(config3.aLength,config3.cLength,config3.startAngle,0.0)));

	spritFou->setPosition(point1);
	spriteXian->setPosition(point2);
	spriteYao->setPosition(point3);

	spritFou->setZOrder(2);
	spriteXian->setZOrder(1);
	spriteYao->setZOrder(1);

	spritFou->setScale(0.9);
	spriteXian->setScale(0.9);
	spriteYao->setScale(0.9);
}

void CharacterScene::doEllipse()
{
	EllipseActionInterval *ellipse1 = EllipseActionInterval::actionWithDuration(0.6,config1);
	CCSequence *sequence1 = CCSequence::create(ellipse1,CCCallFuncN::create(this, callfuncN_selector(CharacterScene::animateEndCallBack)),NULL);
	sequence1->setTag(1);
	spritFou->runAction(sequence1);

	EllipseActionInterval *ellipse2 = EllipseActionInterval::actionWithDuration(0.6,config2);
	CCSequence *sequence2 = CCSequence::create(ellipse2,CCCallFuncN::create(this, callfuncN_selector(CharacterScene::animateEndCallBack)),NULL);
	sequence2->setTag(1);
    spriteXian->runAction(sequence2);

	EllipseActionInterval *ellipse3 = EllipseActionInterval::actionWithDuration(0.6,config3);
	CCSequence *sequence3 = CCSequence::create(ellipse3,CCCallFuncN::create(this, callfuncN_selector(CharacterScene::animateEndCallBack)),NULL);
	sequence3->setTag(1);
    spriteYao->runAction(sequence3);
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

	if (sprite->isEqual(spritFou))
	{
		CCLOG("fou");
	} else if (sprite->isEqual(spriteXian))
	{
		CCLOG("xian");
	} else if (sprite->isEqual(spriteYao))
	{
		CCLOG("yao");
	}

	CCAction *action = sprite->getActionByTag(1);
	if (action!=NULL && !action->isDone())
	{
		return;
	}
	int zOrder = sprite->getZOrder();
	if (zOrder==2)
	{
		return;
	}

	spritFou->setZOrder(1);
	spriteXian->setZOrder(1);
	spriteYao->setZOrder(1);

	float x = sprite->getPositionX();
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	if (x>winSize.width * 0.5)
	{
		config1.step = -1;
		config2.step = -1;
		config3.step = -1;
	} else {
		config1.step = 1;
		config2.step = 1;
		config3.step = 1;
	}

	sprite->setZOrder(2);

	this->doEllipse();
}

void CharacterScene::animateEndCallBack(CCNode *node)
{
    CCSprite *sprite = (CCSprite *)node;
    lrEllipseConfig *config = (lrEllipseConfig *)sprite->getUserData();
	if (config->step==1)
	{
		config->startAngle += 2 * M_PI * 1/3;
	}
	else
	{
		config->startAngle -= 2 * M_PI * 1/3;
	}

	//CCSprite *fou = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("fou.png"));
    
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

