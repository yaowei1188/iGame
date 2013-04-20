#include "CCMessageDialog.h"

using namespace cocos2d;

CCScene* CCMessageDialog::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        CCMessageDialog *layer = CCMessageDialog::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool CCMessageDialog::init()
{
    bool bRet = false;
    do 
    {
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////

        CC_BREAK_IF(! CCLayer::init());
        
        CCSprite *mBg = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("提示框.png"));
        CCSprite *cancelNormal = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("no_1.png"));
        CCSprite *cancelHighlight = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("no_2.png"));
        CCSprite *OKNormal = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("ok_1.png"));
        CCSprite *OKHighlight = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("ok_2.png"));

        CCSize mSize=CCDirector::sharedDirector()->getWinSize();
        mBg->setPosition(ccp(mSize.width / 2, mSize.height / 2));
        this->addChild(mBg);
        
        CCLabelTTF* pLabel=CCLabelTTF::create("Are you sure ?","Arial",20);
        pLabel->setPosition(ccp(mSize.width / 2, mSize.height / 2+40));
        this->addChild(pLabel);
        
        CCMenuItemSprite *pMenuOK = CCMenuItemSprite::create(
                                                             OKNormal,
                                                             OKHighlight,
                                                             NULL,
                                                             this,
                                                             menu_selector(CCMessageDialog::submitClicked));
        pMenuOK->setPosition(ccp(mSize.width *(3.0/10.0), mSize.height / 2-30));
        
        CCMenuItemSprite *pMenuCancel = CCMenuItemSprite::create(
                                                             cancelNormal,
                                                             cancelHighlight,
                                                             NULL,
                                                             this,
                                                             menu_selector(CCMessageDialog::submitClicked));
        pMenuCancel->setPosition(ccp(mSize.width *(7.0/10.0), mSize.height / 2-30));

        CCMenu* pMenu = CCMenu::create(pMenuOK,pMenuCancel,NULL);
        pMenu->setPosition(CCPointZero);  
        this->addChild(pMenu);
        
        bRet = true;
    } while (0);

    return bRet;
}

void CCMessageDialog::registerWithTouchDispatcher(void){

	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, INT_MIN , true);
}

bool CCMessageDialog::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	return true;
}

void CCMessageDialog::submitClicked(CCObject *pSender)
{
	CCLOG("i was clicked");
    this->removeFromParentAndCleanup(true);
}

