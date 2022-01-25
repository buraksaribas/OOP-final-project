#pragma once
#include "Resource.h"
class Water : public Resource
{
public:
	Water(std::string name, int amount) : Resource(name, amount){}
	~Water() {}
	int GetAmount() {
		return amount;
	}
	void SetAmount(int amount) {
		this->amount = amount;
	}
};