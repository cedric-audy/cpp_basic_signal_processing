#pragma once
#include "ProcessStrategy.h"

class BoxFilterStrategy : public virtual ProcessStrategy
{
private:
	int mKernelSize;
	bool mVertical;

protected:

public:
	void process();
	int kernelSize();
	void setKernelSize(int s);
	void setVertical(bool b);
	BoxFilterStrategy();
};

