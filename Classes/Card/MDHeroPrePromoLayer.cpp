#include "MDHeroPrePromoLayer.h"

#define TASK_COLUMN  3
#define TASK_ROW  3

CCScene* MDHeroPrePromoLayer::scene()
{
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		MDHeroPrePromoLayer *layer = MDHeroPrePromoLayer::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool MDHeroPrePromoLayer::init()
{
	selectedindex = 0;

	bool bRet = false;
	do 
	{

		CC_BREAK_IF(! CCLayer::init());

		bRet = true;
	} while (0);

	return bRet;
}

void MDHeroPrePromoLayer::showTaskInfo()
{
	this->ShowLoadingIndicator("");

	CCHttpRequest *request = new CCHttpRequest();
	request->setRequestType(CCHttpRequest::kHttpGet);
	request->setResponseCallback(this,httpresponse_selector(MDHeroPrePromoLayer::requestFinishedCallback));
	request->setTag("101");

	string _strUrl = CompleteUrl(URL_FRIEND_LIST);
	_strUrl.append(CCUserDefault::sharedUserDefault()->getStringForKey("userinfo"));

	request->setUrl(_strUrl.c_str());

	CCHttpClient *client = CCHttpClient::getInstance();
	client->send(request);

	request->release();
}

void MDHeroPrePromoLayer::requestFinishedCallback(CCHttpClient* client, CCHttpResponse* response)
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
		CCMessageBox("invoke web api failed!","ERROR");
		return;
	}

	std::string requestTag(response->getHttpRequest()->getTag());

	if (requestTag == "101") {
	} else if (requestTag == "102"){
	}
}

bool MDHeroPrePromoLayer::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_lblPreQuality", CCLabelTTF*, this->m_lblPreQuality);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_lblAftQuality", CCLabelTTF*, this->m_lblAftQuality);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_lblCardName", CCLabelTTF*, this->m_lblCardName);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_lblRank", CCLabelTTF*, this->m_lblLevel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_lbExp", CCLabelTTF*, this->m_lblExp);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_lbHP", CCLabelTTF*, this->m_lblHp);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_lblAttack", CCLabelTTF*, this->m_lblAttack);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_lblDefence", CCLabelTTF*, this->m_lblDefence);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_lblSuper", CCLabelTTF*, this->m_lblSuper);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_lblAftRank", CCLabelTTF*, this->m_lblAftRank);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_lbAftExp", CCLabelTTF*, this->m_lbAftExp);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_lbAftHP", CCLabelTTF*, this->m_lbAftHP);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_lblAftAttack", CCLabelTTF*, this->m_lblAftAttack);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_lblAftDefence", CCLabelTTF*, this->m_lblAftDefence);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_lblAftSuper", CCLabelTTF*, this->m_lblAftSuper);

    //CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_sCardBefore", CCSprite*, this->m_sCardBefore);
    //CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_sCardAfter", CCSprite*, this->m_sCardAfter);
	return true;
}

SEL_MenuHandler MDHeroPrePromoLayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
	return NULL;
}

SEL_CCControlHandler MDHeroPrePromoLayer::onResolveCCBCCControlSelector(CCObject *pTarget, const char * pSelectorName) {

	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "buttonClicked:", MDHeroPrePromoLayer::buttonClicked);
	return NULL;
}

void MDHeroPrePromoLayer::onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader)
{
    this->setFntTitle(101);
    this->setFntTitle(102);
}

