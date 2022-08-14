#ifndef _MyRocker_H_
#define _MyRocker_H_
#include "cocos2d.h"
// Ò¡¸Ë×´Ì¬Ã¶¾Ù
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
	// Ò¡¸Ë×´Ì¬
	ROCKER_STATE state;
	// Ò¡¸Ë±³¾°
	cocos2d::Sprite* m_spRockerBG;
	// Ò¡¸Ë
	cocos2d::Sprite* m_spRocker;
	// µ¥µã´¥ÃþÊÂ¼þ¼àÌýÆ÷
	cocos2d::EventListenerTouchOneByOne* touchOneByOne;
	// ÊÇ·ñ´¥Åöµ½Ò¡¸Ë
	bool m_isTouchRocker;
	//¶¯Ì¬»ñÈ¡×ø±ê
	cocos2d::Vec2 getRockerPos(cocos2d::Vec2 touchPos);

public:
	//»ñÈ¡Ò¡¸Ë
	cocos2d::Vec2 getDirection();
	// »ñÈ¡Ò¡¸ËµÄ×´Ì¬
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