#ifndef _MyStar_H_
#define _MyStar_H_
#include "cocos2d.h"
#include <list>
using namespace std;
struct MyPoint
{
	int x;
	int y;
	int f;
	int g;
	int h;
	MyPoint* parent;
};
class MyStar
{
public:
	// open表
	list<MyPoint*> _open;
	// close表
	list<MyPoint*> _close;
	// 路径表
	list<MyPoint*> _path;
	// 起点
	MyPoint *startPos;
	// 终点
	MyPoint *endPos;

	bool isRoad(int x, int y, cocos2d::TMXTiledMap* map);
public:
	list<MyPoint*>& findPath(cocos2d::Vec2 spos, cocos2d::Vec2 epos, cocos2d::TMXTiledMap* map);
private:
	// 寻找open表中F值最小的点
	MyPoint* findMinF();
	// 判断是不是路
	// 判断是不是在close表
	bool isInClose(MyPoint* pos);
	// 判断是不是在open表，如果在返回出当前点,不在返回空
	MyPoint* isInOpen(MyPoint* pos);
	// 清空链表
	void clearList();
};
#endif