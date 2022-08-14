#include"WeaponBase.h"
#include"HeroBullet.h"
#include "Manager.h"
#include"GameLayer.h"
#define _Pi 3.1415
USING_NS_CC;
// 导入声音头文件
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

WeaponBase* WeaponBase::create(std::string iconPath, float shootSpeed, const GUN_TYPE& type, int costEnergy, std::string weaponName, const WEAPON_QUALITY& quality,int damage)
{
	WeaponBase* sp =new WeaponBase;
	if (sp&&sp->init(iconPath, shootSpeed, type, costEnergy, weaponName, quality, damage))
	{
		sp->autorelease();
	}
	else
	{
		delete sp;
		sp = nullptr;
	}
	return sp;
}
bool WeaponBase::init(std::string iconPath,float shootSpeed,const GUN_TYPE& type,int costEnergy,std::string weaponName,const WEAPON_QUALITY& quality,int damage)
{
	if (!Sprite::initWithFile(iconPath))
	{
		return false;
	}
	m_weaponIconPath = iconPath;
	m_Damage = damage;
	setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	setPosition(25, 20);
	m_CoolDown = shootSpeed;
	m_GunType = type;
	m_WeaponState = NONEATTACK;
	m_CostEnergy = costEnergy;
	m_WeaponName = weaponName;
	m_WeaponQuality = quality;
	//attack();
	return true;
}

void WeaponBase::attack()
{
	if (m_WeaponState == NONEATTACK)
	{
		m_WeaponState = ATTACKING;

		SimpleAudioEngine::getInstance()->playEffect("music/fx_heroGun.wav");
		this->schedule(schedule_selector(WeaponBase::changeAttackState),0,1, m_CoolDown);
		shoot(0.1f);
	}
}
void WeaponBase::shoot(float dt)
{
	if (GameLayer::role== 0){
		findTarget();

		if (GameLayer::jinengxuanzhe == 0){

			for (int i = -2; i < 2; i++){
				HeroBullet* bullet = HeroBullet::create("HeroBullet/laser.png", m_Damage, 600);
				bullet->setScale(2, 2);
				bullet->setRotation(getRotation() + 10 * i);
				bullet->setPosition(getMuzzlePos() + this->getParent()->getPosition());
				bullet->move();
				this->getParent()->getParent()->addChild(bullet);
				// 添加到对象池
				Manager::getInstance()->_objPool.push_back(bullet);
			}
		}
		else if (GameLayer::jinengxuanzhe == 1){
			for (int i = -20; i < -12; i++){

				HeroBullet* bullet = HeroBullet::create("HeroBullet/laser.png", m_Damage, 600);
				
				bullet->setScale(2, 2);
				bullet->setRotation(getRotation() + 10 * i);
				bullet->setPosition(getMuzzlePos() + this->getParent()->getPosition());
				bullet->move();
				this->getParent()->getParent()->addChild(bullet);
				// 添加到对象池
				Manager::getInstance()->_objPool.push_back(bullet);
			}
		}
		else if (GameLayer::jinengxuanzhe == 3){
			for (int i = -20; i < 20; i++){

				HeroBullet* bullet = HeroBullet::create("HeroBullet/laser.png", m_Damage, 600);
				bullet->setScale(2, 2);
				bullet->setRotation(getRotation() + 10 * i);
				bullet->setPosition(getMuzzlePos() + this->getParent()->getPosition());
				bullet->move();
				this->getParent()->getParent()->addChild(bullet);
				// 添加到对象池
				Manager::getInstance()->_objPool.push_back(bullet);
			}
		}
	}
	else if (GameLayer::role==1){

		findTarget();
		if (GameLayer::jinengxuanzhe == 0){

			HeroBullet* bullet = HeroBullet::create("HeroBullet/bulletlist.PNG", m_Damage, 600);
				bullet->setScale(0.7, 0.7);
				bullet->setRotation(getRotation());
				bullet->setPosition(getMuzzlePos() + this->getParent()->getPosition());
				bullet->move();
				this->getParent()->getParent()->addChild(bullet);
				// 添加到对象池
				Manager::getInstance()->_objPool.push_back(bullet);
			//}
		}
		else if (GameLayer::jinengxuanzhe == 1){
			for (int i = -8; i < 8; i=i+4){

				HeroBullet* bullet = HeroBullet::create("HeroBullet/bulletlist.PNG", m_Damage, 600);
				bullet->setScale(0.7, 0.7);
				bullet->setRotation(getRotation() + 10 * i);
				bullet->setPosition(getMuzzlePos() + this->getParent()->getPosition());
				bullet->move();
				this->getParent()->getParent()->addChild(bullet);
				// 添加到对象池
				Manager::getInstance()->_objPool.push_back(bullet);
			}
		}
		else if (GameLayer::jinengxuanzhe == 3){
			HeroBullet* bullet = HeroBullet::create("HeroBullet/bullet1.PNG", 1100, 600);
				bullet->setScale(0.5, 0.5);
				bullet->setRotation(getRotation());
				bullet->setPosition(getMuzzlePos() + this->getParent()->getPosition());
				bullet->move();
				this->getParent()->getParent()->addChild(bullet);
				// 添加到对象池
				Manager::getInstance()->_objPool.push_back(bullet);

		}

	}
}
const Vec2& WeaponBase::getMuzzlePos()
{

	float r = this->getContentSize().width;
	float angel = getRotation();
	float corner = angel / 180 * _Pi;
	float cos_Corner = cos(corner);
	float sin_Corner = sin(-corner);
	float x = r * cos_Corner;
	float y = r * sin_Corner;
	Vec2 targetPos(x,y/*-getContentSize().height/2*/);
	return targetPos+this->getPosition();
}

void WeaponBase::findTarget()
{
	//auto monster_livePool = MonsterFactory::getInstance()->_objPool._livePool;
	//float min = 0;
	//bool isFind = false;
	//Enemy* temp = nullptr;
	//Vec2 muzzlePosInWorld = getMuzzlePos() + this->getParent()->getPosition();
	//for (auto monster : monster_livePool)
	//{
	//	Vec2 dirPos = monster->getPosition() - muzzlePosInWorld;
	//	//float dis = dirPos.distance(muzzlePosInWorld);
	//	float angel = dirPos.getAngle();
	//	angel = -(angel * 180 / _Pi);
	//	CCLOG("%f", this->getRotation());
	//	CCLOG("%f", angel);
	//	if (this->getRotation()+15>=angel&&this->getRotation()-15<=angel)
	//	{

	//		this->setRotation(angel);
	//		return;
	//	}
	//}
}
void WeaponBase::changeAttackState(float dt){

	m_WeaponState = NONEATTACK;
	this->unschedule(schedule_selector(WeaponBase::changeAttackState));
}