//
//  CCTabView.m
//
//  Created by Michael YUE on 12/03/12.
//  Copyright (c) 2012 private. All rights reserved.
//

#include "CCTabView.h"
#include <math.h>

//#define TAB_NORMAL "tab_normal.png"
//#define TAB_ACTIVE "tab_active.png"
//#define TAB_LINE "tab_line.png"
//#define TAB_EDGE "tab_kuan.9.png"

#define kCCMenuTouchPriority 1

CCTabView::CCTabView(CCRect rect)
{
    this->setContentSize(rect.size);
    this->setPosition(rect.origin);
    
    // set default values
    _tabSize = DEF_HEADER_SIZE;
    _leftMargin = 8.0;
    _midPad = 0.0;
    _leftInsect = 14.0;
    _topInsect = 11.0;
    _titleFontName = "Arial";
    _titleFontColor = ccc3(0xfb,0xcf,0x4b);
    _titleFontSize = 16.0;
    _preSelectedTab = NULL;
    _selectedTab = 0;
    _tabNameArray = CCArray::create();
	_tabNameArray->retain();
	_tabViewArray = CCArray::create();
	_tabViewArray->retain();
    
    // pre-load tab images
    //CCTextureCache::sharedTextureCache()->addImage(TAB_NORMAL);
    //CCTextureCache::sharedTextureCache()->addImage(TAB_LINE);
    //CCTextureCache::sharedTextureCache()->addImage(TAB_ACTIVE);
    //CCTexture2D * edgeTexture = CCTextureCache::sharedTextureCache()->addImage(TAB_EDGE);
    //_edgeSize = edgeTexture->getContentSize();
    
    // create sub view container
    _tabView = CCLayer::create();
	_tabView->setAnchorPoint(CCPointZero);
	_tabView->setPosition(CCPointZero);
    this->addChild(_tabView);

}

CCTabView::~CCTabView()
{
    CC_SAFE_DELETE(_tabNameArray);
    CC_SAFE_DELETE(_tabViewArray);
}

void CCTabView::addTab(const char * tabName, CCLayer * tabView)
{
    CCString * strTabName = CCString::create(tabName);
    CCDictionary *dict = CCDictionary::create();
    dict->setObject(strTabName, "TabTitle");
    _tabNameArray->addObject(dict);
    
    _tabViewArray->addObject(tabView);
}

void CCTabView::addTab(const char * tabName,const char * tabNormal,const char * tabActive, CCLayer * tabView)
{
    CCDictionary *dict = CCDictionary::create();

    CCString * strTabName = CCString::create(tabName);
    dict->setObject(strTabName, "TabTitle");
    
    CCString * strTabNormal = CCString::create(tabNormal);
    dict->setObject(strTabNormal, "TabNormal");
    
    CCString * strTabActive = CCString::create(tabActive);
    dict->setObject(strTabActive, "TabActive");

    _tabNameArray->addObject(dict);
    
    _tabViewArray->addObject(tabView);
}

// tab clicked events
void CCTabView::tabClicked(CCObject * obj)
{
    CCMenuItemSprite * pMenu = dynamic_cast<CCMenuItemSprite*>(obj);
    if ( pMenu != _preSelectedTab )
    {
		// unselected previous one
		if ( _preSelectedTab != NULL )
		{
			_preSelectedTab->unselected();
		}

        pMenu->selected(); 

        _preSelectedTab = pMenu;
        
        // showing related tab view
        int tabIndex = pMenu->getTag();
        
        // remove previous tab view
        _tabView->removeAllChildrenWithCleanup(true);
        CCLayer * subView = (CCLayer *)_tabViewArray->objectAtIndex(tabIndex);
        //float yPos = this->getContentSize().height - _tabSize.height - subView->getContentSize().height;
        subView->setPosition(ccp(2,-36));
		subView->setAnchorPoint(CCPointZero);
        _tabView->addChild(subView);
    } else {
        pMenu->selected(); 
    }
}


