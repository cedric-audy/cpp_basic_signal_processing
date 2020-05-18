#pragma once
#include "DirectionnalKernelStrategy.h"
class BoxFilterStrategy :
	public DirectionnalKernelStrategy
{
protected:
	inline unsigned char iterationAction(const unsigned char * p);
public:
	BoxFilterStrategy();
};

