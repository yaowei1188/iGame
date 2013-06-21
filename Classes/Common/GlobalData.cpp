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