#include"AnimateTools.h"
cocos2d::Animate* AnimateTools::create(int startNum, int num, const std::string& format, float delayPerUnit, int loops)
{
	cocos2d::Animate* animate = nullptr;
	// ´´½¨¶¯»­
	cocos2d::Animation* animation =
		cocos2d::Animation::create();
	for (int i = startNum; i < startNum + num; i++)
	{
		char path[256] = { 0 };
		sprintf(path, format.c_str(), i);
		animation->addSpriteFrameWithFileName(path);
	}
	animation->setDelayPerUnit(delayPerUnit);
	animation->setLoops(loops);
	animate = cocos2d::Animate::create(animation);
	return animate;
}
cocos2d::Vector<cocos2d::SpriteFrame*> AnimateTools::getAnimation(const char* format, int count) {

	cocos2d::SpriteFrameCache* const spriteFrameCach = cocos2d::SpriteFrameCache::getInstance();

	cocos2d::Vector<cocos2d::SpriteFrame*> spriteFrames;
	char str[100] = {};
	for (size_t i = 0; i < count; i++)
	{
		sprintf(str, format, i);
		spriteFrames.pushBack(spriteFrameCach->getSpriteFrameByName(str));
	}
	return spriteFrames;
}

cocos2d::ui::LoadingBar* AnimateTools::init() {
	cocos2d::ui::LoadingBar* load = cocos2d::ui::LoadingBar::create("progressBar/progressBar3.png");
	load->setDirection(cocos2d::ui::LoadingBar::Direction::LEFT);
	static cocos2d::SpriteFrameCache* const spriteCache = cocos2d::SpriteFrameCache::getInstance();
	spriteCache->addSpriteFramesWithFile("Plist/MageSecond.plist");
	load->setPercent(5);
	spriteCache->addSpriteFramesWithFile("Plist/MageSecond-0.plist");
	load->setPercent(10);
	spriteCache->addSpriteFramesWithFile("Plist/MageSecond-1.plist");
	load->setPercent(15);
	spriteCache->addSpriteFramesWithFile("Plist/MageSecond-2.plist");
	load->setPercent(20);
	spriteCache->addSpriteFramesWithFile("Plist/MageSecond-3.plist");
	load->setPercent(25);
	spriteCache->addSpriteFramesWithFile("Plist/MageSecond-4.plist");
	load->setPercent(30);
	spriteCache->addSpriteFramesWithFile("Plist/MageSecond-5.plist");
	load->setPercent(40);
	spriteCache->addSpriteFramesWithFile("Plist/MageSecond-6.plist");
	load->setPercent(45);
	spriteCache->addSpriteFramesWithFile("Plist/MageSecond-7.plist");
	load->setPercent(50);
	spriteCache->addSpriteFramesWithFile("Plist/MageSecond-8.plist");
	load->setPercent(55);
	spriteCache->addSpriteFramesWithFile("Plist/MageSecond-9.plist");
	load->setPercent(60);
	spriteCache->addSpriteFramesWithFile("Plist/MageSecond-10.plist");
	load->setPercent(80);
	spriteCache->addSpriteFramesWithFile("Plist/MageSecond-11.plist");
	load->setPercent(90);
	spriteCache->addSpriteFramesWithFile("Plist/MageSecond-12.plist");
	load->setPercent(100);
	return load;
}