#include "MyStar.h"
using namespace cocos2d;
// Ѱ��·������㣻�յ㣩
list<MyPoint*>& MyStar::findPath(cocos2d::Vec2 spos, cocos2d::Vec2 epos, cocos2d::TMXTiledMap* map)
{
	clearList();

	// �յ�
	endPos = new MyPoint;
	endPos->x = epos.x;
	endPos->y = epos.y;
	// ���
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
	// �������뵽open��
	_open.push_back(startPos);

	while (!_open.empty())
	{
		// 1.ȡ��open����Fֵ��С�ĵ�
		MyPoint* curPos = findMinF();
		// ��open���Ƴ�
		_open.remove(curPos);
		// ���뵽close��
		_close.push_back(curPos);

		// 2.������ǰ����Χ8����
		for (int i = -1; i <= 1; i++)
		{
			for (int j = -1; j <= 1 ; j++)
			{
				if (i == 0 && j == 0)
					continue;
				MyPoint* pos = new MyPoint;
				pos->x = curPos->x + i;
				pos->y = curPos->y + j;
				// �ж��ǲ����յ�
				if (pos->x == endPos->x && pos->y == endPos->y)
				{
					// �յ㸳ֵ���ڵ㡣
					endPos->parent = curPos;

					// ��ȡ·������
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
				// �ǲ���·
				if (isRoad(pos->x,pos->y,map))
				{
					// �ж��ǲ�����close��
					if (!isInClose(pos))
					{
						// �ж��ǲ�����open��
						int x = map->getTileSize().width;
						int y = map->getTileSize().height;
						int r = sqrt(x*x + y * y);
						if (MyPoint* ptInOpen = isInOpen(pos))// ��
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
						else // ����
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
						// �ϰ���
						delete pos;
						pos = nullptr;
					}
				}
				else
				{
					// �ϰ���
					delete pos;
					pos = nullptr;
				}
			}
		}
	}

	return _path;
}

// �ж��ǲ���·
bool MyStar::isRoad(int x, int y, cocos2d::TMXTiledMap* map)
{
	TMXLayer* layer = map->getLayer("walk");
	if (0 != layer->getTileGIDAt(Vec2(x, y)))
	{
		return false;
	}
	return true;
}

// �ж��ǲ�����close��
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

// �ж��ǲ�����open������ڷ��س���ǰ��,���ڷ��ؿ�
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
// Ѱ��open����Fֵ��С�ĵ�
MyPoint* MyStar::findMinF()
{
	// �����һ��Fֵ��С
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

// �������
void MyStar::clearList()
{
	while (!_open.empty())
	{
		// ɾ����һ��Ԫ��
		delete _open.front();
		// �ͷ�����ĵ�һ��Ԫ��
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