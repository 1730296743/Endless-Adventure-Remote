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

	// 摇杆背景
	m_spRockerBG = Sprite::create(rockerbgfilename);

	m_spRockerBG->setLocalZOrder(5);
	this->addChild(m_spRockerBG);
	m_spRockerBG->setPosition(pos);
	// 摇杆
	m_spRocker = Sprite::create(rockerfilename);

	m_spRocker->setLocalZOrder(5);
	this->addChild(m_spRocker);
	m_spRocker->setPosition(pos);
	// 1.初始化单点触摸事件监听器
	touchOneByOne = EventListenerTouchOneByOne::create();
	touchOneByOne->onTouchBegan = [&](Touch* touch, Event* event)
	{
		// 1.获取触摸点坐标
		Vec2 touchpos = touch->getLocation();
		
		// 2.获取摇杆的包围盒
		Rect boundingbox = m_spRocker->getBoundingBox();
		// 3.判断包围盒是否包含触摸点坐标
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
		// 建立在有触摸到摇杆
		if (m_isTouchRocker)
		{
			// 1.获取触摸点坐标
			Vec2 pos = touch->getLocation();
			//CCLOG("%f,%f", pos.x, pos.y);
			// 2.判断触摸点是否在摇杆背景范围内
			// 触摸点到圆心的距离
			float dis = pos.distance(m_spRockerBG->getPosition());
			// 圆的半径
			float r = m_spRockerBG->getContentSize().width / 2;
			if (dis < r)
			{
				// 2.1 在：摇杆跟随手指移动
				m_spRocker->setPosition(pos);
			}
			else
			{
				// 2.2.不在：动态获取坐标设置给摇杆
				m_spRocker->setPosition(getRockerPos(pos));
			}

			// 根据手指的位置来确定摇杆的状态
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
		// 1.是否触碰到摇杆还原
		m_isTouchRocker = false;
		// 2.摇杆位置还原
		m_spRocker->setPosition(m_spRockerBG->getPosition());
		//m_spRocker->runAction(MoveTo::create(0.1, m_spRockerBG->getPosition()));
		// 3.还原摇杆状态
		state = ROCKER_STAY;
		m_spRocker->setOpacity(255);

		m_spRockerBG->setOpacity(255);
	};
	// 2.添加到事件分发器
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchOneByOne,this);


	return true;
}

//动态获取坐标
Vec2 MyRocker::getRockerPos(Vec2 touchPos)
{
	// 大三角
	float R = touchPos.distance(m_spRockerBG->getPosition());
	float X = touchPos.x - m_spRockerBG->getPositionX();
	float Y = touchPos.y - m_spRockerBG->getPositionY();
	// 小三角形
	float r = m_spRockerBG->getContentSize().width/2;
	float x = r / R*X;
	float y = r / R*Y;

	x += m_spRockerBG->getPositionX();
	y += m_spRockerBG->getPositionY();

	return Vec2(x, y);
}
// 获取摇杆的状态
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