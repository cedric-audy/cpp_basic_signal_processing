#pragma once
#include "ProcessStrategy.h"
class TresholderStrategy :
	public ProcessStrategy
{

private:
	int mTreshold;
	bool mToBinary;

public:
	void process();
	void setToBinary(bool b);
	void setTreshold(int t);
	TresholderStrategy();
};

