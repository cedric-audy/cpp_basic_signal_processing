#pragma once
#include "ProcessStrategy.h"
class FindCircleStrategy :
	public ProcessStrategy
{
private:
	size_t mCircleRadius;
public:
	void setRadius(size_t r);
	void process();
	FindCircleStrategy();
};

