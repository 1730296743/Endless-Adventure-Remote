#pragma once

#ifndef __MA_LL_H__
#define __MA_LL_H__

#include "ui/CocosGUI.h"
#include "cocos2d.h"
#include <vector>
#include"MenuLayer.h"
#include "Hero.h"
#include "MainPart.h"
#include "MainInterface.h"
#include<stdlib.h>

class Mall : public cocos2d::Layer{
    CC_SYNTHESIZE(std::vector<std::string>, m_Mall, MMall);
public:

    static cocos2d::Scene* createScene();

    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(Mall);

    Label* coinNum;
private:
   
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    void CloseMall(Ref* pSender);

    void chushihua();

    void Mall::FlushCoin(float dt);
    
};

#endif // DEBUG