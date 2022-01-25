#pragma once
#include "Army.h"

class Bowman : public Army
{
public:
	Bowman(std::string name, Weapon* weapon) : Army(name, 100, 10, weapon)
	{
	}
	~Bowman() {
		//std::cout << " ------>Destroy Bowman\n";
	}
};

