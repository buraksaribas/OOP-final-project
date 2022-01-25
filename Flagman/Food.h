#pragma once
#include "Resource.h"
class Food : public Resource
{
public:
	Food(std::string name, int amount) : Resource(name, amount) {}
	~Food() {}
	int GetAmount() {
		return amount;
	}
	void SetAmount(int amount) {
		this->amount = amount;
	}
};