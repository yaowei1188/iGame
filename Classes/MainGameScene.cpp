//
//  MainGameScene.cpp
//  cctest
//
//  Created by China Team on 4/9/13.
//
//

#include "MainGameScene.h"

MainGameScene::MainGameScene()
{
    mMainSceneTemp = NULL;
    mMainLayer = NULL;
    mChatLayer = NULL;
    mlayArray = CCArray::create();
    mlayArray->retain();
}

MainGameScene::~MainGameScene()
{
    mlayArray->release();
}

void MainGameScene::onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader)
{
    this->mMainSceneTemp->setDelegate(this);
    this->mMainLayer->setDelegate(this);
    this->mlayArray->addObject(mMainLayer);
}

bool MainGameScene::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mMainSceneTemp", MainSceneTemplate*, this->mMainSceneTemp);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mMainLayer", MainInnerLayer*, this->mMainLayer);
//    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mChatLayer", ChatLayer*, this->mChatLayer);
    
    return true;
}

void MainGameScene::toolBarButtonClickedCallBack(CCControlButton *pSender) {

    switch (pSender->getTag()) {
        case TOOLBAR_BTN_COMPETITION_TAG:
            CCLOG("11111");
            break;
        case TOOLBAR_BTN_GOD_DEMON_TAG:
            CCLOG("22222");
            break;
        case TOOLBAR_BTN_RANKLIST_TAG:
            CCLOG("33333");
            break;
        case TOOLBAR_BTN_FRIENDS_TAG:
            this->PushLayer((CCLayer *)this->GetLayer("FriendListScene"));
            break;
        case TOOLBAR_BTN_ITEMS_TAG:
            CCLOG("55555");
            break;
        case TOOLBAR_BTN_MAIL_TAG:
            CCLOG("66666");
            this->PushLayer((CCLayer *)this->GetLayer("MailMainScene"));
            break;
        case TOOLBAR_BTN_SETTING_TAG:
            CCLOG("77777");
            queryDB();
            break;
        case 8:
            CCLOG("8888");
            this->AddChatLayer();
            break;
    }
}

void MainGameScene::menuItemClickedCallBack(CCMenuItem *pItem)
{
    int number=1;
    if (intSelectedMenu==pItem->getTag()) {
        if (MENUBAR_HERO_TAG == intSelectedMenu) {
            this->PopToNLayer(2);
        } else {
            this->PopToRoot();
        }
        return;
    }
    
    intSelectedMenu = pItem->getTag();
    
    CCLayer *layer = NULL;
    if (intSelectedMenu == MENUBAR_MAINPAGE_TAG) {
        layer = mMainLayer;
        mMainLayer->showTooBar(true);
    } else if (intSelectedMenu == MENUBAR_TASK_TAG) {
        layer = (CCLayer *)this->GetLayer("TaskListScene");
	} else if (intSelectedMenu == MENUBAR_COPY_TAG) {
		//layer = (CCLayer *)this->GetLayer("MDBattleLayer");
		layer = (CCLayer *)MDBattleLayer::create();
	} else if (intSelectedMenu == MENUBAR_HERO_TAG) {
		layer = (CCLayer *)this->GetLayer("MDHeroMainLayer");
	} else if (intSelectedMenu == MENUBAR_GROUP_TAG) {
		this->updateUserInfo(80,100,150,200,5,900);
		return;
		//layer = (CCLayer *)this->GetLayer("MDHeroMainLayer");
	} else if (intSelectedMenu == MENUBAR_SHOP_TAG) {
		//layer = (CCLayer *)this->GetLayer("MDHeroMainLayer");
	} else {
        return;
    }
    
    if (MENUBAR_HERO_TAG == intSelectedMenu) {
        if ((CCLayer *)mlayArray->objectAtIndex(0)==mMainLayer) {
            number = 2;
            mMainLayer->showTooBar(false);
        }
    }
    
    this->RemoveChatLayer();
    
    for (int i=mlayArray->count()-1; i>=number-1; i--) {
        CCLayer *layer = (CCLayer *)mlayArray->objectAtIndex(i);
        layer->removeFromParentAndCleanup(true);
        mlayArray->removeObjectAtIndex(i);
    }
    
    if (pItem->getTag() == MENUBAR_HERO_TAG) {
        if (number == 1) {
            mlayArray->addObject(mMainLayer);
            mMainLayer->setPosition(ccp(0, 38));
            mMainLayer->showTooBar(false);
            this->addChild(mMainLayer);
        }
    }
    
    mlayArray->addObject(layer);
    
    layer->setPosition(ccp(0, 38));
    this->addChild(layer);
}

