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
	m_sCardPlayer->setUserObject(this);
	return true;
}

void MDCardPlayer::playAnnimateFrame(std::string p_name,int count)
{
	CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();  
	cache->addSpriteFramesWithFile("flash.plist");
	CCArray* animFrames = CCArray::createWithCapacity(count);

	char firstFrame[64] = {0};
	for(int i=1;i<=count;i++)
	{
		string prefix(p_name);
		char strPlist[64] = {0};
		if(i<10)
		{
			prefix.append("0");
		}
		sprintf(strPlist,"%s%d.png",prefix.c_str(),i); 
		if (i==1)
		{
			strcpy(firstFrame,strPlist);
		}
		CCSpriteFrame *spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(strPlist);
		animFrames->addObject(spriteFrame);
	}

	CCAnimation *animation = CCAnimation::createWithSpriteFrames(animFrames, 0.1f);
	CCAnimate *animate = CCAnimate::create(animation);
	//CCActionInterval* seq = CCSequence::create(animate,NULL);
		//CCFlipX::create(true),
		//animate->copy()->autorelease(),
		//CCFlipX::create(false),
		//NULL);

	CCSequence *sequence = CCSequence::create(animate,CCCallFuncN::create(this, callfuncN_selector(MDCardPlayer::removeNodeCallBack)),NULL);

	CCSprite *sprite = CCSprite::createWithSpriteFrameName(firstFrame);
	this->m_sCardPlayer->getParent()->addChild(sprite);
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	sprite->setPosition(ccp(winSize.width * 0.1,winSize.height * 0.5));

	sprite->runAction(sequence);
	//m_sCardPlayer->runAction(animate);
}

void MDCardPlayer::playParadeAnnimation()
{
	CCJumpBy *jump = CCJumpBy::create(2.0,ccp(0,0),15,4);
	CCRepeatForever *repeat = CCRepeatForever::create(jump);
	m_sCardPlayer->runAction(repeat);
}

void MDCardPlayer::stopAllAction()
{
	m_sCardPlayer->stopAllActions();
}

void MDCardPlayer::playAttackAnnimation(CCArray *enemyList)
{
    string attack("myAttack1.plist");
    CCParticleSystem *_particle = CCParticleSystemQuad::create(attack.c_str());
    m_sCardPlayer->getParent()->addChild(_particle);
    CCPoint point = m_sCardPlayer->getPosition();
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    point.x = winSize.width * 0.5;
    _particle->setPosition(point);
    _particle->setAutoRemoveOnFinish(true);
    
//    m_EnemyList = CC_SAFE_RETAIN(enemyList);
    m_EnemyList = enemyList;
    
//    this->scheduleSelector(schedule_selector(MDCardPlayer::allEnemyUnderAttack), this, 2,false);
    
    CCDirector::sharedDirector()->getScheduler()->scheduleSelector(
                                                                   schedule_selector(MDCardPlayer::allEnemyUnderAttack), this, 0.3, false);
    
}

void MDCardPlayer::playShakeAnnimation()
{
	CCShake *shake = CCShake::create(0.5,4,2);
	m_sCardPlayer->runAction(shake);
}

void MDCardPlayer::playDeadAnnimation()
{
	CCActionInterval *colorAction = CCSequence::create(
		CCTintTo::create(0.2f, 255, 0, 0),
		CCTintTo::create(0.2f, 0, 255, 0),
		CCTintTo::create(0.2f, 0, 0, 255),
//		CCTintTo::create(0.2f, 0, 255, 255),
//		CCTintTo::create(0.2f, 255, 255, 0),
//		CCTintTo::create(0.2f, 255, 0, 255),
		CCTintTo::create(0.2f, 255, 255, 255),
		NULL);
	m_sCardPlayer->runAction(colorAction);
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
	m_emitter->setDuration(0.5);
	m_emitter->retain();
	m_sCardPlayer->addChild(m_emitter);
	m_emitter->setTexture( CCTextureCache::sharedTextureCache()->addImage("particle-fire.png") );
	m_emitter->setPosition(30,30);
	m_emitter->setAutoRemoveOnFinish(true);
}

