#pragma once
#include "KernelProcessStrategy.h"
class DirectionnalKernelStrategy :
	public KernelProcessStrategy
{

private:

protected:
	bool mVertical;
	size_t callCount;
	size_t count;
	size_t mKernelSize;
	size_t xyCount;
	size_t offset;
	size_t limit;
	size_t alt; //alt is the value we insert in the kernel vector 
	void incOffsetCount();
	inline virtual unsigned char iterationAction(const unsigned char * p) = 0;
	const std::vector<unsigned char> DirectionnalKernelStrategy::formKernel(const unsigned char * c);
public:
	void setVertical(bool v);
	void setKernelSize(size_t k);
	void process();
};

