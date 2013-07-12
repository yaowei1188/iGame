//
//  MDCardPlayer.cpp
//  mengdou
//
//  Created by ivan on 6/3/13.
//
//

#include "MDCardPlayer.h"
#include "CCShake.h"

bool MDCardPlayer::init()
{
	m_sCardPlayer = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("head_sunwukong.png"));
	m_sCardPlayer->setAnchorPoint(ccp(0.5,1));
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	m_sCardPlayer->setUserObject(this);
	m_sCardPlayer->setPosition(ccp(winSize.width/2,winSize.height/2 - 100));
	return true;
}

void MDCardPlayer::playParadeAnnimation()
{
	CCShake *shake = CCShake::create(2,10);
	shake->_original = m_sCardPlayer->getPosition();
	m_sCardPlayer->runAction(CCShake::create(2,10));
}

void MDCardPlayer::playAttackAnnimation()
{

}

void MDCardPlayer::playMistreatAnnimation()
{

}

void MDCardPlayer::playDeadAnnimation()
{

}
