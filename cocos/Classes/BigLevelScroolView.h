#pragma once
//#include "MyHead.h"

#include "cocos2d.h"
USING_NS_CC;

class BigLevelScroolView : public CCLayerColor
{
private:
	// ���µ�
	CCPoint m_pTouchDownPoint;
	// ̧��� ���ʹ���ж��Ƿ�Ϊ����¼�
	CCPoint m_pTouchUpPoint;
	// ��ǰ������
	CCPoint m_pTouchCurPoint;

	int m_nCurSelectItem;			//��ǰ������ѡ����һ��ID
	timeval m_pStarTime;
	timeval m_pEndTime;
	CCRect m_rRectTouchSize;		//������������λ�� ��С
	float m_fItemWidth;				//С�� ���
	float m_fItemHeight;
	float deltaX;					//С����
	CCLayerColor* m_pContainerLayer;		//����
	float maxMove;					//�ƶ���Layerλ�������Сֵ
	float minMove;
	bool bXiFu;						//�Ƿ�����
	float scale;

	SEL_MenuHandler clickHandler;
	SEL_MenuHandler selectHandler;
	CCObject* origion;

	bool isTouchInsideNode(CCNode* node, cocos2d::CCTouch *pTouch);
	float needMoveDisOfItem(int showIndex);
	int getNearestItem(float x);


	CC_SYNTHESIZE_RETAIN(CCArray*, m_pAllNodes, m_pAllNodes); 	// �洢����ҳ��
public:
	BigLevelScroolView();
	virtual ~BigLevelScroolView();
	virtual bool init();
	void initLayer(CCRect m_rRectTouchSize, float m_fItemWidth, float m_fItemHeight, float deltaX, bool xifu, float scale, SEL_MenuHandler handler, SEL_MenuHandler selectHandler, CCObject* object);
	CREATE_FUNC(BigLevelScroolView);

	void addNode(CCNode* node);
	void update(float dt);
	void goToShowItem(int item);
};