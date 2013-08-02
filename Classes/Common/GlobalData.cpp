//
//  GlobalData.cpp
//  mengdou
//
//  Created by ivan on 6/3/13.
//
//

#include "GlobalData.h"

#define QUERY_CATEGORY_FRACTION "1"
#define QUERY_CATEGORY_CARDINFO "2"

static CCDictionary *dictLanguage;
static CCArray *arrayTasks;
static CCArray *arrayCards;
static CCDictionary* userinfo;
static CCArray* arrayFraction;
static CCDictionary* dictCard;

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

//CCDictionary* GlobalData::getFraction(std::string name)
//{
//    if (arrayTasks==NULL) {
//        
//    }
//    return (CCDictionary*)arrayTasks->objectAtIndex(0);
//};

int GlobalData::sqliteExecCallBack( void * para, int n_column, char ** column_value, char ** column_name )
{
    const char *myPara = (const char *)para;
    printf("para:%s",myPara);
    if (strcmp(myPara, QUERY_CATEGORY_FRACTION)) {
        CCDictionary *dict = CCDictionary::create();
        for(int i = 0 ; i < n_column; i ++ )
        {
            //        str:string name = column_name[i];
            //        std::string value = column_value[i];
            dict->setObject(CCString::create(column_value[i]), column_name[i]);
            //        printf( "瀛楁鍚�%s 瀛楁鍊�%s",  column_name[i], column_value[i] );
        }
        arrayFraction->addObject(dict);
    } else if(strcmp(myPara, QUERY_CATEGORY_CARDINFO)) {
        dictCard = CCDictionary::create();
        for(int i = 0 ; i < n_column; i ++ )
        {
            dictCard->setObject(CCString::create(column_value[i]), column_name[i]);
        }
    }

    return 0;
}

CCDictionary* GlobalData::getCardInfoById(std::string cardId)
{
    if (dictCard==NULL) {
        dictCard = CCDictionary::create();
    }

//    sqlite3 *pDB = NULL;
//    char* errMsg = NULL;
//    std::string dbPath = CCFileUtils::sharedFileUtils()->fullPathForFilename("card.s3db");
//    int result = sqlite3_open_v2(dbPath.c_str(),&pDB,SQLITE_OPEN_READONLY, NULL);
//    if (result!=SQLITE_OK) {
//        return NULL;
//    }
//
//    std::string szSql = "select * from game_role where roleid = ";
//
//    const char *argc = QUERY_CATEGORY_CARDINFO;
//    result = sqlite3_exec(pDB,szSql.c_str(), sqliteExecCallBack, (void *)argc, &errMsg);
//    if (result != SQLITE_OK) {
//        return NULL;
//    }

    return dictCard;
}

CCArray* GlobalData::getFraction(std::string name)
{
    if (arrayFraction!=NULL) {
        return arrayFraction;
    }

    arrayFraction = CCArray::create();
    
//    sqlite3 *pDB = NULL;
//    char* errMsg = NULL;
//    std::string dbPath = CCFileUtils::sharedFileUtils()->fullPathForFilename("card.s3db");
//    int result = sqlite3_open_v2(dbPath.c_str(),&pDB,SQLITE_OPEN_READWRITE, NULL);
//    if (result!=SQLITE_OK) {
//        return NULL;
//    }
//
//    std::string szSql = "select * from game_group";
//
//    const char *argc = QUERY_CATEGORY_FRACTION;
//    result = sqlite3_exec(pDB,szSql.c_str(), sqliteExecCallBack, (void *)argc, &errMsg);
//    if (result != SQLITE_OK) {
//        return NULL;
//    }

    return arrayFraction;
}

CCArray* GlobalData::getAllCards(std::string name)
{
    if (arrayCards==NULL) {
        arrayCards = CCArray::createWithContentsOfFile("Card1.plist");
		arrayCards->retain();
    }
    return arrayCards;
};

CCDictionary* GlobalData::getCardById(std::string cardId)
{
    if (arrayCards==NULL) {
        arrayCards = CCArray::createWithContentsOfFile("Card1.plist");
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
