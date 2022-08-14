#pragma once
#ifndef __MainPart_H__
#define __MainPart_H__
#include "cocos2d.h"
#include<Vector>

class MainPart{
	CC_SYNTHESIZE(int, m_Price, Price);
	CC_SYNTHESIZE(int, m_CoinNum, CoinNum);
	CC_SYNTHESIZE(int, m_MaxDefense, MaxDefense);
	CC_SYNTHESIZE(int, m_Defense, Defense);
	CC_SYNTHESIZE(int, m_MaxEnergy, MaxEnergy);
	CC_SYNTHESIZE(int, m_Energy, Energy);
	CC_SYNTHESIZE(int, m_Level, Level);
	CC_SYNTHESIZE(int, m_Exp, Exp);
	CC_SYNTHESIZE(std::string, m_imagePath, ImagePath);
	CC_SYNTHESIZE(std::vector<std::string>, m_equip, Equip);
public:
	static MainPart* getMainPart();
private:
	class CGarbo {
	public:
		~CGarbo()
		{
			if (MainPart::mainPart)
				delete MainPart::mainPart;
		}
	};
	static  MainPart* mainPart;
	static CGarbo Garbo;
	MainPart();

	
};
#endif