//
//  MainInnerLayer.cpp
//  cctest
//
//  Created by China Team on 4/9/13.
//
//

#include "MainInnerLayer.h"
#include "MainGameScene.h"


MainInnerLayer::MainInnerLayer()
{
    mTableView = NULL;
    m_layToolBar = NULL;

	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("art_head.plist");
     
    mCardList =  CCArray::create();
	CardQueryCriteria *query = new CardQueryCriteria();
	query->cardName = "ft001_2;ft003_2;ft004_2;ft005_2;ft006_2;ft017_2";
	mCardList= GlobalData::getAllCardProfile(query);
 //   mCardList->addObject(CCString::create("head_rulaifo.png"));
 //   mCardList->addObject(CCString::create("head_sunwukong.png"));
 //   mCardList->addObject(CCString::create("head_erlangsheng.png"));
	//mCardList->addObject(CCString::create("head_rulaifo.png"));
	//mCardList->addObject(CCString::create("head_sunwukong.png"));
	//mCardList->addObject(CCString::create("head_erlangsheng.png"));

    mCardList->retain();

    this->mlblName = NULL;
    this->mlblHealth = NULL;
    this->mlblPower = NULL;
    this->mlblGold = NULL;
    this->mlblBronze = NULL;
    this->mlblGrade = NULL;
    this->m_sPlayerContainer = NULL;
    this->m_sCharacter = NULL;
    this->btnAgate = NULL;

}

MainInnerLayer::~MainInnerLayer()
{
    CC_SAFE_RELEASE(mTableView);
    CC_SAFE_RELEASE(m_layToolBar);

    CC_SAFE_RELEASE(mlblName);
    CC_SAFE_RELEASE(mlblHealth);
    CC_SAFE_RELEASE(mlblPower);
    CC_SAFE_RELEASE(mlblGold);
    CC_SAFE_RELEASE(mlblBronze);
    CC_SAFE_RELEASE(mlblGrade);
    CC_SAFE_RELEASE(btnAgate);

    CC_SAFE_RELEASE(m_sPlayerContainer);
}

void MainInnerLayer::getCharacterProfile()
{
	dictCharacter = GlobalData::getCardProfileByName("101");
}

void MainInnerLayer::updateUserInfo(int hp,int maxhp,int exp,int maxExp,int grade,int gold)
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

void MainInnerLayer::onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader)
{
    std::string text = ShowString("sun");

    this->mlblName->setString(text.c_str());
    this->mlblHealth->setZOrder(20);
    this->mlblPower->setZOrder(10);

    hpBar = MDProgressBar::create("x1.png","x2.png","x3.png",84,0.5);
    hpBar->setPosition(ccp(43, 361));
    this->addChild(hpBar);

    expBar = MDProgressBar::create("t1.png","t2.png","t3.png",84,1.0);
    expBar->setPosition(ccp(201, 361));
    this->addChild(expBar);

    CCDictionary *userInfo = GlobalData::getUserinfo();
	if (userInfo!=NULL)
	{    
		CCNumber* fraction = (CCNumber*)userInfo->objectForKey("fraction");
        if(fraction->getIntValue()==FACTION_FAIRY)
        {
            m_sPlayerContainer->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(SPRITE_FACTION_FAIRY_CONTAINER));
        }
        else if (fraction->getIntValue()==FACTION_BUDDHA)
        {
            m_sPlayerContainer->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(SPRITE_FACTION_BUDDHA_CONTAINER));
        }
        else if (fraction->getIntValue()==FACTION_DEMON)
        {
            m_sPlayerContainer->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(SPRITE_FACTION_DEMON_CONTAINER));
        }
	}

	mTableView->setDirection(kCCScrollViewDirectionHorizontal);
	mTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
	mTableView->setDataSource(this);
	mTableView->setViewSize(CCSizeMake(266, 65));
	mTableView->isPagingEnableX = true;
	mTableView->setBounceable(false);
	mTableView->setDelegate(this);
    
    mTableView->reloadData();

//    if (m_sCharacter==NULL) {
//        m_sCharacter = CCSprite::createWithSpriteFrameName("character_sunwukong.png");
//        m_sCharacter->setPosition(ccp(150,144));
//        this->addChild(m_sCharacter);
//
//        CCSize sSize = m_sCharacter->getContentSize();
//
//        this->glowEffect(ccp(sSize.width * 0.5,sSize.height * 0.5), CCSizeMake(5.0, 5.0f), ccc3(255, 230, 0), 1.0f, m_sCharacter);
//    }
}

void MainInnerLayer::tableCellHighlight(CCTableView* table, CCTableViewCell* cell)
{
    CCSprite *sSelected = (CCSprite*)cell->getChildByTag(121);
    sSelected->setVisible(true);
}

