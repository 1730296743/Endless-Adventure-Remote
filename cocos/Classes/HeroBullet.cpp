#include"HeroBullet.h"
#include"Hero.h"
#include"TMXTools.h"
#include "Manager.h"
#define _Pi 3.1415
USING_NS_CC;
HeroBullet* HeroBullet::create(std::string imagePath, int damage, int moveSpeed)
{
	HeroBullet* sp = new HeroBullet;
	if (sp&&sp->init(imagePath,damage,moveSpeed))
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
bool HeroBullet::init(std::string imagePath, int damage, int moveSpeed)
{
	if (!Sprite::initWithFile(imagePath))
	{
		return false;
	}
	m_IsLive = true;
	m_BulletType = HERO_BULLET_Laser;
	setImagePath(imagePath);
	setDamage(damage);
	setMoveSpeed(moveSpeed);
	m_MaxDis = 600;


	setLocalZOrder(3);
	setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	return true;
}
void HeroBullet::move()
{
	m_StartPos = this->getPosition();
	//子弹到原点的向量坐标
	float r = m_MaxDis*2;
	float angel = getRotation();
	float corner = angel / 180 * _Pi;
	float cos_Corner = cos(corner);
	float sin_Corner = sin(-corner);
	float x = r * cos_Corner;
	float y = r * sin_Corner;
	Vec2 pos = getPosition();
	Vec2 targetPos(x+pos.x, y+pos.y);
	float time = targetPos.distance(pos)/ m_moveSpeed;
	this->runAction(MoveTo::create(time, targetPos));
	//this->schedule(schedule_selector(HeroBullet::collider));
}
bool HeroBullet::isCollider()
{
	bool flag= colliderWithMonster() || colliderWithBox() || isFloor() || isOutRange();
	if (flag)
	{
		
	}
	return flag;
}

bool HeroBullet::colliderWithMonster()
{
	auto monsterManager = Manager::getInstance();
	for ( auto monster :  monsterManager->_enemyObjPool)
	{
		if (this->getBoundingBox().intersectsRect(monster->getBoundingBox()))
		{
			monster->setHp(monster->getHp() - m_Damage);
			return true;
		}
	}
	return false;
}
bool HeroBullet::colliderWithBox()
{
	//BoxManager* boxManager = BoxManager::getIntance();
	//auto iteratorBox = boxManager->m_objPool._livePool.begin();
	//while (iteratorBox != boxManager->m_objPool._livePool.end())
	//{

	//	Box* box = *iteratorBox;
	//	//bool targetIsDie = box->getIsLive();
	//	iteratorBox++;
	//	if (this->getBoundingBox().intersectsRect(box->getBoundingBox()))
	//	{
	//		box->setHp(box->getHp() - m_Damage);
	//		//CCLOG("命中");
	//		return true;
	//	}
	//}
	return false;
}
bool HeroBullet::isFloor()
{
	Vec2 pos = this->getPosition();
	TMXTiledMap* map = (TMXTiledMap*)this->getParent();
	Vec2 nextPosInMap = TMXTools::transformPosInMap(pos, map);
	Vec2 nextPosIndex = TMXTools::getPosIndexInMap(nextPosInMap, map);

	if (nextPosIndex.x >= map->getMapSize().width || nextPosIndex.x <= 0 || nextPosIndex.y >= map->getMapSize().height || nextPosIndex.y <= 0)
	{
		return false;
	}
	bool isDestroy = !TMXTools::isColliderInMapWith(nextPosIndex, map, "walk", 0);
	
	return isDestroy;
}

bool HeroBullet::isOutRange()
{

	float dis = this->getPosition().distance(m_StartPos);
	if (dis >= m_MaxDis)
	{
		return true;
	}
	return false;
}