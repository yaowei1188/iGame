//
//  MainLayerBase.cpp
//  iGame
//
//  Created by yao on 13-4-20.
//
//

#include "MainLayerBase.h"

MainLayerBase::MainLayerBase()
{
    this->loading = NULL;
}

void MainLayerBase::OpenNewScene(const char *pCCBFileName)
{
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    ccbReader->autorelease();
    
    CCScene *pScene = ccbReader->createSceneWithNodeGraphFromFile(pCCBFileName);
    CCDirector::sharedDirector()->replaceScene(pScene);
}

void MainLayerBase::PushScene(const char *pCCBFileName)
{
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    ccbReader->autorelease();
    
    CCScene *pScene = ccbReader->createSceneWithNodeGraphFromFile(pCCBFileName);
    CCDirector::sharedDirector()->pushScene(CCTransitionMoveInR::create(0.3, pScene));
}

CCNode* MainLayerBase::GetLayer(const char *pCCBFileName)
{
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    ccbReader->autorelease();
    
    return ccbReader->readNodeGraphFromFile(pCCBFileName);
}

//label 描边
CCRenderTexture* MainLayerBase::createStroke(cocos2d::CCLabelTTF *label, float size, cocos2d::ccColor3B color)
{
    float x=label->getTexture()->getContentSize().width+size*2;
    float y=label->getTexture()->getContentSize().height+size*2;
    CCRenderTexture *rt=CCRenderTexture::create(x, y);
    CCPoint originalPos=label->getPosition();
    ccColor3B originalColor=label->getColor();
    label->setColor(color);
    ccBlendFunc originalBlend=label->getBlendFunc();
    //label->setBlendFunc((ccBlendFunc){GL_SRC_ALPHA,GL_ONE});
    CCPoint center=ccp(x/2+size, y/2+size);
    rt->begin();
    for (int i=0; i<360; i+=15) {
        float _x=center.x+sin(CC_DEGREES_TO_RADIANS(i))*size;
        float _y=center.y+cos(CC_DEGREES_TO_RADIANS(i))*size;
        
        label->setPosition(ccp(_x, _y));
        label->visit();
        
    }
    rt->end();
    label->setPosition(originalPos);
    label->setColor(originalColor);
    label->setBlendFunc(originalBlend);
    float rtX=originalPos.x-size;
    float rtY=originalPos.y-size;
    
    rt->setPosition(ccp(rtX, rtY));
    
    return rt;
}

void MainLayerBase::ShowLoadingIndicator(const char *pCCBFileName)
{
    if (loading==NULL) {
        loading = LoadingScene::create();
        this->addChild(loading);
    }
}

void MainLayerBase::HideLoadingIndicator()
{
    if (loading==NULL) {
        return;
    }
    
    this->loading->removeFromParentAndCleanup(true);
    this->loading = NULL;
}

bool MainLayerBase::ValidateResponseData(CCNode* pSender,void *data)
{
	this->HideLoadingIndicator();

	CCHttpResponse *response =  (CCHttpResponse*)data;
	if(response == NULL)
	{
		return false;
	}

	int statusCode = response->getResponseCode();
	char statusString[64] = {};
	CCLOG(statusString, "HTTP Status Code: %d, tag = %s", statusCode, response->getHttpRequest()->getTag());

	if (!response->isSucceed())   
	{  
		CCLog("error buffer: %s", response->getErrorBuffer());
		CCMessageBox("ERROR", response->getErrorBuffer());
		return false;
	}

	return true;
}

bool MainLayerBase::ValidateResponseData(CCHttpClient* client, CCHttpResponse* response)
{
	this->HideLoadingIndicator();

	if(response == NULL)
	{
		return false;
	}

	int statusCode = response->getResponseCode();
	char strStatusCode[50];
	sprintf(strStatusCode,"ERROR:HTTP Status Code: %d",statusCode);
	CCLOG("HTTP Status Code: %d, tag = %s", statusCode, response->getHttpRequest()->getTag());

	if (!response->isSucceed())
	{
		CCMessageBox(strStatusCode, "error");
		return false;
	}

	return true;
}

std::string MainLayerBase::CompleteUrl(std::string function_url)
{
    std::string url(API_URL);
    url.append(function_url);
    return url;
}

std::string MainLayerBase::getLocalString(std::string name)
{
    CCDictionary *dict = CCDictionary::createWithContentsOfFile("chs.plist");
    return ((CCString*)dict->objectForKey(name))->getCString();
}

std::string MainLayerBase::showUTF8String(std::string name)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
std::string text = WStrToUTF8(StringToWString(name));
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
std::string text = name;
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	std::string text = WStrToUTF8(StringToWString(name));
#endif
	return text;
}