void CCTabView::initTabData()
{
    int tabNameCount = _tabNameArray->count();
    int tabViewCount = _tabViewArray->count();
    if ( tabNameCount <= 0 || tabViewCount <= 0 ) 
	{
		return;
	}
    
    int tabCount = MAX(tabNameCount,tabViewCount);
    
	CCPoint tabStartPos = ccp(_tabSize.width/2 + _leftMargin,this->getContentSize().height-_tabSize.height/2);
    CCPoint lastPos = CCPointZero;
	CCMenu * pMenu = CCMenu::create();
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu);

    for ( int i = 0 ; i < tabCount ; i++ )
    {
        CCDictionary *dict = (CCDictionary *)_tabNameArray->objectAtIndex(i);
        CCString * tabNormal = (CCString *)dict->objectForKey("TabNormal");
        CCString * tabActive = (CCString *)dict->objectForKey("TabActive");
        
        // set tab background
        lastPos = ccpAdd(tabStartPos,ccp((_tabSize.width+_midPad - 1)*i,0));
//        CCMenuItemImage * oneTab = CCMenuItemImage::create(TAB_NORMAL, TAB_ACTIVE, TAB_NORMAL, this, menu_selector(CCTabView::tabClicked));
        
        CCSprite *sNormal = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(tabNormal->getCString()));
        CCSprite *sSelected = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(tabActive->getCString()));
        CCSprite *sLocked = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(tabNormal->getCString()));
        
        CCMenuItemSprite *oneTab = CCMenuItemSprite::create(sNormal, sSelected, sLocked, this, menu_selector(CCTabView::tabClicked));
        
        oneTab->setPosition(lastPos);
        oneTab->setTag(i);

		pMenu->addChild(oneTab);
        
        if ( i == _selectedTab ) 
        {
            oneTab->selected();
            _preSelectedTab = oneTab;
            
            _tabView->removeAllChildrenWithCleanup(true);

            CCLayer * subView = (CCLayer *)_tabViewArray->objectAtIndex(i);
            //float yPos = this->getContentSize().height - subView->getContentSize().height;
            subView->setPosition(ccp(2,-36));
			subView->setAnchorPoint(CCPointZero);
            _tabView->addChild(subView);
        }
        
        // set tab title
        //CCString * titleName = (CCString *)dict->objectForKey("TabTitle");
        //CCLabelTTF * ttl = CCLabelTTF::create(titleName->getCString(),_titleFontName.c_str(),_titleFontSize);
        //ttl->setColor(_titleFontColor);
        //ttl->setPosition(lastPos);
        //this->addChild(ttl);
    }
    
