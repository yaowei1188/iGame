//
//  GlobalData.cpp
//  mengdou
//
//  Created by ivan on 6/3/13.
//
//

#include "GlobalData.h"

static CCDictionary *dictLanguage;

CCString* GlobalData::getLocalString(std::string name)
{
    if (dictLanguage==NULL) {
        dictLanguage = CCDictionary::createWithContentsOfFile("chs.plist");
    }
    return (CCString*)dictLanguage->objectForKey(name);
}