//
//  EllipseActionInterval.cpp
//  cctest
//
//  Created by China Team on 4/9/13.
//
//

#include "EllipseActionInterval.h"



EllipseActionInterval::EllipseActionInterval()
{

}

EllipseActionInterval::~EllipseActionInterval()
{
    
}

EllipseActionInterval* EllipseActionInterval::actionWithDuration(float t, const lrEllipseConfig& c)
{  
	EllipseActionInterval *pTuoyuanBy = new EllipseActionInterval();  
	pTuoyuanBy->initWithDuration(t, c);  
	pTuoyuanBy->autorelease();  

	return pTuoyuanBy;  
}  

bool EllipseActionInterval::initWithDuration(float t, const lrEllipseConfig& c)  
{  
	if (CCActionInterval::initWithDuration(t))  
	{  
		m_sConfig = c;  
		return true;  
	}  

	return false;  
}  
void EllipseActionInterval::update(float time) 
{  
	if (m_pTarget)     
	{  
		float a = m_sConfig.aLength;   
		float c = m_sConfig.cLength;
		float x = getEllipseX(a, c, m_sConfig.startAngle, time/3 * m_sConfig.step);
		float y = getEllipseY(a, c, m_sConfig.startAngle, time/3 * m_sConfig.step);  
		CCPoint point = ccpAdd(m_sConfig.centerPosition, ccp(x, y));
		m_pTarget->setPosition(point); 
	}  
} 
