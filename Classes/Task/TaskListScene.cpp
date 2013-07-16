#include "TaskListScene.h"
#include "TaskDetailScene.h"

#define TASK_COLUMN  3
#define TASK_ROW  3

//CCScene* TaskListScene::scene()
//{
//	CCScene * scene = NULL;
//	do 
//	{
//		// 'scene' is an autorelease object
//		scene = CCScene::create();
//		CC_BREAK_IF(! scene);
//
//		// 'layer' is an autorelease object
//		TaskListScene *layer = TaskListScene::create();
//		CC_BREAK_IF(! layer);
//
//		// add layer as a child to scene
//		scene->addChild(layer);
//	} while (0);
//
//	// return the scene
//	return scene;
//}

// on "init" you need to initialize your instance
bool TaskListScene::init()
{
	selectedindex = 2;

	bool bRet = false;
	do 
	{
		//////////////////////////////////////////////////////////////////////////
		// super init first
		//////////////////////////////////////////////////////////////////////////

        mTaskList = CCArray::create();
        mTaskList->retain();
        
        mTaskList->addObject(CCString::create("test1"));
        mTaskList->addObject(CCString::create("test2"));
        mTaskList->addObject(CCString::create("test3"));
        mTaskList->addObject(CCString::create("test4"));
        mTaskList->addObject(CCString::create("test5"));
        mTaskList->addObject(CCString::create("test6"));
        
		CC_BREAK_IF(! CCLayer::init());

		bRet = true;
	} while (0);

	return bRet;
}

void TaskListScene::retrieveCurrentTask()
{
	this->ShowLoadingIndicator("");

	CCHttpRequest *request = new CCHttpRequest();
	request->setRequestType(CCHttpRequest::kHttpPost);
	request->setResponseCallback(this,httpresponse_selector(TaskListScene::requestFinishedCallback));
	request->setTag("101");

	string _strUrl = CompleteUrl(URL_TASK_RETRIEVE_CURRENT);
	string _strPostData("encryptedUserInfo=");
	_strPostData.append(CCUserDefault::sharedUserDefault()->getStringForKey("userinfo"));
	_strPostData.append("&userGameRoleId=" + CCUserDefault::sharedUserDefault()->getStringForKey("gameRoleId"));
	request->setRequestData(_strPostData.c_str(), _strPostData.length());

	request->setUrl(_strUrl.c_str());

	CCHttpClient *client = CCHttpClient::getInstance();
	client->send(request);

	request->release();
}

void TaskListScene::requestFinishedCallback(CCHttpClient* client, CCHttpResponse* response)
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

	if (requestTag == "101") 
	{
		mTaskDict = dynamic_cast<CCDictionary *>(dictionary->objectForKey("gameRoleCurrentTaskResponse"));
		if (mTaskDict == NULL)
		{
			return;
		}
		upperIndex = ((CCNumber*)mTaskDict->objectForKey("index"))->getIntValue();
		subIndex = ((CCNumber*)mTaskDict->objectForKey("subIndex"))->getIntValue();

		if (upperIndex==0)
		{
			upperIndex++;
		}

		if (subIndex==0)
		{
			subIndex++;
		}

		if (subIndex==10)
		{
			upperIndex++;
			subIndex=0;
		}

		this->showTaskLists();

	} else if (requestTag == "102")
	{

	}
}

bool TaskListScene::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mTableView", CCTableView*, this->mTableView);
	return true;
}

SEL_MenuHandler TaskListScene::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
	return NULL;
}

SEL_CCControlHandler TaskListScene::onResolveCCBCCControlSelector(CCObject *pTarget, const char * pSelectorName) {

	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "buttonClicked:", TaskListScene::buttonClicked);
	return NULL;
}

unsigned int TaskListScene::numberOfCellsInTableView(CCTableView *table)
{
	return mTaskList->count();
}

CCSize TaskListScene::cellSizeForTable(CCTableView *table)
{
	return CCSizeMake(60, 38);
}

CCSize TaskListScene::tableCellSizeForIndex(CCTableView *table, unsigned int idx)
{
	return CCSizeMake(60, 38);
}

void TaskListScene::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
    
}

