#ifndef _Hero_H_
#define _Hero_H_

#include<Vector>
#include "cocos2d.h"
#define Initial_Accelerated_Speed 1.0f
#define Initial_Speed 15.0f
#define MapDisUpAndDown 150
#define MapDisLeftAndRight 200
#define HeroAnimateKey 61

class WeaponBase;

enum HERO_STATE
{
	HERO_STAY,
	HERO_MOVE
};
enum HERO_TYPE
{
	HERO_KNIGHT,
	HERO_MAGICER,
	HERO_NONE
};

enum SKILL_STATE
{
	UNUSED,
	USING,
	COOLDOWN
};
enum HERO_TOWARD
{
	LEFT,
	RIGHT
};

class Hero : public cocos2d::Sprite
{
	CC_SYNTHESIZE(int, m_Level, Level);
	CC_SYNTHESIZE_READONLY(int, m_Price, Price);
	CC_SYNTHESIZE(int, m_Exp, Exp);
	CC_SYNTHESIZE(int,m_CoinNum,CoinNum);
	CC_SYNTHESIZE(int, m_MaxDefense, MaxDefense);
	CC_SYNTHESIZE(int, m_Defense, Defense);
	CC_SYNTHESIZE(HERO_STATE, m_HeroState, HeroState);
	CC_SYNTHESIZE_READONLY(HERO_TOWARD, m_Hero_Toward, Hero_Toward);
	CC_SYNTHESIZE_READONLY(HERO_TYPE, m_HeroType, HeroType);
	CC_SYNTHESIZE(float, m_CoolDownTime, CoolDownTime);
	CC_SYNTHESIZE(cocos2d::Vec2, m_StartPos, StartPos);
	CC_SYNTHESIZE(int, m_MaxEnergy, MaxEnergy);
	CC_SYNTHESIZE_READONLY(int, m_Energy, Energy);
	CC_SYNTHESIZE(int, m_hp, Hp);
	CC_SYNTHESIZE(int, m_MaxHp, MaxHp);
	CC_SYNTHESIZE(std::string, m_imagePath, ImagePath);
	CC_SYNTHESIZE(float, m_MoveSpeed, MoveSpeed);
	CC_SYNTHESIZE(WeaponBase*, m_MainWeapon, MainWeapon);
	CC_SYNTHESIZE(std::vector<std::string>, m_equip, Equip);
	//CC_SYNTHESIZE(WeaponBase*, m_DeputyWeapon, DeputyWeapon);
protected:
	
public:
	static Hero* create(const std::string& imagePath);
	virtual bool init(const std::string& imagePath);
	virtual bool checkNeedToMoveMap(const cocos2d::Vec2&directionVec2);
	virtual bool checkNextPosCanMove(const cocos2d::Vec2&directionVec2,cocos2d::TMXTiledMap* map);
	virtual void move(const cocos2d::Vec2& directionVec2, cocos2d::TMXTiledMap* map,int p);
	void HeroWalking(int p);
	virtual void setEnergy(const int& energy);
	virtual void mainWeaponAttack();

	virtual void useSkill()noexcept{
	};
};
#endif