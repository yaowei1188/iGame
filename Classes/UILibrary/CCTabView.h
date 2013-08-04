//
//  CCTabView.h
//  testxdoceione
//
//  Created by Michael YUE on 12/03/12.
//  Copyright (c) 2012 private. All rights reserved.
//

#ifndef _CCTABVIEW_H_
#define _CCTABVIEW_H_


#include "cocos2d.h"

USING_NS_CC;


#define DEF_HEADER_SIZE CCSizeMake(66,42)

class  CCTabView : public CCLayer
{
public:
    CCTabView(CCRect rect = CCRectZero);
    virtual ~CCTabView();
    
    void addTab(const char * tabName, CCLayer * tabView);
    void addTab(const char * tabName,const char * tabNormal,const char * tabActive, CCLayer * tabView);

    virtual void onEnter();
	virtual void onExit();
    
    // handle touch events
//    virtual void registerWithTouchDispatcher();
//	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
//	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
//	virtual void ccTouchCancelled(CCTouch *touch, CCEvent* event);
//	virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
    
    // tab clicked events
    void tabClicked(CCObject * obj);
    
    // properties
    // middle padding position between tabs
    CC_SYNTHESIZE(float,_midPad,MidPad);
    
    // left margin for first tab
    CC_SYNTHESIZE(float,_leftMargin,LeftMargin);
    
    // tab header image size
    CC_SYNTHESIZE(CCSize,_tabSize,TabSize);
    
    // tab edge frame size
    CC_SYNTHESIZE(float,_leftInsect,LeftInsect);
    CC_SYNTHESIZE(float,_topInsect,TopInsect);
    
    // tab title font size and color
    CC_SYNTHESIZE(float,_titleFontSize,TitleFontSize);
    CC_SYNTHESIZE(std::string,_titleFontName,TitleFontName);
    CC_SYNTHESIZE(ccColor3B,_titleFontColor,TitleFontColor);
    
    // default selected tab
    CC_SYNTHESIZE(int,_selectedTab,SelectedTab);
    
    // same tab title and related tab sub view
    CC_SYNTHESIZE(CCArray *,_tabNameArray,TabNameArray);
    CC_SYNTHESIZE(CCArray *,_tabViewArray,TabViewArray);

	CCLayer * getSelectedLayer();
    
private:
    void initTabData();
    CCSize _edgeSize;
    
    CCMenuItemSprite * _preSelectedTab;
    CCLayer * _tabView;
    
};

#endif