#include "MainPart.h"

MainPart* MainPart::mainPart = nullptr;
MainPart::MainPart() {
	//setImagePath(imagePath);
	m_Level = 1;
	m_Exp = 0;
	m_MaxEnergy = 200;
	m_Energy = m_MaxEnergy;
	m_MaxDefense = 5;
	m_Defense = m_MaxDefense;
	m_CoinNum = 150; 
	m_equip.push_back("resource/dynamicRes/itemicons//101011.png");
	//m_equip.push_back("resource/dynamicRes/bigequip/100001.png");
	/*m_equip.push_back("resource/dynamicRes/bigequip/100002.png");
	m_equip.push_back("resource/dynamicRes/bigequip/100003.png"); 
	m_equip.push_back("resource/dynamicRes/bigequip/100004.png");
	m_equip.push_back("resource/dynamicRes/artifactIcon/big/200002.png");
	m_equip.push_back("resource/dynamicRes/artifactIcon/big/200004.png");
	m_equip.push_back("resource/dynamicRes/artifactIcon/big/200005.png");
	m_equip.push_back("resource/dynamicRes/artifactIcon/big/200024.png");
	m_equip.push_back("resource/dynamicRes/artifactIcon/big/200006.png");
	m_equip.push_back("resource/dynamicRes/artifactIcon/big/200007.png");
	m_equip.push_back("resource/dynamicRes/artifactIcon/big/200008.png");
	m_equip.push_back("resource/dynamicRes/artifactIcon/big/200009.png");
	m_equip.push_back("resource/dynamicRes/artifactIcon/big/200010.png");
	m_equip.push_back("resource/dynamicRes/artifactIcon/big/200011.png");
	m_equip.push_back("resource/dynamicRes/artifactIcon/big/200012.png");
	m_equip.push_back("resource/dynamicRes/artifactIcon/big/200023.png");*/
	m_Price = 500;
}

MainPart* MainPart::getMainPart() {
	if (mainPart == nullptr) {
		mainPart = new MainPart();
	}
	return mainPart;
}