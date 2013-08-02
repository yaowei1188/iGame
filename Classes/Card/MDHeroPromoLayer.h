#ifndef __HERO_PROMO_LAYER_H__
#define __HERO_PROMO_LAYER_H__

#include "cocos2d.h"
#include "cocos-ext.h"

#include "MainGameScene.h"
#include "MainLayerBase.h"

using namespace cocos2d;
using namespace cocos2d::extension;

class MDHeroPromoLayer : public MainLayerBase,
//	public CCTableViewDataSource,
//	public CCTableViewDelegate,
	public CCBSelectorResolver,
	public CCNodeLoaderListener,
	public CCBMemberVariableAssigner
{
public:
	MDHeroPromoLayer();
	~MDHeroPromoLayer();

	virtual bool init();  

	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene();

	// a selector callback
	void requestFinishedCallback(CCHttpClient* client, CCHttpResponse* response);

	// implement the "static node()" method manually
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(MDHeroPromoLayer,create);

	virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);

	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);

	void buttonClicked(CCObject * sender , CCControlEvent controlEvent);
	void doSearch();

private:

	CCDictionary *mTaskList;
    
    CCLabelTTF *m_lblWindNum;
    CCLabelTTF *m_lblWindStr;
    CCLabelTTF *m_lblFireNum;
    CCLabelTTF *m_lblFireStr;
    CCLabelTTF *m_lblWaterNum;
    CCLabelTTF *m_lblWaterStr;
    CCLabelTTF *m_lblStoneNum;
    CCLabelTTF *m_lblStoneStr;
};

#endif  // __TASK_DETAIL_SCENE_H__