//    // draw edges
//    // left top 
//    CCTexture2D * angleTexture = CCTextureCache::sharedTextureCache()->textureForKey(TAB_EDGE);
//    CCSprite * leftTopSprite = CCSprite::createWithTexture(angleTexture, CCRectMake(0,0,9,7));
//    float yPos = this->getContentSize().height - _tabSize.height;
//    leftTopSprite->setPosition(ccp(0.0,yPos));
//    this->addChild(leftTopSprite);
//    
//    // between left to and first tab
//    CCTexture2D * line = CCTextureCache::sharedTextureCache()->textureForKey(TAB_LINE);
//    int lineCount = _leftMargin;
//    for ( int i = 0 ; i < lineCount ; i++ )
//    {
//        CCSprite * oneline = CCSprite::createWithTexture(line);
//        oneline->setPosition(ccp(4 + i, leftTopSprite->getPosition().y + 21.0));
//        this->addChild(oneline);
//    }
//    
//    // last tab up to right top
//    lineCount = this->getContentSize().width - (lastPos.x+_tabSize.width/2);
//    CCPoint startPos = ccp(lastPos.x+_tabSize.width/2,leftTopSprite->getPosition().y + 21.0);
//    int j = 0;
//    for ( j = 0 ; j < lineCount ; j++ )
//    {
//        CCSprite * oneline = CCSprite::createWithTexture(line);
//        oneline->setPosition(ccpAdd(startPos, ccp(j,0)));
//        this->addChild(oneline);
//    }
//    
//    // right top 
//    CCSprite * rightTopSprite = CCSprite::createWithTexture(angleTexture, CCRectMake(10,0,9,7));
//    rightTopSprite->setPosition(ccp(startPos.x+j,yPos));
//    this->addChild(rightTopSprite);
//    
//    // from right top to right bottom
//    lineCount = this->getContentSize().height - _tabSize.height - 9;
//    startPos = ccp(startPos.x+j,yPos-3);
//    for ( j = 0 ; j < lineCount ; j++ )
//    {
//        CCSprite * oneline = CCSprite::createWithTexture(angleTexture, CCRectMake(10,7,9,1));
//        oneline->setPosition(ccpAdd(startPos, ccp(0,-j)));
//        this->addChild(oneline);
//    }
//    
//    // bottom right 
//    CCSprite * rightBottomSprite = CCSprite::createWithTexture(angleTexture, CCRectMake(10,8,9,7));
//    rightBottomSprite->setPosition(ccp(startPos.x,startPos.y-j));
//    this->addChild(rightBottomSprite);
//    
//    // from right bottom to left bottom
//    lineCount = this->getContentSize().width-9;
//    startPos = ccp(startPos.x-5,startPos.y-j-1);
//    for ( j = 0 ; j < lineCount ; j++ )
//    {
//        CCSprite * oneline = CCSprite::createWithTexture(angleTexture, CCRectMake(10,8,1,9));
//        oneline->setPosition(ccpAdd(startPos, ccp(-j,0)));
//        this->addChild(oneline);
//    }
//    
//    // left bottom 
//    CCSprite * leftBottomSprite = CCSprite::createWithTexture(angleTexture, CCRectMake(0,8,9,7));
//    leftBottomSprite->setPosition(ccp(0,rightBottomSprite->getPosition().y));
//    this->addChild(leftBottomSprite);
//    
//    // from left bottom to left top
//    lineCount = this->getContentSize().height - _tabSize.height-9;
//    startPos = ccpAdd(ccp(0,0),ccp(0,leftBottomSprite->getPosition().y));
//    for ( j = 0 ; j < lineCount ; j++ )
//    {
//        CCSprite * oneline = CCSprite::createWithTexture(angleTexture, CCRectMake(0,7,9,1));
//        oneline->setPosition(ccpAdd(startPos, ccp(0,j)));
//        this->addChild(oneline);
//    }
}

void CCTabView::onEnter()
{
    // to do something here
    this->initTabData();
    
    CCLayer::onEnter();
}

void CCTabView::onExit()
{
    //CCTextureCache::sharedTextureCache()->removeTextureForKey(TAB_NORMAL);
    //CCTextureCache::sharedTextureCache()->removeTextureForKey(TAB_ACTIVE);
    //CCTextureCache::sharedTextureCache()->removeTextureForKey(TAB_LINE);
    //CCTextureCache::sharedTextureCache()->removeTextureForKey(TAB_EDGE);
    
    CCLayer::onExit();
}


///////Menu - Events
//void CCTabView::registerWithTouchDispatcher()
//{
//	//CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuTouchPriority-1, false);
//}
//
//bool CCTabView::ccTouchBegan(CCTouch* touch, CCEvent* event)
//{
//
//	//CCPoint touchLocation = touch->locationInView();
//	
//	return true;
//}
//
//void CCTabView::ccTouchEnded(CCTouch *touch, CCEvent* event)
//{
//	
//}
//
//void CCTabView::ccTouchCancelled(CCTouch *touch, CCEvent* event)
//{
//	
//}
//
//void CCTabView::ccTouchMoved(CCTouch* touch, CCEvent* event)
//{
//	
//}
