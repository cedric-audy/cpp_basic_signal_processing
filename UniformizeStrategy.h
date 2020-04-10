#pragma once
#include "ProcessStrategy.h"

class UniformizeStrategy:public virtual ProcessStrategy
{
	//for now, will uniformize and normalize, as it saves a traversal
private:
	float mMin;
	float mMax;

protected:

public:
	bool isValid(); //to make sure we have the appropriate input
	void process();
	int max();
	int min();
	UniformizeStrategy();
};

