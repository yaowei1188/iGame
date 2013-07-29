//
//  MainGameScene.cpp
//  cctest
//
//  Created by China Team on 4/9/13.
//
//

#include "MainSceneTemplate.h"



MainSceneTemplate::MainSceneTemplate()
{
    this->mlblName = NULL;
    this->mlblHealth = NULL;
    this->mlblPower = NULL;
    this->mlblGold = NULL;
    this->mlblBronze = NULL;
    this->mlblGrade = NULL;
    this->m_sPlayerContainer = NULL;
}

MainSceneTemplate::~MainSceneTemplate()
{
    CC_SAFE_RELEASE(mlblName);
    CC_SAFE_RELEASE(mlblHealth);
    CC_SAFE_RELEASE(mlblPower);
    CC_SAFE_RELEASE(mlblGold);
    CC_SAFE_RELEASE(mlblBronze);
    CC_SAFE_RELEASE(mlblGrade);
    
    CC_SAFE_RELEASE(m_sPlayerContainer);
}

void MainSceneTemplate::updateUserInfo(int hp,int maxhp,int exp,int maxExp,int grade,int gold)
{
	if (maxhp!=0.0)
	{
		hpBar->setPercent((float)hp / (float)maxhp);
		string _result = IntToString(hp)+"/" + IntToString(maxhp);
		this->mlblHealth->setString(_result.c_str());
	}
    
	if (maxExp!=0.0)
	{
		expBar->setPercent((float)exp / (float)maxExp);
		string _result = IntToString(exp)+"/" + IntToString(maxExp);
		this->mlblPower->setString(_result.c_str());
	}

	if (grade>0)
	{
		this->mlblGrade->setString(IntToString(grade).c_str());
	}
	
	if (gold>0)
	{
		this->mlblGold->setString(IntToString(gold).c_str());
	}
}

void MainSceneTemplate::onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader)
{
	std::string text = ShowString("sun");

    this->mlblName->setString(text.c_str());
    this->mlblHealth->setZOrder(20);
    this->mlblPower->setZOrder(10);

    hpBar = MDProgressBar::create("x1.png","x2.png","x3.png",84,0.5);
    hpBar->setPosition(ccp(43, 398));
    this->addChild(hpBar);

    expBar = MDProgressBar::create("t1.png","t2.png","t3.png",84,1.0);
    expBar->setPosition(ccp(201, 398));
    this->addChild(expBar);
    
//    CCSpriteBatchNode *batchNode = CCSpriteBatchNode::create("main.png");
//    this->addChild(batchNode);

//    CCSprite *lhCap = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("x1.png"));
//	CCScale9Sprite *mhCap = CCScale9Sprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("x2.png"));
//    CCSprite *rhCap = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("x3.png"));
//    lhCap->setAnchorPoint(ccp(0,0.5));
//    lhCap->setPosition(ccp(43,399));
//    mhCap->setPosition(ccp(48,399));
//    mhCap->setAnchorPoint(ccp(0,0.5));
//    mhCap->setContentSize(CCSizeMake(82, 9));
//    rhCap->setAnchorPoint(ccp(0,0.5));
//    rhCap->setPosition(ccp(130,399));
//    
//    batchNode->addChild(lhCap);
//    this->addChild(mhCap);
//    batchNode->addChild(rhCap);

//    CCSprite *lpCap = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("t1.png"));
//	CCScale9Sprite *mpCap = CCScale9Sprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("t2.png"));
//    CCSprite *rpCap = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("t3.png"));
//    lpCap->setAnchorPoint(ccp(0,0.5));
//    lpCap->setPosition(ccp(201,399));
//    mpCap->setPosition(ccp(206,399));
//    mpCap->setAnchorPoint(ccp(0,0.5));
//    mpCap->setContentSize(CCSizeMake(83, 9));
//    rpCap->setAnchorPoint(ccp(0,0.5));
//    rpCap->setPosition(ccp(289,399));
//    
//    batchNode->addChild(lpCap);
//    this->addChild(mpCap);
//    batchNode->addChild(rpCap);

	//CCDictionary *userInfo = GlobalData::getUserinfo();
	//CCNumber* fraction = (CCNumber*)userInfo->objectForKey("fraction");
	//if(fraction->getIntValue()==FACTION_FAIRY)
	//{
	//	m_sPlayerContainer->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(SPRITE_FACTION_FAIRY_CONTAINER));
	//}
	//else if (fraction->getIntValue()==FACTION_BUDDHA)
	//{
	//	m_sPlayerContainer->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(SPRITE_FACTION_BUDDHA_CONTAINER));
	//}
	//else if (fraction->getIntValue()==FACTION_DEMON)
	//{
	//	m_sPlayerContainer->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(SPRITE_FACTION_DEMON_CONTAINER));
	//}
}

bool MainSceneTemplate::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mlblName", CCLabelTTF*, this->mlblName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mlblHealth", CCLabelTTF*, this->mlblHealth);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mlblPower", CCLabelTTF*, this->mlblPower);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mlblBronze", CCLabelTTF*, this->mlblBronze);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mlblGold", CCLabelTTF*, this->mlblGold);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mlblGrade", CCLabelTTF*, this->mlblGrade);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_sPlayerContainer", CCSprite*, this->m_sPlayerContainer);
    
    return true;
}

void MainSceneTemplate::toolBarBtnClicked(CCObject *pSender, CCControlEvent pCCControlEvent) {
	CCLOG("button clicked");
}

void MainSceneTemplate::menuBarBtnClicked(CCObject *pSender)
{
    CCMenuItem *button = (CCMenuItem*) pSender;
    if(m_delegate != NULL) {
        m_delegate->menuItemClickedCallBack(button);
    }
}

SEL_MenuHandler MainSceneTemplate::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "menuBarBtnClicked:", MainSceneTemplate::menuBarBtnClicked);
	return NULL;
}

SEL_CCControlHandler MainSceneTemplate::onResolveCCBCCControlSelector(CCObject *pTarget, const char * pSelectorName) {
    
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "toolBarBtnClicked:", MainSceneTemplate::toolBarBtnClicked);
	return NULL;
}

bool MainSceneTemplate::init()
{
    return true;
}
