#include"TMXTools.h"
cocos2d::Vec2 TMXTools::transformPosInMap(const cocos2d::Vec2& pos, cocos2d::TMXTiledMap* map)
{
	float xInMap = pos.x;
	float mapH = map->getTileSize().height*map->getMapSize().height;
	float yInMap = mapH - pos.y;
	return cocos2d::Vec2(xInMap, yInMap);
}

cocos2d::Vec2 TMXTools::transfromPosToWorld(const cocos2d::Vec2& pos, cocos2d::TMXTiledMap* map)
{
	float xInWorld = pos.x;
	float mapH = map->getTileSize().height*map->getMapSize().height;
	float yInWorld = pos.y+mapH;
	return cocos2d::Vec2(xInWorld, yInWorld);

}
cocos2d::Vec2 TMXTools::getPosIndexInMap(const cocos2d::Vec2& pos, cocos2d::TMXTiledMap* map)
{
	int xIndex = pos.x / map->getTileSize().width;
	int yIndex = pos.y / map->getTileSize().height;
	return cocos2d::Vec2(xIndex, yIndex);
}
int TMXTools::getPosIdInMap(const cocos2d::Vec2& posInMap, cocos2d::TMXTiledMap* map, const std::string& layerName)
{
	cocos2d::TMXLayer* layer = map->getLayer(layerName);
	int gid = layer->getTileGIDAt(posInMap);
	return gid;
}

int TMXTools::getPosIdInLayer(const cocos2d::Vec2& posInMap, cocos2d::TMXLayer* layer)
{
	int gid = layer->getTileGIDAt(posInMap);
	return gid;
}
bool TMXTools::isColliderInMapWith(cocos2d::Vec2 posInMap, cocos2d::TMXTiledMap* map, const std::string& layerName, int index)
{
	int indexInMap = getPosIdInMap(posInMap, map, layerName);
	return indexInMap == index;
}


bool  TMXTools::isColliderInLayerWith(cocos2d::Vec2 posInMap, cocos2d::TMXLayer* layer, int index)
{
	int indexInMap = getPosIdInLayer(posInMap, layer);
	return indexInMap == index;
}