#include "BoxFilterStrategy.h"


unsigned char BoxFilterStrategy::iterationAction(const unsigned char * p)
{
	auto r = formKernel(p);
	size_t sum = 0;
	size_t n = 0;
	for (auto& val : r) {
		if (val > 0) { ++n; }
		sum += val;
	}
	n = n == 0 ? 1 : n;
	return sum/n;
}

BoxFilterStrategy::BoxFilterStrategy()
{
	alt = 0;
	one_to_one = true;
}
