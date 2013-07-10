//
//  SharpLabelTTF.h
//  cctest
//
//  Created by China Team on 4/9/13.
//
//

#ifndef __IGAME__SharpLabelTTF__
#define __IGAME__SharpLabelTTF__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"

using namespace cocos2d;
using namespace cocos2d::extension;

class SharpLabelTTF : public cocos2d::CCLabelTTF {

	CCPoint intendedPosition_;
	void fixPosition ();
public:
//	virtual void onEnter();
//	virtual void setPosition(CCPoint position);
	virtual void setString(const char * str);
//	virtual void setParent(CCNode * parent);
//	void setRotation(float rotation);
};

#endif /* defined(__cctest__SharpLabelTTF__) */
