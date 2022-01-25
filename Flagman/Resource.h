#pragma once
#include <string>
class Resource
{
protected:
	std::string name;
	int amount;
public:
	Resource(std::string name, int amount) : name(name), amount(amount) {}
	std::string GetName() {
		return name;
	}
	virtual int GetAmount() = 0;
	virtual void SetAmount(int amount) = 0;
};
