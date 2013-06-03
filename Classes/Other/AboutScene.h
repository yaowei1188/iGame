//
//  AboutScene.h
//  cctest
//
//  Created by China Team on 4/9/13.
//
//

#ifndef __cctest__AboutScene__
#define __cctest__AboutScene__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"

using namespace cocos2d;
using namespace cocos2d::extension;

class AboutScene : public cocos2d::CCLayer,public CCBSelectorResolver {
public:
    ~AboutScene();
    AboutScene();
    
    // returns a Scene that contains the HelloWorld as the only child
    static cocos2d::CCScene* scene();
    
    void buttonPressed(CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent);
    
    void appleClicked(CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent);
    
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
    
    CREATE_FUNC(AboutScene);
    
    virtual bool init();
    
};

#endif /* defined(__cctest__AboutScene__) */
