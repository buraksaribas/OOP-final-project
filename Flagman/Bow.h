#pragma once
#include "Weapon.h"
class Bow : public Weapon
{
public:
	Bow() : Weapon("Bow")
	{
	}
	~Bow() { 
		//std::cout << " ----->Destroy Bow\n"; 
	}
	virtual int CalculateDamage(int power)
	{
		return power * 2 + (rand() % 20 + 1);
	}
};