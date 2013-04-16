#include "TaskListScene.h"

using namespace cocos2d;

CCScene* TaskListScene::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
//        TaskListScene *layer = TaskListScene::create();
//        CC_BREAK_IF(! layer);

        // add layer as a child to scene
//        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool TaskListScene::init()
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

bool TaskListScene::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    //CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mTableViewFriend", CCTableView*, this->mTableViewFriend);
    return true;
}

void TaskListScene::onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader)
{
    CCLOG("TEST");
    
//    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
//    
//    mTableViewFriend->removeFromParentAndCleanup(true);
//        
//    mTableViewFriend = CCTableView::create(this, CCSizeMake(312, 250));
//    mTableViewFriend->setDirection(kCCScrollViewDirectionVertical);
//    mTableViewFriend->setPosition(ccp(0,winSize.height/2-30));
//    mTableViewFriend->setDelegate(this);
//    this->addChild(mTableViewFriend);
//    mTableViewFriend->reloadData();

//    mTableViewFriend->setDirection(kCCScrollViewDirectionVertical);
////    mTableViewFriend->setVerticalFillOrder(kCCTableViewFillTopDown);
//    mTableViewFriend->setDataSource(this);
//    mTableViewFriend->setDelegate(this);
//    mTableViewFriend->reloadData();
}

//unsigned int TaskListScene::numberOfRowsInSection(unsigned int mSection,CCTableView * mTableView)
//{
//    return 20;
//}
//
//CCTableViewCell * TaskListScene::cellForRowAtIndexPath(CCIndexPath &mIndexPath,CCTableView * mTableView)
//{
//    static const char * cellIdentifier = "cell-identifier";
//	
//	char labelStr[60];
//	sprintf(labelStr, "%d",mIndexPath.row);
//	
//	CCTableViewCell * cell = (CCTableViewCell *) mTableView->dequeueReusableCellWithIdentifier(cellIdentifier);
//	if (cell == NULL) {
//		printf("cell alloc row =%d\n",mIndexPath.row);
//		cell = new CCTableViewCell(cellIdentifier);
//		cell->autorelease();
//		
//		CCLabelTTF * label = CCLabelTTF::create(labelStr, "Arial", 16);
//		label->setColor(ccc3(0, 0, 0));
//		label->setPosition(ccp(40,60/2.0));
//		label->setColor(ccc3(255,255,255));
//		label->setTag(20);
//		cell->addChild(label);
//        //		cell->parentView = _tableView;
////		cell->setColor(ccc3(128, 128, 128));
//	}
//	else{
//		CCLabelTTF * label = (CCLabelTTF * ) cell->getChildByTag(20);
//		if (label) {
//			label->setString(labelStr);
//		}
//	}
//	return cell;
//}
//float TaskListScene::cellHeightForRowAtIndexPath(CCIndexPath & mIndexPath,CCTableView * mTableView)
//{
//    return 60;
//}

void TaskListScene::requestFinishedCallback(CCNode* pSender,void *data)
{

}

