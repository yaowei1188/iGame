//
//  MDCardPlayer.cpp
//  mengdou
//
//  Created by ivan on 6/3/13.
//
//

#include "MDCardPlayer.h"
#include "CCShake.h"

MDCardPlayer * MDCardPlayer::create(std::string p_cardName)
{
	MDCardPlayer * ptr = new MDCardPlayer();
	if(ptr != NULL && ptr->init(p_cardName)) {
		ptr->autorelease();
		return ptr;
	}
	CC_SAFE_DELETE(ptr);
	return NULL;
}

bool MDCardPlayer::init(std::string p_cardName)
{
	m_sCardPlayer = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(p_cardName.c_str()));
	//m_sCardPlayer->setAnchorPoint(ccp(0.5,0.5));
	////m_sCardPlayer->setAnchorPoint(CCPointZero);
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	m_sCardPlayer->setUserObject(this);
	//m_sCardPlayer->setPosition(ccp(winSize.width/2,winSize.height/2 - 100));
	return true;
}

void MDCardPlayer::playParadeAnnimation()
{
	CCJumpBy *jump = CCJumpBy::create(2.0,ccp(0,0),15,4);
	CCRepeatForever *repeat = CCRepeatForever::create(jump);
	m_sCardPlayer->runAction(repeat);
}

void MDCardPlayer::playAttackAnnimation()
{

}

void MDCardPlayer::playMistreatAnnimation()
{
	CCShake *shake = CCShake::create(1,6,2);
	m_sCardPlayer->runAction(shake);
}

void MDCardPlayer::playDeadAnnimation()
{

}

void MDCardPlayer::playWiggleAnnimation()
{
	m_sCardPlayer->stopAllActions();
	CCRotateBy * rotLeft = CCRotateBy::create(0.1,-4.0);
	CCRotateBy * rotCenter = CCRotateBy::create(0.1,0.0);
	CCRotateBy * rotRight = CCRotateBy::create(0.1,4.0);
	CCSequence * rotSeq = CCSequence::create(rotLeft, rotCenter, rotRight, rotCenter, NULL);
	m_sCardPlayer->runAction(CCRepeatForever::create(rotSeq));  
}

void MDCardPlayer::MoveToPosition()
{
	m_sCardPlayer->stopAllActions();

	m_sCardPlayer->runAction(CCEaseBackOut::create(CCMoveTo::create(0.2,m_location)));  
}

void MDCardPlayer::playFireEffect()
{
	CCParticleFire *m_emitter = CCParticleFire::create();
	m_emitter->setDuration(1);
	m_emitter->retain();
	m_sCardPlayer->addChild(m_emitter);
	m_emitter->setTexture( CCTextureCache::sharedTextureCache()->addImage("particle-fire.png") );
	m_emitter->setPosition(30,30);
	m_emitter->setAutoRemoveOnFinish(true);
}

void MDCardPlayer::playGalaxy()
{
	CCParticleGalaxy *m_emitter = CCParticleGalaxy::create();
	//m_emitter->setDuration(1);
	m_emitter->retain();
	m_sCardPlayer->addChild(m_emitter);
	m_emitter->setTexture( CCTextureCache::sharedTextureCache()->addImage("particle-fire.png") );
	m_emitter->setPosition(30,30);
	m_emitter->setAutoRemoveOnFinish(true);
}

