#ifndef __CARD_ALCHEMY_LAYER_H__
#define __CARD_ALCHEMY_LAYER_H__

#include "cocos2d.h"
#include "cocos-ext.h"

#include "SimpleAudioEngine.h"
#include "MainGameScene.h"
#include "MainSceneTemplate.h"
#include "MainLayerBase.h"
#include "MDHeroListLayer.h"
#include "SlidingMenu.h"
#include "MDProgressBar.h"

using namespace cocos2d;
using namespace cocos2d::extension;

class MDCardAlchemyLayer : public MainLayerBase,MDHeroListLayerDelegate,
//	public CCTableViewDataSource,
//	public CCTableViewDelegate,
	public CCBSelectorResolver,
	public CCNodeLoaderListener,
	public CCBMemberVariableAssigner
{
public:
	MDCardAlchemyLayer();
	~MDCardAlchemyLayer();

	virtual bool init();  

	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene();


	// implement the "static node()" method manually
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(MDCardAlchemyLayer,create);

private:

	virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);

	void buttonClicked(CCObject * sender , CCControlEvent controlEvent);
//	void didClickButton(CCMessageDialog* dialog,unsigned int index);
	void executeTask(std::string &targetUser);
	virtual void didSelectedItems(CCArray *pItems);

    void menuItemCallback(CCObject* pSender);
    void startAlchemy();
    void step(float dt);

    // a selector callback
	void requestFinishedCallback(CCHttpClient* client, CCHttpResponse* response);
	void doSearch();
    
	unsigned int selectedindex;
	CCDictionary *mTaskList;
	int selectedButton;

    MDProgressBar *barBg;
    MDProgressBar *barFront;
    CCLabelBMFont* lblTime;
    float waitTime;
    float remainTime;
};

#endif  // __CARD_ALCHEMY_LAYER_H__