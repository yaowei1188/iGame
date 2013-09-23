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
#include "StringExt.h"
#include "MDSoundManager.h"
#include "GlobalData.h"

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
	m_intActionCategory = CardCategoryNone;
	isActionFinished = false;
	m_AnimateList= NULL;
	isDead = false;
}

bool MDCardPlayer::init(std::string p_cardName)
{
	//m_sCardPlayer = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(p_cardName.c_str()));

	m_sCardPlayer = CCSprite::create(p_cardName.c_str());
	//if (GlobalData::factor!=1.0)
	//{
	//	m_sCardPlayer->setScale(GlobalData::factor);
	//}
			m_sCardPlayer->setScale(CCDirector::sharedDirector()->getContentScaleFactor()/2);
	m_sCardPlayer->setUserObject(this);

	return true;
}

void MDCardPlayer::playAssistAnnimateFrame(MDCardPlayer *target)
{
	setActionPara(CardCategoryAssist);

	CCArray *arrayAnimate = CCArray::create();

	CCDictionary *dictAnnimate = CCDictionary::create();
	dictAnnimate->setObject(CCString::create("mrj"),"Annimate");
	arrayAnimate->addObject(dictAnnimate);

	dictAnnimate = CCDictionary::create();
	dictAnnimate->setObject(CCString::create("e17"),"Annimate");
	dictAnnimate->setObject(CCString::create("30"),"PosOffsetY");
	arrayAnimate->addObject(dictAnnimate);

	dictAnnimate = CCDictionary::create();
	dictAnnimate->setObject(CCString::create("e20"),"Annimate");
	dictAnnimate->setObject(CCString::create("15"),"PosOffsetX");
	arrayAnimate->addObject(dictAnnimate);

	//arrayAnimate->addObject(CCString::create("mrj"));//粉色的心
	//arrayAnimate->addObject(CCString::create("e17"));//位置偏下 恢复的
	//arrayAnimate->addObject(CCString::create("e20"));//位置偏左 恢复的

	srand(time(NULL));
	int category = rand()%arrayAnimate->count();

	dictAnnimate = (CCDictionary *)arrayAnimate->objectAtIndex(category);
	std::string strCategory = ((CCString *)dictAnnimate->objectForKey("Annimate"))->getCString();
	CCString *strXPos = (CCString *)dictAnnimate->objectForKey("PosOffsetX");
	CCString *strYPos = (CCString *)dictAnnimate->objectForKey("PosOffsetY");

	m_strAnnimatePath = strCategory + std::string(".xml");

	AnimatePacker::getInstance()->loadAnimations(m_strAnnimatePath.c_str()); 
	CCSprite *sprite = CCSprite::create("transparent.png");

	sprite->setUserObject(target);

	this->m_sCardPlayer->getParent()->addChild(sprite);
	CCPoint pos = target->m_sCardPlayer->getPosition();
	if (strXPos != NULL)
	{
		pos.x += strXPos->intValue();
	}
	if (strYPos != NULL)
	{
		pos.y += strYPos->intValue();
	}

	sprite->setPosition(pos);

	CCDelayTime *_delay = CCDelayTime::create(0.6);
	CCAnimate *_animate = AnimatePacker::getInstance()->getAnimate(strCategory.c_str());
	CCFiniteTimeAction* _underAttack = CCCallFuncN::create( this, callfuncN_selector(MDCardPlayer::playUnderAttackAnnimate));
	CCFiniteTimeAction* _removeCallBack = CCCallFuncN::create(this, callfuncN_selector(MDCardPlayer::removeNodeCallBack));

	CCSequence *sequence = CCSequence::create(_delay,_animate,_underAttack,_removeCallBack,NULL);

	this->playAttackInstruction();

	sprite->runAction(sequence);
}

