#include "GameLayer.h"
#include "Manager.h"
#include"AnimateTools.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
#include "Enemy.h"
#include"login.h"
#include"MenuLayer.h"
#include"BigLevelScroolView.h"
#include"SimpleAudioEngine.h"
#include "LogoLayer.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include"HeroBullet.h"
using namespace cocos2d::ui;
#include "Mouse.h"
#include"ftlist.h"
USING_NS_CC;
using namespace cocostudio::timeline;
using namespace CocosDenshion;


int GameLayer::s_iLv = 0;
int GameLayer::role = 0;
int  GameLayer::jinengxuanzhe = 0;
int GameLayer::guanka = 1;


void GameLayer::update1(float dt) {
	struct timeval now;
	gettimeofday(&now, NULL);
	int nowTime = now.tv_sec;   //��ȡ���ö�ʱ�����ʱ��
	if ((nowTime - oldTime) == 2)
		//�жϵ��ö�ʱ�����ʱ�䣨���ܵ����˼��ζ�ʱ�����Ƿ�����ö�ʱ��ǰ��ʱ�����1s
	{
		jieng1 = false;
		this->num++;
		this->oldTime = nowTime;   //�����趨���ö�ʱ��ǰ��ʱ��
	}
}

void GameLayer::update2(float dt) {
	struct timeval now;
	gettimeofday(&now, NULL);
	int nowTime = now.tv_sec;   //��ȡ���ö�ʱ�����ʱ��
	if ((nowTime - oldTime1) == 4)
		//�жϵ��ö�ʱ�����ʱ�䣨���ܵ����˼��ζ�ʱ�����Ƿ�����ö�ʱ��ǰ��ʱ�����1s
	{
		jieng2 = false;
		this->num1++;
		this->oldTime1 = nowTime;   //�����趨���ö�ʱ��ǰ��ʱ��
	}
}



Scene* GameLayer::createScene()
{
	// �����ճ���
	Scene* scene = Scene::create();
	// ����logo��
	GameLayer* layer = GameLayer::create();
	// �Ѳ���ӵ�������
	scene->addChild(layer);
	return scene;
}