void MainGameScene::PushLayer(CCLayer *subLayer,bool fromRight)
{
    this->RemoveChatLayer();
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCLayer *prevLayer = (CCLayer *)mlayArray->objectAtIndex(mlayArray->count()-1);
	prevLayer->setTouchPriority(-129);
    
    if (fromRight) {
        CCSequence *sequence = CCSequence::create(CCMoveBy::create(0.2, CCPointMake(-CCDirector::sharedDirector()->getWinSize().width,0)),CCCallFuncN::create(this, callfuncN_selector(MainGameScene::removeNodeCallBack)),NULL);
        
        prevLayer->runAction(sequence);
        
        subLayer->setPosition(ccp(0 + winSize.width,38));
        this->addChild(subLayer);
        subLayer->runAction(CCMoveTo::create(0.2, ccp(0,38)));
        
        this->mlayArray->addObject(subLayer);
    }
}

void MainGameScene::AddChatLayer()
{
    if (mChatLayer== NULL) {
        mChatLayer = (ChatLayer *)this->GetLayer("ChatLayer.ccbi");
    } else {
        return;
    }
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    mChatLayer->setPosition(ccp(0 - winSize.width,38));
    this->addChild(mChatLayer);
    mChatLayer->runAction(CCMoveTo::create(0.2, ccp(0,38)));
}

void MainGameScene::RemoveChatLayer()
{
    if (mChatLayer==NULL) {
        return;
    }
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCSequence *sequence = CCSequence::create(CCMoveBy::create(0.2, ccp(0 - winSize.width,0)),CCCallFuncN::create(this, callfuncN_selector(MainGameScene::removeNodeCallBack)),CCCallFunc::create(this, callfunc_selector(MainGameScene::SetNull)),NULL);
    
    mChatLayer->runAction(sequence);
}

void MainGameScene::SetNull()
{
    mChatLayer = NULL;
}

void MainGameScene::removeNodeCallBack(CCNode* pNode)
{
    pNode->removeFromParentAndCleanup(true);
}

void MainGameScene::removeAndCleanNodeCallBack(CCNode* pNode)
{
    pNode->removeFromParentAndCleanup(true);
    mlayArray->removeLastObject();
}

void MainGameScene::PopToRoot()
{
    this->PopToNLayer(1);
}

void MainGameScene::PopToNLayer(int nLayer)
{
    this->RemoveChatLayer();
    
    if (mlayArray->count()<=nLayer) {
        return;
    }
    
    for (int i=mlayArray->count()-2; i>=nLayer; i--) {
        CCLayer *layer = (CCLayer *)mlayArray->objectAtIndex(i);
        layer->removeFromParentAndCleanup(true);
        mlayArray->removeObjectAtIndex(i);
    }
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCLayer *current = (CCLayer *)mlayArray->objectAtIndex(mlayArray->count()-1);
    
    CCSequence *sequence = CCSequence::create(CCMoveBy::create(0.2, CCPointMake(winSize.width,0)),CCCallFuncN::create(this, callfuncN_selector(MainGameScene::removeAndCleanNodeCallBack)),NULL);
    
    current->runAction(sequence);
    
    CCLayer *layer = (CCLayer *)mlayArray->objectAtIndex(nLayer-1);
    
    layer->setPosition(ccp(-320, layer->getPosition().y));
    this->addChild(layer);
    layer->runAction(CCMoveTo::create(0.2, ccp(0,layer->getPosition().y)));
}