void MDHeroPrePromoLayer::setCardInfo(CCDictionary *dict)
{
	int intLevel = ((CCString *)dict->objectForKey("beginGrade"))->intValue();
	string strLevelImg("Card_Level");
	strLevelImg.append(IntToString(intLevel));
	strLevelImg.append(".png");
	m_sCardBefore = CCSprite::create(strLevelImg.c_str());
	m_sCardBefore->setScale(CCDirector::sharedDirector()->getContentScaleFactor()/2);
	m_sCardBefore->setPosition(ccp(82,247));
	this->addChild(m_sCardBefore);

	CCSize bgSize = m_sCardBefore->getContentSize();

	string strLevelImg1("Card_Level");
	strLevelImg1.append(IntToString(intLevel+1));
	strLevelImg1.append(".png");
	m_sCardAfter = CCSprite::create(strLevelImg1.c_str());
	m_sCardAfter->setScale(CCDirector::sharedDirector()->getContentScaleFactor()/2);
	m_sCardAfter->setPosition(ccp(238,247));
	this->addChild(m_sCardAfter);

	CCString *strGroupId = (CCString *)dict->objectForKey("game_group_id");
	std::string strGroup = determineGroup(strGroupId);
	CCSprite *sCardGroupBefore = CCSprite::createWithSpriteFrameName(strGroup.c_str());
	sCardGroupBefore->setAnchorPoint(ccp(1,1));
	sCardGroupBefore->setPosition(ccp(bgSize.width - 5,bgSize.height - 10));
	m_sCardBefore->addChild(sCardGroupBefore);

	std::string strCardImg("art/art_profile/");
	strCardImg.append(((CCString *)dict->objectForKey("cardProfileImg"))->getCString());
	strCardImg.append(".png");

	CCSprite *sPeopleBefore = CCSprite::create(strCardImg.c_str());
	sPeopleBefore->setPosition(ccp(bgSize.width * 0.5,bgSize.height * 0.5));
	//sPeopleBefore->setScale(CCDirector::sharedDirector()->getContentScaleFactor()/2);
	m_sCardBefore->addChild(sPeopleBefore);


	//m_sCardAfter->setScale(CCDirector::sharedDirector()->getContentScaleFactor()/2);

	CCSprite *sCardGroupAfter = CCSprite::createWithSpriteFrameName(strGroup.c_str());
	sCardGroupAfter->setAnchorPoint(ccp(1,1));
	sCardGroupAfter->setPosition(ccp(bgSize.width - 5,bgSize.height - 10));
	m_sCardAfter->addChild(sCardGroupAfter);

	CCSprite *sPeopleAfter = CCSprite::create(strCardImg.c_str());
	sPeopleAfter->setPosition(ccp(bgSize.width * 0.5,bgSize.height * 0.5));
	//sPeopleAfter->setScale(CCDirector::sharedDirector()->getContentScaleFactor()/2);
	m_sCardAfter->addChild(sPeopleAfter);

	m_lblCardName->setString(((CCString *)dict->objectForKey("roleName"))->getCString());
	m_lblCardName->enableStroke(ccc3(45, 1, 2), 0.6);

	std::string strLevel("LV.");
	strLevel.append(IntToString(((CCString *)dict->objectForKey("beginGrade"))->intValue()));
	m_lblLevel->setColor(ccc3(242, 179, 20));
	m_lblLevel->enableStroke(ccc3(51, 1, 4), 0.3);
	m_lblLevel->setString(strLevel.c_str());

	m_lblHp->setString(IntToString(((CCString *)dict->objectForKey("blood"))->intValue()).c_str());

	m_lblDefence->setString(IntToString(((CCString *)dict->objectForKey("defence"))->intValue()).c_str());
	m_lblDefence->enableStroke(ccc3(45, 1, 2), 0.2);

	m_lblAttack->setString(IntToString(((CCString *)dict->objectForKey("attack"))->intValue()).c_str());
	m_lblAttack->enableStroke(ccc3(45, 1, 2), 0.2);

	float fltCrit = ((CCString *)dict->objectForKey("crit"))->floatValue();
	string _critStr("+");
	_critStr.append(floatToPercent(fltCrit).c_str());
	m_lblSuper->setString(_critStr.c_str());
	//float fltDodge = ((CCString *)dict->objectForKey("dodge"))->floatValue();
	//m_lblAvoid->setString(floatToPercent(fltDodge).c_str());
	//m_lblAvoid->enableStroke(ccc3(45, 1, 2), 0.3);
}

void MDHeroPrePromoLayer::buttonClicked(CCObject * sender , CCControlEvent controlEvent)
{
	MainGameScene *mainScene = (MainGameScene *)this->getParent();
	CCControlButton *button = (CCControlButton *)sender;
	switch (button->getTag()) {
	case 101:
        {
            mainScene->PushLayer((CCLayer *)this->GetLayer("MDHeroPromoLayer"));
            break;
        }
	case 102:
        {
            mainScene->PopLayer();
            break;
        }
		break;
	}
}

MDHeroPrePromoLayer::MDHeroPrePromoLayer()
{
	mTaskList = NULL;
    
    m_lblPreQuality = NULL;
    m_lblAftQuality = NULL;
    m_lblCardName = NULL;
    
    m_lblLevel = NULL;
    m_lblExp = NULL;
    m_lblHp = NULL;
    m_lblAttack = NULL;
    m_lblDefence = NULL;
    m_lblSuper = NULL;
    
    m_lblAftRank = NULL;
    m_lbAftExp = NULL;
    m_lbAftHP = NULL;
    m_lblAftAttack = NULL;
    m_lblAftDefence = NULL;
    m_lblAftSuper = NULL;

    m_sCardBefore = NULL;
    m_sCardAfter = NULL;
}

MDHeroPrePromoLayer::~MDHeroPrePromoLayer()
{
	CC_SAFE_RELEASE(m_lblPreQuality);
    CC_SAFE_RELEASE(m_lblAftQuality);
    CC_SAFE_RELEASE(m_lblCardName);
    
    CC_SAFE_RELEASE(m_lblLevel);
    CC_SAFE_RELEASE(m_lblExp);
    CC_SAFE_RELEASE(m_lblHp);
    CC_SAFE_RELEASE(m_lblAttack);
    CC_SAFE_RELEASE(m_lblDefence);
    CC_SAFE_RELEASE(m_lblSuper);
    
    CC_SAFE_RELEASE(m_lblAftRank);
    CC_SAFE_RELEASE(m_lbAftExp);
    CC_SAFE_RELEASE(m_lbAftHP);
    CC_SAFE_RELEASE(m_lblAftAttack);
    CC_SAFE_RELEASE(m_lblAftDefence);
    CC_SAFE_RELEASE(m_lblAftSuper);
}

