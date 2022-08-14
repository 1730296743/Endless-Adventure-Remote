#include "MyRocker.h"
using namespace cocos2d;
MyRocker* MyRocker::create(const std::string& rockerbgfilename,const std::string& rockerfilename,const Vec2& pos){
	MyRocker* pMyRocker = new MyRocker;
	if (pMyRocker && pMyRocker->init(rockerbgfilename, rockerfilename, pos)){
		pMyRocker->autorelease();
	}
	else{
		delete pMyRocker;
		pMyRocker = nullptr;
	}
	return pMyRocker;
}
bool MyRocker::init(const std::string& rockerbgfilename,const std::string& rockerfilename,const Vec2& pos){

	if (!Layer::init()){
		return false;
	}
	m_isTouchRocker = false;
	state = ROCKER_STAY;

	// ҡ�˱���
	m_spRockerBG = Sprite::create(rockerbgfilename);

	m_spRockerBG->setLocalZOrder(5);
	this->addChild(m_spRockerBG);
	m_spRockerBG->setPosition(pos);
	// ҡ��
	m_spRocker = Sprite::create(rockerfilename);

	m_spRocker->setLocalZOrder(5);
	this->addChild(m_spRocker);
	m_spRocker->setPosition(pos);
	// 1.��ʼ�����㴥���¼�������
	touchOneByOne = EventListenerTouchOneByOne::create();
	touchOneByOne->onTouchBegan = [&](Touch* touch, Event* event)
	{
		// 1.��ȡ����������
		Vec2 touchpos = touch->getLocation();
		
		// 2.��ȡҡ�˵İ�Χ��
		Rect boundingbox = m_spRocker->getBoundingBox();
		// 3.�жϰ�Χ���Ƿ��������������
		if (boundingbox.containsPoint(touchpos))
		{
			m_isTouchRocker = true;
			m_spRocker->setOpacity(100);
			m_spRockerBG->setOpacity(100);
		}

		return true; 
	};
	touchOneByOne->onTouchMoved = [&](Touch* touch, Event* event)
	{
		// �������д�����ҡ��
		if (m_isTouchRocker)
		{
			// 1.��ȡ����������
			Vec2 pos = touch->getLocation();
			//CCLOG("%f,%f", pos.x, pos.y);
			// 2.�жϴ������Ƿ���ҡ�˱�����Χ��
			// �����㵽Բ�ĵľ���
			float dis = pos.distance(m_spRockerBG->getPosition());
			// Բ�İ뾶
			float r = m_spRockerBG->getContentSize().width / 2;
			if (dis < r)
			{
				// 2.1 �ڣ�ҡ�˸�����ָ�ƶ�
				m_spRocker->setPosition(pos);
			}
			else
			{
				// 2.2.���ڣ���̬��ȡ�������ø�ҡ��
				m_spRocker->setPosition(getRockerPos(pos));
			}

			// ������ָ��λ����ȷ��ҡ�˵�״̬
			pos -= m_spRockerBG->getPosition();
			if (pos.y / pos.x >= 1 || pos.y / pos.x <= -1)
			{
				if (pos.y > 0)
				{
					state = ROCKER_UP;
				}
				else
				{
					state = ROCKER_DOWN;
				}
			}
			else if (pos.y / pos.x<1 && pos.y / pos.x>-1)
			{
				if (pos.x > 0)
				{
					state = ROCKER_RIGHT;
				}
				else
				{
					state = ROCKER_LEFT;
				}
			}
		}
	};
	touchOneByOne->onTouchEnded = [&](Touch* touch, Event* event)
	{
		// 1.�Ƿ�����ҡ�˻�ԭ
		m_isTouchRocker = false;
		// 2.ҡ��λ�û�ԭ
		m_spRocker->setPosition(m_spRockerBG->getPosition());
		//m_spRocker->runAction(MoveTo::create(0.1, m_spRockerBG->getPosition()));
		// 3.��ԭҡ��״̬
		state = ROCKER_STAY;
		m_spRocker->setOpacity(255);

		m_spRockerBG->setOpacity(255);
	};
	// 2.��ӵ��¼��ַ���
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchOneByOne,this);


	return true;
}

//��̬��ȡ����
Vec2 MyRocker::getRockerPos(Vec2 touchPos)
{
	// ������
	float R = touchPos.distance(m_spRockerBG->getPosition());
	float X = touchPos.x - m_spRockerBG->getPositionX();
	float Y = touchPos.y - m_spRockerBG->getPositionY();
	// С������
	float r = m_spRockerBG->getContentSize().width/2;
	float x = r / R*X;
	float y = r / R*Y;

	x += m_spRockerBG->getPositionX();
	y += m_spRockerBG->getPositionY();

	return Vec2(x, y);
}
// ��ȡҡ�˵�״̬
ROCKER_STATE MyRocker::getState()
{
	return state;
}

Vec2 MyRocker::getDirection()
{
	float x = m_spRocker->getPositionX() - m_spRockerBG->getPositionX();
	float y = m_spRocker->getPositionY() - m_spRockerBG->getPositionY();
	Vec2 vec2(x, y);
	vec2.normalize();
	return vec2;
}