CCTableViewCell* TaskListScene::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
	CCString *string = (CCString *)mTaskList->objectAtIndex(idx);
    CCSprite *sSelected = NULL;
	CCTableViewCell *cell = table->dequeueCell();
    CCLabelTTF *_lblTaskName = NULL;
    
    CCSize size = this->tableCellSizeForIndex(table,idx);
    
	if (!cell) {
		cell = new CCTableViewCell();
		cell->autorelease();
        
		sSelected = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("task_selected.png"));
		sSelected->setTag(122);
		sSelected->setPosition(ccp(size.width * 0.5,size.height * 0.5));
        if (selectedindex == idx) {
            sSelected->setVisible(true);
        } else {
            sSelected->setVisible(false);
        }

		cell->addChild(sSelected);
        
        _lblTaskName = CCLabelTTF::create(string->getCString(), "Arial", 14);
        _lblTaskName->setTag(123);
		_lblTaskName->setPosition(ccp(size.width * 0.5,size.height * 0.5));
		cell->addChild(_lblTaskName);
	}
	else
	{
		sSelected = (CCSprite*)cell->getChildByTag(122);
        if (selectedindex == idx) {
            sSelected->setVisible(true);
        } else {
            sSelected->setVisible(false);
        }
        
        _lblTaskName = (CCLabelTTF*)cell->getChildByTag(123);
        _lblTaskName->setString(string->getCString());
	}
    
	return cell;
}

void TaskListScene::showTaskLists()
{
    mArrayList = CCArray::create();
	mArrayList->retain();

    CCSize windowSize = CCDirector::sharedDirector()->getWinSize();

    for (int i = 1;i<= 24 ;i++)
    {
        CCMenuItemSprite* itmspr = NULL;
        CCSprite *sNormal = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("task_normal.png"));
        CCSprite *sSelected = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("task_progress.png"));
        CCSprite *sLocked = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("task_locked.png"));
		CCSprite *sPassed = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("task_passed.png"));

        if (i > upperIndex) {
            itmspr = CCMenuItemSprite::create(sLocked, NULL, NULL, NULL, NULL);
        } else if (i == upperIndex) {
            itmspr = CCMenuItemSprite::create(sNormal, sSelected, sLocked, this, menu_selector(TaskListScene::menuItemCallback));
		} else if (i < upperIndex) { 
			itmspr = CCMenuItemSprite::create(sPassed, NULL, NULL, NULL, NULL);
		}
        itmspr->setTag(i);
        mArrayList->addObject(itmspr);
    }

    CCPoint p = ccp(100,80);

    float eWidth =  (TASK_COLUMN-1)*(p.x);

    CCPoint menuPosition = ccp(windowSize.width/2.0f -eWidth/2.0f , windowSize.height/2.0f + 30);

    sliderMenu = SlidingMenuGrid::menuWithArray(mArrayList,TASK_COLUMN,TASK_ROW,menuPosition,p );
    sliderMenu->setAnchorPoint(ccp(0.5, 0.5));
    sliderMenu->setContentSize(CCSizeMake(280,400));
    
    this->addChild(sliderMenu);
}

void TaskListScene::onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader)
{
    mTableView->setDirection(kCCScrollViewDirectionHorizontal);
	mTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
	mTableView->setDataSource(this);
	mTableView->setViewSize(CCSizeMake(300, 38));
	mTableView->isPagingEnableX = true;
	mTableView->setBounceable(false);
	mTableView->setDelegate(this);
    
    mTableView->reloadData();
    
	this->retrieveCurrentTask();
}

void TaskListScene::menuItemCallback(CCObject* pSender)
{
    CCLOG ("Item CLICKED: %d",  ((CCMenuItemSprite*)pSender)->getTag());

    MainGameScene *mainScene = (MainGameScene *)this->getParent();
	TaskDetailScene *detailScene = (TaskDetailScene *)this->GetLayer("TaskDetailScene");
	detailScene->upperIndex = this->upperIndex;
	detailScene->subIndex = this->subIndex;
    mainScene->PushLayer(detailScene);
}

void TaskListScene::buttonClicked(CCObject * sender , CCControlEvent controlEvent)
{
	MainGameScene *mainScene = (MainGameScene *)this->getParent();
	CCControlButton *button = (CCControlButton *)sender;
	switch (button->getTag()) {
	case 101:
		CCLOG("11111");
		mainScene->returnToMainLayer();
		break;
	case 102:
		CCLOG("22222");
        sliderMenu->gotoNextPage();
		break;
	}
}

TaskListScene::TaskListScene()
{
	mArrayList = NULL;
    mTableView = NULL;
}

TaskListScene::~TaskListScene()
{
    CC_SAFE_RELEASE(mTableView);
}

