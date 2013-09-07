//
//  MDCardPlayer.cpp
//  mengdou
//
//  Created by ivan on 6/3/13.
//
//

#include "MDCardPlayer.h"
#include "CCShake.h"
#include "AnimatePacker.h"

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

MDCardPlayer::MDCardPlayer()
{
	m_hostCardPlayer = NULL;
	m_lblValue = NULL;
	isActionFinished = false;
	m_AnimateList= NULL;
}

bool MDCardPlayer::init(std::string p_cardName)
{
	m_sCardPlayer = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(p_cardName.c_str()));
	m_sCardPlayer->setUserObject(this);

	return true;
}

void MDCardPlayer::playAnnimateFrame(MDCardPlayer *target)
{
	//CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();  
	//cache->addSpriteFramesWithFile("flash.plist");
	//CCArray* animFrames = CCArray::createWithCapacity(count);

	//char firstFrame[64] = {0};
	//for(int i=1;i<=count;i++)
	//{
	//	string prefix(p_name);
	//	char strPlist[64] = {0};
	//	if(i<10)
	//	{
	//		prefix.append("0");
	//	}
	//	sprintf(strPlist,"%s%d.png",prefix.c_str(),i); 
	//	if (i==1)
	//	{
	//		strcpy(firstFrame,strPlist);
	//	}
	//	CCSpriteFrame *spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(strPlist);
	//	animFrames->addObject(spriteFrame);
	//}

	//CCAnimation *animation = CCAnimation::createWithSpriteFrames(animFrames, 0.1f);
	//CCAnimate *animate = CCAnimate::create(animation);
	////CCActionInterval* seq = CCSequence::create(animate,NULL);
	//	//CCFlipX::create(true),
	//	//animate->copy()->autorelease(),
	//	//CCFlipX::create(false),
	//	//NULL);

	//CCSequence *sequence = CCSequence::create(animate,CCCallFuncN::create(this, callfuncN_selector(MDCardPlayer::removeNodeCallBack)),NULL);

	//CCSprite *sprite = CCSprite::createWithSpriteFrameName(firstFrame);
	//this->m_sCardPlayer->getParent()->addChild(sprite);
	//CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	//sprite->setPosition(ccp(winSize.width * 0.1,winSize.height * 0.5));

	//sprite->runAction(sequence);
	////m_sCardPlayer->runAction(animate);

	CCArray *arrayAnimate = CCArray::create();
	arrayAnimate->addObject(CCString::create("hlz"));
	arrayAnimate->addObject(CCString::create("hqz"));
	arrayAnimate->addObject(CCString::create("kszd"));
	arrayAnimate->addObject(CCString::create("ldz"));
	arrayAnimate->addObject(CCString::create("ln"));
	arrayAnimate->addObject(CCString::create("mrj"));

	arrayAnimate->addObject(CCString::create("myz"));
	arrayAnimate->addObject(CCString::create("pjj"));
	arrayAnimate->addObject(CCString::create("qbj"));

	//arrayAnimate->addObject(CCString::create("qishouTX"));
	arrayAnimate->addObject(CCString::create("sdjx"));

	arrayAnimate->addObject(CCString::create("sfzs"));
	arrayAnimate->addObject(CCString::create("sjsql"));
	arrayAnimate->addObject(CCString::create("sjzs"));
	arrayAnimate->addObject(CCString::create("sqzs"));
	arrayAnimate->addObject(CCString::create("srzs"));
	arrayAnimate->addObject(CCString::create("szh"));

	arrayAnimate->addObject(CCString::create("tgn"));
	arrayAnimate->addObject(CCString::create("tjbgz"));
	arrayAnimate->addObject(CCString::create("tx"));
	arrayAnimate->addObject(CCString::create("wjqf"));
	arrayAnimate->addObject(CCString::create("wlbf"));

	arrayAnimate->addObject(CCString::create("xfz"));
	arrayAnimate->addObject(CCString::create("yhly"));//quanti
	arrayAnimate->addObject(CCString::create("yszs"));//position
	arrayAnimate->addObject(CCString::create("zhxj"));
	
	srand(time(NULL));
	int category = rand()%arrayAnimate->count();

	std::string strCategory = ((CCString *)arrayAnimate->objectAtIndex(category))->getCString();


	AnimatePacker::getInstance()->loadAnimations((strCategory + std::string(".xml")).c_str()); 
	CCSprite *sprite = CCSprite::create("transparent.png");

	sprite->setUserObject(target);

	this->m_sCardPlayer->getParent()->addChild(sprite);
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	//sprite->setPosition(ccp(winSize.width * 0.5,winSize.height * 0.5));
	sprite->setPosition(target->m_sCardPlayer->getPosition());

	CCDelayTime *_delay = CCDelayTime::create(0.6);
	CCAnimate *_animate = AnimatePacker::getInstance()->getAnimate(strCategory.c_str());
	CCFiniteTimeAction* _underAttack = CCCallFuncN::create( this, callfuncN_selector(MDCardPlayer::playUnderAttackAnnimate));
	CCFiniteTimeAction* _removeCallBack = CCCallFuncN::create(this, callfuncN_selector(MDCardPlayer::removeNodeCallBack));

	CCSequence *sequence = CCSequence::create(_delay,_animate,_underAttack,_removeCallBack,NULL);

	this->playAttackInstruction();

	sprite->runAction(sequence);

	
	/*sprite->runAction( CCRepeatForever::create(AnimatePacker::getInstance()->getAnimate(strCategory.c_str())));*/
}


