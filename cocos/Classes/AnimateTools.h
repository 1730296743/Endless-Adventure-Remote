#ifndef _AnimateTools_H_
#define _AnimateTools_H_
#include "cocos2d.h"
#include "ui/CocosGUI.h"
class AnimateTools{
public:
	// ��������ʼֵ������֡������;�ļ���;����
	static cocos2d::Animate* create(int startNum, int num, const std::string& format, float delayPerUnit, int loops);
	static cocos2d::Vector<cocos2d::SpriteFrame*> getAnimation(const char* format, int count);
	cocos2d::ui::LoadingBar* init();
};
#endif