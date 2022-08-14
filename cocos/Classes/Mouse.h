#ifndef __LOGO_SelfCreate_H__//预编译处理防止头文件被引用
#define __LOGO_SelfCreate_H__
#include "cocos2d.h"
#include "MainInterface.h"
USING_NS_CC;

class SecondScene :public Layer
{
public:

	Vector <Sprite *>vecBullet;
	static cocos2d::Scene * CreateScene();

	CREATE_FUNC(SecondScene);

	
	bool touchBegan2(Touch*touch, Event*event);

	virtual bool init();

	void EnterFirstScene(Ref* ref);	

};
#endif