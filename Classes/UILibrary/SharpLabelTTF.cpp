//
//  SharpLabelTTF.cpp
//  cctest
//
//  Created by China Team on 4/9/13.
//
//

#include "SharpLabelTTF.h"

double roundf(double r)
{
	return (r > 0.0) ? floor(r + 0.5) : ceil(r - 0.5);
}

void SharpLabelTTF::fixPosition () {

	CCSize dim = this->getTexture()->getContentSize();

//	this->setPosition(intendedPosition_);
    this->setPosition(ccp(200, 200));

	if (this->getScaleX() < 0.3 || this->getScaleY() < 0.3) return;

	// compute world (= screen) coordinate of top left position of label  
	CCPoint worldSpaceTopleft = this->convertToWorldSpace(ccp(0,dim.height));

	// align origin on a pixel boundary on screen coordinates
	worldSpaceTopleft.x = roundf(worldSpaceTopleft.x * CC_CONTENT_SCALE_FACTOR()) / CC_CONTENT_SCALE_FACTOR();
	worldSpaceTopleft.y = roundf(worldSpaceTopleft.y * CC_CONTENT_SCALE_FACTOR()) / CC_CONTENT_SCALE_FACTOR();


	// transform back into node space
	CCPoint nodeSpaceTopleft = this->convertToNodeSpace(worldSpaceTopleft);

	// adjust position by the computed delta
	CCPoint delta = ccpSub(nodeSpaceTopleft, ccp(0,dim.height));
	CCPoint newPos = ccpAdd(this->getPosition(), delta);

	// finally set the position data
	this->setPosition(newPos);
}

// capture modification calls to adjust position
//void SharpLabelTTF::onEnter() 
//{
//	this->fixPosition();
//	CCLabelTTF::onEnter();
//}
//
//void SharpLabelTTF::setParent(CCNode * parent) 
//{
//	CCLabelTTF::setParent(parent);
//	this->fixPosition();
//}

void SharpLabelTTF::setString(const char * str)
{
	CCLabelTTF::setString(str);
	this->fixPosition();
}

//void SharpLabelTTF::setPosition(CCPoint position)
//{
//	intendedPosition_ = position;
////	this->fixPosition();
//}
//
//
//void SharpLabelTTF::setRotation(float rotation) {
//	CCLabelTTF::setRotation(rotation);
//	this->fixPosition();
//}