void MDCardPlayer::playAttackAnnimateFrame(MDCardPlayer *target)
{
	setActionPara();

	CCArray *arrayAnimate = CCArray::create();

	//arrayAnimate->addObject(CCString::create("hlz"));//从上而下的火焰，位置不正确;
	//arrayAnimate->addObject(CCString::create("hqz"));//斜着飞的蝙蝠
	//arrayAnimate->addObject(CCString::create("kszd"));//红色的XXXX
	//arrayAnimate->addObject(CCString::create("ldz"));//几把弯刀
	//arrayAnimate->addObject(CCString::create("ln"));//横向闪电
	//arrayAnimate->addObject(CCString::create("mrj"));//粉色的心

	//arrayAnimate->addObject(CCString::create("myz"));//灰色的一团烟雾
	//arrayAnimate->addObject(CCString::create("pjj"));//断掉的剑
	//arrayAnimate->addObject(CCString::create("qbj"));//长矛

	////arrayAnimate->addObject(CCString::create("qishouTX"));
	//arrayAnimate->addObject(CCString::create("sdjx"));//圆形冰圈

	//arrayAnimate->addObject(CCString::create("sfzs"));//雷神之锤
	//arrayAnimate->addObject(CCString::create("sjsql"));//喷发的冰泉
	//arrayAnimate->addObject(CCString::create("sjzs"));//从下到上的红色的矛
	//arrayAnimate->addObject(CCString::create("sqzs"));//从下到上三把匕首
	//arrayAnimate->addObject(CCString::create("srzs"));//挥舞的三把刀
	//arrayAnimate->addObject(CCString::create("szh"));//圆形的火圈

	//arrayAnimate->addObject(CCString::create("tgn"));//从上而下的闪电
	//arrayAnimate->addObject(CCString::create("tjbgz"));//阴阳
	//arrayAnimate->addObject(CCString::create("tx"));//圆形的爆炸
	//arrayAnimate->addObject(CCString::create("wjqf"));//从上而下的三把飞弹 爆炸 位置不正确
	//arrayAnimate->addObject(CCString::create("wlbf"));//方形的冰圈

	//arrayAnimate->addObject(CCString::create("xfz"));//黑色的风
	//arrayAnimate->addObject(CCString::create("yhly"));//从下到上的爆炸 位置不正确
	//arrayAnimate->addObject(CCString::create("yszs"));//位置不正确
	//arrayAnimate->addObject(CCString::create("zhxj"));//骷髅头

	//arrayAnimate->addObject(CCString::create("e0"));
	//arrayAnimate->addObject(CCString::create("e4"));//位置偏右
	//arrayAnimate->addObject(CCString::create("e5"));
	//arrayAnimate->addObject(CCString::create("e11"));
	//arrayAnimate->addObject(CCString::create("e13"));//龙
	//arrayAnimate->addObject(CCString::create("e16"));
	//arrayAnimate->addObject(CCString::create("e17"));//位置偏下 恢复的
	//arrayAnimate->addObject(CCString::create("e20"));//位置偏左 恢复的

	CCDictionary *dictAnnimate = CCDictionary::create();
	if (this->side==1)
	{
		dictAnnimate = CCDictionary::create();
		dictAnnimate->setObject(CCString::create("yszs"),"Annimate");//position
		arrayAnimate->addObject(dictAnnimate);
		dictAnnimate = CCDictionary::create();
		dictAnnimate->setObject(CCString::create("yhly"),"Annimate");//position
		arrayAnimate->addObject(dictAnnimate);
		dictAnnimate = CCDictionary::create();
		dictAnnimate->setObject(CCString::create("hlz"),"Annimate");
		dictAnnimate->setObject(CCString::create("210"),"PosOffsetY");
		arrayAnimate->addObject(dictAnnimate);
		dictAnnimate = CCDictionary::create();
		dictAnnimate->setObject(CCString::create("hqz"),"Annimate");
		arrayAnimate->addObject(dictAnnimate);
		dictAnnimate = CCDictionary::create();
		dictAnnimate->setObject(CCString::create("myz"),"Annimate");
		arrayAnimate->addObject(dictAnnimate);
		dictAnnimate = CCDictionary::create();
		dictAnnimate->setObject(CCString::create("tjbgz"),"Annimate");
		arrayAnimate->addObject(dictAnnimate);
		dictAnnimate = CCDictionary::create();
		dictAnnimate->setObject(CCString::create("xfz"),"Annimate");
		arrayAnimate->addObject(dictAnnimate);
		dictAnnimate = CCDictionary::create();
		dictAnnimate->setObject(CCString::create("zhxj"),"Annimate");
		arrayAnimate->addObject(dictAnnimate);
		dictAnnimate = CCDictionary::create();
		dictAnnimate->setObject(CCString::create("srzs"),"Annimate");
		arrayAnimate->addObject(dictAnnimate);
		dictAnnimate = CCDictionary::create();
		dictAnnimate->setObject(CCString::create("pjj"),"Annimate");
		arrayAnimate->addObject(dictAnnimate);
		dictAnnimate = CCDictionary::create();
		dictAnnimate->setObject(CCString::create("qbj"),"Annimate");
		arrayAnimate->addObject(dictAnnimate);
		dictAnnimate = CCDictionary::create();
		dictAnnimate->setObject(CCString::create("kszd"),"Annimate");
		arrayAnimate->addObject(dictAnnimate);
		dictAnnimate = CCDictionary::create();
		dictAnnimate->setObject(CCString::create("szh"),"Annimate");
		arrayAnimate->addObject(dictAnnimate);
	} else {
		dictAnnimate = CCDictionary::create();
		dictAnnimate->setObject(CCString::create("sjzs"),"Annimate");
		arrayAnimate->addObject(dictAnnimate);
		dictAnnimate = CCDictionary::create();
		dictAnnimate->setObject(CCString::create("ldz"),"Annimate");
		arrayAnimate->addObject(dictAnnimate);
		dictAnnimate = CCDictionary::create();
		dictAnnimate->setObject(CCString::create("ln"),"Annimate");
		arrayAnimate->addObject(dictAnnimate);
		dictAnnimate = CCDictionary::create();
		dictAnnimate->setObject(CCString::create("sdjx"),"Annimate");
		arrayAnimate->addObject(dictAnnimate);
		dictAnnimate = CCDictionary::create();
		dictAnnimate->setObject(CCString::create("sfzs"),"Annimate");
		arrayAnimate->addObject(dictAnnimate);
		dictAnnimate = CCDictionary::create();
		dictAnnimate->setObject(CCString::create("sjsql"),"Annimate");
		arrayAnimate->addObject(dictAnnimate);
		dictAnnimate = CCDictionary::create();
		dictAnnimate->setObject(CCString::create("sqzs"),"Annimate");
		arrayAnimate->addObject(dictAnnimate);

		dictAnnimate = CCDictionary::create();
		dictAnnimate->setObject(CCString::create("tgn"),"Annimate");
		arrayAnimate->addObject(dictAnnimate);
		dictAnnimate = CCDictionary::create();
		dictAnnimate->setObject(CCString::create("tx"),"Annimate");
		arrayAnimate->addObject(dictAnnimate);
		dictAnnimate = CCDictionary::create();
		dictAnnimate->setObject(CCString::create("wjqf"),"Annimate");
		dictAnnimate->setObject(CCString::create("120"),"PosOffsetY");
		arrayAnimate->addObject(dictAnnimate);
		dictAnnimate = CCDictionary::create();
		dictAnnimate->setObject(CCString::create("wlbf"),"Annimate");
		arrayAnimate->addObject(dictAnnimate);
		dictAnnimate = CCDictionary::create();
		dictAnnimate->setObject(CCString::create("e0"),"Annimate");
		arrayAnimate->addObject(dictAnnimate);
		dictAnnimate = CCDictionary::create();
		dictAnnimate->setObject(CCString::create("e4"),"Annimate");
		dictAnnimate->setObject(CCString::create("-12"),"PosOffsetX");
		arrayAnimate->addObject(dictAnnimate);
		dictAnnimate = CCDictionary::create();
		dictAnnimate->setObject(CCString::create("e5"),"Annimate");
		arrayAnimate->addObject(dictAnnimate);
		dictAnnimate = CCDictionary::create();
		dictAnnimate->setObject(CCString::create("e11"),"Annimate");
		arrayAnimate->addObject(dictAnnimate);
		dictAnnimate = CCDictionary::create();
		dictAnnimate->setObject(CCString::create("e13"),"Annimate");
		arrayAnimate->addObject(dictAnnimate);
		dictAnnimate = CCDictionary::create();
		dictAnnimate->setObject(CCString::create("e16"),"Annimate");
		arrayAnimate->addObject(dictAnnimate);
		dictAnnimate = CCDictionary::create();
		dictAnnimate->setObject(CCString::create("e17"),"Annimate");
		arrayAnimate->addObject(dictAnnimate);
		dictAnnimate = CCDictionary::create();
		dictAnnimate->setObject(CCString::create("e20"),"Annimate");
		arrayAnimate->addObject(dictAnnimate);
	}
	
	srand(time(NULL));
	int category = rand()%arrayAnimate->count();

	dictAnnimate = (CCDictionary *)arrayAnimate->objectAtIndex(category);
	std::string strCategory = ((CCString *)dictAnnimate->objectForKey("Annimate"))->getCString();
	CCString *strXPos = (CCString *)dictAnnimate->objectForKey("PosOffsetX");
	CCString *strYPos = (CCString *)dictAnnimate->objectForKey("PosOffsetY");

	m_strAnnimatePath = strCategory + std::string(".xml");

	AnimatePacker::getInstance()->loadAnimations(m_strAnnimatePath.c_str()); 
	CCSprite *sprite = CCSprite::create("transparent.png");
	

	sprite->setUserObject(target);

	this->m_sCardPlayer->getParent()->addChild(sprite);

	CCPoint pos = target->m_sCardPlayer->getPosition();
	if (strXPos != NULL)
	{
		pos.x += strXPos->intValue();
	}
	if (strYPos != NULL)
	{
		pos.y += strYPos->intValue();
	}

	sprite->setPosition(pos);

	CCDelayTime *_delay = CCDelayTime::create(0.6);
	CCAnimate *_animate = AnimatePacker::getInstance()->getAnimate(strCategory.c_str());
	CCFiniteTimeAction* _underAttack = CCCallFuncN::create( this, callfuncN_selector(MDCardPlayer::playUnderAttackAnnimate));
	CCFiniteTimeAction* _removeCallBack = CCCallFuncN::create(this, callfuncN_selector(MDCardPlayer::removeNodeCallBack));

	CCSequence *sequence = CCSequence::create(_delay,_animate,_underAttack,_removeCallBack,NULL);

	this->playAttackInstruction();

	sprite->runAction(sequence);
}


