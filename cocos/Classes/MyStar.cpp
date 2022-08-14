#include "MyStar.h"
using namespace cocos2d;
// 寻找路径（起点；终点）
list<MyPoint*>& MyStar::findPath(cocos2d::Vec2 spos, cocos2d::Vec2 epos, cocos2d::TMXTiledMap* map)
{
	clearList();

	// 终点
	endPos = new MyPoint;
	endPos->x = epos.x;
	endPos->y = epos.y;
	// 起点
	startPos = new MyPoint;
	startPos->x = spos.x;
	startPos->y = spos.y;
	startPos->g = 0;
	int x = map->getTileSize().width;
	int y = map->getTileSize().height;
	int r = sqrt(x*x + y * y);
	startPos->h = (abs(endPos->x - startPos->x) + abs(endPos->y - startPos->y)) * r;
	startPos->f = startPos->g + startPos->h;
	startPos->parent = nullptr;
	// 将起点加入到open表
	_open.push_back(startPos);

	while (!_open.empty())
	{
		// 1.取出open表中F值最小的点
		MyPoint* curPos = findMinF();
		// 从open中移除
		_open.remove(curPos);
		// 加入到close表
		_close.push_back(curPos);

		// 2.遍历当前点周围8个点
		for (int i = -1; i <= 1; i++)
		{
			for (int j = -1; j <= 1 ; j++)
			{
				if (i == 0 && j == 0)
					continue;
				MyPoint* pos = new MyPoint;
				pos->x = curPos->x + i;
				pos->y = curPos->y + j;
				// 判断是不是终点
				if (pos->x == endPos->x && pos->y == endPos->y)
				{
					// 终点赋值父节点。
					endPos->parent = curPos;

					// 获取路径链表
					_path.push_back(endPos);
					MyPoint* temp = endPos;
					while (temp->parent != nullptr)
					{
						_path.push_back(temp->parent);
						temp = temp->parent;
					}

					_path.pop_back();

					delete pos;
					pos = nullptr;
					return _path;
				}
				// 是不是路
				if (isRoad(pos->x,pos->y,map))
				{
					// 判断是不是在close表
					if (!isInClose(pos))
					{
						// 判断是不是在open表
						int x = map->getTileSize().width;
						int y = map->getTileSize().height;
						int r = sqrt(x*x + y * y);
						if (MyPoint* ptInOpen = isInOpen(pos))// 在
						{
							pos->g = curPos->g + (abs(i) != abs(j) ? x : r);
							if (pos->g < ptInOpen->g)
							{
								ptInOpen->g = pos->g;
								ptInOpen->f = ptInOpen->g + ptInOpen->h;
								ptInOpen->parent = curPos;
								delete pos;
								pos = nullptr;
							}
						}
						else // 不在
						{
							pos->g = curPos->g + (abs(i) != abs(j) ? x : r);
							pos->h = (abs(endPos->x - pos->x) + abs(endPos->y - pos->y)) * x;
							pos->f = pos->g + pos->h;
							pos->parent = curPos;
							_open.push_back(pos);
						}
					}
					else
					{
						// 障碍物
						delete pos;
						pos = nullptr;
					}
				}
				else
				{
					// 障碍物
					delete pos;
					pos = nullptr;
				}
			}
		}
	}

	return _path;
}

// 判断是不是路
bool MyStar::isRoad(int x, int y, cocos2d::TMXTiledMap* map)
{
	TMXLayer* layer = map->getLayer("walk");
	if (0 != layer->getTileGIDAt(Vec2(x, y)))
	{
		return false;
	}
	return true;
}

// 判断是不是在close表
bool MyStar::isInClose(MyPoint* pos)
{
	for (MyPoint* point : _close)
	{
		if (point->x == pos->x &&point->y == pos->y)
		{
			return true;
		}
	}
	return false;
}

// 判断是不是在open表，如果在返回出当前点,不在返回空
MyPoint* MyStar::isInOpen(MyPoint* pos)
{
	for (MyPoint* point : _open)
	{
		if (point->x == pos->x &&point->y == pos->y)
		{
			return point;
		}
	}
	return nullptr;
}
// 寻找open表中F值最小的点
MyPoint* MyStar::findMinF()
{
	// 假设第一个F值最小
	MyPoint* minF = _open.front();
	
	list<MyPoint*>::iterator itPoint = _open.begin();
	for (itPoint++; itPoint != _open.end(); itPoint++)
	{
		if ((*itPoint)->f < minF->f)
		{
			minF = *itPoint;
		}
	}
	return minF;
}

// 清空链表
void MyStar::clearList()
{
	while (!_open.empty())
	{
		// 删除第一个元素
		delete _open.front();
		// 释放链表的第一个元素
		_open.pop_front();
	}
	while (!_close.empty())
	{
		delete _close.front();
		_close.pop_front();
	}
	while (!_path.empty())
	{
		delete _path.front();
		_path.pop_front();
	}
}