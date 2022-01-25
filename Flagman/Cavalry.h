#pragma once
#include "Army.h"

class Cavalry : public Army
{
public:
	Cavalry(std::string name, Weapon* weapon) : Army(name, 100, 20, weapon)
	{
	}
	~Cavalry() {
		//std::cout << " ---->Destroy Cavalry\n" << std::endl;
	}
};

