#pragma once
#include "Army.h"

class Swordsman : public Army
{
public:
	Swordsman(std::string name, Weapon* weapon) : Army(name, 100, 15, weapon)
	{
	}
	~Swordsman() {
		//std::cout << " ---->Destroy Swordsman" << name << std::endl;
	}
};