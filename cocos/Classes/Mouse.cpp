#include"Mouse.h"
#include "LogoLayer.h"
#include "ui/CocosGUI.h"
using namespace cocos2d::ui;
#include "MenuLayer.h"
USING_NS_CC;
bool SecondScene::touchBegan2(Touch*touch, Event*event)//������ʼ������bool����
{

	
	CallFunc* callfunc = CallFunc::create([](){
		//log("change secne");
		Director::getInstance()->replaceScene(MainInterface::createScene());
		// �л���������
	});
	// ��ʱ�������ն�����ʲô����ִ�У��β�Ϊʱ�䡣
	DelayTime* dt = DelayTime::create(0.5f);
	// ���ж�������˳��ִ��
	Sequence* seq1 = Sequence::create(dt, callfunc, nullptr);
	// ִ�ж���
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


	// ��Ӽ����¼����βΣ��ص�����	
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
			// �л���������
			break;
		case cocos2d::ui::Widget::TouchEventType::CANCELED:
			log("CANCELED");
			break;
		default:
			break;
		}
	});
	
	
	
		DelayTime* dt = DelayTime::create(2.5f);
		// ���ж�������˳��ִ��
		Sequence* seq1 = Sequence::create(dt, nullptr, nullptr);

		auto dispatcher = Director::getInstance()->getEventDispatcher();
		auto listener = EventListenerTouchOneByOne::create();
		listener->onTouchBegan = CC_CALLBACK_2(SecondScene::touchBegan2, this);
		listener->setSwallowTouches(true);//�����´��ݴ���
		dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
		//btnStartGame->setPosition(vec);
	

		
	CallFunc* callfunc = CallFunc::create([](){
		Director::getInstance()->replaceScene(MainInterface::createScene());
		// �л���������
	});
	// ��ʱ�������ն�����ʲô����ִ�У��β�Ϊʱ�䡣
	DelayTime* dt11 = DelayTime::create(2.5f);
	// ���ж�������˳��ִ��
	Sequence* seq11 = Sequence::create(dt11, callfunc, nullptr);
	// ִ�ж���
	this->runAction(seq11);

	
	return true;

}