//
//  StringExt.h
//  iGame
//
//  Created by China Team on 4/25/13.
//
//

#ifndef __iGame__StringExt__
#define __iGame__StringExt__

#include <iostream>

inline std::string trimLeft(const std::string& str) {
    std::string t = str;
    for (std::string::iterator i = t.begin(); i != t.end(); i++) {
        if (!isspace(*i)) {
            t.erase(t.begin(), i);
            break;
        }
    }
    return t;
}

inline std::string trimRight(const std::string& str) {
    if (str.begin() == str.end()) {
        return str;
    }
    
    std::string t = str;
    for (std::string::iterator i = t.end() - 1; i != t.begin(); i--) {
        if (!isspace(*i)) {
            t.erase(i + 1, t.end());
            break;
        }
    }
    return t;
}

inline std::string trim(const std::string& str) {
    std::string t = str;
    
    std::string::iterator i;
    for (i = t.begin(); i != t.end(); i++) {
        if (!isspace(*i)) {
            t.erase(t.begin(), i);
            break;
        }
    }
    
    if (i == t.end()) {
        return t;
    }
    
    for (i = t.end() - 1; i != t.begin(); i--) {
        if (!isspace(*i)) {
            t.erase(i + 1, t.end());
            break;
        }
    }
    
    return t;
}

#endif /* defined(__iGame__StringExt__) */
