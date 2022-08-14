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

    //��ȡ��������
    cocos2d::Vector<cocos2d::SpriteFrame*> getAnimation(const char* format, int count);

    //��ʼ��Ϸ
    void enterFight(Ref* pSender);

    void Music(Ref* pSender);

    //����
    void Announcement(Ref* pSender);

    //���а�
    void LeaderBoard(Ref* pSender);

    //��Ʒ
    void Commodity(Ref* pSender);

    //����
    void Evalution(Ref* pSender);

    //����ת��
    void Lucky_turnable(Ref* pSender);

    //������ɱ
    void OnlineSpike(Ref* pSender);

    //���з�����
    void Call_server(Ref* pSender);

    //
    void bimg_gnyg_cijihuangdao(Ref* pSender);

    //��ɽ�۽�
    void bimg_zjm_huashanluenjian(Ref* pSender);

    //��������
    void bimg_zjm_jianghulilian(Ref* pSender);

    //����
    void bimg_zjm_jinjie(Ref* pSender);

    //��ɫ
    void bimg_zjm_juese(Ref* pSender);

    //��ս�ĳ�
    void bimg_zjm_juezhanhuangcheng(Ref* pSender);

    //������
    void bimg_zjm_liangongya(Ref* pSender);

    //����
    void bimg_zjm_lingchong(Ref* pSender);

    //���
    void bimg_zjm_shenbing(Ref* pSender);

    //����boss
    void bimg_zjm_shijieBOSS(Ref* pSender);

    //����
    void bimg_zjm_tianming(Ref* pSender);

    //ͨ����
    void bimg_zjm_tongtianta(Ref* pSender);

    //Χ��ħ��
    void bimg_zjm_weijiaomojiao(Ref* pSender);

    //������
    void bimg_zjm_xiakexing(Ref* pSender);

    //�ķ�
    void bimg_zjm_xinfa(Ref* pSender);

    //����
    void bimg_zjm_zhaoshi(Ref* pSender);

    //װ��
    void bimg_zjm_zhuangbei(Ref* pSender);

    //�������
    void avatarCenter(Ref* pSender);

    void Closezhuangbei(Ref* pSender);

    void CloseDashboard(Ref* pSender);

    void FlushCoin(float dt);

    void CloseTishi(Ref* pSender);

    void lizi();
};

#endif // DEBUG

