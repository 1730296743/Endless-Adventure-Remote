#include "Manager.h"

Manager* Manager::pInstance = nullptr;
Manager* Manager::getInstance()
{
	if (pInstance == nullptr)
	{
		pInstance = new Manager;
	}
	return pInstance;
}