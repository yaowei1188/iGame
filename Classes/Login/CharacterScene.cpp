#include "CharacterScene.h"
#include "JsonBox.h"

using namespace cocos2d;

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

		config.aLength = 100;
		config.cLength = 30;
		//config.startAngle = M_PI * 1/3;
		config.centerPosition = ccp(160,320);

        ////////////////////////////////////////////////////////////////////////////
        //// add your codes below...
        ////////////////////////////////////////////////////////////////////////////
        
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

	spritFou = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("fou.png"));
    spriteXian = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("xian.png"));
	spriteYao = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("yao.png"));
	//spritFou->setAnchorPoint(ccp(0.5,0.5));
	//spriteXian->setAnchorPoint(ccp(0,0));
	//spriteYao->setAnchorPoint(ccp(0,0));

	this->addChild(spriteXian);
	this->addChild(spriteYao);
		this->addChild(spritFou);

	CCPoint point = ccpAdd(config.centerPosition,ccp(tuoyuanXat(config.aLength,config.cLength,M_PI * 0/3,0.0),tuoyuanYat(config.aLength,config.cLength,M_PI * 0/3,0.0)));
	CCPoint point1 = ccpAdd(config.centerPosition,ccp(tuoyuanXat(config.aLength,config.cLength,M_PI * 1/3,0.0),tuoyuanYat(config.aLength,config.cLength,M_PI * 1/3,0.0)));
	CCPoint point2 = ccpAdd(config.centerPosition,ccp(tuoyuanXat(config.aLength,config.cLength,M_PI * 2/3,0.0),tuoyuanYat(config.aLength,config.cLength,M_PI * 2/3,0.0)));

	spritFou->setPosition(point);
	spriteXian->setPosition(point1);
	spriteYao->setPosition(point2);
	//this->doEllipse();
}

void CharacterScene::doEllipse()
{
	lrEllipseConfig config1= config;
	config1.startAngle = M_PI * 0/3;
	EllipseActionInterval *ellipse = EllipseActionInterval::actionWithDuration(1,config1);
	spritFou->runAction(ellipse);

	lrEllipseConfig config2= config;
	config2.startAngle = M_PI * 1/3;
	EllipseActionInterval *ellipse1 = EllipseActionInterval::actionWithDuration(1,config2);
	spriteXian->runAction(ellipse1);

	lrEllipseConfig config3= config;
	config3.startAngle = M_PI * 2/3;
	EllipseActionInterval *ellipse2 = EllipseActionInterval::actionWithDuration(1,config3);
	spriteYao->runAction(ellipse2);
}

bool CharacterScene::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_txtAccount", CCEditBox*, this->m_txtAccount);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_Imggroup", CCSprite*, this->m_ImgGroup);
    return true;
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

