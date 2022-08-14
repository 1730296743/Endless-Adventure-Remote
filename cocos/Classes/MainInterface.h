#pragma once
#pragma warning(disable: 4996)

#ifndef __MAIN_INTERFACE_H__
#define __MAIN_INTERFACE_H__

#include "ui/CocosGUI.h"
#include "cocos2d.h"
#include <vector>
#include"MenuLayer.h"
#include "Hero.h"
#include "Mall.h"
#include "MainPart.h"
#include<stdlib.h>

#define _CRT_NONSTDC_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS

class MainInterface : public cocos2d::Layer {
    MainPart* mall;
    Sprite* tishi;
    MainPart* main_part;
    Layer* zhuangbei;
    Layer* Dashboard;
    int music = -1;
    int x = 0;
public:

    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(MainInterface);

    //获取动作序列
    cocos2d::Vector<cocos2d::SpriteFrame*> getAnimation(const char* format, int count);

    //开始游戏
    void enterFight(Ref* pSender);

    void Music(Ref* pSender);

    //公告
    void Announcement(Ref* pSender);

    //排行榜
    void LeaderBoard(Ref* pSender);

    //商品
    void Commodity(Ref* pSender);

    //考核
    void Evalution(Ref* pSender);

    //幸运转盘
    void Lucky_turnable(Ref* pSender);

    //在线秒杀
    void OnlineSpike(Ref* pSender);

    //呼叫服务器
    void Call_server(Ref* pSender);

    //
    void bimg_gnyg_cijihuangdao(Ref* pSender);

    //华山论剑
    void bimg_zjm_huashanluenjian(Ref* pSender);

    //江湖历练
    void bimg_zjm_jianghulilian(Ref* pSender);

    //竞技
    void bimg_zjm_jinjie(Ref* pSender);

    //角色
    void bimg_zjm_juese(Ref* pSender);

    //决战荒城
    void bimg_zjm_juezhanhuangcheng(Ref* pSender);

    //练功崖
    void bimg_zjm_liangongya(Ref* pSender);

    //主角
    void bimg_zjm_lingchong(Ref* pSender);

    //神兵
    void bimg_zjm_shenbing(Ref* pSender);

    //世界boss
    void bimg_zjm_shijieBOSS(Ref* pSender);

    //天命
    void bimg_zjm_tianming(Ref* pSender);

    //通天塔
    void bimg_zjm_tongtianta(Ref* pSender);

    //围剿魔教
    void bimg_zjm_weijiaomojiao(Ref* pSender);

    //侠客行
    void bimg_zjm_xiakexing(Ref* pSender);

    //心法
    void bimg_zjm_xinfa(Ref* pSender);

    //找事
    void bimg_zjm_zhaoshi(Ref* pSender);

    //装备
    void bimg_zjm_zhuangbei(Ref* pSender);

    //人物面板
    void avatarCenter(Ref* pSender);

    void Closezhuangbei(Ref* pSender);

    void CloseDashboard(Ref* pSender);

    void FlushCoin(float dt);

    void CloseTishi(Ref* pSender);

    void lizi();
};

#endif // DEBUG

