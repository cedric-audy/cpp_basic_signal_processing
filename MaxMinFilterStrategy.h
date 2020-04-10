#pragma once
#include "ProcessStrategy.h"

class MaxMinFilterStrategy :
	public virtual ProcessStrategy
{
private:
	int mKernelSize;
	bool mMaxFilter;
	bool mVertical;

protected:


public:
	void process();
	int kernelSize();
	void setKernelSize(int s);
	void setMax(bool b);
	void setVertical(bool b);

	MaxMinFilterStrategy();
};

