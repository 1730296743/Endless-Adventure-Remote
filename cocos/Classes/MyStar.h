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
	// open��
	list<MyPoint*> _open;
	// close��
	list<MyPoint*> _close;
	// ·����
	list<MyPoint*> _path;
	// ���
	MyPoint *startPos;
	// �յ�
	MyPoint *endPos;

	bool isRoad(int x, int y, cocos2d::TMXTiledMap* map);
public:
	list<MyPoint*>& findPath(cocos2d::Vec2 spos, cocos2d::Vec2 epos, cocos2d::TMXTiledMap* map);
private:
	// Ѱ��open����Fֵ��С�ĵ�
	MyPoint* findMinF();
	// �ж��ǲ���·
	// �ж��ǲ�����close��
	bool isInClose(MyPoint* pos);
	// �ж��ǲ�����open������ڷ��س���ǰ��,���ڷ��ؿ�
	MyPoint* isInOpen(MyPoint* pos);
	// �������
	void clearList();
};
#endif