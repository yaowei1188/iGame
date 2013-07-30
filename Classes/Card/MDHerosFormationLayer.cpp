#include "MDHerosFormationLayer.h"

#define TASK_COLUMN  3
#define TASK_ROW  3

CCScene* MDHerosFormationLayer::scene()
{
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		MDHerosFormationLayer *layer = MDHerosFormationLayer::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool MDHerosFormationLayer::init()
{
	bool bRet = false;
	do 
	{

		CC_BREAK_IF(! CCLayer::init());

		bRet = true;
	} while (0);

	return bRet;
}

void MDHerosFormationLayer::doSearch()
{
	this->ShowLoadingIndicator("");

	CCHttpRequest *request = new CCHttpRequest();
	request->setRequestType(CCHttpRequest::kHttpGet);
	request->setResponseCallback(this,httpresponse_selector(MDHerosFormationLayer::requestFinishedCallback));
	request->setTag("101");

	string _strUrl = CompleteUrl(URL_FRIEND_LIST);
	_strUrl.append(CCUserDefault::sharedUserDefault()->getStringForKey("userinfo"));

	request->setUrl(_strUrl.c_str());

	CCHttpClient *client = CCHttpClient::getInstance();
	client->send(request);

	request->release();
}

void MDHerosFormationLayer::requestFinishedCallback(CCHttpClient* client, CCHttpResponse* response)
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

bool MDHerosFormationLayer::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_lblFightCapacity", CCLabelTTF*, this->m_lblFightCapacity);
	return true;
}

SEL_MenuHandler MDHerosFormationLayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
	return NULL;
}

SEL_CCControlHandler MDHerosFormationLayer::onResolveCCBCCControlSelector(CCObject *pTarget, const char * pSelectorName) {

	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "buttonClicked:", MDHerosFormationLayer::buttonClicked);
	return NULL;
}

