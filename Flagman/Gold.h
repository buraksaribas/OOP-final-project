#pragma once
#include "Resource.h"
class Gold : public Resource
{
public:
	Gold(std::string name, int amount) : Resource(name, amount) {}
	~Gold() {}
	int GetAmount() {
		return amount;
	}
	void SetAmount(int amount) {
		this->amount = amount;
	}
};