void MDCardPlayer::playAttackInstruction()
{
	int offset = 25;
	if (side==1)
	{
		offset = -25;
	}
	//m_sCardPlayer->stopAllActions();
	CCMoveBy * rotMoveUp = CCMoveBy::create(0.1,ccp(0,offset));
	CCRotateBy * rotLeft = CCRotateBy::create(0.1,18.0);
	CCRotateBy * rotRight = CCRotateBy::create(0.1,-18.0);
	CCMoveBy * rotMoveDown = CCMoveBy::create(0.1,ccp(0,-offset));
	CCSequence * rotSeq = CCSequence::create(rotMoveUp,rotLeft, rotRight,rotMoveDown, NULL);
	m_sCardPlayer->runAction(rotSeq);

	if (m_intActionCategory == CardCategoryAttack)
	{
		CCSprite *normalAttack = CCSprite::create("attack_img.png");

		CCPoint pos = ccp(m_sCardPlayer->getPosition().x, m_sCardPlayer->getPosition().y + 40);
		if (side==1)
		{
			normalAttack->setRotation(180);
			pos = ccp(m_sCardPlayer->getPosition().x, m_sCardPlayer->getPosition().y -40);
		}
		normalAttack->setPosition(pos);
		m_sCardPlayer->getParent()->addChild(normalAttack);

		CCActionInterval * moveto=CCMoveTo::create(0.4, pos);//改动 ccp(enemy->getPosition().x, enemy->getPosition().y)
		CCFiniteTimeAction* _removeCallBack = CCCallFuncN::create(this, callfuncN_selector(MDCardPlayer::removeNodeCallBack));
		CCFiniteTimeAction *playerAct=CCSequence::create(moveto,_removeCallBack,NULL);
		normalAttack->runAction(playerAct);
	}
}

