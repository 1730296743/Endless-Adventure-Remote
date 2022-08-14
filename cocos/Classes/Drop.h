#pragma once

#ifndef _DROP_H_
#define _DROP_H_
#include<Vector>
#include "cocos2d.h"
class Drop{

	CC_SYNTHESIZE(std::vector<std::string>, m_drop, Mdrop);
public:
	static Drop* getDrop();
private:
	class CGarbo {
	public:
		~CGarbo()
		{
			if (Drop::drop)
				delete Drop::drop;
		}
	};
	static  Drop* drop;
	static CGarbo Garbo;
	Drop();
};

#endif
