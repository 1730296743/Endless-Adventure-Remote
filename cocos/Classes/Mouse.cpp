#include"Mouse.h"
#include "LogoLayer.h"
#include "ui/CocosGUI.h"
using namespace cocos2d::ui;
#include "MenuLayer.h"
USING_NS_CC;
bool SecondScene::touchBegan2(Touch*touch, Event*event)//触摸开始，返回bool类型
{

	
	CallFunc* callfunc = CallFunc::create([](){
		//log("change secne");
		Director::getInstance()->replaceScene(MainInterface::createScene());
		// 切换场景代码
	});
	// 延时动作：空动作，什么都不执行，形参为时间。
	DelayTime* dt = DelayTime::create(0.5f);
	// 序列动作。按顺序执行
	Sequence* seq1 = Sequence::create(dt, callfunc, nullptr);
	// 执行动作
	this->runAction(seq1);
	
	return true;
}
cocos2d::Scene * SecondScene::CreateScene()
{
	Scene * scene = Scene::create();
	SecondScene * layer = SecondScene::create();
	scene->addChild(layer);
	
	return scene;
}
bool SecondScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size winsize = Director::getInstance()->getWinSize();


	//Button* 
	Button* btnStartGame = Button::create("llm/Endless_ Adventure_logo.png", "llm/Endless_ Adventure_logo.png");
	this->addChild(btnStartGame);
	btnStartGame->setPosition(Vec2(winsize.width / 2, winsize.height / 2));


	// 添加监听事件。形参：回调函数	
	btnStartGame->addTouchEventListener([](Ref* ref, Widget::TouchEventType type)
	{
		switch (type)
		{
		case cocos2d::ui::Widget::TouchEventType::BEGAN:
			CCLOG("BEGANNN");
			Director::getInstance()->replaceScene(MainInterface::createScene());
			break;
		case cocos2d::ui::Widget::TouchEventType::MOVED:
			log("MOVED");
			break;
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			log("ENDED");
			// 切换场景代码
			break;
		case cocos2d::ui::Widget::TouchEventType::CANCELED:
			log("CANCELED");
			break;
		default:
			break;
		}
	});
	
	
	
		DelayTime* dt = DelayTime::create(2.5f);
		// 序列动作。按顺序执行
		Sequence* seq1 = Sequence::create(dt, nullptr, nullptr);

		auto dispatcher = Director::getInstance()->getEventDispatcher();
		auto listener = EventListenerTouchOneByOne::create();
		listener->onTouchBegan = CC_CALLBACK_2(SecondScene::touchBegan2, this);
		listener->setSwallowTouches(true);//不向下传递触摸
		dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
		//btnStartGame->setPosition(vec);
	

		
	CallFunc* callfunc = CallFunc::create([](){
		Director::getInstance()->replaceScene(MainInterface::createScene());
		// 切换场景代码
	});
	// 延时动作：空动作，什么都不执行，形参为时间。
	DelayTime* dt11 = DelayTime::create(2.5f);
	// 序列动作。按顺序执行
	Sequence* seq11 = Sequence::create(dt11, callfunc, nullptr);
	// 执行动作
	this->runAction(seq11);

	
	return true;

}