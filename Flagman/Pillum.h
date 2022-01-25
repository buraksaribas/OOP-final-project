#pragma once
#include "Weapon.h"
class Pillum : public Weapon
{
public:
	Pillum() : Weapon("Pillum")
	{
	}
	~Pillum()
	{
		//std::cout << " ------>Destroy pillum\n";
	}
	virtual int CalculateDamage(int power)
	{
		return power * 4 + (rand() % 30 + 10);
	}
};