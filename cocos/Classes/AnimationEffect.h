#pragma once
#include"cocos2d.h"
class AnimationEffect
	:public cocos2d::Sprite
{
public:
	static AnimationEffect* create(int startNum, int num, const std::string& format, float delayPerUnit, int loops);
	virtual bool init(int startNum, int num, const std::string& format, float delayPerUnit, int loops);
};