#include "Hero.h"
#include "TMXTools.h"
#include"WeaponBase.h"

#define _Pi 3.1415
USING_NS_CC;
Hero* Hero::create(const std::string& imagePath)
{
	Hero* hero = new Hero;
	if (hero&&hero->init(imagePath)){
		hero->autorelease();
		return hero;
	}
	else{
		CC_SAFE_DELETE(hero);
	}
	return nullptr;
}
bool Hero::init(const std::string& imagePath)
{
	if (!Sprite::initWithFile(imagePath))
	{
		return false;
	}
	setImagePath(imagePath);
	m_Level = 1;
	m_Hero_Toward = RIGHT;
	m_MaxHp = 100;
	m_hp = m_MaxHp;
	m_Exp = 0;
	m_MoveSpeed = 2;
	m_MaxEnergy = 200;
	m_Energy = m_MaxEnergy;
	m_MaxDefense = 5;
	m_Defense = m_MaxDefense;
	m_HeroState = HERO_MOVE;
	m_CoinNum = 15;
	m_equip.push_back("resource/dynamicRes/bigequip/100001.png");
	setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	m_MainWeapon = WeaponBase::create("Weapon/weapon_Rocker.png", 0.5, GUN_ROCKER, 3, "вои╚атс╔", RED, 10);
	//m_DeputyWeapon = WeaponFactory::create(SWORD_NORMAL);
	//m_DeputyWeapon->retain();
	m_Price = 500;
	setHeroState(HERO_STAY);
	this->setLocalZOrder(2);
	this->addChild(m_MainWeapon,3);

	m_MainWeapon->setLocalZOrder(2);
	return true;
}
//void Hero::setDefense(int defense)
//{
//	m_Defense = defense;
//	m_Defense = m_Defense < 0 ? 0 : m_Defense;
//	m_Defense = m_Defense > m_MaxDefense ? m_MaxDefense : m_Defense;
//	if (m_Defense>=0&& m_Defense <= m_MaxDefense)
//	{
//		EventDispatcher* _dispatcher = Director::getInstance()->getEventDispatcher();
//		_dispatcher->dispatchCustomEvent(HeroInfoBarDefenseKey, this);
//	}
//}

void Hero::move(const cocos2d::Vec2& directionVec2, cocos2d::TMXTiledMap* map,int p){

	if (directionVec2==Vec2::ZERO){
		return;
	}
	Vec2 moveOffset = directionVec2 * m_MoveSpeed;
	Vec2 nextPos = this->getPosition() + directionVec2 * m_MoveSpeed;

	setHeroState(HERO_MOVE);

	float angel;
	angel = -(directionVec2.getAngle() * 180 / _Pi);
	m_MainWeapon->setRotation(angel);
	bool canMove = true;
	
	canMove = canMove && checkNextPosCanMove(nextPos, map);
	bool isNeedToMoveMap = !checkNeedToMoveMap(directionVec2);

	if (canMove){

		if (isNeedToMoveMap){

			map->setPosition(map->getPosition() - moveOffset);

		}
		HeroWalking(p);
		this->setPosition(this->getPosition() + moveOffset);
		
	}
}

bool Hero::checkNextPosCanMove(const cocos2d::Vec2&nextPos, cocos2d::TMXTiledMap* map)
{
	Vec2 nextPosInMap = TMXTools::transformPosInMap(nextPos, map);
	Vec2 nextPosIndex = TMXTools::getPosIndexInMap(nextPosInMap, map);
	CCLOG("x = %f,y = %f", nextPosInMap.x, nextPosInMap.y);
	bool canMove = TMXTools::isColliderInMapWith(nextPosIndex, map, "walk", 0);
	return canMove;
}

