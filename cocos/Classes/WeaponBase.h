#ifndef _WeaponBase_H_
#define _WeaponBase_H_
#include"cocos2d.h"
enum GUN_TYPE
{
	GUN_LASER,
	SWORD_NORMAL,
	GUN_ROCKER,
	GUN_NONE,
	NONE
};
enum WEAPON_QUALITY
{
	WHITE,
	GREEN,
	BLUE,
	PURPLE,
	RED,
	ORANGE
};
enum WEAPON_STATE
{	
	NONEATTACK,
	ATTACKING,
	AFTER_SHAKING
};
class WeaponBase
	:public cocos2d::Sprite
{
private:
	CC_SYNTHESIZE_READONLY(WEAPON_QUALITY,m_WeaponQuality,WeaponQuality);
	CC_SYNTHESIZE_READONLY(std::string,m_weaponIconPath,WeaponIconPath);
	CC_SYNTHESIZE(int, m_Damage, damage);
	CC_SYNTHESIZE(WEAPON_STATE,m_WeaponState,WeaponState);
	CC_SYNTHESIZE(GUN_TYPE,m_GunType,GunType);
	CC_SYNTHESIZE(int, m_CostEnergy, CostEnergy);
	CC_SYNTHESIZE(std::string, m_WeaponName, WeaponName);
	CC_SYNTHESIZE(float, m_CoolDown, CoolDown);
protected:
public:
	
	virtual void changeAttackState(float dt);
	virtual void findTarget();
	virtual const cocos2d::Vec2& getMuzzlePos();
	virtual void attack();
	virtual void shoot(float dt);
	static WeaponBase* create(std::string iconPath, float shootSpeed, const GUN_TYPE& type, int costEnergy, std::string weaponName, const WEAPON_QUALITY& quality,int damage);
	virtual bool init(std::string iconPath, float shootSpeed, const GUN_TYPE& type, int costEnergy, std::string weaponName, const WEAPON_QUALITY& quality,int damage);
};
#endif