#pragma once
#include "Weapon.h"
class Sword : public Weapon
{
public:
	Sword() : Weapon("Sword")
	{
	}
	~Sword()
	{
		//std::cout << " ------>Destroy sword\n";
	}
	virtual int CalculateDamage(int power)
	{
		return power * 3 + (rand() % 20 + 5);
	}
};