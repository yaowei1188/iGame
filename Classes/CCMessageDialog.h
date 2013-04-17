#ifndef __CCMESSAGEDIALOG_SCENE_H__
#define __CCMESSAGEDIALOG_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"

#include "SimpleAudioEngine.h"
#include "XmlParser.h"

using namespace cocos2d;
using namespace cocos2d::extension;

class CCMessageDialog : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();

    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CCMessageDialog, create);
    
	void submitClicked(CCObject *pSender);
    virtual void registerWithTouchDispatcher(void);
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);

	CCControlButton *btnSubmit;
};

#endif  // __LOGINSCENE_SCENE_H__