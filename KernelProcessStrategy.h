#pragma once
#include "ConvolutionProcessStrategy.h"
class KernelProcessStrategy :
	public ConvolutionProcessStrategy
{

private:
protected:
	inline virtual unsigned char iterationAction(const unsigned char * p) = 0;
	virtual const std::vector<unsigned char> formKernel(const unsigned char * c) = 0;

	//virtual void iterationProcedure(std::vector<unsigned char*>& inputs, std::vector<unsigned char*>& outputs) = 0;
public:
};