void MDCardPlayer::playGalaxyEffect()
{
	CCParticleGalaxy *m_emitter = CCParticleGalaxy::create();
	//m_emitter->setDuration(1);
	m_emitter->retain();
	m_sCardPlayer->addChild(m_emitter);
	m_emitter->setTexture( CCTextureCache::sharedTextureCache()->addImage("particle-fire.png") );
	m_emitter->setPosition(30,30);
	m_emitter->setAutoRemoveOnFinish(true);
}

void MDCardPlayer::playMeteorEffect(MDCardPlayer *target)
{
	CCParticleMeteor *m_emitter = CCParticleMeteor::create();
    m_emitter->setGravity(ccp(0,-10));
	m_emitter->setDuration(0.3);
	m_emitter->retain();
	m_sCardPlayer->getParent()->addChild(m_emitter);
	m_emitter->setTexture( CCTextureCache::sharedTextureCache()->addImage("particle-fire.png") );
	m_emitter->setPosition(m_sCardPlayer->getPosition());
	m_emitter->setAutoRemoveOnFinish(true);
    m_emitter->setUserObject(target);
    
    
    CCMoveTo *_moveAction = CCMoveTo::create(0.3, target->m_sCardPlayer->getPosition());
    CCFiniteTimeAction* _actionMoveDone = CCCallFuncN::create( this, callfuncN_selector(MDCardPlayer::actionFinished));
    
    m_emitter->runAction(CCSequence::create(_moveAction,_actionMoveDone,NULL));
}

void MDCardPlayer::playFireEffect(MDCardPlayer *target)
{
    CCParticleSystem *_particle = CCParticleSystemQuad::create("fire.plist");
    _particle->setDuration(0.3);
    m_sCardPlayer->getParent()->addChild(_particle);
    _particle->setPosition(m_sCardPlayer->getPosition());
    _particle->setAutoRemoveOnFinish(true);
    _particle->setUserObject(target);
    
    CCMoveTo *_moveAction = CCMoveTo::create(0.3, target->m_sCardPlayer->getPosition());
    CCFiniteTimeAction* _actionMoveDone = CCCallFuncN::create( this, callfuncN_selector(MDCardPlayer::actionFinished));
    
    _particle->runAction(CCSequence::create(_moveAction,_actionMoveDone,NULL));
}

void MDCardPlayer::playEcllipseEffect(MDCardPlayer *target)
{
    CCParticleSystem *_particle = CCParticleSystemQuad::create("ellipse.plist");
    _particle->setDuration(0.3);
    target->m_sCardPlayer->addChild(_particle);
    _particle->setPosition(ccp(30,0));
    _particle->setAutoRemoveOnFinish(true);
    _particle->setUserObject(target);
    
    CCDelayTime *_delayTime = CCDelayTime::create(0.3);
    CCFiniteTimeAction* _actionMoveDone = CCCallFuncN::create( this, callfuncN_selector(MDCardPlayer::actionFinished));
    _particle->runAction(CCSequence::create(_delayTime,_actionMoveDone,NULL));
}

void MDCardPlayer::actionFinished(CCNode* sender)
{
    MDCardPlayer *target = (MDCardPlayer *)sender->getUserObject();
    target->playShakeAnnimation();
    target->playFireEffect();
}

void MDCardPlayer::allEnemyUnderAttack(float dt)
{
    CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(MDCardPlayer::allEnemyUnderAttack), this);
    for (int i=0; i<m_EnemyList->count(); i++) {
        MDCardPlayer *enemyPlayer = (MDCardPlayer *)m_EnemyList->objectAtIndex(i);
        enemyPlayer->playShakeAnnimation();
        enemyPlayer->playDeadAnnimation();
    }
}

void MDCardPlayer::playExploreEffect(MDCardPlayer *target)
{
    CCParticleSystem *_particle = CCParticleSystemQuad::create("explore1.plist");
    m_sCardPlayer->addChild(_particle);
    _particle->setPosition(30,30);
    _particle->setAutoRemoveOnFinish(true);
}

void MDCardPlayer::removeNodeCallBack(CCNode* pNode)
{
	pNode->removeFromParentAndCleanup(true);
}

