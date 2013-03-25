#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"

#include "SimpleAudioEngine.h"
#include "XmlParser.h"

using namespace cocos2d;
using namespace cocos2d::extension;

class HelloWorld : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void requestFinishedCallback(CCNode* pSender,void *p);

    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);
	void submitClicked(CCObject *pSender,CCControlEvent event);
	void doSubmit();

	CCEditBox *m_txtAccount;
	CCEditBox *m_txtPassword;
	CCLabelTTF *lblAccount;
	CCLabelTTF *lblPassword;

	CCControlButton *btnSubmit;
};

#endif  // __HELLOWORLD_SCENE_H__