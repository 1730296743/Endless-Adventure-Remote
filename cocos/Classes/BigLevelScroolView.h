#pragma once
//#include "MyHead.h"

#include "cocos2d.h"
USING_NS_CC;

class BigLevelScroolView : public CCLayerColor
{
private:
	// 按下点
	CCPoint m_pTouchDownPoint;
	// 抬起点 配合使用判断是否为点击事件
	CCPoint m_pTouchUpPoint;
	// 当前触摸点
	CCPoint m_pTouchCurPoint;

	int m_nCurSelectItem;			//当前滑动条选中那一行ID
	timeval m_pStarTime;
	timeval m_pEndTime;
	CCRect m_rRectTouchSize;		//整个滑动窗口位置 大小
	float m_fItemWidth;				//小项 宽高
	float m_fItemHeight;
	float deltaX;					//小项间隔
	CCLayerColor* m_pContainerLayer;		//容器
	float maxMove;					//移动的Layer位移最大，最小值
	float minMove;
	bool bXiFu;						//是否吸附
	float scale;

	SEL_MenuHandler clickHandler;
	SEL_MenuHandler selectHandler;
	CCObject* origion;

	bool isTouchInsideNode(CCNode* node, cocos2d::CCTouch *pTouch);
	float needMoveDisOfItem(int showIndex);
	int getNearestItem(float x);


	CC_SYNTHESIZE_RETAIN(CCArray*, m_pAllNodes, m_pAllNodes); 	// 存储所有页层
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