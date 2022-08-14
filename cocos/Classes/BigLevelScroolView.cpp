#include "BigLevelScroolView.h"

BigLevelScroolView::BigLevelScroolView() : m_pTouchDownPoint(Vec2::ZERO), m_pTouchUpPoint(Vec2::ZERO), m_pTouchCurPoint(Vec2::ZERO), m_pAllNodes(NULL),
m_nCurSelectItem(0), m_pContainerLayer(NULL), deltaX(0), origion(NULL)
{
}

BigLevelScroolView::~BigLevelScroolView()
{
	CC_SAFE_RELEASE_NULL(m_pAllNodes);
	this->unscheduleUpdate();
}

bool BigLevelScroolView::init()
{
	if (!CCLayerColor::init())
	{
		return false;
	}

	auto listener1 = EventListenerTouchOneByOne::create();
	// 设置是否吞没事件，在 onTouchBegan 方法返回 true 时吞没
	listener1->setSwallowTouches(true);
	listener1->onTouchBegan = [this](Touch* pTouch, Event* event){
		m_pTouchDownPoint = pTouch->getLocation();
		if (m_rRectTouchSize.containsPoint(m_pTouchDownPoint))
		{
			m_pTouchCurPoint = m_pTouchDownPoint;
			gettimeofday(&m_pStarTime, NULL);
			return true;
		}
		else
		{
			return false;
		}
		return true;
	};
	listener1->onTouchMoved = [this](Touch* pTouch, Event* event){
		CCPoint touchPoint = pTouch->getLocation();
		CCPoint posPoint = CCPointMake(m_pContainerLayer->getPositionX() + touchPoint.x - m_pTouchCurPoint.x, m_pContainerLayer->getPositionY());

		if (posPoint.x < (minMove - 30))
		{
			posPoint.x = minMove - 30;
		}
		if (posPoint.x >(maxMove + 30))
		{
			posPoint.x = maxMove + 30;
		}

		m_pContainerLayer->setPosition(posPoint);
		m_pTouchCurPoint = touchPoint;
	};
	listener1->onTouchEnded = [this](Touch* pTouch, Event* event){

		gettimeofday(&m_pEndTime, NULL);

		m_pTouchUpPoint = pTouch->getLocation();
		// 计算按下和抬起的偏移量
		float const offset = (m_pTouchUpPoint.x - m_pTouchDownPoint.x) * (m_pTouchUpPoint.x - m_pTouchDownPoint.x) + (m_pTouchUpPoint.y - m_pTouchDownPoint.y) * (m_pTouchUpPoint.y - m_pTouchDownPoint.y);

		if (offset < (5 * 5)) {

			for (int i = 0; i< m_pAllNodes->count(); i++)
			{
				CCNode* node = (CCNode*)m_pAllNodes->objectAtIndex(i);

				if (isTouchInsideNode(node, pTouch)){
					goToShowItem(i);

					if (origion){
						this->setTag(i);
						(origion->*clickHandler)(this);
					}
				}
			}
		}
		else {

			double time = (((&m_pEndTime)->tv_sec*1000.0 + (&m_pEndTime)->tv_usec / 1000.0) - ((&m_pStarTime)->tv_sec*1000.0 + (&m_pStarTime)->tv_usec / 1000.0));
			float d = m_pTouchUpPoint.x - m_pTouchDownPoint.x;
			float speed = d / time * 1000;
			float a = 1500;
			float absSpeed = fabs(speed);

			float t = absSpeed / a;
			//距离
			float x = 0.5f*a*t*t;
			if (x >800){
				x = 800;
				t = 0.8f;
			}
			x = speed <0 ? -x : x;
			x = x + m_pContainerLayer->getPositionX();

			if (bXiFu){
				x = needMoveDisOfItem(getNearestItem(x));

			}
			if (x < minMove){
				x = minMove;
			}
			if (x > maxMove){
				x = maxMove;
			}
			if (t > 0.5){
				t = 0.5f;
			}

			this->setTag(getNearestItem(x));
			(origion->*selectHandler)(this);

			m_pContainerLayer->runAction(CCEaseBackOut::create(CCMoveTo::create(t, ccp(x, m_pContainerLayer->getPositionY()))));
		}

	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener1, this);

	this->setTouchEnabled(true);
	this->scheduleUpdate();
	this->setm_pAllNodes(CCArray::createWithCapacity(1));
	return true;
}


