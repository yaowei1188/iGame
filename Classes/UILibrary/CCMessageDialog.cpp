#include "CCMessageDialog.h"

using namespace cocos2d;

CCMessageDialog::CCMessageDialog()
: m_pDelegate(NULL)
{
    
}

//CCScene* CCMessageDialog::scene()
//{
//    CCScene * scene = NULL;
//    do 
//    {
//        // 'scene' is an autorelease object
//        scene = CCScene::create();
//        CC_BREAK_IF(! scene);
//
//        // 'layer' is an autorelease object
//        CCMessageDialog *layer = CCMessageDialog::create();
//        CC_BREAK_IF(! layer);
//
//        // add layer as a child to scene
//        scene->addChild(layer);
//    } while (0);
//
//    // return the scene
//    return scene;
//}

// on "init" you need to initialize your instance
bool CCMessageDialog::init()
{
    bool bRet = false;
    do 
    {
        CC_BREAK_IF(! CCLayer::init());
        
        this->setTouchEnabled(true);
        
        CCSprite *mBg = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("prompt_dialog.png"));
        CCSprite *cancelNormal = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("btn_bg.png"));
        CCSprite *cancelHighlight = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("btn_bg_highlight.png"));
        CCSprite *OKNormal = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("btn_bg.png"));
        CCSprite *OKHighlight = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("btn_bg_highlight.png"));

        CCSize mSize=CCDirector::sharedDirector()->getWinSize();
        mBg->setPosition(ccp(mSize.width / 2, mSize.height / 3));
        mBg->setAnchorPoint(ccp(0.5,0.5));
        this->addChild(mBg);
        
        lblTitle = CCLabelTTF::create("Are you sure ?","Arial",20);
        lblTitle->setPosition(ccp(mSize.width / 2, mSize.height / 3+40));
        this->addChild(lblTitle);
        
        CCMenuItemSprite *pMenuOK = CCMenuItemSprite::create(
                                                             OKNormal,
                                                             OKHighlight,
                                                             NULL,
                                                             this,
                                                             menu_selector(CCMessageDialog::buttonClicked));
        pMenuOK->setPosition(ccp(mSize.width *(3.0/10.0), mSize.height / 3-30));
		pMenuOK->setTag(0);
        
        CCMenuItemSprite *pMenuCancel = CCMenuItemSprite::create(
                                                             cancelNormal,
                                                             cancelHighlight,
                                                             NULL,
                                                             this,
                                                             menu_selector(CCMessageDialog::buttonClicked));
        pMenuCancel->setPosition(ccp(mSize.width *(7.0/10.0), mSize.height / 3-30));
		pMenuCancel->setTag(1);

        CCMenu* pMenu = CCMenu::create(pMenuOK,pMenuCancel,NULL);
        pMenu->setPosition(CCPointZero);
        this->addChild(pMenu);
        
        bRet = true;
    } while (0);

    return bRet;
}

void CCMessageDialog::setTitle(const char * title)
{
	lblTitle->setString(title);
}

void CCMessageDialog::registerWithTouchDispatcher(void)
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0 , true);
}

bool CCMessageDialog::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	return true;
}

void CCMessageDialog::buttonClicked(CCObject *pSender)
{
	int tag = ((CCNode *)pSender)->getTag();
	if (m_pDelegate!=NULL)
	{
		m_pDelegate->didClickButton(this,tag);
	}
    this->removeFromParentAndCleanup(true);
}

