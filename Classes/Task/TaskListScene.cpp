#include "TaskListScene.h"

#define TASK_COLUMN  3
#define TASK_ROW  3

CCScene* TaskListScene::scene()
{
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		TaskListScene *layer = TaskListScene::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool TaskListScene::init()
{
	selectedindex = -1;

	bool bRet = false;
	do 
	{
		//////////////////////////////////////////////////////////////////////////
		// super init first
		//////////////////////////////////////////////////////////////////////////

		CC_BREAK_IF(! CCLayer::init());

		this->retrieveCurrentTask();

		//mArrayList =  CCArray::create();
		//mArrayList = CCArray::create(CCString::create("Li1"),CCString::create("张三"),CCString::create("Li3"),CCString::create("李四"),CCString::create("Li1653"),CCString::create("Li1qwe"),CCString::create("Li1"),CCString::create("Li1"),CCString::create("Li409"),CCString::create("Li134"),CCString::create("Li51"),CCString::create("Li18974523"),CCString::create("Li1"),CCString::create("Li1"),CCString::create("Li1"),CCString::create("Li1"),CCString::create("Li1"),CCString::create("Li124"),CCString::create("Li1998"),CCString::create("Li3561"),NULL);
		//mArrayList->retain();

		bRet = true;
	} while (0);

	return bRet;
}

void TaskListScene::retrieveCurrentTask()
{
	this->ShowLoadingIndicator("");

	CCHttpRequest *request = new CCHttpRequest();
	request->setRequestType(CCHttpRequest::kHttpGet);
	request->setResponseCallback(this,callfuncND_selector(TaskListScene::requestFinishedCallback));
	request->setTag("101");

	string _strUrl = CompleteUrl(URL_TASK_RETRIEVE_CURRENT);
	_strUrl.append(CCUserDefault::sharedUserDefault()->getStringForKey("userinfo"));

	request->setUrl(_strUrl.c_str());

	CCHttpClient *client = CCHttpClient::getInstance();
	client->send(request);

	request->release();

	/*this->ShowLoadingIndicator("");

	CCHttpRequest *request = new CCHttpRequest();
	request->setRequestType(CCHttpRequest::kHttpPost);
	request->setResponseCallback(this,callfuncND_selector(TaskListScene::requestFinishedCallback));
	request->setTag("101");

	string _strUrl = CompleteUrl(URL_TASK_RETRIEVE_CURRENT);
	string _strPostData("encryptedUserInfo=");
	_strPostData.append(CCUserDefault::sharedUserDefault()->getStringForKey("userinfo"));
	request->setRequestData(_strPostData.c_str(), _strPostData.length());

	request->setUrl(_strUrl.c_str());

	CCHttpClient *client = CCHttpClient::getInstance();
	client->send(request);

	request->release();*/
}

void TaskListScene::requestFinishedCallback(CCNode* pSender,void *Rspdata)
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
		mArrayList = dynamic_cast<CCArray *>(dictionary->objectForKey("friendList"));
		if (mArrayList==NULL)
		{
			return;
		}

		selectedindex = -1;
//		mTableView->reloadData();
	} else if (requestTag == "102"){

	}
}

bool TaskListScene::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
//	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mTableView", CCTableView*, this->mTableView);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_lblTitle", CCLabelTTF*, this->m_lblTitle);
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


void TaskListScene::showTaskLists()
{
    mArrayList = CCArray::createWithCapacity(24);

    CCSize windowSize = CCDirector::sharedDirector()->getOpenGLView()->getDesignResolutionSize();

    for (int i = 0;i<24;i++)
    {
        CCMenuItemSprite* itmspr = NULL;
        CCSprite *sNormal = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("task_normal.png"));
        CCSprite *sSelected = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("task_progress.png"));
        CCSprite *sLocked = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("task_locked.png"));

        if (i > 3) {
            itmspr = CCMenuItemSprite::create(sLocked, NULL, NULL, this, NULL);
        } else {
            itmspr = CCMenuItemSprite::create(sNormal, sSelected, sLocked, this, menu_selector(TaskListScene::menuItemCallback));
        }
        itmspr->setTag(i);
        mArrayList->addObject(itmspr);
    }

    CCPoint p = ccp(100,80);

    float eWidth =  (TASK_COLUMN-1)*(p.x);
    float eHeight = (TASK_ROW-1)*(p.y);

    CCPoint menuPosition = ccp(windowSize.width/2.0f -eWidth/2.0f ,
                               windowSize.height/2.0f + 30);

    sliderMenu = SlidingMenuGrid::menuWithArray(mArrayList,TASK_COLUMN,TASK_ROW,menuPosition,p );
    sliderMenu->setAnchorPoint(ccp(0.5, 0.5));
    sliderMenu->setContentSize(CCSizeMake(280,400));
    
    this->addChild(sliderMenu);
}

void TaskListScene::onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader)
{
	//doSearchFriend();
    showTaskLists();
}

void TaskListScene::menuItemCallback(CCObject* pSender)
{
    CCLOG ("Item CLICKED: %d",  ((CCMenuItemSprite*)pSender)->getTag());

//    CCMessageDialog *box = CCMessageDialog::create();
//    box->setTitle("Are you sure add this guy as your friends?");
//    box->setDelegate(this);
//    this->addChild(box);
    
    MainGameScene *mainScene = (MainGameScene *)this->getParent();
    mainScene->PushLayer((CCLayer *)this->GetLayer("TaskDetailScene"));
}

void TaskListScene::didClickButton(CCMessageDialog* dialog,unsigned int index)
{
	if (index == 0)
	{
		CCDictionary *dict = (CCDictionary *)mArrayList->objectAtIndex(selectedindex);
		string encryptedUserInfo(dict->valueForKey("encryptedUserInfo")->getCString());
		this->executeTask(encryptedUserInfo);
	}
}

void TaskListScene::executeTask(std::string &targetUser)
{
	CCHttpRequest *request = new CCHttpRequest();
	request->setRequestType(CCHttpRequest::kHttpGet);
	request->setResponseCallback(this,callfuncND_selector(TaskListScene::requestFinishedCallback));
	request->setTag("103");

	string _strUrl = CompleteUrl(URL_FRIEND_DELETE);
	_strUrl.append(CCUserDefault::sharedUserDefault()->getStringForKey("userinfo"));
	_strUrl.append("/" + targetUser);

	request->setUrl(_strUrl.c_str());

	CCHttpClient *client = CCHttpClient::getInstance();
	client->send(request);

	request->release();
}

void TaskListScene::buttonClicked(CCObject * sender , CCControlEvent controlEvent)
{
	MainGameScene *mainScene = (MainGameScene *)this->getParent();
	CCControlButton *button = (CCControlButton *)sender;
	switch (button->getTag()) {
	case 101:
		CCLOG("11111");
		mainScene->PopLayer();
		break;
	case 102:
		CCLOG("22222");
        sliderMenu->gotoNextPage();
		break;
	}
}

TaskListScene::TaskListScene()
{
//	mTableView = NULL;
	//    mMainSceneTemp = NULL;
	mArrayList = NULL;
    m_lblTitle = NULL;
}

TaskListScene::~TaskListScene()
{
	//    mTableViewMail->release();
	//    mMainSceneTemp->release();
	//    mArrayList->release();
}

