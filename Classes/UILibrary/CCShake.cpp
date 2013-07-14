//
//  CCShake.cpp
//  Mengdou
//
//  Created by China Team on 4/9/13.
//
//

#include "CCShake.h"

// not really useful, but I like clean default constructors
CCShake::CCShake() : _strength_x(0), _strength_y(0)
{
}

CCShake* CCShake::create( float d, float strength )
{
	// call other construction method with twice the same strength
	return create( d, strength, strength );
}

CCShake* CCShake::create(float duration, float strength_x, float strength_y)
{
	CCShake *p_action = new CCShake();
	p_action->initWithDuration(duration, strength_x, strength_y);
	p_action->autorelease();

	return p_action;
}

bool CCShake::initWithDuration(float duration, float strength_x, float strength_y)
{
	if (CCActionInterval::initWithDuration(duration))
	{
		_strength_x = strength_x;
		_strength_y = strength_y;
		_havePosition = false;
		return true;
	}

	return false;
}

// Helper function. I included it here so that you can compile the whole file
// it returns a random value between min and max included
float fgRangeRand( float min, float max )
{
	float rnd = ((float)rand()/(float)RAND_MAX);
	return rnd*(max-min)+min;
}

void CCShake::update(float time)
{
	float randx = fgRangeRand( -_strength_x, _strength_x );
	float randy = fgRangeRand( -_strength_y, _strength_y );
	if (!_havePosition)
	{
		_havePosition = true;
		_original = m_pTarget->getPosition();
	}

	// move the target to a shaked position
	m_pTarget->setPosition( ccpAdd(_original,ccp( randx, randy)));
}

//void CCShake::startWithTarget(CCNode *pTarget)
//{
//	CCActionInterval::startWithTarget( pTarget );
//
//	// save the initial position
//	_initial_x = pTarget->getPosition().x;
//	_initial_y = pTarget->getPosition().y;
//}

void CCShake::stop(void)
{
	// Action is done, reset clip position
	m_pTarget->setPosition( _original );

	CCActionInterval::stop();
}
