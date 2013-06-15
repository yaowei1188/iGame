//
//  EllipseActionInterval.h
//  cctest
//
//  Created by China Team on 4/9/13.
//
//

#ifndef __IGAME__EllipseActionInterval__
#define __IGAME__EllipseActionInterval__

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;

static inline float getEllipseX( float a, float c, float startAngle,float t )//返回X坐标  
{
	return a*cos(startAngle + 2*M_PI*t);
}
static inline float getEllipseY( float a, float c, float startAngle,float t )//返回Y坐标  
{
	return c*sin(startAngle + 2*M_PI*t);  
} 

typedef struct _lrEllipseConfig {  
	CCPoint centerPosition;
	float aLength;
	float cLength;
	float startAngle;
	float step;
} lrEllipseConfig; 

class EllipseActionInterval : public cocos2d::CCActionInterval {
public:
    ~EllipseActionInterval();
    EllipseActionInterval();

	bool initWithDuration(float t, const lrEllipseConfig& c);  
	virtual void update(float time);
	static EllipseActionInterval *actionWithDuration(float t, const lrEllipseConfig& c); 
    
protected:  
	lrEllipseConfig m_sConfig;  
	CCPoint m_startPosition;  
	CCPoint s_startPosition;  
    
};
#endif