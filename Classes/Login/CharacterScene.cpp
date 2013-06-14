#include "CharacterScene.h"
#include "JsonBox.h"

using namespace cocos2d;

#define ELLIPSE_WIDTH 100
#define ELLIPSE_HEIGHT 30

CharacterScene::CharacterScene()
{
    m_txtAccount = NULL;
	m_ImgGroup = NULL;
}

CharacterScene::~CharacterScene()
{
    CC_SAFE_RELEASE(m_txtAccount);
	CC_SAFE_RELEASE(m_ImgGroup);
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
		config1.startAngle = M_PI * 0/3;
		config1.centerPosition = ccp(winSize.width * 0.5,320);

        config2.aLength = ELLIPSE_WIDTH;
		config2.cLength = ELLIPSE_HEIGHT;
		config2.startAngle = M_PI * 1/3;
		config2.centerPosition = ccp(winSize.width * 0.5,320);

        config3.aLength = ELLIPSE_WIDTH;
		config3.cLength = ELLIPSE_HEIGHT;
		config3.startAngle = M_PI * 2/3;
		config3.centerPosition = ccp(winSize.width * 0.5,320);
        
        bRet = true;
    } while (0);

    return bRet;
}

void CharacterScene::doSubmit()
{
	CCHttpRequest *request = new CCHttpRequest();
	request->setRequestType(CCHttpRequest::kHttpGet);
	request->setResponseCallback(this,callfuncND_selector(CharacterScene::requestFinishedCallback));
	request->setTag("103");
    
	string _strUrl = CompleteUrl(URL_FRIEND_DELETE);
	_strUrl.append(CCUserDefault::sharedUserDefault()->getStringForKey("userinfo"));
    
	request->setUrl(_strUrl.c_str());
    
	CCHttpClient *client = CCHttpClient::getInstance();
	client->send(request);
    
	request->release();
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
    m_txtAccount->setFontColor(ccc3(255,255,153));
    m_txtAccount->setFont("Arial", 16);
    m_txtAccount->setPosition(ccp(148, 40));



//    spritFou = CCMenuItemSprite::create(CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("fou.png")), NULL, NULL, this, menu_selector(CharacterScene::menuItemCallback));
//
//    spriteXian = CCMenuItemSprite::create(CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("xian.png")), NULL, NULL, this, menu_selector(CharacterScene::menuItemCallback));
//
//    spriteYao = CCMenuItemSprite::create(CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("yao.png")), NULL, NULL, this, menu_selector(CharacterScene::menuItemCallback));
//
//    CCMenu *menu = CCMenu::create(spritFou,spriteXian,spriteYao);

	spritFou = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("fou.png"));
    spriteXian = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("xian.png"));
	spriteYao = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("yao.png"));
	//spritFou->setAnchorPoint(ccp(0.5,0.5));
	//spriteXian->setAnchorPoint(ccp(0,0));
	//spriteYao->setAnchorPoint(ccp(0,0));

    spriteXian->setUserData(&config1);
    spriteYao->setUserData(&config2);
    spritFou->setUserData(&config3);

	this->addChild(spriteXian);
	this->addChild(spriteYao);
    this->addChild(spritFou);

	CCPoint point = ccpAdd(config1.centerPosition,ccp(tuoyuanXat(config1.aLength,config1.cLength,M_PI * 0/3,0.0),tuoyuanYat(config1.aLength,config1.cLength,config1.startAngle,0.0)));
	CCPoint point1 = ccpAdd(config2.centerPosition,ccp(tuoyuanXat(config2.aLength,config2.cLength,M_PI * 1/3,0.0),tuoyuanYat(config2.aLength,config2.cLength,config2.startAngle,0.0)));
	CCPoint point2 = ccpAdd(config3.centerPosition,ccp(tuoyuanXat(config3.aLength,config3.cLength,M_PI * 2/3,0.0),tuoyuanYat(config3.aLength,config3.cLength,config3.startAngle,0.0)));

	spritFou->setPosition(point);
	spriteXian->setPosition(point1);
	spriteYao->setPosition(point2);
}

void CharacterScene::doEllipse()
{
	EllipseActionInterval *ellipse = EllipseActionInterval::actionWithDuration(1,config1);
	spritFou->runAction(CCSequence::create(ellipse,CCCallFuncN::create(this, callfuncN_selector(CharacterScene::animateEndCallBack()))));

	EllipseActionInterval *ellipse1 = EllipseActionInterval::actionWithDuration(1,config2);
    spriteXian->runAction(CCSequence::create(ellipse,CCCallFuncN::create(this, callfuncN_selector(CharacterScene::animateEndCallBack()))));

	EllipseActionInterval *ellipse2 = EllipseActionInterval::actionWithDuration(1,config3);
    spriteYao->runAction(CCSequence::create(ellipse,CCCallFuncN::create(this, callfuncN_selector(CharacterScene::animateEndCallBack()))));
}

bool CharacterScene::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_txtAccount", CCEditBox*, this->m_txtAccount);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_Imggroup", CCSprite*, this->m_ImgGroup);
    return true;
}

void CharacterScene::menuItemCallback(CCObject* pSender)
{
    CCMenuItemSprite *item = (CCMenuItemSprite*)pSender;
}

void CharacterScene::animateEndCallBack(CCNode *node)
{
    CCSprite *sprite = (CCSprite *)node;
    lrEllipseConfig *config = (lrEllipseConfig *)sprite->getUserData();
    config->startAngle += 2 * M_PI * 1/3;
}

void CharacterScene::buttonClicked(CCObject *pSender, CCControlEvent pCCControlEvent) {
    
    CCControlButton *button = (CCControlButton*) pSender;
    
	this->doEllipse();
	
    //switch (button->getTag()) {
    //    case LOGIN_BUTTON_ACTION_SIGNIN_TAG:
    //        CCLOG("signin");
    //        break;
    //}
}

SEL_MenuHandler CharacterScene::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
	return NULL;
}

SEL_CCControlHandler CharacterScene::onResolveCCBCCControlSelector(CCObject *pTarget, const char * pSelectorName) {
    
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "buttonClicked:", CharacterScene::buttonClicked);
	return NULL;
}

