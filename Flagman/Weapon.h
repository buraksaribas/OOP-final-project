#pragma once
#include <string>
#include <iostream>
class Weapon
{
public:
	Weapon(std::string name)  : name(name)
	{
	}
	std::string GetName() {
		return name;
	}

	virtual int CalculateDamage(int power) = 0;
	virtual ~Weapon() { 
		//std::cout << " --->Destroy weapon\n"; 
	}
private:
	std::string name;
};



