#pragma once
#include "Resource.h"
class Wood : public Resource
{
public:
	Wood(std::string name, int amount) : Resource(name, amount) 
	{
	}
	~Wood(){}
	int GetAmount() {
		return amount;
	}
	void SetAmount(int amount) {
		this->amount = amount;
	}
};