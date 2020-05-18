#pragma once
#include "ConvolutionProcessStrategy.h"
class MeanStrategy :
	public ConvolutionProcessStrategy
{
private:
	//virtual void iterationProcedure(std::vector<unsigned char*> &inputs, std::vector<unsigned char*> &outputs);

	size_t sum;
	size_t n;
	unsigned char iterationAction(const unsigned char * p);

public:
	void process();
	MeanStrategy();
};

