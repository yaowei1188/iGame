//
//  MDProgressBar.h
//  cctest
//
//  Created by China Team on 4/9/13.
//
//

#ifndef _I_MDProgressBar__
#define _I_MDProgressBar__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"

using namespace cocos2d;
using namespace cocos2d::extension;

class MDProgressBar : public cocos2d::CCNode {
public:
    ~MDProgressBar();
    MDProgressBar();
    
    virtual bool init(const char *lcap,const char *mcap,const char *rcap,float pwidth,float percent);

    static MDProgressBar * create(const char *lcap,const char *mcap,const char *rcap,float pwidth,float percent);

    void setPercent(float percent);

private:
    CCSprite *m_lCap;
    CCScale9Sprite *m_mCap;
    CCSprite *m_rCap;
    float m_percent;
    float m_barWidth;
    
};

#endif
