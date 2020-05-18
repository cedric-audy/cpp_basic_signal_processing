#include "DirectionnalKernelStrategy.h"

const std::vector<unsigned char> DirectionnalKernelStrategy::formKernel(const unsigned char * c)
{
	++callCount;
	std::vector<unsigned char> r{};
	for (int k = -floor(mKernelSize / 2); k < ceil(mKernelSize / 2); k++)
	{
		if (k + xyCount > 0 && k + xyCount < limit) {
			r.push_back(*(c + k * offset));
		}
		else {
			r.push_back(alt);
		}
	}
	incOffsetCount();
	return r;
}

void DirectionnalKernelStrategy::setVertical(bool v)
{
	mVertical = v;
}

void DirectionnalKernelStrategy::setKernelSize(size_t k)
{
	mKernelSize = k;
}

void DirectionnalKernelStrategy::process()
{
	mVertical = false;
	count = 0;
	xyCount = 0;
	offset = mVertical ? mInput[0]->width() : 1;
	limit = mVertical ? mInput[0]->height() : mInput[0]->width();
	auto[ins, outs] = prepOutput();
	ConvolutionProcessStrategy::iterate(ins, outs);
}

void DirectionnalKernelStrategy::incOffsetCount()
{
	if (callCount%max_size == 0) {
		++count;
		if (count%offset == 0) {
			++xyCount;
			if (xyCount == limit) {
				xyCount = 0;
			}
		}
	
	}
}