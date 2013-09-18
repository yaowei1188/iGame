//
//  GlobalData.cpp
//  mengdou
//
//  Created by ivan on 6/3/13.
//
//

#include "GlobalData.h"
#include "StringExt.h"

#define QUERY_CATEGORY_FRACTION "1"
#define QUERY_CATEGORY_CARDINFO "2"
#define QUERY_CATEGORY_CARDBYGROUP "3"
#define QUERY_CARD_PROFILE_BY_NAME "4"
#define QUERY_CARD_PROFILE_ALL "5"

static CCDictionary *dictLanguage;
static CCArray *arrayTasks;
static CCArray *arrayCards;
static CCArray *arrayCardProfile;
static CCDictionary* userinfo;
static CCArray* arrayFraction;
static CCDictionary* dictCard;
static CCArray *arrayEnemyFormation;

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

    if (strcmp(myPara, QUERY_CATEGORY_FRACTION)==0) {
        CCDictionary *dict = CCDictionary::create();
        for(int i = 0 ; i < n_column; i ++ )
        {
            dict->setObject(CCString::create(column_value[i]), column_name[i]);
        }
        arrayFraction->addObject(dict);
    } else if(strcmp(myPara, QUERY_CATEGORY_CARDINFO)==0) {
        dictCard = CCDictionary::create();
        for(int i = 0 ; i < n_column; i ++ )
        {
            dictCard->setObject(CCString::create(column_value[i]), column_name[i]);
        }
	} else if(strcmp(myPara, QUERY_CATEGORY_CARDBYGROUP)==0) {
		dictCard = CCDictionary::create();
		for(int i = 0 ; i < n_column; i ++ )
		{
			dictCard->setObject(CCString::create(column_value[i]), column_name[i]);
		}
		arrayCardProfile->addObject(dictCard);
	} else if(strcmp(myPara, QUERY_CARD_PROFILE_BY_NAME)==0) {
		dictCard = CCDictionary::create();
		for(int i = 0 ; i < n_column; i ++ )
		{
			dictCard->setObject(CCString::create(column_value[i]), column_name[i]);
		}
	} else if(strcmp(myPara, QUERY_CARD_PROFILE_ALL)==0) {
		dictCard = CCDictionary::create();
		for(int i = 0 ; i < n_column; i ++ )
		{
			dictCard->setObject(CCString::create(column_value[i]), column_name[i]);
		}
		arrayCards->addObject(dictCard);
	}

    return 0;
}

CCDictionary* GlobalData::getCardInfoById(std::string cardId)
{
    if (dictCard==NULL) {
        dictCard = CCDictionary::create();
    }

    sqlite3 *pDB = NULL;
    char* errMsg = NULL;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	std::string dbPath = getWritablePath();
#else
	std::string dbPath = CCFileUtils::sharedFileUtils()->fullPathForFilename("card.s3db");
#endif
    int result = sqlite3_open_v2(dbPath.c_str(),&pDB,SQLITE_OPEN_READONLY, NULL);
    if (result!=SQLITE_OK) {
        return NULL;
    }

    std::string szSql = "select * from game_role where roleid = ";

    const char *argc = QUERY_CATEGORY_CARDINFO;
    result = sqlite3_exec(pDB,szSql.c_str(), sqliteExecCallBack, (void *)argc, &errMsg);
    if (result != SQLITE_OK) {
        return NULL;
    }

    return dictCard;
}

CCArray* GlobalData::getFraction(std::string name)
{
    if (arrayFraction!=NULL) {
        return arrayFraction;
    }

    arrayFraction = CCArray::create();
    
    sqlite3 *pDB = NULL;
    char* errMsg = NULL;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	std::string dbPath = getWritablePath();
#else
	std::string dbPath = CCFileUtils::sharedFileUtils()->fullPathForFilename("card.s3db");
#endif
    int result = sqlite3_open_v2(dbPath.c_str(),&pDB,SQLITE_OPEN_READWRITE, NULL);
    if (result!=SQLITE_OK) {
        return NULL;
    }

    std::string szSql = "select * from game_group";

    const char *argc = QUERY_CATEGORY_FRACTION;
    result = sqlite3_exec(pDB,szSql.c_str(), sqliteExecCallBack, (void *)argc, &errMsg);
    if (result != SQLITE_OK) {
        return NULL;
    }

    return arrayFraction;
}

