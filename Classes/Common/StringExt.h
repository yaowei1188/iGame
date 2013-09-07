//
//  StringExt.h
//  iGame
//
//  Created by China Team on 4/25/13.
//
//

#ifndef __StringExt__
#define __StringExt__

#include <iostream>
#include <iterator>

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

//convert from wstring to UTF8 using self-coding-converting
inline void WStrToUTF8(std::string& dest, const wstring& src){
	dest.clear();
	for (size_t i = 0; i < src.size(); i++){
		wchar_t w = src[i];
		if (w <= 0x7f)
			dest.push_back((char)w);
		else if (w <= 0x7ff){
			dest.push_back(0xc0 | ((w >> 6)& 0x1f));
			dest.push_back(0x80| (w & 0x3f));
		}
		else if (w <= 0xffff){
			dest.push_back(0xe0 | ((w >> 12)& 0x0f));
			dest.push_back(0x80| ((w >> 6) & 0x3f));
			dest.push_back(0x80| (w & 0x3f));
		}
		else if (sizeof(wchar_t) > 2 && w <= 0x10ffff){
			dest.push_back(0xf0 | ((w >> 18)& 0x07)); // wchar_t 4-bytes situation
			dest.push_back(0x80| ((w >> 12) & 0x3f));
			dest.push_back(0x80| ((w >> 6) & 0x3f));
			dest.push_back(0x80| (w & 0x3f));
		}
		else
			dest.push_back('?');

	}
}

//simple warpper
inline std::string WStrToUTF8(const std::wstring& str){
	std::string result;
	WStrToUTF8(result, str);
	return result;
}

inline std::wstring StringToWString(const std::string &s)
{
	std::wstring wsTmp(s.begin(), s.end());

	return wsTmp;
}

inline std::string floatToString(float number)
{
	std::ostringstream buff;
	buff<<number;
	return buff.str();
}

inline std::string floatToPercent(float number)
{
	number = number * 100;
	std::string temp(floatToString(number));
	temp.append("%");
	return temp;
}

inline std::string IntToString (int number)
{
	std::ostringstream buff;
	buff<<number;
	return buff.str();
}

inline ccColor3B convertColor(const std::string &str)
{
	long color;
    char * pEnd;
    
    if(str.find("#")!=-1)
    {
        color =strtol(str.substr(1).c_str(), &pEnd,16);
    } else {
        color =strtol(str.c_str(), &pEnd,16);
    }
    
    int R = (color & 0xFF0000 )>>16;
    int G = (color & 0x00FF00 )>>8;
    int B =  color & 0x0000FF;
    return ccc3(R, G, B);
}

inline std::string secondsToString(int seconds)
{
    int time = seconds;
    int hour;
    int min;
    int sec;
    string result;

    hour=time/3600;
    time=time%3600;
    min=time/60;
    time=time%60;
    sec=time;
    if (hour < 10) {
        result.append("0");
    }
    result.append(IntToString(hour) + ":");
    if (min < 10) {
        result.append("0");
    }
    result.append(IntToString(min) + ":");
    if (sec < 10) {
        result.append("0");
    }
    result.append(IntToString(sec));
    return result;
}

inline std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}

inline std::vector<std::string> split(const std::string &s, char delim) {
	std::vector<std::string> elems;
	split(s, delim, elems);
	return elems;
}

inline std::string vectorToString(std::vector<std::string> &vec, std::string delim) {
	std::stringstream  ss;

	//std::ostream_iterator<std::string> out_file_iterator ( out_file, delim );

	std::copy(vec.begin(), vec.end()-1,ostream_iterator<std::string>(ss, delim.c_str()));

	ss << vec.back();

	return ss.str();
}

#endif /* defined(__StringExt__) */
