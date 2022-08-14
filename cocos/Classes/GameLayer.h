// Ԥ���봦��
#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__

#include "cocos2d.h"
#include "Drop.h"
USING_NS_CC;
#include "Hero.h"
#include "MyRocker.h"

// ����״̬
enum CURRENT_BUTTON
{
	ROCKER,		// ҡ��
	ATTACK_BTN,	// ����
	JUMP_BTN,	// ��Ծ
	NONE_BTN	// ��״̬
};

class GameLayer : public Layer
{

private:
	// �������
	bool flag;
	bool flag1;
	bool flag3;

	// ��ť״̬
	CURRENT_BUTTON buttonState;
	CURRENT_BUTTON buttonState1;
	CURRENT_BUTTON buttonState3;


public:
	// ������ť
	Sprite* m_attackBtn;
	Sprite* m_attackBtn1;
	Sprite* m_attackBtn3;

	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GameLayer);
public:
	static int guanka;
	// �ؿ�
	static int s_iLv;
	// ��ͼ
	TMXTiledMap* m_Map;
	// Ӣ��
	Hero* m_pHero;
	// ҡ��
	MyRocker* m_pMyRocker;

	void HeroWalking();
	// Ӣ���ƶ�
	void setHeroMove(float dt);

	void update(float dt);
	static int jinengxuanzhe;
	static int role;
	void PerishMonister();


	void initMonster();
	~GameLayer();



	//��ʱ��
//	CREATE_FUNC(GameLayer);
	bool jieng1;
	int oldTime;  //����schedule��ʱ��ǰ��ʱ��
	int num;      //��ʱ
	virtual void update1(float dt);  //schedule��ʱ�����õķ���


	bool jieng2;
	int oldTime1;  //����schedule��ʱ��ǰ��ʱ��
	int num1;      //��ʱ
	virtual void update2(float dt);  //schedule��ʱ�����õķ���

	void Reward();
	void UpLevel();
};

#endif