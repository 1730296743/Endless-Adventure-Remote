#include"MenuLayer.h"
#include"BigLevelScroolView.h"
#include"SimpleAudioEngine.h"
#include"LogoLayer.h"
#include"GameLayer.h"
#include "ui/CocosGUI.h"
using namespace cocos2d::ui;
#include"login.h"
#include "Mouse.h"
#include "MainInterface.h"
using namespace CocosDenshion;
int x = 0;
int muslc = -1;

Scene* MenuLayer::createScene() {
	Scene* scene = Scene::create();
	MenuLayer* layer = MenuLayer::create();
	scene->addChild(layer);
	return scene;
}
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in MainInterfaceScene.cpp\n");
}

bool MenuLayer::init() {
	if (!Layer::init()) {
		return false;
	}

	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("musicNew/maps/scene_00_1_dream_of_adventurer.mp3", true);

	auto const visibleSize = Director::getInstance()->getVisibleSize();
	auto back = MenuItemImage::create(
		"images/dating1.png",
		"images/dating2.png",
		CC_CALLBACK_1(MenuLayer::BackMainInterface, this));

	if (back == nullptr ||
		back->getContentSize().width <= 0 ||
		back->getContentSize().height <= 0) {
		CC_SAFE_DELETE(back);
	}
	else {
		float const x = visibleSize.width / 2 - back->getContentSize().width / 2 + 190;
		float const y = visibleSize.height / 2 - back->getContentSize().height / 2 + 50;
		back->setPosition(Vec2(x, y));
		back->setScale(0.16f);
	}
	Menu* menu = Menu::create(back, NULL);
	this->addChild(menu,3);

	Size const winSize = Director::getInstance()->getWinSize();
	Sprite* spLogo3 = Sprite::create("resource/dynamicRes/newsingleboss/elite/img_bg02.png");
	spLogo3->setPosition(winSize.width / 2, winSize.height / 2);
	// Ìí¼Óµ½²ã
	this->addChild(spLogo3);

	BigLevelScroolView* view = BigLevelScroolView::create();
	view->setPosition(Vec2(0, 480 - (480 - 200) / 2));
	view->setContentSize(Size(320, 200));
	view->initLayer(Rect(0, 50, 800, 380), 320, 200, -20, true, 0.5f, menu_selector(MenuLayer::onClickCallBack), menu_selector(MenuLayer::onSelectCallBack), this);

	Button* bg[7] = {0};
	for (int i = 1; i <= 6; i++) {
		char filename[48];
		sprintf(filename, "resource/dynamicRes/treasure/img_xkx_fwbj_%d.png", i);
		bg[i] = Button::create(filename, filename);
		bg[i]->setOpacity(170);
		bg[i]->setTag(i - 1);
		view->addNode(bg[i]);
	}
	bg[1]->addTouchEventListener([this](Ref* ref, Widget::TouchEventType type) {
		this->onClickCallFunc(6, 5);
		});
	bg[2]->addTouchEventListener([this](Ref* ref, Widget::TouchEventType type) {
		this->onClickCallFunc(6, 4);
		});
	bg[3]->addTouchEventListener([this](Ref* ref, Widget::TouchEventType type) {
		this->onClickCallFunc(6, 3);
		});
	bg[4]->addTouchEventListener([this](Ref* ref, Widget::TouchEventType type) {
		this->onClickCallFunc(6, 1);
		});
	bg[5]->addTouchEventListener([this](Ref* ref, Widget::TouchEventType type) {
		this->onClickCallFunc(6, 2);
		});
	bg[6]->addTouchEventListener([this](Ref* ref, Widget::TouchEventType type) {
		this->onClickCallFunc(6, 0);
		});

	view->goToShowItem(0);
	this->addChild(view);

	Button* btnStartGame = Button::create("images/Music1.png", "images/Music2.png");
	this->addChild(btnStartGame);
	btnStartGame->setPosition(Vec2(winSize.width - 50, 50));
	btnStartGame->addTouchEventListener([](Ref* ref, Widget::TouchEventType type){
			switch (type){
			case cocos2d::ui::Widget::TouchEventType::BEGAN:
				muslc = muslc + 1;
				x = 1;
				if (muslc % 2 == 1)
					SimpleAudioEngine::sharedEngine()->playBackgroundMusic("musicNew/maps/scene_00_1_dream_of_adventurer.mp3", true);
				else
				{

					SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
				}

				break;
			}
		});
	Button* ren = Button::create("seshou.png");
	this->addChild(ren);
	ren->setPosition(Vec2(winSize.width - 200, 50));
	ren->addTouchEventListener([this](Ref* ref, Widget::TouchEventType type){
			switch (type)
			{
			case cocos2d::ui::Widget::TouchEventType::BEGAN:
				GameLayer::role = 0;
				break;
			}
		});

	Button* ren1 = Button::create("fasi.png");
	//ren1->setScale(0.3, 0.3);
	this->addChild(ren1);
	ren1->setPosition(Vec2(winSize.width - 290, 50));
	ren1->addTouchEventListener([this](Ref* ref, Widget::TouchEventType type)
		{
			switch (type)
			{
			case cocos2d::ui::Widget::TouchEventType::BEGAN:
				GameLayer::role = 1;
				cocos2d::log("ssss");
				break;
			}
		});


	return true;
}
void MenuLayer::onClickCallBack(Ref* ref) {

}
void MenuLayer::onSelectCallBack(Ref* ref) {

}
void MenuLayer::onClickCallFunc(int grade, int Level) {

	cocos2d::ui::Widget::TouchEventType::BEGAN;
	SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	GameLayer::s_iLv = Level;
	GameLayer::guanka = grade;
	Director::getInstance()->replaceScene(GameLayer::createScene());

}


void MenuLayer::BackMainInterface(Ref* pSender) {

	Director::getInstance()->replaceScene(MainInterface::createScene());
}