void BigLevelScroolView::update(float dt)
{
	int const nearestItemIndex = getNearestItem(m_pContainerLayer->getPositionX());

	float const dis = fabs(m_rRectTouchSize.size.width / 2 - m_pContainerLayer->getPositionX()) - (nearestItemIndex * (m_fItemWidth + deltaX * 2) + m_fItemWidth / 2 + deltaX);

	

	/**/float scaleTemp = fabs(dis) / (m_fItemWidth / 2 + deltaX);

	for (int i = 0; i<m_pAllNodes->count(); i++)
	{
		((CCNode*)m_pAllNodes->objectAtIndex(i))->setScale(scale);
	}

	if ((1 - scaleTemp) > 1)
	{
		scaleTemp = 0;
	}
	else if ((1 - scaleTemp) < scale)
	{
		scaleTemp = 1 - scale;
	}

	((CCNode*)m_pAllNodes->objectAtIndex(nearestItemIndex))->setScale(1 - scaleTemp);

}

void BigLevelScroolView::initLayer(CCRect m_rRectTouchSize, float m_fItemWidth, float m_fItemHeight, float deltaX, bool bXiFu, float scale, SEL_MenuHandler clickHandler, SEL_MenuHandler selectHandler, CCObject* object)
{
	this->origion = object;
	this->clickHandler = clickHandler;
	this->selectHandler = selectHandler;
	this->m_rRectTouchSize = m_rRectTouchSize;
	this->m_fItemWidth = m_fItemWidth;
	this->m_fItemHeight = m_fItemHeight;
	this->deltaX = deltaX;
	this->bXiFu = bXiFu;
	this->scale = scale;

	this->ignoreAnchorPointForPosition(false);
	this->setAnchorPoint(ccp(0, 1));

	m_pContainerLayer = CCLayerColor::create(ccc4(0, 255, 0, 0));
	m_pContainerLayer->ignoreAnchorPointForPosition(false);
	m_pContainerLayer->setAnchorPoint(ccp(0, 0));
	m_pContainerLayer->setPosition(ccp(0, 0));

	this->addChild(m_pContainerLayer);
}

void BigLevelScroolView::addNode(CCNode* node)
{
	node->setPositionX(node->getTag() * (m_fItemWidth + deltaX * 2) + m_fItemWidth / 2 + deltaX);
	node->setPositionY(m_fItemHeight / 2);
	//node->setPositionY(  -200 );
	m_pAllNodes->addObject(node);
	m_pContainerLayer->addChild(node);

	maxMove = m_rRectTouchSize.size.width / 2 - (m_fItemWidth / 2 + deltaX);
	minMove = -((m_fItemWidth + deltaX * 2) * m_pAllNodes->count() - m_rRectTouchSize.size.width + m_rRectTouchSize.size.width / 2 - (m_fItemWidth / 2 + deltaX));
}
/****/

void BigLevelScroolView::goToShowItem(int item)
{
	float f = needMoveDisOfItem(item);
	m_pContainerLayer->runAction(CCEaseBackOut::create(CCMoveTo::create(0.2f, ccp(f, m_pContainerLayer->getPositionY()))));
}

float BigLevelScroolView::needMoveDisOfItem(int showIndex)
{
	float showX = showIndex * (m_fItemWidth + deltaX * 2) + m_fItemWidth / 2 + deltaX;

	float needMove = m_rRectTouchSize.size.width / 2 - showX;

	return needMove;
}

int BigLevelScroolView::getNearestItem(float x)
{
	int item = (m_rRectTouchSize.size.width / 2 - x) / (m_fItemWidth + deltaX * 2);

	if (item < 0)
	{
		item = 0;
	}if (item >= m_pAllNodes->count())
	{
		item = m_pAllNodes->count() - 1;
	}
	return item;
}

bool BigLevelScroolView::isTouchInsideNode(CCNode* node, cocos2d::CCTouch *pTouch)
{
	CCPoint touchLocation = pTouch->getLocation(); // Get the touch position
	touchLocation = node->getParent()->convertToNodeSpace(touchLocation);
	CCRect bBox = node->boundingBox();
	return bBox.containsPoint(touchLocation);
}