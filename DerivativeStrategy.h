#pragma once
#include "ProcessStrategy.h"
class DerivativeStrategy :
	public ProcessStrategy
{
private:
	bool mVertical;

public:
	void process();
	void setVertical(bool v);
	DerivativeStrategy();
};

