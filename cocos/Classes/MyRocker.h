#ifndef _MyRocker_H_
#define _MyRocker_H_
#include "cocos2d.h"
// ҡ��״̬ö��
enum ROCKER_STATE
{
	ROCKER_STAY,
	ROCKER_UP,
	ROCKER_DOWN,
	ROCKER_LEFT,
	ROCKER_RIGHT
};
class MyRocker : public cocos2d::Layer
{
private:
	// ҡ��״̬
	ROCKER_STATE state;
	// ҡ�˱���
	cocos2d::Sprite* m_spRockerBG;
	// ҡ��
	cocos2d::Sprite* m_spRocker;
	// ���㴥���¼�������
	cocos2d::EventListenerTouchOneByOne* touchOneByOne;
	// �Ƿ�����ҡ��
	bool m_isTouchRocker;
	//��̬��ȡ����
	cocos2d::Vec2 getRockerPos(cocos2d::Vec2 touchPos);

public:
	//��ȡҡ��
	cocos2d::Vec2 getDirection();
	// ��ȡҡ�˵�״̬
	ROCKER_STATE getState();
public:
	virtual void setPosition(const cocos2d::Vec2& pos) override
	{
		m_spRockerBG->setPosition(pos);
		m_spRocker->setPosition(pos);
	}
	static MyRocker* create(const std::string& rockerbgfilename,
		const std::string& rockerfilename,
		const cocos2d::Vec2& pos);
	virtual bool init(const std::string& rockerbgfilename,
		const std::string& rockerfilename,
		const cocos2d::Vec2& pos);
};
#endif