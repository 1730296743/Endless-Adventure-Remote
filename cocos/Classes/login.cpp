#include "ui/CocosGUI.h"
#include"login.h"
using namespace cocos2d::ui;
#include"GameLayer.h"
#include"MenuLayer.h"
#include"SimpleAudioEngine.h"

using namespace cocos2d::ui;
using namespace CocosDenshion;
Scene* login::createScene()
{
	// �����ճ���
	Scene* scene = Scene::create();
	// ����logo��
	login* layer = login::create();
	// �Ѳ���ӵ�������
	scene->addChild(layer);
	return scene;
}
bool login::init()
{
	if (!Layer::init())
	{
		return false;
	}
	// ��ȡ��Ļ��С
	Size winSize = Director::getInstance()->getWinSize();

	// ����logo
	Sprite* spLogo = Sprite::create("loadpage11111.png");
	// ��ӵ���

	this->addChild(spLogo);

	spLogo->setScale(0.5, 0.5);
	spLogo->setPosition(winSize.width / 2, winSize.height / 2+100);


	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("shengl.wav", true);


	Button* exit = Button::create("next.png");
	this->addChild(exit);
	exit->setScale(0.3, 0.3);
	exit->setPosition(Vec2(Director::getInstance()->getWinSize().width/4, Director::getInstance()->getWinSize().height /4));
	exit->addTouchEventListener([](Ref* ref, Widget::TouchEventType type)
	{
		switch (type)
		{
		case cocos2d::ui::Widget::TouchEventType::BEGAN:
			CCLOG("BEGANNN");
			SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
			GameLayer::guanka = GameLayer::guanka + 1;
			Director::getInstance()->replaceScene(GameLayer::createScene());
			break;
		}
	});


	Button* exit1 = Button::create("return.png");
	this->addChild(exit1);
	exit1->setScale(0.3, 0.3);
	exit1->setPosition(Vec2(Director::getInstance()->getWinSize().width / 4+300, Director::getInstance()->getWinSize().height / 4));
	exit1->addTouchEventListener([](Ref* ref, Widget::TouchEventType type)
	{
		switch (type)
		{
		case cocos2d::ui::Widget::TouchEventType::BEGAN:
			CCLOG("BEGANNN");
			SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
			
			Director::getInstance()->replaceScene(MenuLayer::createScene());
			break;
		}
	});

	
	return true;
}
