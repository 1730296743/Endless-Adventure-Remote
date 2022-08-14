#ifndef __LOGO_LAYER_H__
#define __LOGO_LAYER_H__

#include "cocos2d.h"
USING_NS_CC;

class LogoLayer : public Layer
{
public:	
	bool touchBegan(Touch*touch, Event*event, Sprite* s, RepeatForever* rfMouse);
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(LogoLayer);
};

#endif