void MDHerosFormationLayer::onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader)
{
	CCSize winSize = this->getContentSize();
	int row = 0;
	int col = 0;

	for(int i=0;i<6;i++)
	{
		CCScale9Sprite *scaleSprite = NULL;
		if (i<4)
		{
			scaleSprite = CCScale9Sprite::createWithSpriteFrameName("card_embattle_bg.png");
		} else {
			scaleSprite = CCScale9Sprite::createWithSpriteFrameName("card_upgrade_hero_bg.png");
		}
        scaleSprite->setInsetLeft(5);
        scaleSprite->setInsetRight(5);

		CCControlButton *btn = CCControlButton::create(scaleSprite);
		btn->setPreferredSize(CCSizeMake(150 * 0.71,205 * 0.71));
		btn->setAnchorPoint(ccp(0.5,0.5));
		CCSize spriteSize = scaleSprite->getContentSize();
		btn->setPosition(ccp(spriteSize.width * 0.5 + col++ * spriteSize.width,winSize.height - spriteSize.height * 0.5  - 45 - row * spriteSize.height));

		if (i<4)
		{
			CCLabelTTF *lblCardName = CCLabelTTF::create("erlangsheng", "Arial", 14.0);
			lblCardName->setAnchorPoint(ccp(0.5,1));
			lblCardName->setTag(99);
			lblCardName->setPosition(ccp(spriteSize.width * 0.5,spriteSize.height - 5));

			CCLabelTTF *lblCardLevel = CCLabelTTF::create("Lv.100", "Arial", 14.0);
			lblCardLevel->setAnchorPoint(ccp(0.5,1));
			lblCardLevel->setTag(100);
			lblCardLevel->setPosition(ccp(spriteSize.width * 0.5,spriteSize.height - 70));

			std::string strGroup = determineGroup(CCString::create("1"));
			CCSprite *sCardGroup = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(strGroup.c_str()));
			sCardGroup->setAnchorPoint(ccp(1,1));
			sCardGroup->setPosition(ccp(spriteSize.width - 5,spriteSize.height - 5));
			sCardGroup->setScale(0.71);
			
			
			CCSprite *sCard = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("head_erlangsheng.png"));
			sCard->setAnchorPoint(ccp(0.5,1));
			sCard->setTag(101);
			sCard->setPosition(ccp(spriteSize.width * 0.5,spriteSize.height - 25));
			sCard->setScale(0.71);

			CCLabelTTF *lblAttack = CCLabelTTF::create("攻+60点", "Arial", 12.0);
			lblAttack->setAnchorPoint(ccp(0.5,1));
			lblAttack->setTag(102);
			lblAttack->setPosition(ccp(spriteSize.width * 0.5,38));
			lblAttack->setColor(ccc3(252,255,56));

			CCLabelTTF *lblHP = CCLabelTTF::create("血+125点", "Arial", 12.0);
			lblHP->setAnchorPoint(ccp(0.5,1));
			lblHP->setTag(103);
			lblHP->setPosition(ccp(spriteSize.width * 0.5,55));
			lblHP->setColor(ccc3(213,0,0));

			scaleSprite->addChild(sCard);
			scaleSprite->addChild(lblCardName);
			scaleSprite->addChild(lblCardLevel);
			scaleSprite->addChild(lblAttack);
			scaleSprite->addChild(lblHP);
			scaleSprite->addChild(sCardGroup);

			CCControlButton *btnUp = CCControlButton::create(CCScale9Sprite::createWithSpriteFrameName("card_embattle_dropup.png"));
			btnUp->setBackgroundSpriteForState(CCScale9Sprite::createWithSpriteFrameName("card_embattle_dropup_highlight.png"),CCControlStateHighlighted);
			btnUp->addTargetWithActionForControlEvents(this,cccontrol_selector(MDHerosFormationLayer::touchUpInside), CCControlEventTouchUpInside);
			scaleSprite->addChild(btnUp);
			btnUp->setTag(1);
			btnUp->setPreferredSize(CCSizeMake(96,15));
			btnUp->setAnchorPoint(ccp(0.5,0));
			btnUp->setPosition(ccp(spriteSize.width * 0.5,7));
			btnUp->setZoomOnTouchDown(false);
		}

		this->addChild(btn);

		if ((i+1) % 3 == 0)
		{
			row++;
			col = 0;
		}
	}
	
}