void MDCardPlayer::playParadeAnnimation()
{
	CCJumpBy *jump = CCJumpBy::create(2.0,ccp(0,0),15,4);
	//CCRepeatForever *repeat = CCRepeatForever::create(jump);
	m_sCardPlayer->runAction(jump);
}

void MDCardPlayer::stopAllAction()
{
	m_sCardPlayer->stopAllActions();
}

void MDCardPlayer::playRainAnnimation(CCArray *enemyList)
{
	//MDSoundManager::playEffect(ATTACK_EFFECT);

	setActionPara();

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
	CCShake *_shake = CCShake::create(0.65,4,2);
	CCFiniteTimeAction* _determineHealth = CCCallFuncN::create( this, callfuncN_selector(MDCardPlayer::determineHealth));
	CCFiniteTimeAction* _actionFinished = CCCallFuncN::create( this, callfuncN_selector(MDCardPlayer::actionFinished));
	CCDelayTime *_delayTime = CCDelayTime::create(0.5);

	if (m_hostCardPlayer->m_intActionCategory == CardCategoryAssist)
	{
		m_sCardPlayer->runAction(CCSequence::create(_determineHealth,_delayTime,_actionFinished,NULL));
	}
	else
	{
		m_sCardPlayer->runAction(CCSequence::create(_shake,_determineHealth,_delayTime,_actionFinished,NULL));
	}

	m_lblValue = (CCLabelTTF *)m_sCardPlayer->getChildByTag(101);

	CCSize size = m_sCardPlayer->getContentSize();
	if (m_lblValue==NULL)
	{
		m_lblValue = CCLabelTTF::create("","Marker Felt",40);
		m_sCardPlayer->addChild(m_lblValue);
	}
	m_lblValue->setPosition(ccp(size.width * 0.5,size.height * 0.5));
	if (m_hostCardPlayer-> m_intActionCategory==CardCategoryAssist)
	{
		m_lblValue->setColor(ccc3(0,255,0));
	}
	else
	{
		m_lblValue->setColor(ccc3(255,0,0));
	}
	m_lblValue->setString(IntToString(m_intValue).c_str());
	m_lblValue->setVisible(true);
	CCDelayTime *_delayTime1 = CCDelayTime::create(1.0);

	CCMoveBy *_moveUp= CCMoveBy::create(0.3,ccp(0,30));
	CCHide *_hideAction = CCHide::create();
	m_lblValue->runAction(CCSequence::create(_moveUp,_delayTime1,_hideAction,NULL));
}

