#ifndef _AnimateTools_H_
#define _AnimateTools_H_
#include "cocos2d.h"
#include "ui/CocosGUI.h"
class AnimateTools{
public:
	// 参数：起始值；精灵帧的数量;文件名;次数
	static cocos2d::Animate* create(int startNum, int num, const std::string& format, float delayPerUnit, int loops);
	static cocos2d::Vector<cocos2d::SpriteFrame*> getAnimation(const char* format, int count);
	cocos2d::ui::LoadingBar* init();
};
#endif