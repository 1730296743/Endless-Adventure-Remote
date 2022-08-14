#include "Mall.h"
cocos2d::Scene* Mall::createScene() {
	Scene* scene = Scene::create();
	Mall* layer = Mall::create();
	scene->addChild(layer);
	return scene;
}

bool Mall::init() {
	if (!Layer::init()) {
		return false;
	}

	auto const visibleSize = Director::getInstance()->getVisibleSize();
	chushihua();
	//商城面板
	Sprite* mall = Sprite::create("images/mallnew.png");
	CCASSERT(mall != nullptr, "images/mallnew.png");
	mall->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(mall, 1);

	auto closeItem = MenuItemImage::create(
		"images/delete.png",
		"images/delete1.png",
		CC_CALLBACK_1(Mall::CloseMall, this));

	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0) {
		CC_SAFE_DELETE(closeItem);
	}
	else {
		float const x = visibleSize.width - closeItem->getContentSize().width - visibleSize.width / 2 + 25;
		float const y = visibleSize.height - closeItem->getContentSize().height - visibleSize.height / 2 + 50;
		closeItem->setPosition(Vec2(x, y));
	}
	Menu* menu_queren = Menu::create(closeItem, NULL);
	this->addChild(menu_queren, 2);

	int k = 0;
	if (m_Mall.size() != 0) {

		for (int j = 0; j < 3; j++) {
			for (int i = 0; i < 6; i++) {
				Sprite* pris = Sprite::create(m_Mall.at(k));
				CCASSERT(pris != nullptr, "images/mallnew.png");
				pris->setPosition(Vec2(170 + i * 130, 500 - j * 130 - 70));
				mall->addChild(pris, 3);
				k++;
				if (m_Mall.size() == k + 1) {
					break;
				}
			}
			if (m_Mall.size() == k + 1) {
				break;
			}
		}
	}
	FlushCoin(1);
	//按钮
	int t = k;
	Button* bg[18] = { 0 };
	if (k != 0) {
		int temp = 0;
		for (int j = 0; j < 3; j++) {
			for (int i = 0; i < 6; i++) {
				bg[temp] = Button::create("images/xinfa.png", "images/xinfa.png");
				//bg[temp]->setOpacity(170);
				bg[temp]->setTag(temp - 1);
				bg[temp]->setScale(0.1f);
				bg[temp]->setPosition(Vec2(170 + i * 130, 500 - j * 130 - 135));
				mall->addChild(bg[temp]);
				k--;
				temp++;
				if (k == 0) {
					break;
				}
			}
			if (k == 0) {
				break;
			}
		}
	}
	bg[0]->addTouchEventListener([this](Ref* ref, Widget::TouchEventType type) {
		switch (type) {
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			if (MainPart::getMainPart()->getCoinNum() >= 5) {
				this->removeChild(coinNum);
				MainPart::getMainPart()->setCoinNum(MainPart::getMainPart()->getCoinNum() - 5);
				FlushCoin(1);
				std::vector<std::string> str = MainPart::getMainPart()->getEquip();
				str.push_back(this->getMMall().at(0).c_str());
				MainPart::getMainPart()->setEquip(str);
				cocos2d::log("mall-------%s", this->getMMall().at(0).c_str());
				cocos2d::log("ei------%s", MainPart::getMainPart()->getEquip().front().c_str());
				cocos2d::log("-------------%d-------%s", MainPart::getMainPart()->getEquip().size(), MainPart::getMainPart()->getEquip().back().c_str());
			}
			break;
		}
		});

	bg[1]->addTouchEventListener([this](Ref* ref, Widget::TouchEventType type) {
		switch (type) {
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			if (MainPart::getMainPart()->getCoinNum() >= 5) {
				this->removeChild(coinNum);
				MainPart::getMainPart()->setCoinNum(MainPart::getMainPart()->getCoinNum() - 5);
				FlushCoin(1);
				std::vector<std::string> str = MainPart::getMainPart()->getEquip();
				str.push_back(this->getMMall().at(1).c_str());
				MainPart::getMainPart()->setEquip(str);
			}
		}
		});

	bg[2]->addTouchEventListener([this](Ref* ref, Widget::TouchEventType type) {
		switch (type) {
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			if (MainPart::getMainPart()->getCoinNum() >= 5) {
				this->removeChild(coinNum);
				MainPart::getMainPart()->setCoinNum(MainPart::getMainPart()->getCoinNum() - 5);
				FlushCoin(1);
				std::vector<std::string> str = MainPart::getMainPart()->getEquip();
				str.push_back(this->getMMall().at(2).c_str());
				MainPart::getMainPart()->setEquip(str);
			}
		}
		});

	bg[3]->addTouchEventListener([this](Ref* ref, Widget::TouchEventType type) {
		switch (type) {
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			if (MainPart::getMainPart()->getCoinNum() >= 5) {
				this->removeChild(coinNum);
				MainPart::getMainPart()->setCoinNum(MainPart::getMainPart()->getCoinNum() - 5);
				FlushCoin(1);
				std::vector<std::string> str = MainPart::getMainPart()->getEquip();
				str.push_back(this->getMMall().at(3).c_str());
				MainPart::getMainPart()->setEquip(str);
			}
		}
		});

	bg[4]->addTouchEventListener([this](Ref* ref, Widget::TouchEventType type) {
		switch (type) {
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			if (MainPart::getMainPart()->getCoinNum() >= 5) {
				this->removeChild(coinNum);
				MainPart::getMainPart()->setCoinNum(MainPart::getMainPart()->getCoinNum() - 5);
				FlushCoin(1);
				std::vector<std::string> str = MainPart::getMainPart()->getEquip();
				str.push_back(this->getMMall().at(4).c_str());
				MainPart::getMainPart()->setEquip(str);
			}
		}
		});

	bg[5]->addTouchEventListener([this](Ref* ref, Widget::TouchEventType type) {
		switch (type) {
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			if (MainPart::getMainPart()->getCoinNum() >= 5) {
				this->removeChild(coinNum);
				MainPart::getMainPart()->setCoinNum(MainPart::getMainPart()->getCoinNum() - 5);
				FlushCoin(1);
				std::vector<std::string> str = MainPart::getMainPart()->getEquip();
				str.push_back(this->getMMall().at(5).c_str());
				MainPart::getMainPart()->setEquip(str);
			}
		}
		});

	bg[6]->addTouchEventListener([this](Ref* ref, Widget::TouchEventType type) {
		switch (type) {
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			if (MainPart::getMainPart()->getCoinNum() >= 5) {
				this->removeChild(coinNum);
				MainPart::getMainPart()->setCoinNum(MainPart::getMainPart()->getCoinNum() - 5);
				FlushCoin(1);
				std::vector<std::string> str = MainPart::getMainPart()->getEquip();
				str.push_back(this->getMMall().at(6).c_str());
				MainPart::getMainPart()->setEquip(str);
			}
		}
		});

	bg[7]->addTouchEventListener([this](Ref* ref, Widget::TouchEventType type) {
		switch (type) {
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			if (MainPart::getMainPart()->getCoinNum() >= 5) {
				this->removeChild(coinNum);
				MainPart::getMainPart()->setCoinNum(MainPart::getMainPart()->getCoinNum() - 5);
				FlushCoin(1);
				std::vector<std::string> str = MainPart::getMainPart()->getEquip();
				str.push_back(this->getMMall().at(7).c_str());
				MainPart::getMainPart()->setEquip(str);
			}
		}
		});

	bg[8]->addTouchEventListener([this](Ref* ref, Widget::TouchEventType type) {
		switch (type) {
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			if (MainPart::getMainPart()->getCoinNum() >= 5) {
				this->removeChild(coinNum);
				MainPart::getMainPart()->setCoinNum(MainPart::getMainPart()->getCoinNum() - 5);
				FlushCoin(1);
				std::vector<std::string> str = MainPart::getMainPart()->getEquip();
				str.push_back(this->getMMall().at(8).c_str());
				MainPart::getMainPart()->setEquip(str);
			}
		}
		});

	bg[9]->addTouchEventListener([this](Ref* ref, Widget::TouchEventType type) {
		switch (type) {
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			if (MainPart::getMainPart()->getCoinNum() >= 5) {
				this->removeChild(coinNum);
				MainPart::getMainPart()->setCoinNum(MainPart::getMainPart()->getCoinNum() - 5);
				FlushCoin(1);
				std::vector<std::string> str = MainPart::getMainPart()->getEquip();
				str.push_back(this->getMMall().at(9).c_str());
				MainPart::getMainPart()->setEquip(str);
			}
		}
		});

	bg[10]->addTouchEventListener([this](Ref* ref, Widget::TouchEventType type) {
		switch (type) {
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			if (MainPart::getMainPart()->getCoinNum() >= 5) {
				this->removeChild(coinNum);
				MainPart::getMainPart()->setCoinNum(MainPart::getMainPart()->getCoinNum() - 5);
				FlushCoin(1);
				std::vector<std::string> str = MainPart::getMainPart()->getEquip();
				str.push_back(this->getMMall().at(10).c_str());
				MainPart::getMainPart()->setEquip(str);
			}
		}
		});

	bg[11]->addTouchEventListener([this](Ref* ref, Widget::TouchEventType type) {
		switch (type) {
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			if (MainPart::getMainPart()->getCoinNum() >= 5) {
				this->removeChild(coinNum);
				MainPart::getMainPart()->setCoinNum(MainPart::getMainPart()->getCoinNum() - 5);
				FlushCoin(1);
				std::vector<std::string> str = MainPart::getMainPart()->getEquip();
				str.push_back(this->getMMall().at(11).c_str());
				MainPart::getMainPart()->setEquip(str);
			}
		}
		});

	bg[12]->addTouchEventListener([this](Ref* ref, Widget::TouchEventType type) {
		switch (type) {
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			if (MainPart::getMainPart()->getCoinNum() >= 5) {
				this->removeChild(coinNum);
				MainPart::getMainPart()->setCoinNum(MainPart::getMainPart()->getCoinNum() - 5);
				FlushCoin(1);
				std::vector<std::string> str = MainPart::getMainPart()->getEquip();
				str.push_back(this->getMMall().at(12).c_str());
				MainPart::getMainPart()->setEquip(str);
			}
		}
		});

	bg[13]->addTouchEventListener([this](Ref* ref, Widget::TouchEventType type) {
		switch (type) {
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			if (MainPart::getMainPart()->getCoinNum() >= 5) {
				this->removeChild(coinNum);
				MainPart::getMainPart()->setCoinNum(MainPart::getMainPart()->getCoinNum() - 5);
				FlushCoin(1);
				std::vector<std::string> str = MainPart::getMainPart()->getEquip();
				str.push_back(this->getMMall().at(13).c_str());
				MainPart::getMainPart()->setEquip(str);
			}
		}
		});

	bg[14]->addTouchEventListener([this](Ref* ref, Widget::TouchEventType type) {
		switch (type) {
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			if (MainPart::getMainPart()->getCoinNum() >= 5) {
				this->removeChild(coinNum);
				MainPart::getMainPart()->setCoinNum(MainPart::getMainPart()->getCoinNum() - 5);
				FlushCoin(1);
				std::vector<std::string> str = MainPart::getMainPart()->getEquip();
				str.push_back(this->getMMall().at(14).c_str());
				MainPart::getMainPart()->setEquip(str);
			}
		}
		});

	bg[15]->addTouchEventListener([this](Ref* ref, Widget::TouchEventType type) {
		switch (type) {
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			if (MainPart::getMainPart()->getCoinNum() >= 5) {
				this->removeChild(coinNum);
				MainPart::getMainPart()->setCoinNum(MainPart::getMainPart()->getCoinNum() - 5);
				FlushCoin(1);
				std::vector<std::string> str = MainPart::getMainPart()->getEquip();
				str.push_back(this->getMMall().at(15).c_str());
				MainPart::getMainPart()->setEquip(str);
			}
		}
		});

	bg[16]->addTouchEventListener([this](Ref* ref, Widget::TouchEventType type) {
		switch (type) {
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			if (MainPart::getMainPart()->getCoinNum() >= 5) {
				this->removeChild(coinNum);
				MainPart::getMainPart()->setCoinNum(MainPart::getMainPart()->getCoinNum() - 5);
				FlushCoin(1);
				std::vector<std::string> str = MainPart::getMainPart()->getEquip();
				str.push_back(this->getMMall().at(16).c_str());
				MainPart::getMainPart()->setEquip(str);
			}
		}
		});

	bg[17]->addTouchEventListener([this](Ref* ref, Widget::TouchEventType type) {
		switch (type) {
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			if (MainPart::getMainPart()->getCoinNum() >= 5) {
				this->removeChild(coinNum);
				MainPart::getMainPart()->setCoinNum(MainPart::getMainPart()->getCoinNum() - 5);
				FlushCoin(1);
				std::vector<std::string> str = MainPart::getMainPart()->getEquip();
				str.push_back(this->getMMall().at(17).c_str());
				MainPart::getMainPart()->setEquip(str);
			}
		}
		});

	//价格
	int f = t;
	if (t != 0) {
		for (int j = 0; j < 3; j++) {
			for (int i = 0; i < 6; i++) {
				char st[3];
				_itoa(5, st, 10);
				std::string str = st;
				auto coinNum = Label::createWithTTF(str.c_str(), "fonts/arial.ttf", 24);
				if (coinNum == nullptr) {
					CC_SAFE_DELETE(coinNum);
				}
				else {
					// position the label on the center of the screen
					float const x = visibleSize.width - 150;
					float const y = visibleSize.height - 76;
					coinNum->setPosition(Vec2(170 + i * 130 + 15, 500 - j * 130 - 135));
					coinNum->setScale(0.9f);
					// add the label as a child to this layer
					mall->addChild(coinNum, 2);
				}
				t--;
				if (t == 0) {
					break;
				}
			}
			if (t == 0) {
				break;
			}
		}
	}
	//金币消耗
	if (f != 0) {
		for (int j = 0; j < 3; j++) {
			for (int i = 0; i < 6; i++) {
				auto coinNum = Sprite::create("resource/dynamicRes/itemicons/600001.png");
				if (coinNum == nullptr) {
					CC_SAFE_DELETE(coinNum);
				}
				else {
					// position the label on the center of the screen
					float const x = visibleSize.width - 150;
					float const y = visibleSize.height - 76;
					coinNum->setPosition(Vec2(170 + i * 130 - 15, 500 - j * 130 - 135));
					coinNum->setScale(0.35f);
					// add the label as a child to this layer
					mall->addChild(coinNum, 2);
				}
				f--;
				if (f == 0) {
					break;
				}
			}
			if (f == 0) {
				break;
			}
		}
	}

	//金币
	auto coin = cocos2d::Sprite::create("resource/dynamicRes/itemicons/600001.png");
	if (coin == nullptr) {
		CC_SAFE_DELETE(coin);
	}
	else {
		coin->setAnchorPoint(cocos2d::Vec2(1, 1));
		float const x = visibleSize.width - 190;
		float const y = visibleSize.height - 60;
		coin->setPosition(Vec2(x, y));
		coin->setScale(0.4f);

	}
	mall->addChild(coin, 7);

	return true;
}