void MDCardPlayer::playFeebleAnnimation()
{
	CCActionInterval *colorAction = CCSequence::create(
		CCTintTo::create(0.15f, 255, 0, 0),
		CCTintTo::create(0.15f, 0, 255, 0),
		CCTintTo::create(0.15f, 0, 0, 255),
		//		CCTintTo::create(0.2f, 0, 255, 255),
		//		CCTintTo::create(0.2f, 255, 255, 0),
		//		CCTintTo::create(0.2f, 255, 0, 255),
		CCTintTo::create(0.15f, 255, 255, 255),
		NULL);
	m_sCardPlayer->runAction(colorAction);
}


void MDCardPlayer::playDeadAnnimation()
{
	CCActionInterval *colorAction = CCSequence::create(
		CCTintTo::create(0.0f, 255, 0, 0),
		//CCTintTo::create(0.2f, 0, 255, 0),
		//CCTintTo::create(0.2f, 0, 0, 255),
//		CCTintTo::create(0.2f, 0, 255, 255),
//		CCTintTo::create(0.2f, 255, 255, 0),
//		CCTintTo::create(0.2f, 255, 0, 255),
		//CCTintTo::create(0.2f, 255, 255, 255),
		NULL);
	m_sCardPlayer->runAction(colorAction);
}

void MDCardPlayer::playWiggleAnnimation()
{
	//m_sCardPlayer->stopAllActions();
	CCRotateBy * rotLeft = CCRotateBy::create(0.1,-4.0);
	CCRotateBy * rotCenter = CCRotateBy::create(0.1,0.0);
	CCRotateBy * rotRight = CCRotateBy::create(0.1,4.0);
	CCSequence * rotSeq = CCSequence::create(rotLeft, rotCenter, rotRight, rotCenter, NULL);
	m_sCardPlayer->runAction(CCRepeatForever::create(rotSeq));
}

void MDCardPlayer::MoveToPosition()
{
	//m_sCardPlayer->stopAllActions();

	m_sCardPlayer->runAction(CCEaseBackOut::create(CCMoveTo::create(0.2,m_location)));  
}