void MDCardPlayer::playAttackInstruction()
{
	m_sCardPlayer->stopAllActions();
	CCMoveBy * rotMoveUp = CCMoveBy::create(0.1,ccp(0,25));
	CCRotateBy * rotLeft = CCRotateBy::create(0.1,18.0);
	CCRotateBy * rotRight = CCRotateBy::create(0.1,-18.0);
	CCMoveBy * rotMoveDown = CCMoveBy::create(0.1,ccp(0,-25));
	CCSequence * rotSeq = CCSequence::create(rotMoveUp,rotLeft, rotRight,rotMoveDown, NULL);
	m_sCardPlayer->runAction(rotSeq);
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

void MDCardPlayer::playRainAnnimation(CCArray *enemyList)
{
    string attack("myAttack1.plist");
    CCParticleSystem *_particle = CCParticleSystemQuad::create(attack.c_str());
    m_sCardPlayer->getParent()->addChild(_particle);
    CCPoint point = m_sCardPlayer->getPosition();
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    point.x = winSize.width * 0.5;
    _particle->setPosition(point);
    _particle->setAutoRemoveOnFinish(true);
    
    m_EnemyList = enemyList;

	CCDelayTime *delay = CCDelayTime::create(0.6);

	CCFiniteTimeAction* _delayFinished = CCCallFuncN::create( this, callfuncN_selector(MDCardPlayer::allEnemyUnderAttack));

	this->playAttackInstruction();

	m_sCardPlayer->runAction(CCSequence::create(delay,_delayFinished,NULL));
    
    //CCDirector::sharedDirector()->getScheduler()->scheduleSelector( schedule_selector(MDCardPlayer::allEnemyUnderAttack), this, 0.6, false);
    
}

void MDCardPlayer::playShakeAnnimation()
{
	CCShake *_shake = CCShake::create(0.5,4,2);
	
	CCFiniteTimeAction* _actionFinished = CCCallFuncN::create( this, callfuncN_selector(MDCardPlayer::actionFinished));
	CCDelayTime *_delayTime = CCDelayTime::create(2.0);

	m_sCardPlayer->runAction(CCSequence::create(_shake,_delayTime,_actionFinished,NULL));
	m_lblValue = (CCLabelTTF *)m_sCardPlayer->getChildByTag(101);

	if (m_lblValue==NULL)
	{
		m_lblValue = CCLabelTTF::create("63","Arial",13);
		m_sCardPlayer->addChild(m_lblValue);
	}
	m_lblValue->setVisible(true);
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
    CCFiniteTimeAction* _actionMoveDone = CCCallFuncN::create( this, callfuncN_selector(MDCardPlayer::playUnderAttackAnnimate));
    
	this->playAttackInstruction();

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
    CCFiniteTimeAction* _actionMoveDone = CCCallFuncN::create( this, callfuncN_selector(MDCardPlayer::playUnderAttackAnnimate));
    
	this->playAttackInstruction();

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
    CCFiniteTimeAction* _actionMoveDone = CCCallFuncN::create( this, callfuncN_selector(MDCardPlayer::playUnderAttackAnnimate));

	this->playAttackInstruction();

    _particle->runAction(CCSequence::create(_delayTime,_actionMoveDone,NULL));
}

void MDCardPlayer::setCardData(CCDictionary *dict)
{
	this->m_fltTotalHp = ((CCString *)dict->objectForKey("blood"))->intValue();
	this->m_fltDefencePoint = ((CCString *)dict->objectForKey("defence"))->floatValue();
	this->m_fltAttackPoint = ((CCString *)dict->objectForKey("attack"))->intValue();
	this->m_fltDodgePoint = ((CCString *)dict->objectForKey("dodge"))->floatValue();
}

void MDCardPlayer::actionFinished(CCNode* sender)
{
	if (m_hostCardPlayer!=NULL)
	{
		if (!m_hostCardPlayer->isActionFinished)
		{
			m_hostCardPlayer->isActionFinished = true;

			if(m_delegate != NULL) {
				m_delegate->didActionFinished(this);
			}
		}
	} else {
		if(m_delegate != NULL) {
			m_delegate->didActionFinished(this);
		}
	}
}

void MDCardPlayer::playUnderAttackAnnimate(CCNode* sender)
{
	MDCardPlayer *target = (MDCardPlayer *)sender->getUserObject();
	target->setHostCardPlayer(NULL);
	target->playShakeAnnimation();
	target->playFireEffect();
}

void MDCardPlayer::allEnemyUnderAttack(CCNode *pnode)
{
	CCLOG("allEnemyUnderAttack");
	//CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(MDCardPlayer::allEnemyUnderAttack), this);

	isActionFinished = false;

	for (int i=0; i<m_EnemyList->count(); i++) {
		MDCardPlayer *enemyPlayer = (MDCardPlayer *)m_EnemyList->objectAtIndex(i);

		enemyPlayer->setHostCardPlayer(this);
		enemyPlayer->playDeadAnnimation();
		enemyPlayer->playShakeAnnimation();
		
	}
}

//void MDCardPlayer::allEnemyUnderAttack(float dt)
//{
//	CCLOG("allEnemyUnderAttack");
//    CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(MDCardPlayer::allEnemyUnderAttack), this);
//
//	isActionFinished = false;
//
//    for (int i=0; i<m_EnemyList->count(); i++) {
//        MDCardPlayer *enemyPlayer = (MDCardPlayer *)m_EnemyList->objectAtIndex(i);
//		
//		enemyPlayer->setHostCardPlayer(this);
//        enemyPlayer->playShakeAnnimation();
//        enemyPlayer->playDeadAnnimation();
//    }
//}

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

