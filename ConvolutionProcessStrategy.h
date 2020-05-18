#pragma once
#include "ProcessStrategy.h"
#include <utility>

using processPtrs = std::pair<std::vector<unsigned char *>, std::vector<unsigned char *>>;

class ConvolutionProcessStrategy :
	public ProcessStrategy
{

private:


	std::vector<unsigned char*> getChannelsPtrs(channelType c);
	virtual void iterationProcedure(std::vector<unsigned char*>& inputs, std::vector<unsigned char*>& outputs);
protected:
	bool one_to_one; //implying false is n images to 1
	size_t max_size;
	processPtrs prepOutput();
	
	inline virtual unsigned char iterationAction(const unsigned char * p) = 0;
	virtual const std::vector<unsigned char> formKernel(const unsigned char * c);

	void iterate(std::vector<unsigned char *> &inputs, std::vector<unsigned char*> &outputs);
	void setOneToOne(bool oneto1);

public:
	void setMaxSize(size_t max);
	ConvolutionProcessStrategy();
	virtual void process();
};

