#include "LogoLayer.h"
#include "ui/CocosGUI.h"
using namespace cocos2d::ui;
#include "Mouse.h"
int touchchumo = 0;

bool LogoLayer::touchBegan(Touch*touch, Event*event, Sprite* s, RepeatForever* rfMouse)//触摸开始，返回bool类型
{
	Vec2 pos = touch->getLocation();
	
	return true;
}
Scene* LogoLayer::createScene()
{
	// 创建空场景
	Scene* scene = Scene::create();
	// 创建logo层
	Layer* layer = LogoLayer::create();
	// 把层添加到场景上
	scene->addChild(layer);
	return scene;
}
bool LogoLayer::init()
{
	if ( !Layer::init() )
    {
        return false;
    }
	
	// 获取屏幕大小
	Size winSize = Director::getInstance()->getWinSize();
	//this->setColor(cocos2d::Color3B::BLUE);

	// 创建logo
	Sprite* spLogo = Sprite::create("llm/logo_Valley_of_the_Wind.png");
	// 添加到层

	this->addChild(spLogo);

	spLogo->setScale(0.5, 0.5);
	// 设置logo位置
	spLogo->setPosition(winSize.width / 2, winSize.height / 2);


	ScaleTo* scaleToBig = ScaleTo::create(1.0f, 1.0);
	ScaleTo* scaleToSmall = ScaleTo::create(1.0f, 0.5);

	Sequence* seq = Sequence::create(scaleToSmall, scaleToBig, nullptr);
	Repeat* rf = Repeat::create(seq, 1);
	spLogo->runAction(rf);


	CCActionInterval * actionTo = CCRotateTo::create(1, 180);//时间 度数
	CCActionInterval * actionTo2 = CCRotateTo::create(1, 360);
	CCActionInterval * actionTo0 = CCRotateTo::create(2, 0);


	spLogo->runAction(CCSequence::create(actionTo, actionTo2, NULL));

	FadeIn* logoIn = FadeIn::create(2.0f);
	auto* logoOut = FadeOut::create(3.0f);
	Sequence* seqMouse1 = Sequence::create(logoIn, logoOut, nullptr);
	RepeatForever* rfMouse1 = RepeatForever::create(seqMouse1);

	MoveTo* mLeft = MoveTo::create(1.50f, Vec2(50, winSize.height - 100));
	FlipX* fright = FlipX::create(true);
	MoveTo* mRight = MoveTo::create(0.9f, Vec2(winSize.width-50,winSize.height - 100));
	FlipX* fleft = FlipX::create(false);

	Sequence* seqMouse = Sequence::create(mLeft, fright, mRight, fleft, nullptr);

	RepeatForever* rfMouse= RepeatForever::create(seqMouse);


	
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true); //阻止向下传递

		// 动作回调
	CallFunc* callfunc = CallFunc::create([](){
		Director::getInstance()->replaceScene(SecondScene::CreateScene());
		// 切换场景代码
	});
	// 延时动作：空动作，什么都不执行，形参为时间。
	DelayTime* dt = DelayTime::create(6.0f);
	// 序列动作。按顺序执行
	Sequence* seq1 = Sequence::create(dt, callfunc, nullptr);
	// 执行动作
	this->runAction(seq1);
    return true;
}