// ��ʼ��
bool GameLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	// ��ȡ��Ļ��С
	Size winSize = Director::getInstance()->getWinSize();

	cocos2d::SpriteFrameCache* const spriteCache = cocos2d::SpriteFrameCache::getInstance();
	/*spriteCache->addSpriteFramesWithFile("Plist/MageSecond.plist");
	spriteCache->addSpriteFramesWithFile("Plist/MageSecond-0.plist");
	spriteCache->addSpriteFramesWithFile("Plist/MageSecond-1.plist");
	spriteCache->addSpriteFramesWithFile("Plist/MageSecond-2.plist");
	spriteCache->addSpriteFramesWithFile("Plist/MageSecond-3.plist");
	spriteCache->addSpriteFramesWithFile("Plist/MageSecond-4.plist");
	spriteCache->addSpriteFramesWithFile("Plist/MageSecond-5.plist");
	spriteCache->addSpriteFramesWithFile("Plist/MageSecond-6.plist");
	spriteCache->addSpriteFramesWithFile("Plist/MageSecond-7.plist");
	spriteCache->addSpriteFramesWithFile("Plist/MageSecond-8.plist");
	spriteCache->addSpriteFramesWithFile("Plist/MageSecond-9.plist");
	spriteCache->addSpriteFramesWithFile("Plist/MageSecond-10.plist");
	spriteCache->addSpriteFramesWithFile("Plist/MageSecond-11.plist");
	spriteCache->addSpriteFramesWithFile("Plist/MageSecond-12.plist");
	auto frames1 = AnimateTools::getAnimation("Walking/Necromancer_03_Walking_%03d.png", 18);
	auto frames2 = AnimateTools::getAnimation("Walking/Archer_Walking_%03d.png", 18);*/

	// ���ص�ͼ
	char mapName[64] = { 0 };
	sprintf(mapName, "Map/map_%d.tmx", s_iLv);
	m_Map = TMXTiledMap::create(mapName);
	this->addChild(m_Map);

	if (role == 0){
		m_pHero = Hero::create("shooter/Walking/Archer_Walking_000.png");
		m_pHero->setScale(0.2, 0.2);
	}
	else if (role == 1){
		m_pHero = Hero::create("Mage/Walking/Necromancer_03_Walking_000.png");
		m_pHero->setScale(0.2, 0.2);
	}
	m_Map->addChild(m_pHero);
	m_pHero->setPosition(300, 300);
	// ��ʼ������
	flag = false;
	buttonState = CURRENT_BUTTON::NONE_BTN;

	// ҡ��
	m_pMyRocker = MyRocker::create("Direction_bc.png", "Direction_bt.png", Vec2(100, 100));
	this->addChild(m_pMyRocker);

	// ����
	EventListenerTouchAllAtOnce* _event = EventListenerTouchAllAtOnce::create();
	_event->onTouchesBegan = [&](const std::vector<Touch*>& touches, Event* event) {
		
		for (int i = 0; i < touches.size(); i++){

			Touch* touch = touches[i];
			if (m_pMyRocker->getBoundingBox().containsPoint(touch->getLocation())){

				buttonState = CURRENT_BUTTON::ROCKER;
				this->schedule(schedule_selector(GameLayer::setHeroMove));
				
				flag = true;
			}
			Vec2 const v3 = touches[i]->getLocationInView();

		}
	};
	_event->onTouchesEnded = [&](const std::vector<Touch*>& touches, Event* event){
		if (!flag){
			return;
		}

		m_pHero->setHeroState(HERO_STAY);
		switch (buttonState){
		case ROCKER:{
					   this->unschedule(schedule_selector(GameLayer::setHeroMove));
					   buttonState = NONE_BTN;
					   flag = false;
		}
			break;
		}
	};
	this->setTouchEnabled(true);
	EventDispatcher* _dispatcher = Director::getInstance()->getEventDispatcher();
	_dispatcher->addEventListenerWithSceneGraphPriority(_event, this);


	Button* exit = Button::create("images/return1.png", "images/return2.png");
	this->addChild(exit);
	exit->setScale(0.16);
	exit->setPosition(Vec2(Director::getInstance()->getWinSize().width-90, Director::getInstance()->getWinSize().height-70));
	exit->addTouchEventListener([](Ref* ref, Widget::TouchEventType type)
	{
		switch (type)
		{
		case cocos2d::ui::Widget::TouchEventType::BEGAN:
			Director::getInstance()->replaceScene(MenuLayer::createScene());
			break;
		}
	});

	// ���䰴ť

	if (role == 1){
		m_attackBtn3 = Sprite::create("resource/dynamicRes/lotterySkill/bchh.png");
	}
	else if (role == 0){
		m_attackBtn3 = Sprite::create("resource/dynamicRes/lotterySkill/bkhp1.png");
	}
	m_attackBtn3->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
	m_attackBtn3->setPosition(winSize.width - 200, 50);
	this->addChild(m_attackBtn3);
	// ��ʼ������
	flag3 = false;
	buttonState3 = CURRENT_BUTTON::NONE_BTN;

	jieng2 = false;

	// ����
	EventListenerTouchAllAtOnce* _event3 = EventListenerTouchAllAtOnce::create();
	_event3->onTouchesBegan = [&](const std::vector<Touch*>& touches, Event* event) {
		for (int i = 0; i < touches.size(); i++){
			Touch* touch = touches[i];
			// ****
			// �ж��Ƿ�����������ť
			if (m_attackBtn3->getBoundingBox().containsPoint(touch->getLocation()))
			{

				if (jieng2 == false){
					jieng2 =true;

					GameLayer::jinengxuanzhe = 3;
					Animation* animationMouse = Animation::create();

					if (role == 0){
						char mapName[44] = { 0 };
						for (int i = 0; i < 15; i++) {
							sprintf(mapName, "shooter/Shooting/Archer_Shooting_%d.png", i);
							animationMouse->addSpriteFrameWithFileName(mapName);
						}
						animationMouse->setDelayPerUnit(0.05f);
					}
					else if (role == 1){
						char mapName[55] = { 0 };
						for (int i = 0; i < 13; i++) {
							sprintf(mapName, "Mage/Attacking/Necromancer_03_Casting_Spells_%d.png", i);
							animationMouse->addSpriteFrameWithFileName(mapName);
						}
						animationMouse->setDelayPerUnit(0.05f);
					}
					animationMouse->setLoops(1);
					Animate* animateMouse = Animate::create(animationMouse);
					m_pHero->runAction(animateMouse);
					// ����״̬
					buttonState3 = CURRENT_BUTTON::ATTACK_BTN;
					// ����///////////////////////////////////////////////////////////////////
					m_pHero->mainWeaponAttack();
					// ��ť��͸��
					m_attackBtn3->setOpacity(70);
					flag3 = true;
				}
				//��ʱ��
				struct timeval now;
				gettimeofday(&now, NULL);
				this->num1 = 0;    //��ʱ��0��ʼ
				CCLOG("%d", this->num1);
				this->oldTime1 = now.tv_sec;  //��ȡ���ö�ʱ��ǰ��ʱ��
				schedule(schedule_selector(GameLayer::update2));
			}



		}
	};
	_event3->onTouchesEnded = [&](const std::vector<Touch*>& touches, Event* event)
	{
		if (!flag3)
		{
			return;
		}
		m_pHero->setHeroState(HERO_STAY);
		switch (buttonState3)
		{
			// *****
			// �����������ǹ�����ť
		case ATTACK_BTN:
		{
						   // ����͸���ȵ�255
						   
						   //m_attackBtn3->setOpacity(255);
						   CCFadeTo* fadein = CCFadeTo::create(5, 255);
						   m_attackBtn3->runAction(fadein);
						   //m_attackBtn1->setOpacity(225);
						   // ��ǰ��ť״̬��Ϊ��
						   buttonState3 = NONE_BTN;

						   flag3 = false;
		}
			break;
		}
	};
	this->setTouchEnabled(true);
	EventDispatcher* _dispatcher3 = Director::getInstance()->getEventDispatcher();
	_dispatcher3->addEventListenerWithSceneGraphPriority(_event3, this);

	if (role == 1){
		// ���䰴ť
		m_attackBtn1 = Sprite::create("resource/dynamicRes/lotterySkill/dxzmj1.png");
	}
	else if (role == 0){
		m_attackBtn1 = Sprite::create("resource/dynamicRes/lotterySkill/fnhl1.png"); 
	}


	m_attackBtn1->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
	m_attackBtn1->setPosition(winSize.width - 70, winSize.height - 400);
	this->addChild(m_attackBtn1);

	// ��ʼ������
	flag1 = false;
	buttonState1 = CURRENT_BUTTON::NONE_BTN;



	jieng1 = false;
	// ����
	EventListenerTouchAllAtOnce* _event2 = EventListenerTouchAllAtOnce::create();
	_event2->onTouchesBegan = [&](const std::vector<Touch*>& touches, Event* event) {

		for (int i = 0; i < touches.size(); i++)
		{	
			Touch* touch = touches[i];
			// ****
			// �ж��Ƿ�����������ť
			if (m_attackBtn1->getBoundingBox().containsPoint(touch->getLocation()))
			{

				if (jieng1 == false){
					jieng1 = true;
					GameLayer::jinengxuanzhe = 1;

					Animation* animationMouse = Animation::create();

					if (role == 0){
						char mapName[44] = { 0 };
						for (int i = 0; i < 15; i++) {
							sprintf(mapName, "shooter/Shooting/Archer_Shooting_%d.png", i);
							animationMouse->addSpriteFrameWithFileName(mapName);
						}
						animationMouse->setDelayPerUnit(0.05f);
					}
					else if (role == 1){
						char mapName[55] = { 0 };
						for (int i = 0; i < 13; i++) {
							sprintf(mapName, "Mage/Attacking/Necromancer_03_Casting_Spells_%d.png", i);
							animationMouse->addSpriteFrameWithFileName(mapName);
						}
						animationMouse->setDelayPerUnit(0.05f);
					}
					animationMouse->setLoops(1);
					Animate* animateMouse = Animate::create(animationMouse);
					m_pHero->runAction(animateMouse);
					// ����״̬
					buttonState1 = CURRENT_BUTTON::ATTACK_BTN;
					// ����/////////////
					m_pHero->mainWeaponAttack();
					// ��ť��͸��
					m_attackBtn1->setOpacity(50);
					flag1 = true;

				}
				/////////////////////////////////////////////////////////////��ʱ��
				struct timeval now;
				gettimeofday(&now, NULL);
				this->num = 0;    //��ʱ��0��ʼ
				CCLOG("%d", this->num);
				this->oldTime = now.tv_sec;  //��ȡ���ö�ʱ��ǰ��ʱ��
				schedule(schedule_selector(GameLayer::update1));

				
			}



		}
	};

	

	_event2->onTouchesEnded = [&](const std::vector<Touch*>& touches, Event* event)
	{
		if (!flag1)
		{
			return;
		}
		m_pHero->setHeroState(HERO_STAY);
		switch (buttonState1)
		{
			// *****
			// �����������ǹ�����ť
		case ATTACK_BTN:
		{

						   // ����͸���ȵ�255
						   //m_attackBtn1->setOpacity(255);

						   ///////////////͸���ȱ仯
						   //CCFadeIn 
						   CCFadeTo* fadein = CCFadeTo::create(2,255);
						   m_attackBtn1->runAction(fadein);
						   buttonState1 = NONE_BTN;

						   flag1 = false;

		}
			break;
		}
		//Sleep(300);
	};
	this->setTouchEnabled(true);
	EventDispatcher* _dispatcher2 = Director::getInstance()->getEventDispatcher();
	_dispatcher2->addEventListenerWithSceneGraphPriority(_event2, this);


	// ���䰴ť
	m_attackBtn = Sprite::create("attack_btn.png");
	m_attackBtn->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
	m_attackBtn->setPosition(winSize.width - 30, 30);
	this->addChild(m_attackBtn);

	// ��ʼ������
	flag = false;
	buttonState = CURRENT_BUTTON::NONE_BTN;

	// ����
	EventListenerTouchAllAtOnce* _event1 = EventListenerTouchAllAtOnce::create();
	_event1->onTouchesBegan = [&](const std::vector<Touch*>& touches, Event* event) {

		for (int i = 0; i < touches.size(); i++)
		{
			Touch* touch = touches[i];
			// ****
			// �ж��Ƿ�����������ť
			if (m_attackBtn->getBoundingBox().containsPoint(touch->getLocation()))
			{
				GameLayer::jinengxuanzhe = 0;

				Animation* animationMouse = Animation::create();

				if (role == 0){

					char mapName[44] = { 0 };
					for (int i = 0; i < 15; i++) {
						sprintf(mapName, "shooter/Shooting/Archer_Shooting_%d.png", i);
						animationMouse->addSpriteFrameWithFileName(mapName);
					}
					animationMouse->setDelayPerUnit(0.05f);
				}
				else if (role == 1){

					char mapName[55] = { 0 };
					for (int i = 0; i < 13; i++) {
						sprintf(mapName, "Mage/Attacking/Necromancer_03_Casting_Spells_%d.png", i);
						animationMouse->addSpriteFrameWithFileName(mapName);
					}
					animationMouse->setDelayPerUnit(0.05f);
				}
				animationMouse->setLoops(1);
				Animate* animateMouse = Animate::create(animationMouse);
				m_pHero->runAction(animateMouse);
				// ����״̬
				buttonState = CURRENT_BUTTON::ATTACK_BTN;
				// ����///////////////////////////////////////////////////////////////////
				m_pHero->mainWeaponAttack();
				// ��ť��͸��
				m_attackBtn->setOpacity(100);
				flag = true;
			}



		}
	};
	_event1->onTouchesEnded = [&](const std::vector<Touch*>& touches, Event* event)
	{
		if (!flag)
		{
			return;
		}

		m_pHero->setHeroState(HERO_STAY);
		switch (buttonState)
		{
			// *****
			// �����������ǹ�����ť
		case ATTACK_BTN:
		{
						   // ����͸���ȵ�255
						   m_attackBtn->setOpacity(255);
						   // ��ǰ��ť״̬��Ϊ��
						   buttonState = NONE_BTN;

						   flag = false;
		}
			break;
		}
	};
	this->setTouchEnabled(true);
	EventDispatcher* _dispatcher1 = Director::getInstance()->getEventDispatcher();
	_dispatcher1->addEventListenerWithSceneGraphPriority(_event1, this);



	initMonster();

	// ����������
	this->scheduleUpdate();
	return true;
}

