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

class MDCardPlayer : public CCObject
{
public:
	CCSprite *m_sCardPlayer;
	CCPoint m_location; //卡牌所在坐标
	int position; //卡牌所在位置

private:
	CCString *m_strCardName;
	

    float m_fltTotalHp;//血量
    float m_fltCurrentHp;//当前血量

	float m_fltAttackPoint;//力-卡牌物理攻击
	float m_fltMagicPoint;//法-卡牌法术攻击
	float m_fltDefencePoint;//防御-卡牌防御

	float m_fltSuperAttackPoint;//暴-卡牌暴击
	float m_fltDodgePoint;//闪避-卡牌闪避
	float m_fltSpiritPoint;//神-卡牌全属性

    float m_fltGroupBUFF; //组队BUFF
    float m_fltActivateBUFF; //激活BUFF
    float m_fltSmallGameBUFF;//小游戏BUFF
    float m_fltVipBUFF;   //VIP BUFF

    int battleMode;//战斗模式
    bool isDead;

	
public:
	void playParadeAnnimation();//播放前进动画
    void playAttackAnnimation();//播放攻击动画
    void playMistreatAnnimation();//播放被攻击动画
    void playDeadAnnimation();//播放死亡动画
	void playWiggleAnnimation();//播放死亡动画
	void MoveToPosition();//返回原来位置
	bool init(std::string p_cardName);
	void playFireEffect();
	//CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(MDCardPlayer,create);

	static MDCardPlayer * create(std::string p_cardName);
	void playGalaxyEffect();
	void playMeteorEffect();
	void stopAllAction();
};

#endif /* defined(__mengdou__MDCardPlayer__) */
