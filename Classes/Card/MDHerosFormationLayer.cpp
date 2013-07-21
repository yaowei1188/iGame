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
		//////////////////////////////////////////////////////////////////////////
		// super init first
		//////////////////////////////////////////////////////////////////////////

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

		CCControlButton *btn = CCControlButton::create(scaleSprite);
		btn->setPreferredSize(CCSizeMake(150 * 0.71,205 * 0.71));
		btn->setAnchorPoint(ccp(0.5,0.5));
		CCSize spriteSize = scaleSprite->getContentSize();
		btn->setPosition(ccp(spriteSize.width * 0.5 + col++ * spriteSize.width,winSize.height - spriteSize.height * 0.5  - 45 - row * spriteSize.height));

		if (i<4)
		{
			CCLabelTTF *lblCardName = CCLabelTTF::create("erlangsheng", "Arial", 14.0);
			lblCardName->setAnchorPoint(ccp(0.5,1));
			lblCardName->setPosition(ccp(spriteSize.width * 0.5,spriteSize.height - 10));

			CCLabelTTF *lblCardLevel = CCLabelTTF::create("Lv.100", "Arial", 14.0);
			lblCardLevel->setAnchorPoint(ccp(0.5,1));
			lblCardLevel->setPosition(ccp(spriteSize.width * 0.5,spriteSize.height - 100));

			std::string strGroup = determineGroup(CCString::create("1"));
			CCSprite *sCardGroup = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(strGroup.c_str()));
			sCardGroup->setAnchorPoint(ccp(1,1));
			sCardGroup->setPosition(ccp(spriteSize.width - 5,spriteSize.height - 10));

			CCSprite *sCard = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("head_erlangsheng.png"));
			sCard->setAnchorPoint(ccp(0.5,1));
			sCard->setPosition(ccp(spriteSize.width * 0.5,spriteSize.height - 36));

			scaleSprite->addChild(sCard);
			scaleSprite->addChild(lblCardName);
			scaleSprite->addChild(lblCardLevel);
			scaleSprite->addChild(sCardGroup);

			CCControlButton *dropup = CCControlButton::create(CCScale9Sprite::createWithSpriteFrameName("card_embattle_dropup.png"));
			dropup->setBackgroundSpriteForState(CCScale9Sprite::createWithSpriteFrameName("card_embattle_dropup_highlight.png"),CCControlStateHighlighted);
			scaleSprite->addChild(dropup);
			dropup->setPreferredSize(CCSizeMake(96,15));
			dropup->setAnchorPoint(ccp(0.5,0));
			dropup->setPosition(ccp(spriteSize.width * 0.5,7));
			dropup->setZoomOnTouchDown(false);
		}

		this->addChild(btn);

		if ((i+1) % 3 == 0)
		{
			row++;
			col = 0;
		}
	}
	
}

void MDHerosFormationLayer::menuItemCallback(CCObject* pSender)
{
	CCMenuItemSprite *sprite = (CCMenuItemSprite*)pSender;

}

std::string MDHerosFormationLayer::determineGroup(CCString* number)
{
	if (number->intValue()==1) {
		return "friends_dairy.png";
	} else if (number->intValue()==2) {
		return "friends_fo.png";
	} else if (number->intValue()==3) {
		return "friends_wizard.png";
	}
	return "";
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

