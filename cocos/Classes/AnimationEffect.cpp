#include"AnimationEffect.h"
#include"AnimateTools.h"
USING_NS_CC;
AnimationEffect* AnimationEffect::create(int startNum, int num, const std::string& format, float delayPerUnit, int loops){
	AnimationEffect* effect = new AnimationEffect;
	if (effect&&effect->init(startNum,num,format, delayPerUnit,loops)){
		effect->autorelease();
	}else{
		delete effect;
		effect = nullptr;
	}
	return effect;
}
bool AnimationEffect::init(int startNum, int num, const std::string& format, float delayPerUnit, int loops){
	if (!Sprite::init()){
		return false;
	}
	Animate* animate = AnimateTools::create(startNum, num, format, delayPerUnit, loops);
	Sequence* seq = Sequence::create(animate, CallFunc::create([&]() {
		this->removeFromParent(); 
	}),nullptr);
	this->setLocalZOrder(2);
	this->runAction(seq);
	return true;
}