#ifndef _Enemy_H_
#define _Enemy_H_
#include"cocos2d.h"
#include"Hero.h"
#include<math.h>
#define monsterMoveKey 60
class Hero;
enum BULLET_TYPE;
enum MONSTER_TYPE
{
	MONSTER_0,
	MONSTER_1,
	MONSTER_2,
	MONSTER_3
};
class Enemy:public cocos2d::Sprite{
protected:
	bool isFirstMove;
public:
	CC_SYNTHESIZE(int, m_MaxHp, MaxHp);
	CC_SYNTHESIZE(float, m_MoveSpeed, MoveSpeed);
	CC_SYNTHESIZE(float, m_MoveRange, MoveRange);
	CC_SYNTHESIZE(BULLET_TYPE, m_bullet_type, BulletType);
	CC_SYNTHESIZE(float, m_Range, Range);
	CC_SYNTHESIZE_READONLY(int, m_hp, Hp);
	CC_SYNTHESIZE(float, m_shootSpeed, ShootSpeed);
	CC_SYNTHESIZE(std::string, m_imagePath, ImagePath);
	CC_SYNTHESIZE(int, m_damage, Damage);
	CC_SYNTHESIZE_READONLY(Hero*, m_Hero, hero);
	CC_SYNTHESIZE_READONLY(bool, m_IsLive, IsLive);
	CC_SYNTHESIZE_READONLY(MONSTER_TYPE, m_MonsterType, MonsterType);
public:
	virtual void startMove();
	virtual void setIsLive(bool val);
	virtual void initMonsterInfo();
	virtual void findHero(float dt);
	virtual void randMove(float dt);
	virtual void sethero(Hero* hero);
	virtual void setHp(const int& hp);
	static Enemy* create(const MONSTER_TYPE& monster_type, Hero* hero, const int& hp, const int damage, const float& shootSpeed,const float& moveSpeed, const float& range,const float&moveRange, const BULLET_TYPE& bullet_type);
	virtual void startShoot();
	virtual void shoot(float dt);
	virtual bool init(const MONSTER_TYPE& monster_type, Hero* hero, const int& hp, const int damage, const float& shootSpeed, const float& moveSpeed, const float& range, const float&moveRange, const BULLET_TYPE& bullet_type);

};
#endif