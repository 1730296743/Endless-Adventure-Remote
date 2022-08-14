#ifndef _Manager_H_
#define _Manager_H_
#include"HeroBullet.h"
#include "Enemy.h"
#include"cocos2d.h"
#include<list>
using namespace std;
class Manager{
private:
	static Manager* pInstance;

public:
	static Manager* getInstance();

	void destroyInstance()
	{
		delete pInstance;
		pInstance = nullptr;
	}
	list<HeroBullet*> _objPool;

	// π÷ŒÔ¡¥±Ì
	list<Enemy*> _enemyObjPool;

};
#endif