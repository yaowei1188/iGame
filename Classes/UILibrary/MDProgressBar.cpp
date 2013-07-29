//
//  MDProgressBar.cpp
//  
//
//  Created by China Team on 4/9/13.
//
//

#include "MDProgressBar.h"

MDProgressBar::MDProgressBar()
{

}

MDProgressBar::~MDProgressBar()
{
    
}

void MDProgressBar::setPercent(float percent)
{
    if (percent==m_percent) {
        return;
    }
    m_percent = percent;
//    if (m_percent < percent) {
//        m_mCap->setContentSize(CCSizeMake(m_barWidth * m_percent, m_mCap->getContentSize().height));
//        m_rCap->setPosition(ccp(m_lCap->getContentSize().width + m_mCap->getContentSize().width - 2,0));
//    }

    m_mCap->setContentSize(CCSizeMake(m_barWidth * m_percent, m_mCap->getContentSize().height));
    m_rCap->setPosition(ccp(m_lCap->getContentSize().width + m_mCap->getContentSize().width - 2,0));
}

MDProgressBar * MDProgressBar::create(const char *lcap,const char *mcap,const char *rcap,float pwidth,float percent)
{
    MDProgressBar * ptr = new MDProgressBar();
    if(ptr != NULL && ptr->init(lcap,mcap,rcap,pwidth,percent)) {
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_DELETE(ptr);
    return NULL;
}

bool MDProgressBar::init(const char *lcap,const char *mcap,const char *rcap,float pwidth,float percent)
{
    bool bRet = false;
    do
    {
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////
        
        CC_BREAK_IF(! CCNode::init());

        m_percent = percent;
        m_barWidth = pwidth;

//        CCSpriteBatchNode *batchNode = CCSpriteBatchNode::create("main.png");

        m_lCap = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(lcap));
        m_lCap->setAnchorPoint(ccp(0,0.5));
        m_lCap->setPosition(ccp(0,0));
        
        m_mCap = CCScale9Sprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(mcap));
        m_mCap->setPosition(ccp(m_lCap->getContentSize().width - 1,0));
        m_mCap->setAnchorPoint(ccp(0,0.5));
        m_mCap->setContentSize(CCSizeMake(m_barWidth * m_percent, m_mCap->getContentSize().height));
        
        m_rCap = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(rcap));
        m_rCap->setAnchorPoint(ccp(0,0.5));
        m_rCap->setPosition(ccp(m_lCap->getContentSize().width + m_mCap->getContentSize().width - 2,0));

//        batchNode->addChild(lhCap);
//        batchNode->addChild(rhCap);
//        batchNode->addChild(mhCap);

        this->addChild(m_lCap);
        this->addChild(m_mCap);
        this->addChild(m_rCap);

//        this->addChild(batchNode);

        bRet = true;
    } while (0);
    
    return bRet;
}
