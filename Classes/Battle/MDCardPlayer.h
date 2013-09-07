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

typedef enum _CardCategory
{
	CardCategoryAttack = 1,
	CardCategoryDefence,
	CardCategoryAssist
} CardCategory;

class MDCardPlayer;

class MDCardPlayerDelegate
{
public:
	virtual void didActionFinished(MDCardPlayer* player) = 0;
};

class MDCardPlayer : public CCScheduler
{
public:

	MDCardPlayer();

	CCSprite *m_sCardPlayer;
	CCLabelTTF *m_lblValue;
	CCPoint m_location; //卡牌所在坐标
	int position; //卡牌所在位置
	CC_SYNTHESIZE(MDCardPlayerDelegate*, m_delegate, Delegate);
	
	CC_SYNTHESIZE(CCDictionary*, m_dicFormation, Formation);

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

	static MDCardPlayer * create(std::string p_cardName);

	void playParadeAnnimation();//播放前进动画
    void playRainAnnimation(CCArray *enemyList);//播放攻击动画
    void playShakeAnnimation();//播放被攻击动画
    void playDeadAnnimation();//播放死亡动画
	void playWiggleAnnimation();//播放死亡动画
	void MoveToPosition();//返回原来位置
	bool init(std::string p_cardName);
	void playFireEffect();
	//CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(MDCardPlayer,create);

	
	void playGalaxyEffect();
	void playMeteorEffect(MDCardPlayer *target);
    void playFireEffect(MDCardPlayer *target);
    void playEcllipseEffect(MDCardPlayer *target);
	void stopAllAction();
    void playExploreEffect(MDCardPlayer *target);
    void playAnnimateFrame(MDCardPlayer *target);

	void setHostCardPlayer(MDCardPlayer *p_hostCardPlayer){m_hostCardPlayer = p_hostCardPlayer;};
	void setCardData(CCDictionary *dict);

	void playAttackInstruction();

private:
    void actionFinished(CCNode* sender);
    //void allEnemyUnderAttack(float dt);
	void allEnemyUnderAttack(CCNode *pnode);
    void removeNodeCallBack(CCNode* pNode);
	void playUnderAttackAnnimate(CCNode* sender);
	void setNodeInvisible(CCNode* pNode);
	void determineValue(MDCardPlayer *target);
	CCArray *m_EnemyList;
	MDCardPlayer *m_hostCardPlayer;
	bool isActionFinished;

	CCArray *m_AnimateList;
	int m_intValue;

};

#endif /* defined(__mengdou__MDCardPlayer__) */