void MDHerosFormationLayer::touchUpInside(CCObject* pSender, CCControlEvent event)
{
	CCControlButton *btn = (CCControlButton *)pSender;
	CCNode *parent = btn->getParent();

	CCSize spriteSize = parent->getContentSize();

	if (btn->getTag()==1)
	{
        CCControlButton *btndown = CCControlButton::create(CCScale9Sprite::createWithSpriteFrameName("card_add_bg.png"));
        btndown->setBackgroundSpriteForState(CCScale9Sprite::createWithSpriteFrameName("card_add_bg_highlight.png"),CCControlStateHighlighted);
        btndown->addTargetWithActionForControlEvents(this,cccontrol_selector(MDHerosFormationLayer::touchUpInside), CCControlEventTouchUpInside);
        parent->addChild(btndown);
        btndown->setTag(2);
        btndown->setPreferredSize(CCSizeMake(96,15));
        btndown->setAnchorPoint(ccp(0.5,0));
        btndown->setPosition(ccp(spriteSize.width * 0.5,spriteSize.height - 45));
        btndown->setZoomOnTouchDown(false);
        
//		CCLabelTTF *lblCardName = (CCLabelTTF *)parent->getChildByTag(99);
//		lblCardName->setVisible(false);

		CCLabelTTF *lblCardLevel = (CCLabelTTF *)parent->getChildByTag(100);
		lblCardLevel->setVisible(false);

		CCSprite *sCard = (CCSprite *)parent->getChildByTag(101);
		sCard->setVisible(false);

		CCLabelTTF *lblAttack = (CCLabelTTF *)parent->getChildByTag(102);
		lblAttack->setPosition(ccpAdd(lblAttack->getPosition(),ccp(0,40)));

		CCLabelTTF *lblHP = (CCLabelTTF *)parent->getChildByTag(103);
		lblHP->setPosition(ccpAdd(lblHP->getPosition(),ccp(0,40)));

		CCLabelTTF *lblDefence = CCLabelTTF::create("防+20点", "Arial", 12.0);
		lblDefence->setAnchorPoint(ccp(0.5,1));
		lblDefence->setPosition(ccp(spriteSize.width * 0.5,61));
		lblDefence->setColor(ccc3(59,243,67));
		lblDefence->setTag(105);
		parent->addChild(lblDefence);

		CCLabelTTF *lblSuper = CCLabelTTF::create("暴+100%", "Arial", 12.0);
		lblSuper->setAnchorPoint(ccp(0.5,1));
		lblSuper->setPosition(ccp(spriteSize.width * 0.5,44));
		lblSuper->setColor(ccc3(238,45,197));
		lblSuper->setTag(106);
		parent->addChild(lblSuper);

		CCLabelTTF *lblDodge = CCLabelTTF::create("闪+15%", "Arial", 12.0);
		lblDodge->setAnchorPoint(ccp(0.5,1));
		lblDodge->setPosition(ccp(spriteSize.width * 0.5,27));
		lblDodge->setColor(ccc3(12,193,237));
		lblDodge->setTag(107);
		parent->addChild(lblDodge);

        btn->setVisible(false);
	} else {
		CCLabelTTF *lblDefence = (CCLabelTTF *)parent->getChildByTag(105);
		lblDefence->removeFromParentAndCleanup(true);

		CCLabelTTF *lblSuper = (CCLabelTTF *)parent->getChildByTag(106);
		lblSuper->removeFromParentAndCleanup(true);

		CCLabelTTF *lblDodge = (CCLabelTTF *)parent->getChildByTag(107);
		lblDodge->removeFromParentAndCleanup(true);

//		CCLabelTTF *lblCardName = (CCLabelTTF *)parent->getChildByTag(99);
//		lblCardName->setVisible(true);

		CCLabelTTF *lblCardLevel = (CCLabelTTF *)parent->getChildByTag(100);
		lblCardLevel->setVisible(true);

		CCSprite *sCard = (CCSprite *)parent->getChildByTag(101);
		sCard->setVisible(true);

		CCLabelTTF *lblAttack = (CCLabelTTF *)parent->getChildByTag(102);
		lblAttack->setPosition(ccpAdd(lblAttack->getPosition(),ccp(0,-40)));

		CCLabelTTF *lblHP = (CCLabelTTF *)parent->getChildByTag(103);
		lblHP->setPosition(ccpAdd(lblHP->getPosition(),ccp(0,-40)));

		CCControlButton *btnUp = (CCControlButton *)parent->getChildByTag(1);
        btnUp->setVisible(true);

        btn->removeFromParentAndCleanup(true);
	}
}

void MDHerosFormationLayer::menuItemCallback(CCObject* pSender)
{
	CCMenuItemSprite *sprite = (CCMenuItemSprite*)pSender;

}

void MDHerosFormationLayer::buttonClicked(CCObject * sender , CCControlEvent controlEvent)
{
	MainGameScene *mainScene = (MainGameScene *)this->getParent();
	CCControlButton *button = (CCControlButton *)sender;
    switch (button->getTag()) {
        case 101:
        {
            mainScene->PopLayer();
            break;
        }
	}
}

MDHerosFormationLayer::MDHerosFormationLayer()
{
	m_lblFightCapacity = NULL;
}

MDHerosFormationLayer::~MDHerosFormationLayer()
{
	CC_SAFE_RELEASE(m_lblFightCapacity);
}

