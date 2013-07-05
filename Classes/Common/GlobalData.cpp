//
//  GlobalData.cpp
//  mengdou
//
//  Created by ivan on 6/3/13.
//
//

#include "GlobalData.h"

static CCDictionary *dictLanguage;
static CCArray *arrayTasks;
static CCArray *arrayCards;
static CCDictionary* userinfo;

CCString* GlobalData::getLocalString(std::string name)
{
    if (dictLanguage==NULL) {
        dictLanguage = CCDictionary::createWithContentsOfFile("chs.plist");
        dictLanguage->retain();
    }
    return (CCString*)dictLanguage->objectForKey(name);
}

CCDictionary* GlobalData::getTasks(std::string name)
{
    if (arrayTasks==NULL) {
        arrayTasks = CCArray::createWithContentsOfFile("Task1.plist");
		arrayTasks->retain();
    }
    return (CCDictionary*)arrayTasks->objectAtIndex(0);
};

CCArray* GlobalData::getAllCards(std::string name)
{
    if (arrayCards==NULL) {
        arrayCards = CCArray::createWithContentsOfFile("Card.plist");
		arrayCards->retain();
    }
    return arrayCards;
};

CCDictionary* GlobalData::getCardById(std::string cardId)
{
    if (arrayCards==NULL) {
        arrayCards = CCArray::createWithContentsOfFile("Card.plist");
		arrayCards->retain();
    }
    CCObject *obj = NULL;
    CCARRAY_FOREACH(arrayCards, obj)
    {
        CCDictionary *dict = (CCDictionary *)obj;
        CCString *strCardId = (CCString *)dict->objectForKey("CardId");
        if (cardId == strCardId->getCString()) {
            return dict;
        }
    }
    return NULL;
}

CCDictionary* GlobalData::getUserinfo()
{
	return userinfo;
}

void GlobalData::setUserinfo(CCDictionary* p_userInfo)
{
	userinfo = p_userInfo;
	userinfo->retain();
}
