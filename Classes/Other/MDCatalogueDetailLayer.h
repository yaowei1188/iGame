#ifndef __MDCATALOGUE_DETAIL_LAYER_H__
#define __MDCATALOGUE_DETAIL_LAYER_H__

#include "cocos2d.h"
#include "cocos-ext.h"

#include "MainGameScene.h"
#include "MainLayerBase.h"

using namespace cocos2d;
using namespace cocos2d::extension;

class MDCatalogueDetailLayer : public MainLayerBase,
	public CCBSelectorResolver,
	public CCNodeLoaderListener,
	public CCBMemberVariableAssigner
{
public:
	MDCatalogueDetailLayer();
	~MDCatalogueDetailLayer();

	virtual bool init();  

	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene();

	// a selector callback
	void requestFinishedCallback(CCHttpClient* client, CCHttpResponse* response);

	// implement the "static node()" method manually
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(MDCatalogueDetailLayer,create);

	virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);

	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);

	void buttonClicked(CCObject * sender , CCControlEvent controlEvent);
    void doPromotion();
    void menuItemCallback(CCObject* pSender);
private:
	unsigned int selectedindex;
    CCSprite *m_sCard;
    CCSprite *m_sFraction;
	CCDictionary *mTaskList;
    
    CCLabelTTF *m_lblLevel;
    CCLabelTTF *m_lblCardName;
    CCLabelTTF *m_lblHp;
    CCLabelTTF *m_lblDefence;
    CCLabelTTF *m_lblAttack;
    CCLabelTTF *m_lblAvoid;
    CCLabelTTF *m_lblDesc;
};

#endif  // __MDCATALOGUE_DETAIL_LAYER_H__