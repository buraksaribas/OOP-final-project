#pragma once
#include "Army.h"

class Catapult : public Army
{
public:
	Catapult(std::string name, Weapon* weapon) : Army(name, 100, 50, weapon)
	{
	}
	~Catapult() {
		//std::cout << " ------>Destroy Catapult\n";
	}
};

