//
//  SharpLabelTTF.h
//  cctest
//
//  Created by China Team on 4/9/13.
//
//

#ifndef __MDMDScrollLabel__
#define __MDMDScrollLabel__

#include "cocos2d.h"


using namespace cocos2d;

class MDScrollLabel : public cocos2d::CCSprite {

public:
    MDScrollLabel();
    ~MDScrollLabel();
    static MDScrollLabel* create(const char *label,CCSize dimensions,const char *fontName, float fontSize);
    bool initWithString(const char *label,CCSize dimensions,const char *fontName, float fontSize);
    void setString(const char *str);
//    CCRect rect();
    bool autoScroll();

    void update(float dt);
    inline void setColor(ccColor3B c){ if(_label1 && _label2){_label1->setColor(c);_label2->setColor(c);}}

    CCTexture2D *getTextureFromSpr(CCSprite *spr1,CCSprite *spr2);
private:
    CCLabelTTF *_label1;
    CCLabelTTF *_label2;
    CCSize  _textSize;
    CCSize m_tContentSize;
    float _dis;
    float _bx;
    
};

#endif
