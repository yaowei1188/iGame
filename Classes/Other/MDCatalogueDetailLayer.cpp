#include "MDCatalogueDetailLayer.h"

CCScene* MDCatalogueDetailLayer::scene()
{
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		MDCatalogueDetailLayer *layer = MDCatalogueDetailLayer::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool MDCatalogueDetailLayer::init()
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

void MDCatalogueDetailLayer::requestFinishedCallback(CCHttpClient* client, CCHttpResponse* response)
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
//		mArrayList = dynamic_cast<CCArray *>(dictionary->objectForKey("friendList"));
//		if (mArrayList==NULL)
//		{
//			return;
//		}
//
//		selectedindex = -1;
//		mTableView->reloadData();
	} else if (requestTag == "102"){

	}
}

bool MDCatalogueDetailLayer::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_sCard", CCSprite*, this->m_sCard);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_sFraction", CCSprite*, this->m_sFraction);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_lblCardName", CCLabelTTF*, this->m_lblCardName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_lblLevel", CCLabelTTF*, this->m_lblLevel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_lblHp", CCLabelTTF*, this->m_lblHp);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_lblDefence", CCLabelTTF*, this->m_lblDefence);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_lblAttack", CCLabelTTF*, this->m_lblAttack);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_lblAvoid", CCLabelTTF*, this->m_lblAvoid);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_lblDesc", CCLabelTTF*, this->m_lblDesc);
	return true;
}

SEL_MenuHandler MDCatalogueDetailLayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
	return NULL;
}

SEL_CCControlHandler MDCatalogueDetailLayer::onResolveCCBCCControlSelector(CCObject *pTarget, const char * pSelectorName) {

	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "buttonClicked:", MDCatalogueDetailLayer::buttonClicked);
	return NULL;
}

void MDCatalogueDetailLayer::onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader)
{
    this->setFntTitle(101);
}

void MDCatalogueDetailLayer::setCardInfo(CCDictionary *dict)
{
    CCSize bgSize = m_sCard->getContentSize();

	CCDictionary *dictCardProfile = GlobalData::getCardProfileByName(((CCString *)dict->objectForKey("cardProfileImg"))->getCString());

    CCString *strGroupId = (CCString *)dictCardProfile->objectForKey("game_group_id");
    std::string strGroup = determineGroup(strGroupId);
    CCSprite *sCardGroup = CCSprite::createWithSpriteFrameName(strGroup.c_str());
    sCardGroup->setAnchorPoint(ccp(1,1));
    sCardGroup->setPosition(ccp(42,360));
    this->addChild(sCardGroup);

    std::string strCardImg("art/art_profile/");
    strCardImg.append(((CCString *)dictCardProfile->objectForKey("cardProfileImg"))->getCString());
	strCardImg.append(".png");

    CCSprite *sPeople = CCSprite::create(strCardImg.c_str());
    sPeople->setPosition(ccp(98,270));
	sPeople->setScale(CCDirector::sharedDirector()->getContentScaleFactor()/2);
    this->addChild(sPeople);

    m_lblDesc->setColor(ccc3(51, 52, 50));
	std::string strLevel("LV.");
	strLevel.append(IntToString(((CCString *)dictCardProfile->objectForKey("beginGrade"))->intValue()));
    m_lblLevel->setColor(ccc3(242, 179, 20));
    m_lblLevel->enableStroke(ccc3(51, 1, 4), 0.3);
    
	m_lblLevel->setString(strLevel.c_str());
	m_lblCardName->setString(((CCString *)dictCardProfile->objectForKey("roleName"))->getCString());
    m_lblCardName->enableStroke(ccc3(45, 1, 2), 0.6);
    
	m_lblDesc->setString(((CCString *)dictCardProfile->objectForKey("roleDescription"))->getCString());

	m_lblHp->setString(IntToString(((CCString *)dictCardProfile->objectForKey("blood"))->intValue()).c_str());
	float fltDefence = ((CCString *)dictCardProfile->objectForKey("defence"))->floatValue();
	m_lblDefence->setString(floatToPercent(fltDefence).c_str());

	m_lblAttack->setString(IntToString(((CCString *)dictCardProfile->objectForKey("attack"))->intValue()).c_str());
    m_lblAttack->enableStroke(ccc3(45, 1, 2), 0.2);
    
	float fltDodge = ((CCString *)dictCardProfile->objectForKey("dodge"))->floatValue();
	m_lblAvoid->setString(floatToPercent(fltDodge).c_str());
    m_lblAvoid->enableStroke(ccc3(45, 1, 2), 0.3);
}

void MDCatalogueDetailLayer::buttonClicked(CCObject * sender , CCControlEvent controlEvent)
{
	CCControlButton *button = (CCControlButton *)sender;
	switch (button->getTag()) {
	case 101:
        {
            MainGameScene *mainScene = (MainGameScene *)this->getParent();
            mainScene->PopLayer();
            break;
        }
	}
}

MDCatalogueDetailLayer::MDCatalogueDetailLayer()
{
	mTaskList = NULL;
    m_sCard = NULL;
    m_sFraction= NULL;
    m_lblLevel = NULL;
    m_lblCardName = NULL;
    m_lblHp = NULL;
    m_lblDefence = NULL;
    m_lblAttack = NULL;
    m_lblAvoid = NULL;
    m_lblDesc = NULL;
}

MDCatalogueDetailLayer::~MDCatalogueDetailLayer()
{
	CC_SAFE_RELEASE(m_sCard);
    CC_SAFE_RELEASE(m_sFraction);
    CC_SAFE_RELEASE(m_lblLevel);
    CC_SAFE_RELEASE(m_lblCardName);
    CC_SAFE_RELEASE(m_lblHp);
    CC_SAFE_RELEASE(m_lblDefence);
    CC_SAFE_RELEASE(m_lblAttack);
    CC_SAFE_RELEASE(m_lblAvoid);
    CC_SAFE_RELEASE(m_lblDesc);
}