void MainInnerLayer::tableCellUnhighlight(CCTableView* table, CCTableViewCell* cell)
{
    CCSprite *sSelected = (CCSprite*)cell->getChildByTag(121);
    sSelected->setVisible(false);
}

void MainInnerLayer::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
	CCLOG("cell touched at index: %i", cell->getIdx());
	//if (selectedindex == cell->getIdx()) {
	//	selectedindex = -1;
	//} else {
	//	selectedindex = cell->getIdx();
	//}

	//table->reloadData();

	MainGameScene *mainScene = (MainGameScene *)this->getParent();
	mainScene->PushLayer((CCLayer *)this->GetLayer("MDHerosFormationLayer"));
}

unsigned int MainInnerLayer::numberOfCellsInTableView(CCTableView *table)
{
	return mCardList->count();
}

CCSize MainInnerLayer::cellSizeForTable(CCTableView *table)
{
	return CCSizeMake(66.5, 65);
}

CCSize MainInnerLayer::tableCellSizeForIndex(CCTableView *table, unsigned int idx)
{
	return CCSizeMake(66.5, 65);
}

CCTableViewCell* MainInnerLayer::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
	//CCString *string = (CCString *)mCardList->objectAtIndex(idx);
	CCDictionary *dict = (CCDictionary *)mCardList->objectAtIndex(idx);
	std::string strCardHeadName(((CCString *)dict->objectForKey("cardHeadImg"))->getCString());
	strCardHeadName.append(".png");

	bool selected = (idx==selectedindex);
    CCSprite *sCard = NULL;
    CCSprite *sSelected = NULL;
	CCTableViewCell *cell = table->dequeueCell();
	if (!cell) {
		cell = new CCTableViewCell();
		cell->autorelease();

//		CCSize size = this->tableCellSizeForIndex(table, idx);

		sSelected = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("card_selected.png"));
		sSelected->setVisible(false);
		sSelected->setTag(121);
		sSelected->setPosition(ccp(2,0));
		sSelected->setAnchorPoint(CCPointZero);
		cell->addChild(sSelected);

		sCard = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(strCardHeadName.c_str()));
		sCard->setTag(122);
		sCard->setPosition(ccp(2,0));
		sCard->setAnchorPoint(CCPointZero);
		cell->addChild(sCard);
	}
	else
	{
		sCard = (CCSprite*)cell->getChildByTag(122);
        sCard->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(strCardHeadName.c_str()));
	}

	return cell;
}

void MainInnerLayer::toolBarBtnClicked(CCObject *pSender, CCControlEvent pCCControlEvent) {
	CCLOG("button clicked");
    
    CCControlButton *button = (CCControlButton*) pSender;
    if(m_delegate != NULL) {
        m_delegate->toolBarButtonClickedCallBack(button);
    }
}

void MainInnerLayer::buttonClicked(CCObject *pSender, CCControlEvent pCCControlEvent) {
	CCLOG("button clicked");
}

bool MainInnerLayer::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mTableView", CCTableView*, this->mTableView);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_layToolBar", CCLayer*, this->m_layToolBar);

    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mlblName", CCLabelTTF*, this->mlblName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mlblHealth", CCLabelTTF*, this->mlblHealth);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mlblPower", CCLabelTTF*, this->mlblPower);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mlblBronze", CCLabelTTF*, this->mlblBronze);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mlblGold", CCLabelTTF*, this->mlblGold);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mlblGrade", CCLabelTTF*, this->mlblGrade);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "btnAgate", CCControlButton*, this->btnAgate);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_sPlayerContainer", CCSprite*, this->m_sPlayerContainer);
    return true;
}

SEL_MenuHandler MainInnerLayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
	return NULL;
}

SEL_CCControlHandler MainInnerLayer::onResolveCCBCCControlSelector(CCObject *pTarget, const char * pSelectorName) {
    
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "toolBarBtnClicked:", MainInnerLayer::toolBarBtnClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "buttonClicked:", MainInnerLayer::buttonClicked);
    
	return NULL;
}

bool MainInnerLayer::init()
{
    return true;
}

void MainInnerLayer::showTooBar(bool show)
{
    this->m_layToolBar->setVisible(show);
//	this->m_sCharacter->setVisible(show);
    this->btnAgate->setVisible(show);

	if (show)
	{
//		 CCSize sSize = m_sCharacter->getContentSize();
		//this->glowEffect(ccp(sSize.width * 0.5,sSize.height * 0.5), CCSizeMake(5.0, 5.0f), ccc3(255, 230, 0), 1.0f, m_sCharacter);
	}
}
