//
//  SharpLabelTTF.cpp
//  cctest
//
//  Created by China Team on 4/9/13.
//
//

#include "MDScrollLabel.h"

#define AutoMoveSpeed -0.5f
#define OFFSET 10.0f
#define BEDISTANCE 7.0f

MDScrollLabel::MDScrollLabel()
{
    _label1 = NULL;
    _label2 = NULL;
}
MDScrollLabel::~MDScrollLabel()
{
    if (_label1) {
        _label1->release();
    }
    if (_label2) {
        _label2->release();
    }

    _label1 = NULL;
    _label2 = NULL;
}
MDScrollLabel* MDScrollLabel::create(const char *label,CCSize dimensions,const char *fontName, float fontSize)
{
    MDScrollLabel *pRet = new MDScrollLabel();
    if(pRet && pRet->initWithString(label, dimensions,fontName, fontSize))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;

}
bool MDScrollLabel::initWithString(const char *label,CCSize dimensions,const char *fontName, float fontSize)
{
    bool bRet = false;
    do
    {

        CC_BREAK_IF(! CCSprite::init());

        this->setContentSize(dimensions);

        m_tContentSize = this->getContentSize();

        _label1 = CCLabelTTF::create(label, fontName, fontSize);
        _label1->setHorizontalAlignment(kCCTextAlignmentLeft);
        _label1->setVerticalAlignment(kCCVerticalTextAlignmentTop);
        _label1->setFlipY(-1);
        _label1->setColor(ccWHITE);
        
        _bx = (m_tContentSize.width-OFFSET)/2;
        
        _label1->setPosition(ccp(_bx-1,0));
        _label1->retain();
        
        _textSize = _label1->getContentSize();

        _label2 = CCLabelTTF::create(label, fontName, fontSize);
        _label2->setFlipY(-1);
        _label2->setColor(ccWHITE);

        _dis = BEDISTANCE +_textSize.width;
        _label2->setPosition(ccp(_bx + _dis,0));
        _label2->retain();

        if (this->autoScroll()) {
            _label1->setAnchorPoint(ccp(0,0));
            _label2->setAnchorPoint(ccp(0,0));
            return initWithTexture(this->getTextureFromSpr(_label1,_label2));
        }
        else
        {
            _label1->setAnchorPoint(ccp(0.5,0));
            _label2->setAnchorPoint(ccp(0.5,0));
            return initWithTexture(this->getTextureFromSpr(_label1,NULL));
        }
        
        bRet = true;
    } while (0);
    
    return bRet;
    
    
}
void MDScrollLabel::setString(const char *str)
{
    this->stopAllActions();
    this->unscheduleUpdate();
    _label1->setString(str);
    _label1->setPosition(ccp(_bx,0));

    _label2->setString(str);
    _label2->setPosition(ccp(_bx + _dis,0));

    _textSize = _label1->getContentSize();


    if (this->autoScroll()) {
        _label1->setAnchorPoint(ccp(0,0));
        _label2->setAnchorPoint(ccp(0,0));
    }
    else
    {
        _label1->setAnchorPoint(ccp(0.5,0));
        _label2->setAnchorPoint(ccp(0.5,0));
        setTexture(getTextureFromSpr(_label1,NULL));
    }

}

//CCRect MDScrollLabel::rect()
//{
//    CCPoint position = this->getPosition();
//    CCPoint anchorPoint = this->getAnchorPoint();
//    return CCRectMake( position.x - m_tContentSize.width*anchorPoint.x,
//                      position.y - m_tContentSize.height*anchorPoint.y,
//                      m_tContentSize.width, m_tContentSize.height);
//}

void MDScrollLabel::update(float dt)
{
    CCLabelTTF *bTTF,*eTTF;
    float m_p = _label1->getPosition().x;

    if (m_p >(OFFSET/2 - _textSize.width)  && m_p < _bx) {
        bTTF = _label1;
        eTTF = _label2;
    }
    else
    {
        bTTF = _label2;
        eTTF = _label1;
    }

    CCPoint p = bTTF->getPosition();


    bTTF->setPosition(ccp(p.x + AutoMoveSpeed,0));
    eTTF->setPosition(ccp(p.x + AutoMoveSpeed + _dis,p.y));

    setTexture(getTextureFromSpr(_label1,_label2));
}

bool MDScrollLabel::autoScroll()
{
    //文本高度大于显示高度，需要滚动
    if (_textSize.width > m_tContentSize.width-OFFSET) {
        this->scheduleUpdate();
        return true;
    }
    return false;
}

CCTexture2D *MDScrollLabel::getTextureFromSpr(CCSprite *spr1,CCSprite *spr2)
{
    CCRenderTexture* rt = CCRenderTexture::create(m_tContentSize.width-OFFSET, m_tContentSize.height);
    rt->begin();
    spr1->visit();
    if (spr2) {
        spr2->visit();
    }
    rt->end();
    return rt->getSprite()->getTexture();
}
