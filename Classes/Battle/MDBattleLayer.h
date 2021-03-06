#ifndef __MDBATTLE_LAYER_H__
#define __MDBATTLE_LAYER_H__

#include "cocos2d.h"
#include "cocos-ext.h"

#include "SimpleAudioEngine.h"
#include "MainGameScene.h"
#include "MDCardPlayer.h"
#include "GlobalData.h"

using namespace cocos2d;
using namespace cocos2d::extension;

typedef enum _BattleWinerSide
{
	BattleWinner_Heros = 1,
	BattleWinner_Enemy,
	BattleWinner_None
} BattleWinerSide;

class MDBattleLayer : public CCLayerColor,
public CCBSelectorResolver,
public CCNodeLoaderListener,
public CCBMemberVariableAssigner,
public CCMessageDialogDelegate,
public MDCardPlayerDelegate
{
public:
    MDBattleLayer();
    ~MDBattleLayer();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();

    // a selector callback
    void requestFinishedCallback(CCHttpClient* client, CCHttpResponse* response);
    void doSearchFriend();
    void addFriendRequest(std::string &userinfo);

    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(MDBattleLayer, create);

	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    
	void buttonClicked(CCObject *pSender,CCControlEvent event);
	void didActionFinished(MDCardPlayer* player);
    
    void toolBarTouchDownAction(CCObject *pSender, CCControlEvent pCCControlEvent);
    
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
    
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);

	virtual void didClickButton(CCMessageDialog* dialog,unsigned int index);
	void prepareFormation();
	void prepareEnemyFormation();

	void prepareBackGround();
	void selectSpriteForTouch(CCPoint touchLocation);
	void panForTranslation(CCPoint translation);
	void exchangeCard(MDCardPlayer *p_cardOne,MDCardPlayer *p_cardTwo);
	void menuCallback(CCObject* sender);
	void startPuzzle();
	void onUpdate(float time);
	void cardMoveForward();
	void backgroundMoveForward();
	void cardMoveFinished(CCNode* sender);
	bool btnTouched;

protected:
//    CCNode*        m_root;
//    CCNode*        m_target;
//    CCMotionStreak *streak;

private:
    
    void playHeroAction();
	void playEnemyAction();
	void doBattle();
	int getNextVictim(CCArray *array);
	int getNextPresenter(CCArray *array,int *num);
	BattleWinerSide determineWinner();
	void prepareMoveForward();
	void showRoundInfo();
	void playWinAction();
	void removeNodeCallBack(CCNode* pNode);
	CCArray *mCardNameList;
	CCArray *mHeroCardList;
	//CCArray *mEnemyCardNameList;
	CCArray *mEnemyCardList;
	CCSprite *m_sSelectedSprite;
    CCArray *mParticle;
	CCArray *mHeroList;
    int intCurrentHeroCard;
	int intCurrentEnemyCard;
	bool actionFinished;
	int m_intRound;
	int m_intEnemyCount;
	int m_intWhoAttack;

	CCLabelTTF *m_lblRoundInfo;
};

#endif  // __LOGINSCENE_SCENE_H__