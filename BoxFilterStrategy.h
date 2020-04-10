#pragma once
#include "ProcessStrategy.h"

class BoxFilterStrategy : public virtual ProcessStrategy
{
private:
	int mKernelSize;
	bool mVertical{false};

protected:

public:
	void process();
	int kernelSize();
	void setKernelSize(int s);
	void setVertical(bool b);
	BoxFilterStrategy();
	BoxFilterStrategy(std::vector<Grayscale1DImage> * input, int kernelSize);
};