// a selector callback
void Mall::menuCloseCallback(cocos2d::Ref* pSender) {
	cocos2d::log("menuCloseCallback");
}

void Mall::CloseMall(Ref* pSender) {
	Director::getInstance()->replaceScene(MainInterface::createScene());
}

void Mall::chushihua() {
	this->m_Mall.push_back("resource/dynamicRes/itemicons/10001.png");
	this->m_Mall.push_back("resource/dynamicRes/itemicons/37001.png");
	this->m_Mall.push_back("resource/dynamicRes/itemicons/37006.png");
	char mapName[44] = { 0 };
	for (int i = 100051; i < 100100; i++) {
		sprintf(mapName, "resource/dynamicRes/itemicons/%d.png", i);
		std::string str = mapName;
		this->m_Mall.push_back(str);
	}

}

void Mall::FlushCoin(float dt) {
	auto const visibleSize = Director::getInstance()->getVisibleSize();
	char st[256];
	_itoa(MainPart::getMainPart()->getCoinNum(), st, 10);
	std::string str = st;
	coinNum = Label::createWithTTF(str.c_str(), "fonts/arial.ttf", 24);
	if (coinNum == nullptr) {
		CC_SAFE_DELETE(coinNum);
	}
	else {
		// position the label on the center of the screen
		float const x = visibleSize.width - 150;
		float const y = visibleSize.height - 76;
		coinNum->setPosition(Vec2(x, y));
		coinNum->setScale(0.9f);
		// add the label as a child to this layer
		this->addChild(coinNum, 1);
	}

}
