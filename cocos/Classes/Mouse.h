#ifndef __LOGO_SelfCreate_H__//Ԥ���봦���ֹͷ�ļ�������
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