CCDictionary* GlobalData::getCardProfileByName(std::string name)
{
	sqlite3 *pDB = NULL;
	char* errMsg = NULL;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	std::string dbPath = getWritablePath();
#else
	std::string dbPath = CCFileUtils::sharedFileUtils()->fullPathForFilename("card.s3db");
#endif
	int result = sqlite3_open_v2(dbPath.c_str(),&pDB,SQLITE_OPEN_READONLY, NULL);
	if (result!=SQLITE_OK) {
		return NULL;
	}

	std::string szSql = "select c.cardHeadImg,c.cardBodyImg,c.cardProfileImg,c.game_group_id,r.roleName,r.starGrade,r.beginGrade,r.blood,r.attack,r.defence,r.crit,r.dodge,r.roleDescription from card c left join game_role r on c.cardProfileImg = r.roleImageId where c.cardProfileImg = '";
	szSql.append(name);
	szSql.append("'");
	const char *argc = QUERY_CARD_PROFILE_BY_NAME;
	result = sqlite3_exec(pDB,szSql.c_str(), sqliteExecCallBack, (void *)argc, &errMsg);
	if (result != SQLITE_OK) {
		return NULL;
	}

	return dictCard;
}

CCArray* GlobalData::getAllCardProfile(CardQueryCriteria *query)
{
	arrayCards = CCArray::create();

	sqlite3 *pDB = NULL;
	char* errMsg = NULL;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	std::string dbPath = getWritablePath();
#else
	std::string dbPath = CCFileUtils::sharedFileUtils()->fullPathForFilename("card.s3db");
#endif
	int result = sqlite3_open_v2(dbPath.c_str(),&pDB,SQLITE_OPEN_READWRITE, NULL);
	if (result!=SQLITE_OK) {
		return NULL;
	}

	std::string szSql = "select c.cardHeadImg,c.cardBodyImg,c.cardProfileImg,c.game_group_id,r.roleName,r.starGrade,r.beginGrade,r.blood,r.attack,r.defence,r.crit,r.dodge,r.roleDescription from card c left join game_role r on c.cardProfileImg = r.roleImageId where r.starGrade is not null";
	if (query != NULL)
	{
		if (query->groupid >= 0)
		{

		}
		if (query->cardName.length()>0)
		{
			std::vector<std::string> slist = split(query->cardName,';');
			if (slist.size()<=1)
			{
				szSql.append(" AND c.cardProfileImg = '");
				szSql.append(slist[0]);
				szSql.append("'");
			} else {
				szSql.append(" AND c.cardProfileImg in (\'");
				std::string sresult = vectorToString(slist,"\',\'");
				szSql.append(sresult);
				szSql.append("\')");
			}
		}
	}

	const char *argc = QUERY_CARD_PROFILE_ALL;
	result = sqlite3_exec(pDB,szSql.c_str(), sqliteExecCallBack, (void *)argc, &errMsg);
	if (result != SQLITE_OK) {
		return NULL;
	}

	return arrayCards;
}

CCArray* GlobalData::getEnemyFormation(int round)
{
	if (arrayEnemyFormation==NULL) {
		arrayEnemyFormation = CCArray::createWithContentsOfFile("Formation.plist");
		arrayEnemyFormation->retain();
	}
	return arrayEnemyFormation;
}


CCArray* GlobalData::getCardProfile(int group)
{
	arrayCardProfile = CCArray::create();

	sqlite3 *pDB = NULL;
	char* errMsg = NULL;
	

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	std::string dbPath = getWritablePath();
#else
	std::string dbPath = CCFileUtils::sharedFileUtils()->fullPathForFilename("card.s3db");
#endif

	int result = sqlite3_open_v2(dbPath.c_str(),&pDB,SQLITE_OPEN_READONLY, NULL);
	if (result!=SQLITE_OK) {
		CCLOG("status=================:%d ",result);
		return arrayCardProfile;
	} else {
		CCLOG("status=================:%d ",result);
	}

	std::string szSql = "select * from card";
	if (group>=0)
	{
		szSql.append(" where game_group_id = ");
		szSql.append(IntToString(group));
	}

	const char *argc = QUERY_CATEGORY_CARDBYGROUP;
	result = sqlite3_exec(pDB,szSql.c_str(), sqliteExecCallBack, (void *)argc, &errMsg);
	if (result!=SQLITE_OK) {
		CCLOG("status=================:%d ",result);
		return arrayCardProfile;
	} else {
		CCLOG("status=================:%d ",result);
	}

	return arrayCardProfile;
}

std::string GlobalData::getWritablePath()
{
	string dbPath = CCFileUtils::sharedFileUtils()->getWritablePath();
	dbPath.append("card.db");

	if (!CCFileUtils::sharedFileUtils()->isFileExist(dbPath))
	{
		CCLog("create new db");
		unsigned long tmpSize;
		unsigned char* readData = CCFileUtils::sharedFileUtils()->getFileData("card.s3db", "rb", &tmpSize);
		FILE *fp = fopen(dbPath.c_str(), "wb");
		fwrite(readData, tmpSize, 1, fp);
		fclose(fp);
	} else {
		CCLog("db already exist!");
		unsigned long tmpSize;
		unsigned char* readData = CCFileUtils::sharedFileUtils()->getFileData("card.s3db", "rb", &tmpSize);
		FILE *fp = fopen(dbPath.c_str(), "wb");
		fwrite(readData, tmpSize, 1, fp);
		fclose(fp);
	}

	return dbPath;
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
