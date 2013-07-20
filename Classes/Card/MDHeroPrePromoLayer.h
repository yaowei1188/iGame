#ifndef __HERO_PRE_PROMO_LAYER_H__
#define __HERO_PRE_PROMO_LAYER_H__

#include "cocos2d.h"
#include "cocos-ext.h"

#include "SimpleAudioEngine.h"
#include "MainGameScene.h"
#include "MainSceneTemplate.h"
#include "MainLayerBase.h"
#include "SlidingMenu.h"

using namespace cocos2d;
using namespace cocos2d::extension;

class MDHeroPrePromoLayer : public MainLayerBase,
//	public CCTableViewDataSource,
//	public CCTableViewDelegate,
	public CCBSelectorResolver,
	public CCNodeLoaderListener,
	public CCBMemberVariableAssigner
{
public:
	MDHeroPrePromoLayer();
	~MDHeroPrePromoLayer();

	virtual bool init();  

	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene();

	// a selector callback
	void requestFinishedCallback(CCHttpClient* client, CCHttpResponse* response);

	// implement the "static node()" method manually
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(MDHeroPrePromoLayer,create);

	virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);

	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);

	void buttonClicked(CCObject * sender , CCControlEvent controlEvent);
    void showTaskInfo();
    
private:
	unsigned int selectedindex;

    CCSprite *m_sCardBefore;
    CCSprite *m_sCardAfter;
	CCDictionary *mTaskList;
    
    CCLabelTTF *m_lblPreQuality;
    CCLabelTTF *m_lblAftQuality;
    CCLabelTTF *m_lblCardName;
    
    CCLabelTTF *m_lblRank;
    CCLabelTTF *m_lbExp;
    CCLabelTTF *m_lbHP;
    CCLabelTTF *m_lblAttack;
    CCLabelTTF *m_lblDefence;
    CCLabelTTF *m_lblSuper;
    
    CCLabelTTF *m_lblAftRank;
    CCLabelTTF *m_lbAftExp;
    CCLabelTTF *m_lbAftHP;
    CCLabelTTF *m_lblAftAttack;
    CCLabelTTF *m_lblAftDefence;
    CCLabelTTF *m_lblAftSuper;
};

#endif  // __TASK_DETAIL_SCENE_H__