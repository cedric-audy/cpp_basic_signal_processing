#include "ProcessStrategy.h"

std::vector<Custom1DImg>* ProcessStrategy::offerOutput()
{
	return &mOutput;
}

void ProcessStrategy::addInput(std::vector<Custom1DImg>* i)
{
	mInput = i;
	mOutput= *(mInput);
}

void ProcessStrategy::addInput(Custom1DImg i) {
	mInput->push_back(i);
	mOutput = *(mInput);
}

void ProcessStrategy::clearInput()
{
	mInput->clear();
	mOutput = *(mInput);
}


