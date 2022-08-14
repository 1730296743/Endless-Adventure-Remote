#ifndef _TMXTools_H_
#define _TMXTools_H_
#include"cocos2d.h"
class TMXTools
{
public:

	//Ŀ�����mapͬһ���ڵ�
	// ��Ŀ������ת��Ϊ�ڵ�ͼ�ϵ�����ϵ
	static cocos2d::Vec2 transformPosInMap(const cocos2d::Vec2& pos, cocos2d::TMXTiledMap* map);

	//��Ŀ����������Ϊ��������
	static cocos2d::Vec2 transfromPosToWorld(const cocos2d::Vec2& pos, cocos2d::TMXTiledMap* map);

	//���Ŀ���ڵ�ͼ�ж�Ӧ������ֵ
	static cocos2d::Vec2 getPosIndexInMap(const cocos2d::Vec2& pos, cocos2d::TMXTiledMap* map);

	//��ȡĿ��λ���ڵ�ͼ�ж�Ӧ�Ĳ�������ֵ��Ӧ��idֵ
	static int getPosIdInMap(const cocos2d::Vec2& pos, cocos2d::TMXTiledMap* map, const std::string& layerName);

	//��ȡ���ڲ��϶�Ӧ����ֵ��Ӧ��idֵ

	static int getPosIdInLayer(const cocos2d::Vec2& pos, cocos2d::TMXLayer* layer);

	/*�Ƿ����ͼ�ж�Ӧindexֵ�Ŀ���ײ*/
	static bool isColliderInMapWith(cocos2d::Vec2 posInMap, cocos2d::TMXTiledMap* map, const std::string& layerName, int index);

	//�Ƿ�����ж�Ӧindexֵ�Ŀ���ײ
	static bool isColliderInLayerWith(cocos2d::Vec2 posInMap, cocos2d::TMXLayer* layer, int index);
};

#endif