bool Hero::checkNeedToMoveMap(const cocos2d::Vec2&directionVec2)
{
	bool isNeedToMoveMap = true;
	Size winSize = Director::getInstance()->getWinSize();
	Vec2 nowPos = this->getPosition() + this->getParent()->getPosition();
	if (directionVec2.x<=0)
	{

		setFlippedX(true);
		m_Hero_Toward = LEFT;
		isNeedToMoveMap = isNeedToMoveMap && !(nowPos.x <= MapDisLeftAndRight);
	}
	else if(directionVec2.x>0)
	{
		m_Hero_Toward = RIGHT;
		setFlippedX(false);
		isNeedToMoveMap = isNeedToMoveMap && !(nowPos.x >= winSize.width - MapDisLeftAndRight);
	}
	if (directionVec2.y > 0)
	{
		isNeedToMoveMap = isNeedToMoveMap && !(nowPos.y >= winSize.height - MapDisUpAndDown);
	}
	else if (directionVec2.y <= 0)
	{
		isNeedToMoveMap = isNeedToMoveMap && !(nowPos.y <= MapDisUpAndDown);
	}

	return isNeedToMoveMap;
}
//void Hero::setHp(const int& hp)
//{
//
//		if (hp < m_hp&&m_Defense > 0)
//		{
//			setDefense(getDefense() - hp);
//			return;
//		}
//		int last_hp = m_hp;
//		m_hp = hp;
//		bool isFlash;
//		m_hp = (isFlash = m_hp < 0) ? 0 : m_hp;
//		m_hp = m_hp > m_MaxHp ? m_MaxHp : m_hp;
//
//
//		if (hp < last_hp && !isFlash)
//		{
//			this->runAction(Sequence::create(FadeOut::create(0.25), FadeIn::create(0.25), nullptr));
//		}
//	EventDispatcher* _dispatcher = Director::getInstance()->getEventDispatcher();
//	_dispatcher->dispatchCustomEvent(HeroInfoBarHpKey, this);
//}

void Hero::mainWeaponAttack()
{
	if (m_MainWeapon->getWeaponState()==NONEATTACK && m_Energy - m_MainWeapon->getCostEnergy()>=0)
	{
		m_MainWeapon->attack();
		setEnergy(getEnergy() - m_MainWeapon->getCostEnergy());
	}
}

void Hero::setEnergy(const int& energy)
{
	m_Energy = energy;
	m_Energy = m_Energy < 0 ? 0 : energy;
	m_Energy = m_Energy > m_MaxEnergy ? m_MaxEnergy : m_Energy;

	
	
}
//void Hero::swapWeapon()
//{
//
//	MusicAudio::getInstance()->createEffect("music/fx_swapWeapon.wav");
//	m_MainWeapon->retain();
//	m_MainWeapon->changeAttackState(0.1f);
//	m_MainWeapon->removeFromParent();
//	m_DeputyWeapon->setFlippedY(m_MainWeapon->isFlippedY());
//	m_DeputyWeapon->setRotation(m_MainWeapon->getRotation());
//	m_DeputyWeapon->setLocalZOrder(2);
//	this->addChild(m_DeputyWeapon,3);
//	m_DeputyWeapon->release();
//	std::swap(m_MainWeapon, m_DeputyWeapon);
//	EventDispatcher* _dispatcher = Director::getInstance()->getEventDispatcher();
//	_dispatcher->dispatchCustomEvent(swapWeaponKey, this);
//}
//
//void Hero::setCoinNum(int val)
//{
//	m_CoinNum = val;
//	m_CoinNum = m_CoinNum < 0 ? 0 : m_CoinNum;
//	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(coinTextKey, this);
//}
void Hero::HeroWalking(int p) {
	Animation* animationMouse = Animation::create();

		if (p == 0) {

			char mapName[60] = { 0 };
			for (int i = 0; i < 18; i++) {
				sprintf(mapName, "shooter/Walking/Archer_Walking_%d.png", i);
				animationMouse->addSpriteFrameWithFileName(mapName);
			}
			animationMouse->setDelayPerUnit(0.05f);
		}
		else if (p == 1) {

			char mapName[60] = { 0 };
			for (int i = 0; i < 18; i++) {
				sprintf(mapName, "Mage/Walking/Necromancer_03_Walking_%d.png", i);
				animationMouse->addSpriteFrameWithFileName(mapName);
			}
			animationMouse->setDelayPerUnit(0.05f);
		}
		animationMouse->setLoops(1);
		this->runAction(Animate::create(animationMouse));
		this->runAction(cocos2d::Spawn::create(cocos2d::Animate::create(animationMouse), nullptr));
}