void MDCardPlayer::playFireEffect()
{
	setActionPara();

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
	setActionPara();

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
	setActionPara();

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
	setActionPara();

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
	setActionPara(CardCategoryAssist);

    CCParticleSystem *_particle = CCParticleSystemQuad::create("ellipse.plist");
    _particle->setDuration(0.3);
    target->m_sCardPlayer->getParent()->addChild(_particle);
    _particle->setPosition(target->m_sCardPlayer->getPosition());
//    target->m_sCardPlayer->addChild(_particle);
//    _particle->setPosition(ccp(30,0));
    _particle->setAutoRemoveOnFinish(true);
    _particle->setUserObject(target);
    
    CCDelayTime *_delayTime = CCDelayTime::create(0.3);
    CCFiniteTimeAction* _underAttackAction = CCCallFuncN::create( this, callfuncN_selector(MDCardPlayer::playUnderAttackAnnimate));

	this->playAttackInstruction();

    _particle->runAction(CCSequence::create(_delayTime,_underAttackAction,NULL));
}

void MDCardPlayer::setCardData(CCDictionary *dict)
{
	this->m_fltTotalHp = ((CCString *)dict->objectForKey("blood"))->intValue();
	this->m_fltCurrentHp = ((CCString *)dict->objectForKey("blood"))->intValue();
	this->m_fltDefencePoint = ((CCString *)dict->objectForKey("defence"))->floatValue();
	this->m_fltAttackPoint = ((CCString *)dict->objectForKey("attack"))->intValue();
	this->m_fltDodgePoint = ((CCString *)dict->objectForKey("dodge"))->floatValue();
}

void MDCardPlayer::determineHealth(CCNode* sender)
{
	m_fltCurrentHp += m_intValue;
	if (m_fltCurrentHp>m_fltTotalHp)
	{
		m_fltCurrentHp=m_fltTotalHp;
	}
	
	if (m_fltCurrentHp <= 0)
	{
		this->playDeadAnnimation();
		isDead = true;
	}
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
	target->setHostCardPlayer(this);
	target->determineValue(this);
	if (m_intActionCategory!=CardCategoryAssist)
	{
		target->playFeebleAnnimation();
	}

	target->playShakeAnnimation();
}

void MDCardPlayer::setActionPara(CardCategory p_cardCategory)
{
	m_intActionCategory = p_cardCategory;

	isActionFinished = false;
}

void MDCardPlayer::allEnemyUnderAttack(CCNode *pnode)
{
	setActionPara();

	for (int i=0; i<m_EnemyList->count(); i++) {
		MDCardPlayer *enemyPlayer = (MDCardPlayer *)m_EnemyList->objectAtIndex(i);
		if(enemyPlayer->isDead)
		{
			continue;
		}

		enemyPlayer->setHostCardPlayer(this);
		enemyPlayer->determineValue(this);
		enemyPlayer->playFeebleAnnimation();
		enemyPlayer->playShakeAnnimation();
		
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
	if (m_strAnnimatePath.length()>0 )
	{
		AnimatePacker::getInstance()->freeAnimations(m_strAnnimatePath.c_str());
		m_strAnnimatePath.clear();
	}
	pNode->removeFromParentAndCleanup(true);
}

void MDCardPlayer::setHostCardPlayer(MDCardPlayer *p_hostCardPlayer)
{
	m_hostCardPlayer = p_hostCardPlayer;

	//int attackValue = max(p_hostCardPlayer->m_fltAttackPoint * 0.8,(p_hostCardPlayer->m_fltAttackPoint - this->m_fltDefencePoint) * (1 + 0.05));
}

void MDCardPlayer::determineValue(MDCardPlayer *p_sender)
{
	//m_intValue = max(p_sender->m_fltAttackPoint * 0.8,(p_sender->m_fltAttackPoint - this->m_fltDefencePoint) * (1 + 0.05));
	m_intValue = -590;
	if (side==0)
	{
		m_intValue = -10;
	}

	if (m_hostCardPlayer->m_intActionCategory ==  CardCategoryAssist)
	{
		m_intValue = abs(m_intValue)/5;
	}
}

