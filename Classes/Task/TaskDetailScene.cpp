#include "TaskDetailScene.h"

#define TASK_COLUMN  3
#define TASK_ROW  3

CCScene* TaskDetailScene::scene()
{
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		TaskDetailScene *layer = TaskDetailScene::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool TaskDetailScene::init()
{
	selectedindex = 0;

	bool bRet = false;
	do 
	{
		//////////////////////////////////////////////////////////////////////////
		// super init first
		//////////////////////////////////////////////////////////////////////////

		CC_BREAK_IF(! CCLayer::init());

		//mTaskList =  CCArray::create();
//		mTaskList = CCArray::create(CCString::create("Li1"),CCString::create("’≈»˝"),CCString::create("Li3"),CCString::create("¿ÓÀƒ"),CCString::create("Li1653"),CCString::create("Li1qwe"),CCString::create("Li1"),CCString::create("Li1"),CCString::create("Li409"),CCString::create("Li134"),CCString::create("Li51"),CCString::create("Li18974523"),CCString::create("Li1"),CCString::create("Li1"),CCString::create("Li1"),CCString::create("Li1"),CCString::create("Li1"),CCString::create("Li124"),CCString::create("Li1998"),CCString::create("Li3561"),NULL);
		//mTaskList->retain();

		bRet = true;
	} while (0);

	return bRet;
}

void TaskDetailScene::doSearch()
{
	this->ShowLoadingIndicator("");

	CCHttpRequest *request = new CCHttpRequest();
	request->setRequestType(CCHttpRequest::kHttpGet);
	request->setResponseCallback(this,callfuncND_selector(TaskDetailScene::requestFinishedCallback));
	request->setTag("101");

	string _strUrl = CompleteUrl(URL_FRIEND_LIST);
	_strUrl.append(CCUserDefault::sharedUserDefault()->getStringForKey("userinfo"));

	request->setUrl(_strUrl.c_str());

	CCHttpClient *client = CCHttpClient::getInstance();
	client->send(request);

	request->release();
}

void TaskDetailScene::requestFinishedCallback(CCNode* pSender,void *Rspdata)
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
	} else if (requestTag == "102"){
		this->doSearch();
		CCMessageBox("delete friend successfully","Success");
	}
}

bool TaskDetailScene::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_sProgress", CCSprite*, this->m_sProgress);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_lblTitle", CCLabelTTF*, this->m_lblTitle);
	return true;
}

SEL_MenuHandler TaskDetailScene::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
	return NULL;
}

SEL_CCControlHandler TaskDetailScene::onResolveCCBCCControlSelector(CCObject *pTarget, const char * pSelectorName) {

	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "buttonClicked:", TaskDetailScene::buttonClicked);
	return NULL;
}


void TaskDetailScene::showTaskInfo()
{
    CCString *str = (CCString *)mTaskList->objectForKey("TaskName");
    CCArray *subTasks = (CCArray *)mTaskList->objectForKey("SubTasks");
    
    if (selectedindex>=subTasks->count()) {
        return;
    }
    
    CCDictionary *task = (CCDictionary *)subTasks->objectAtIndex(selectedindex);
    
    CCLabelTTF *lblCoins = NULL;
    CCLabelTTF *lblExperience = NULL;

    m_lblTitle->setString(str->getCString());

    if (lblSubTitle==NULL) {
        lblSubTitle = CCLabelTTF::create("", "Arial", 16);
        lblSubTitle->setAnchorPoint(CCPointZero);
        lblSubTitle->setPosition(ccp(20, 270));
        lblSubTitle->setColor(TITLE_COLOR);
		lblSubTitle->setTag(0);
        addChild(lblSubTitle);

        
		CCLabelTTF *lblTip = CCLabelTTF::create("即将获得", "Arial", 14);
		lblTip->setPosition(ccp(20, 230));
		lblTip->setAnchorPoint(CCPointZero);
		addChild(lblTip);


		lblCoins = CCLabelTTF::create("", "Arial", 14);
		lblCoins->setTag(2);
		lblCoins->setAnchorPoint(CCPointZero);
		lblCoins->setPosition(ccp(20, 200));
		addChild(lblCoins);

		CCSprite *sBao = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("yuanbao.png"));
		sBao->setPosition(ccp(100, 200));
		sBao->setAnchorPoint(CCPointZero);
		addChild(sBao);

		lblExperience = CCLabelTTF::create("", "Arial", 14);
		lblExperience->setAnchorPoint(CCPointZero);
		lblExperience->setTag(3);
		lblExperience->setPosition(ccp(150, 200));
		addChild(lblExperience);

		CCSprite *sStar = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("shuangxin.png"));
		sStar->setPosition(ccp(240, 200));
		sStar->setAnchorPoint(CCPointZero);
		addChild(sStar);
    } else {
        lblSubTitle = (CCLabelTTF *)getChildByTag(0);
		lblCoins = (CCLabelTTF *)getChildByTag(2);
		lblExperience = (CCLabelTTF *)getChildByTag(3);
    }
    
    lblSubTitle->setString(((CCString *)task->objectForKey("Title"))->getCString());
    
	string strCoins("游戏币+");
	strCoins += ((CCString *)task->objectForKey("Coins"))->getCString();
	lblCoins->setString(strCoins.c_str());

	string strExperience("经验+");
	strExperience += ((CCString *)task->objectForKey("Experience"))->getCString();
	lblExperience->setString(strExperience.c_str());
}

void TaskDetailScene::onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader)
{
	//doSearchFriend();
    
	mTaskList = GlobalData::getTasks("");
	mTaskList->retain();

	showTaskInfo();
}

//void TaskDetailScene::didClickButton(CCMessageDialog* dialog,unsigned int index)
//{
//	if (index == 0)
//	{
//		CCDictionary *dict = (CCDictionary *)mArrayList->objectAtIndex(selectedindex);
//		string encryptedUserInfo(dict->valueForKey("encryptedUserInfo")->getCString());
//		this->executeTask(encryptedUserInfo);
//	}
//}

void TaskDetailScene::executeTask(std::string &targetUser)
{
	CCHttpRequest *request = new CCHttpRequest();
	request->setRequestType(CCHttpRequest::kHttpGet);
	request->setResponseCallback(this,callfuncND_selector(TaskDetailScene::requestFinishedCallback));
	request->setTag("103");

	string _strUrl = CompleteUrl(URL_FRIEND_DELETE);
	_strUrl.append(CCUserDefault::sharedUserDefault()->getStringForKey("userinfo"));
	_strUrl.append("/" + targetUser);

	request->setUrl(_strUrl.c_str());

	CCHttpClient *client = CCHttpClient::getInstance();
	client->send(request);

	request->release();
}

void TaskDetailScene::buttonClicked(CCObject * sender , CCControlEvent controlEvent)
{
	MainGameScene *mainScene = (MainGameScene *)this->getParent();
	CCControlButton *button = (CCControlButton *)sender;
	switch (button->getTag()) {
	case 101:
        {
		mainScene->PopLayer();
		break;
        }
	case 102:
        {
		CCLOG("22222");
            selectedindex++;
            showTaskInfo();
        }
		break;
	}
}

TaskDetailScene::TaskDetailScene()
{
	mTaskList = NULL;
    m_lblTitle = NULL;
    m_sProgress = NULL;
    lblSubTitle = NULL;
}

TaskDetailScene::~TaskDetailScene()
{
	CC_SAFE_RELEASE(m_sProgress);
	CC_SAFE_RELEASE(m_lblTitle);
	CC_SAFE_RELEASE(mTaskList);
	//CC_SAFE_RELEASE(lblSubTitle);
}

