#ifndef _HeroBullet_H_
#define _HeroBullet_H_
#include"cocos2d.h"
class Hero;
enum HERO_BULLET_TYPE
{
	HERO_BULLET_Laser,
	HERO_BULLET_Arrow,
	HERO_BULLET_Bullet,
	HERO_BULLET_Rocker,
	HERO_BULLET_3
};
class HeroBullet
	:public cocos2d::Sprite
{
	CC_SYNTHESIZE(bool, m_IsLive, IsLive);
	CC_SYNTHESIZE(HERO_BULLET_TYPE, m_BulletType, BulletType);
	CC_SYNTHESIZE(std::string, m_imagePath, ImagePath);
	CC_SYNTHESIZE(int, m_Damage, Damage);
	CC_SYNTHESIZE(int, m_moveSpeed, MoveSpeed);
	CC_SYNTHESIZE(cocos2d::Vec2, m_StartPos, StartPos);
	CC_SYNTHESIZE(float, m_MaxDis, MaxDis);
protected:
public:
	virtual bool colliderWithMonster();
	virtual bool colliderWithBox();
	virtual bool isFloor();
	virtual bool isOutRange();
	static HeroBullet* create(std::string imagePath,int damage,int moveSpeed);
	virtual bool init(std::string imagePath, int damage, int moveSpeed);
	virtual void move();
	virtual bool isCollider();
};
#endif