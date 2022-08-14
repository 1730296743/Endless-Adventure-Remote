#include"Enemy.h"
#include"AnimateTools.h"
#include"MyStar.h"
#include"TMXTools.h"
#include"AnimationEffect.h"
#include<string>
#define _Pi 3.1415
USING_NS_CC;
// 导入声音头文件
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
Enemy* Enemy::create(const MONSTER_TYPE& monster_type, Hero* hero, const int& hp, const int damage, const float& shootSpeed, const float& moveSpeed, const float& range, const float&moveRange, const BULLET_TYPE& bullet_type)
{
	Enemy* sp = new Enemy;
	if (sp&&sp->init(monster_type,hero,hp,damage,shootSpeed,moveSpeed,range,moveRange,bullet_type))
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
bool Enemy::init(const MONSTER_TYPE& monster_type, Hero* hero, const int& hp, const int damage, const float& shootSpeed, const float& moveSpeed, const float& range, const float&moveRange, const BULLET_TYPE& bullet_type)
{
	
	char formate[128] = { 0 };
	sprintf(formate, "monster/monster_%d/monster_%d_0.png", monster_type, monster_type);
	m_imagePath = "monster/monster_%d/monster_%d_%d.png";

	if (!Sprite::initWithFile(formate))
	{
		return false;
	}
	m_MaxHp = hp;
	m_MoveRange = moveRange;
	m_Range = range;
	m_Hero = hero;
	m_hp = m_MaxHp;
	m_shootSpeed = shootSpeed;
	m_damage = damage;
	m_MonsterType = monster_type;
	m_bullet_type = bullet_type;
	m_MoveSpeed = moveSpeed;
	setLocalZOrder(3);
	return true;
}

void Enemy::setIsLive(bool val)
{
	m_IsLive = val;
	if (!m_IsLive)
	{
		char formate[128] = { 0 };
		sprintf(formate, "monster/monster_%d/monster_%d_6.png", m_MonsterType, m_MonsterType);
		Sprite* dieSp = Sprite::create(formate);
		dieSp->setLocalZOrder(2);
		this->getParent()->addChild(dieSp);
		AnimationEffect* dieEffect = AnimationEffect::create(0, 1, "monsterSpawnEffect/EnemyDeathEffect.png", 1, 1);
		dieEffect->setScale(0.1);
		dieEffect->runAction(ScaleTo::create(0.3, 1.0f));
		dieSp->addChild(dieEffect);
		dieEffect->setPosition(dieSp->getContentSize().width + 5, dieSp->getContentSize().height + 5);
		dieEffect->setLocalZOrder(2);
		dieSp->setPosition(this->getPosition());
		AnimationEffect* effect = AnimationEffect::create(0, 4, "monsterSpawnEffect/monsterSpawnEffect_%d.png", 0.06f, 1);
		effect->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
		this->getParent()->addChild(effect);
		effect->setPosition(this->getPositionX(), this->getPositionY() - this->getContentSize().height / 2);
		Action* act = Sequence::create(DelayTime::create(3.0f), FadeOut::create(1.0f), RemoveSelf::create(), nullptr);
		effect->runAction(act);
		dieSp->runAction(act->clone());
	}
}
void Enemy::initMonsterInfo()
{

	setColor(Color3B::WHITE);

	m_hp = m_MaxHp;
	char formate[128] = { 0 };
	sprintf(formate, "monster/monster_%d/monster_%d_", m_MonsterType, m_MonsterType);
	char stringEnd[16] = "%d.png";
	strcat(formate, stringEnd);
	Animate* animate = AnimateTools::create(0, 6, formate, 0.12f, -1);

	Enemy::startShoot();
	Enemy::startMove();
	this->runAction(animate);
}
void Enemy::startShoot(){
	this->schedule(schedule_selector(Enemy::shoot), m_shootSpeed, -1, 0);
}

void Enemy::startMove()
{
	this->schedule(schedule_selector(Enemy::findHero),1 , -1, 0);
}
void Enemy::sethero(Hero* hero)
{
	m_Hero = hero;
}
void Enemy::shoot(float dt){
	static float Ht = 0;
	Ht += dt;
	if (m_Hero!=nullptr&&m_Hero->getPosition().distance(this->getPosition())<=m_Range)
	{
		
		Vec2 const hero_pos = m_Hero->getPosition();
		Vec2 const pos = this->getPosition() - hero_pos;
		float angel;
		angel = (-pos.getAngle() * 180 / _Pi);
		int const x = abs(this->getPosition().x - m_Hero->getPosition().x);
		int const y = abs(this->getPosition().y - m_Hero->getPosition().y);
		if (x < 20 && y < 20 && Ht > 1) {
			SimpleAudioEngine::getInstance()->playBackgroundMusic("music/fx_shoot.wav");
			int hp = m_Hero->getHp() - 15;
			m_Hero->setHp(hp);
			Ht = 0;
		}
		this->getBoundingBox();
	}
}

void Enemy::setHp(const int& hp)
{
	m_hp = hp;
	m_hp = m_hp <= 0 ? 0 : m_hp;
	if (m_hp <= 0)
	{
		setIsLive(false);
	}
	else
	{
		TintTo* tinto = TintTo::create(0.1, 255, 0, 0);
		TintTo* tout = TintTo::create(0.1, 255,255, 255);
		runAction(Sequence::create(tinto, tout, nullptr));
	}
}

void Enemy::randMove(float dt)
{
	int rand_x = -1 + rand() % 3;
	int rand_y = -1 + rand() % 3;
	MyStar star;
	TMXTiledMap* m_Map = (TMXTiledMap*)this->getParent();

	Vec2 const monsterPosInMap = TMXTools::transformPosInMap(this->getPosition(), m_Map);
	Vec2 const monsterPosIndex = TMXTools::getPosIndexInMap(monsterPosInMap,m_Map);
	rand_x += monsterPosIndex.x;
	rand_y += monsterPosIndex.y;
	while (!star.isRoad(rand_x, rand_y, m_Map))
	{
		rand_x = -1 + rand() % 3;
		rand_y = -1 + rand() % 3;
		CCLOG("x = %d,y = %d,", rand_x, rand_y);
		rand_x += monsterPosIndex.x;
		rand_y += monsterPosIndex.y;

	}
	int const x = rand_x * m_Map->getTileSize().width + m_Map->getTileSize().width / 2;
	int const y = (m_Map->getMapSize().height - rand_y) * m_Map->getTileSize().height - m_Map->getTileSize().height / 2;
	float const time = Vec2(x, y).distance(this->getPosition()) / this->getMoveSpeed();
	this->stopActionByTag(monsterMoveKey);
	MoveTo* moveTo = MoveTo::create(time, Vec2(x, y));
	FlipX* flip;
	if (rand_x - monsterPosIndex.x > 0){

		flip = FlipX::create(false);
	}

	else{

		flip = FlipX::create(true);
	}
	Sequence* seq = Sequence::create(flip,moveTo,nullptr);
	seq->setTag(monsterMoveKey);
	this->runAction(seq);
}
void Enemy::findHero(float dt){
		if (this->getPosition().distance(m_Hero->getPosition()) <= this->getMoveRange()){
			MyStar mystar;
			TMXTiledMap* m_Map = (TMXTiledMap*)this->getParent();
			Vec2 const monsterPosInMap = TMXTools::transformPosInMap(this->getPosition(), m_Map);
			Vec2 const monsterPosIndex = TMXTools::getPosIndexInMap(monsterPosInMap, m_Map);
			Vec2 const heroPosInMap = TMXTools::transformPosInMap(m_Hero->getPosition(), m_Map);
			Vec2 const heroPosIndex = TMXTools::getPosIndexInMap(heroPosInMap, m_Map);
			Size const winSize = Director::getInstance()->getWinSize();
			Vec2 const monsterPosInWorld(this->getPositionX() + m_Map->getPositionX(), this->getPositionY() + m_Map->getPositionY());
			std::list<MyPoint*>& _path = mystar.findPath(monsterPosIndex, heroPosIndex, m_Map);
			Vector<FiniteTimeAction*> vArray;

			bool const isEmpty = _path.empty();
			while (!_path.empty())
			{
				MyPoint* const point = _path.back();

				int const x = point->x * m_Map->getTileSize().width + m_Map->getTileSize().width / 2;
				int const y = (m_Map->getMapSize().height - point->y) * m_Map->getTileSize().height - m_Map->getTileSize().height / 2;

				float const time = Vec2(x, y).distance(this->getPosition()) / this->getMoveSpeed();
				MoveTo* moveTo = MoveTo::create(time, Vec2(x, y));
				FlipX* flip;

				float const xx = point->x;
				if (xx - monsterPosIndex.x > 0){

					flip = FlipX::create(false);
				}

				else{

					flip = FlipX::create(true);
				}
				_path.pop_back();
				// 添加到数组
				vArray.pushBack(flip);
				vArray.pushBack(moveTo);
			}
			// 根据数组创建序列动画
			if (!isEmpty){
				Sequence* move = Sequence::create(vArray);
				move->setTag(monsterMoveKey);
				// 执行动作
				this->runAction(move);

			}
		}
		else{

			randMove(0.1f);
		}

}