// 预编译处理
#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__

#include "cocos2d.h"
#include "Drop.h"
USING_NS_CC;
#include "Hero.h"
#include "MyRocker.h"

// 触摸状态
enum CURRENT_BUTTON
{
	ROCKER,		// 摇杆
	ATTACK_BTN,	// 攻击
	JUMP_BTN,	// 跳跃
	NONE_BTN	// 无状态
};

class GameLayer : public Layer
{

private:
	// 触摸标记
	bool flag;
	bool flag1;
	bool flag3;

	// 按钮状态
	CURRENT_BUTTON buttonState;
	CURRENT_BUTTON buttonState1;
	CURRENT_BUTTON buttonState3;


public:
	// 攻击按钮
	Sprite* m_attackBtn;
	Sprite* m_attackBtn1;
	Sprite* m_attackBtn3;

	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GameLayer);
public:
	static int guanka;
	// 关卡
	static int s_iLv;
	// 地图
	TMXTiledMap* m_Map;
	// 英雄
	Hero* m_pHero;
	// 摇杆
	MyRocker* m_pMyRocker;

	void HeroWalking();
	// 英雄移动
	void setHeroMove(float dt);

	void update(float dt);
	static int jinengxuanzhe;
	static int role;
	void PerishMonister();


	void initMonster();
	~GameLayer();



	//记时器
//	CREATE_FUNC(GameLayer);
	bool jieng1;
	int oldTime;  //调用schedule定时器前的时间
	int num;      //计时
	virtual void update1(float dt);  //schedule定时器调用的方法


	bool jieng2;
	int oldTime1;  //调用schedule定时器前的时间
	int num1;      //计时
	virtual void update2(float dt);  //schedule定时器调用的方法

	void Reward();
	void UpLevel();
};

#endif