void GameLayer::setHeroMove(float dt)
{
	Vec2 vec2 = m_pMyRocker->getDirection();
	m_pHero->move(vec2, m_Map,role);
}
// ���������º���
void GameLayer::update(float dt){
	// ����Manager���ͷ�ļ�:  #include "Manager.h"
	// �����ӵ�
	auto& hero_pool = Manager::getInstance()->_objPool;
	for (auto heroBullet : hero_pool)
	{
		// �ж��ӵ��Ƿ�����ײ
		if (heroBullet->isCollider())
		{
			// ����Ϊ����
			heroBullet->setIsLive(false);
		}
	}

	// �����ӵ�
	list<HeroBullet*>::iterator iteratorHeroBullet = hero_pool.begin();
	while (iteratorHeroBullet != hero_pool.end())
	{
		HeroBullet* temp = *iteratorHeroBullet;
		// ����ӵ�����
		if (!temp->getIsLive())
		{
			// ��ӱ�ը���鼰����
			Sprite* spBoom = Sprite::create();
			spBoom->setPosition(temp->getPosition());
			temp->getParent()->addChild(spBoom);

			// 1.����֡����
			Animation* aniBoom = Animation::create();
			// 2.��Ӷ���֡

			if (role == 0){
				aniBoom->addSpriteFrameWithFileName("Weapon/boomEffect_2.png");
				aniBoom->addSpriteFrameWithFileName("Weapon/boomEffect_3.png");
				aniBoom->addSpriteFrameWithFileName("Weapon/boomEffect_4.png");
			}
			else if (role == 1){
				aniBoom->addSpriteFrameWithFileName("Weapon/sword0.png");
				aniBoom->addSpriteFrameWithFileName("Weapon/sword1.png");
				aniBoom->addSpriteFrameWithFileName("Weapon/sword2.png");
			}

			// 3.��������������
			// ���ʱ��
			aniBoom->setDelayPerUnit(0.12f);
			// ѭ������ �������
			aniBoom->setLoops(1);
			// 4.��������
			Animate* animateBoom = Animate::create(aniBoom);

			Sequence* seq = Sequence::create(animateBoom, RemoveSelf::create(), nullptr);
			// 5.ִ�ж���
			spBoom->runAction(seq);

			// �Ƴ��ӵ�
			iteratorHeroBullet = hero_pool.erase(iteratorHeroBullet);
			SimpleAudioEngine::getInstance()->playEffect("music/fx_bullet_destroy.wav");
			temp->removeFromParent();
		}
		else
		{
			iteratorHeroBullet++;
		}
	}
	auto const visibleSize = Director::getInstance()->getVisibleSize();
	// ����
	auto& enemy_pool = Manager::getInstance()->_enemyObjPool;
	list<Enemy*>::iterator iteratorEnemy = enemy_pool.begin();
	while (iteratorEnemy != enemy_pool.end()){

		Enemy* temp = *iteratorEnemy;
		// �����������
		if (!temp->getIsLive()){
			Reward();
			UpLevel();
			
			

			// �Ƴ�����
			iteratorEnemy = enemy_pool.erase(iteratorEnemy);
			//SimpleAudioEngine::getInstance()->playEffect("music/fx_bullet_destroy.wav");
			temp->removeFromParent();

			if (enemy_pool.empty()){
				
				if (guanka == 6) {
					Button* nextButton = Button::create("images/nextOne.png", "images/nextOne.png");
					nextButton->setScale(0.1f);
					this->addChild(nextButton,3);
					nextButton->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
					nextButton->addTouchEventListener([this](Ref* ref, Widget::TouchEventType type) {
						Director::getInstance()->replaceScene(MenuLayer::createScene());
						});
				}
				else{
					//Director::getInstance()->replaceScene(login::createScene());
					Button* nextButton = Button::create("images/nextOne.png","images/nextOne.png");
					nextButton->setScale(0.1f);
					this->addChild(nextButton, 3);
					nextButton->setPosition(Vec2(visibleSize.width / 2,visibleSize.height / 2));
					nextButton->addTouchEventListener([this](Ref* ref, Widget::TouchEventType type) {
						Director::getInstance()->replaceScene(MenuLayer::createScene());
						});
					
				}
			}
		}
		else{
			iteratorEnemy++;
		}
	}
	if (m_pHero->getHp() <= 0) {
		Animation* animationMouse = Animation::create();
		if (role == 0) {
			char mapName[44] = { 0 };
			for (int i = 0; i < 15; i++) {
				sprintf(mapName, "shooter/Dying/Archer_Dying_%d.png", i);
				animationMouse->addSpriteFrameWithFileName(mapName);
			}
			animationMouse->setDelayPerUnit(0.05f);
		}
		else if (role == 1) {
			char mapName[55] = { 0 };
			for (int i = 0; i < 14; i++) {
				sprintf(mapName, "Mage/Dying/Necromancer_03_Dying_%d.png", i);
				animationMouse->addSpriteFrameWithFileName(mapName);
			}
			animationMouse->setDelayPerUnit(0.25f);
		}
		animationMouse->setLoops(1);
		Animate* animateMouse = Animate::create(animationMouse);
		m_pHero->runAction(animateMouse);
		this->removeChild(m_pHero);
		PerishMonister();
		this->stopAllActions();
		this->unscheduleUpdate();
		this->unscheduleAllSelectors();
		auto pingbi = Sprite::create("images/pingbi.png");
		pingbi->setPosition(Vec2(visibleSize.width / 2,visibleSize.height / 2));
		this->addChild(pingbi,10);
		Button* nextButton = Button::create("images/shibai1.png", "images/shibai2.png");
		nextButton->setScale(0.1f);
		pingbi->addChild(nextButton, 3);
		nextButton->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
		nextButton->addTouchEventListener([this](Ref* ref, Widget::TouchEventType type) {
			Director::getInstance()->replaceScene(MenuLayer::createScene());
			});

	}
	
}
void GameLayer::HeroWalking() {
	Animation* animationMouse = Animation::create();
	if (m_pHero->getHeroState() == HERO_MOVE) {
		
		if (role == 0) {

			char mapName[60] = { 0 };
			for (int i = 0; i < 18; i++) {
				sprintf(mapName, "shooter/Walking/Archer_Walking_%d.png", i);
				animationMouse->addSpriteFrameWithFileName(mapName);
			}
			animationMouse->setDelayPerUnit(0.05f);
		}
		else if (role == 1) {

			char mapName[60] = { 0 };
			for (int i = 0; i < 18; i++) {
				sprintf(mapName, "Mage/Walking/Necromancer_03_Walking_%d.png", i);
				animationMouse->addSpriteFrameWithFileName(mapName);
			}
			animationMouse->setDelayPerUnit(0.05f);
		}
		animationMouse->setLoops(1);
		m_pHero->runAction(Animate::create(animationMouse));
		m_pHero->runAction(cocos2d::Spawn::create(cocos2d::Animate::create(animationMouse), nullptr));
	}
	else {
		m_pHero->stopAllActions();
	}
}
void GameLayer::initMonster(){
	TMXObjectGroup* monsterObj = m_Map->getObjectGroup("monsterObjects");
	if (!monsterObj)
		return;
	ValueMap vm = monsterObj->getObject("monster");
	float xxx = vm["x"].asFloat();
	float yyy = vm["y"].asFloat();
	for (int i = 0; i < monsterObj->getObjects().size(); i++){
		float x = monsterObj->getObjects().at(i).asValueMap()["x"].asFloat();
		float y = monsterObj->getObjects().at(i).asValueMap()["y"].asFloat();
		int monster_type = monsterObj->getObjects().at(i).asValueMap()["monster_type"].asInt();


		Enemy* enemy = Enemy::create((MONSTER_TYPE)monster_type, m_pHero, guanka*30, 1, 3.0, 100, 300, 300, (BULLET_TYPE)0);//Ѫ

		enemy->setPosition(x, y);
		m_Map->addChild(enemy);
		enemy->initMonsterInfo();

		Manager::getInstance()->_enemyObjPool.push_back(enemy);
	}
}
void GameLayer::UpLevel() {
	if (MainPart::getMainPart()->getExp() == 100) {
		MainPart::getMainPart()->setLevel(MainPart::getMainPart()->getLevel() + 1);
		MainPart::getMainPart()->setDefense(MainPart::getMainPart()->getDefense()+10);
		MainPart::getMainPart()->setEnergy(MainPart::getMainPart()->getEnergy()+10);
	}
	if (this->m_pHero->getExp() % 100 == 100) {
		this->m_pHero->setLevel(this->m_pHero->getLevel() + 1);
		this->m_pHero->setDefense(this->m_pHero->getDefense() + 10);
		this->m_pHero->setEnergy(this->m_pHero->getEnergy() + 10);
	}
}
void GameLayer::Reward() {
	srand((unsigned)time(0));
	MainPart::getMainPart()->setCoinNum(MainPart::getMainPart()->getCoinNum() - 5);
	std::vector<std::string> str = MainPart::getMainPart()->getEquip();
	str.push_back(Drop::getDrop()->getMdrop().at(random() % 100).c_str());
	MainPart::getMainPart()->setEquip(str);

	int const coin = MainPart::getMainPart()->getCoinNum();
	MainPart::getMainPart()->setCoinNum(coin+15);

	int const Exp = MainPart::getMainPart()->getExp();
	MainPart::getMainPart()->setExp(Exp + 50);

	int const HExp = this->m_pHero->getExp();
	this->m_pHero->setExp(HExp + 15);
}
GameLayer::~GameLayer(){
	// �����ӵ�
	auto& hero_pool = Manager::getInstance()->_objPool;
	list<HeroBullet*>::iterator iteratorHeroBullet = hero_pool.begin();
	while (iteratorHeroBullet != hero_pool.end())
	{
		HeroBullet* temp = *iteratorHeroBullet;
		// �Ƴ��ӵ�
		iteratorHeroBullet = hero_pool.erase(iteratorHeroBullet);
		temp->removeFromParent();
		//iteratorHeroBullet++;  ɾ��
	}

	// ����
	auto& enemy_pool = Manager::getInstance()->_enemyObjPool;
	list<Enemy*>::iterator iteratorEnemy = enemy_pool.begin();
	while (iteratorEnemy != enemy_pool.end())
	{
		//log("С������");
		Enemy* temp = *iteratorEnemy;
		if (!temp)
			continue;
			// �Ƴ��ӵ�
			iteratorEnemy = enemy_pool.erase(iteratorEnemy);
			temp->removeFromParent();
	}
}
void GameLayer::PerishMonister() {
	// ����
	auto& enemy_pool = Manager::getInstance()->_enemyObjPool;
	list<Enemy*>::iterator iteratorEnemy = enemy_pool.begin();
	while (iteratorEnemy != enemy_pool.end())
	{
		//log("С������");
		Enemy* temp = *iteratorEnemy;
		if (!temp)
			continue;
		// �Ƴ��ӵ�
		iteratorEnemy = enemy_pool.erase(iteratorEnemy);
		temp->removeFromParent();
	}
}