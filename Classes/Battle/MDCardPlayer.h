//
//  MDCardPlayer.h
//  mengdou
//
//  Created by ivan on 6/3/13.
//
//

#ifndef __mengdou__MDCardPlayer__
#define __mengdou__MDCardPlayer__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"

using namespace std;
using namespace cocos2d;
using namespace cocos2d::extension;

class MDCardPlayer
{
public:

private:s
	CCString *m_strCardName;
	CCSprite *m_sCardPlayer;

	float m_fltPowerPoint;//力-物理攻击
	float m_fltMagicPoint;//法-法术攻击
	float m_fltDefencePoint;//防-卡牌防御

	float m_fltSuperAttackPoint;//暴击-卡牌暴击
	float m_fltDodgePoint;//躲闪-卡牌闪避
	float m_fltSpiritPoint;//神-卡牌全属性

	int battleMode;//默认手动模式0，自动模式1
public:
	void forwardAnnimation();
};

#endif /* defined(__mengdou__MDCardPlayer__) */
