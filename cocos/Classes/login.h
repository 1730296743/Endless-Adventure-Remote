#ifndef __LOGIN_H__
#define __LOGIN_H__

#include "cocos2d.h"
USING_NS_CC;

class login : public Layer
{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(login);
};

#endif