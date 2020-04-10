#pragma once
#include "ProcessStrategy.h"
class Tiny1DGaussStrategy :
	public ProcessStrategy
{
private:
	bool mVertical;

public:
	void process();
	void setVertical(bool v);
	Tiny1DGaussStrategy();
};

