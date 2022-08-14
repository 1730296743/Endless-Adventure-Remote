#ifndef _TMXTools_H_
#define _TMXTools_H_
#include"cocos2d.h"
class TMXTools
{
public:

	//目标需和map同一父节点
	// 将目标坐标转换为在地图上的坐标系
	static cocos2d::Vec2 transformPosInMap(const cocos2d::Vec2& pos, cocos2d::TMXTiledMap* map);

	//将目标坐标做换为世界坐标
	static cocos2d::Vec2 transfromPosToWorld(const cocos2d::Vec2& pos, cocos2d::TMXTiledMap* map);

	//获得目标在地图中对应的索引值
	static cocos2d::Vec2 getPosIndexInMap(const cocos2d::Vec2& pos, cocos2d::TMXTiledMap* map);

	//获取目标位置在地图中对应的层上索引值对应的id值
	static int getPosIdInMap(const cocos2d::Vec2& pos, cocos2d::TMXTiledMap* map, const std::string& layerName);

	//获取表在层上对应索引值对应的id值

	static int getPosIdInLayer(const cocos2d::Vec2& pos, cocos2d::TMXLayer* layer);

	/*是否与地图中对应index值的块碰撞*/
	static bool isColliderInMapWith(cocos2d::Vec2 posInMap, cocos2d::TMXTiledMap* map, const std::string& layerName, int index);

	//是否与层中对应index值的块碰撞
	static bool isColliderInLayerWith(cocos2d::Vec2 posInMap, cocos2d::TMXLayer* layer, int index);
};

#endif