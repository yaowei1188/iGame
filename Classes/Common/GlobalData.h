//
//  GlobalData.h
//  mengdou
//
//  Created by ivan on 6/3/13.
//
//

#ifndef __mengdou__GlobalData__
#define __mengdou__GlobalData__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"

//#include <sqlite3.h>
#include "sqlite3.h"

using namespace std;
using namespace cocos2d;
using namespace cocos2d::extension;

class CardQueryCriteria
{
public:
	std::string cardName;
	int groupid;
};

class GlobalData
{
public:
    static CCString* getLocalString(std::string name);
    
    static CCDictionary* getTasks(std::string name);

    static CCArray* getFraction(std::string name);

    //static CCArray* getAllCards(std::string name);

    //static CCDictionary* getCardById(std::string cardId);
    static CCDictionary* getCardInfoById(std::string cardId);

	static CCDictionary* getUserinfo();
	static void setUserinfo(CCDictionary* p_userInfo);

	static CCArray* getAllCardProfile(CardQueryCriteria *query = NULL);
	static CCDictionary* getCardProfileByName(std::string name);
	static CCArray* getCardProfile(int group);

	static CCArray* getEnemyFormation(int round);

	//static float factor;

private:
    static int sqliteExecCallBack( void * para, int n_column, char ** column_value, char ** column_name );
	static std::string getWritablePath();
};

#endif /* defined(__mengdou__GlobalData__) */
