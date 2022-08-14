#ifndef __MENU_LAYER_H__
#define __MENU_LAYER_H__
#include"cocos2d.h"
USING_NS_CC;
#include"ui\CocosGUI.h"
#include "MainInterface.h"
using namespace cocos2d::ui;
class MenuLayer :public Layer{

public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(MenuLayer);
	void onClickCallBack(Ref* ref);
	void onSelectCallBack(Ref* ref);
	void onClickCallFunc(int grade,int Level);
	void BackMainInterface(Ref* pSender);
};
#endif