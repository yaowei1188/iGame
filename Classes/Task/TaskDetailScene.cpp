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

void TaskDetailScene::moveProgress()
{
   CCPoint position = this->m_sProgress->getPosition();
    position.x = subIndex * 30;
    this->m_sProgress->runAction(CCMoveTo::create(0.2, position));
}

// on "init" you need to initialize your instance
bool TaskDetailScene::init()
{
//	selectedindex = 0;

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
    
//    if (selectedindex>=subTasks->count()) {
//        MainGameScene *mainScene = (MainGameScene *)this->getParent();
//        mainScene->PushLayer((CCLayer *)this->GetLayer("TaskRewardScene"));
//        return;
//    }
    
    //CCDictionary *task = (CCDictionary *)subTasks->objectAtIndex(subIndex-1);
    CCDictionary *task = (CCDictionary *)subTasks->objectAtIndex(subIndex);

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
	//strCoins += ((CCString *)task->objectForKey("Coins"))->getCString();
	char strGainedPoins[20];
	sprintf(strGainedPoins,"%d",gainedCoin);
	strCoins += strGainedPoins;
	lblCoins->setString(strCoins.c_str());

	string strExperience("经验+");
	char strGainedExperience[20];
	sprintf(strGainedExperience,"%d",gainedEmpiricalValue);
	strExperience += strGainedExperience;
	//strExperience += ((CCString *)task->objectForKey("Experience"))->getCString();
	lblExperience->setString(strExperience.c_str());
}

void TaskDetailScene::onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader)
{
	mTaskList = GlobalData::getTasks("");
	mTaskList->retain();
}

void TaskDetailScene::executeTask()
{
    subIndex++;
    if (subIndex>10)
	{
		subIndex = 1;
		upperIndex++;
	}
    
	CCHttpRequest *request = new CCHttpRequest();
	request->setRequestType(CCHttpRequest::kHttpPost);
	request->setResponseCallback(this,httpresponse_selector(TaskDetailScene::requestFinishedCallback));
	request->setTag("102");

	string _strUrl = CompleteUrl(URL_TASK_EXPLORE);
    
    string _strPostData("encryptedUserInfo=");
	_strPostData.append(CCUserDefault::sharedUserDefault()->getStringForKey("userinfo"));
	_strPostData.append("&userGameRoleId=" + CCUserDefault::sharedUserDefault()->getStringForKey("gameRoleId"));

	char strIndex[20];
	char strSubIndex[20];

	sprintf(strIndex,"&index=%d",upperIndex);
	sprintf(strSubIndex,"&subIndex=%d",subIndex);
    
    _strPostData.append(strIndex);
    _strPostData.append(strSubIndex);
    
	request->setRequestData(_strPostData.c_str(), _strPostData.length());

	request->setUrl(_strUrl.c_str());

	CCHttpClient *client = CCHttpClient::getInstance();
	client->send(request);

	request->release();

}

void TaskDetailScene::requestFinishedCallback(CCHttpClient* client, CCHttpResponse* response)
{
	if (!this->ValidateResponseData(client,response))
	{
		return;
	}

	std::vector<char> *buffer = response->getResponseData();
	std::string content(buffer->begin(),buffer->end());

	CCDictionary * dictionary = CCJSONConverter::sharedConverter()->dictionaryFrom(content.c_str());
	int code = ((CCNumber *)dictionary->objectForKey("code"))->getIntValue();
	if (code != 200) 
	{
		CCMessageBox("invoke web api failed!","ERROR");
		return;
	}

	std::string requestTag(response->getHttpRequest()->getTag());

	if (requestTag == "102")
	{
		mTaskDict = dynamic_cast<CCDictionary *>(dictionary->objectForKey("exploreResponse"));
		if (mTaskDict == NULL)
		{
			return;
		}
		upperIndex = ((CCNumber*)mTaskDict->objectForKey("index"))->getIntValue();
		subIndex = ((CCNumber*)mTaskDict->objectForKey("subIndex"))->getIntValue();
		card = (CCString*)mTaskDict->objectForKey("card");
		//code = ((CCNumber*)mTaskDict->objectForKey("code"))->getIntValue();
		gainedCoin = ((CCNumber*)mTaskDict->objectForKey("gainedCoin"))->getIntValue();
		gainedEmpiricalValue = ((CCNumber*)mTaskDict->objectForKey("gainedEmpiricalValue"))->getIntValue();

		this->showTaskInfo();
        this->moveProgress();
	}
}

void TaskDetailScene::buttonClicked(CCObject * sender , CCControlEvent controlEvent)
{
	CCControlButton *button = (CCControlButton *)sender;
	switch (button->getTag()) {
	case 101:
        {
			MainGameScene *mainScene = (MainGameScene *)this->getParent();
			mainScene->PopLayer();
			break;
        }
	case 102:
        {
			CCLOG("22222");
			executeTask();
            //selectedindex++;
            //showTaskInfo();
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

