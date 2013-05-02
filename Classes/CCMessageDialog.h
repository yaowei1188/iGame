#ifndef __CCMESSAGEDIALOG_SCENE_H__
#define __CCMESSAGEDIALOG_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"

#include "SimpleAudioEngine.h"
#include "XmlParser.h"

using namespace cocos2d;
using namespace cocos2d::extension;

class CCMessageDialog;

class CCMessageDialogDelegate
{
public:
	virtual void didClickButton(CCMessageDialog* dialog,unsigned int index) = 0;
};

class CCMessageDialog : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();

    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CCMessageDialog, create);
    
	void buttonClicked(CCObject *pSender);
    virtual void registerWithTouchDispatcher(void);
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);

	void setTitle(const char * title);

	CCMessageDialogDelegate* getDelegate() { return m_pDelegate; }
	void setDelegate(CCMessageDialogDelegate* pDelegate) { m_pDelegate = pDelegate; }

protected:
	CCControlButton *btnSubmit;
	CCLabelTTF *lblTitle;
	CCMessageDialogDelegate* m_pDelegate;
};

#endif  // __LOGINSCENE_SCENE_H__