void MainGameScene::PopLayer()
{
    this->PopToNLayer(mlayArray->count()-1);
}

void MainGameScene::returnToMainLayer()
{
	intSelectedMenu = MENUBAR_MAINPAGE_TAG;

	this->RemoveChatLayer();

	for (int i=mlayArray->count()-1; i>=0; i--) {
		CCLayer *layer = (CCLayer *)mlayArray->objectAtIndex(i);
		layer->removeFromParentAndCleanup(true);
		mlayArray->removeObjectAtIndex(i);
	}

	mlayArray->addObject(mMainLayer);
    mMainLayer->showTooBar(true);
	mMainLayer->setPosition(ccp(0, 38));
	this->addChild(mMainLayer);
}

int LoadMyInfo( void * para, int n_column, char ** column_value, char ** column_name )
{
    int i;
    printf("记录包含 %d 个字段/n", n_column );
    for( i = 0 ; i < n_column; i ++ )
    {
        printf( "字段名:%s  ß> 字段值:%s/n",  column_name[i], column_value[i] );
    }
    printf( "------------------/n");
    return 0;
}

void MainGameScene::queryDB()
{
    sqlite3 *pDB = NULL;
    char* errMsg = NULL;
    std::string sqlstr;
    int result;
    std::string dbPath = CCFileUtils::sharedFileUtils()->fullPathForFilename("Settings.db");
//    dbPath.append("Settings.db");
    result = sqlite3_open(dbPath.c_str(),&pDB);

    std::string szSql="select * from MyTable_1";

    int rc = sqlite3_exec(pDB,szSql.c_str(), LoadMyInfo, NULL, &errMsg);
    
//    sqlite3 *pDB = NULL;
//    char* errMsg = NULL;
//    std::string sqlstr;
//    int result;
//    std::string dbPath = CCFileUtils::sharedFileUtils()->getWritablePath();
//    dbPath.append("Settings.db");
//    result = sqlite3_open(dbPath.c_str(),&pDB);

//    //make table
//    result=sqlite3_exec( pDB, "create table MyTable_1( ID integer primary key autoincrement, name nvarchar(32),password nvarchar(32) ) " , NULL, NULL, &errMsg );
//
//    //insert name column
//    sqlstr=" insert into MyTable_1( name ) values ( 'Takashi' ) ";
//    result = sqlite3_exec( pDB, sqlstr.c_str() , NULL, NULL, &errMsg );
//
//    //insert password column(Here's my Problem)
//    //I want to insert string variable into password column.
//    string pass;
//    pass = "aaaaaaa";
//    sqlstr="insert into MyTable_1( password ) values('pass')";
//
//    //closing sqlite
//    sqlite3_close(pDB);
}

SEL_MenuHandler MainGameScene::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
//	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "menuBarBtnClicked:", MainGameScene::menuBarBtnClicked);
//    
	return NULL;
}

SEL_CCControlHandler MainGameScene::onResolveCCBCCControlSelector(CCObject *pTarget, const char * pSelectorName) {
    
//    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "toolBarBtnClicked:", MainGameScene::toolBarBtnClicked);
    
	return NULL;
}

void MainGameScene::updateUserInfo(int hp,int maxhp,int exp,int maxExp,int grade,int gold)
{
	mMainSceneTemp->updateUserInfo(hp, maxhp, exp, maxExp,grade,gold);
}

bool MainGameScene::init()
{
    return true;
}

CCScene* MainGameScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // add layer as a child to scene
    CCLayer* layer = new MainGameScene();
    scene->addChild(layer);
    layer->release();
    
    return scene;
}
