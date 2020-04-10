#include "ProcessStrategy.h"

std::vector<Grayscale1DImage>* ProcessStrategy::offerOutput()
{
	return &mOutput;
}

void ProcessStrategy::addInput(std::vector<Grayscale1DImage>* i)
{
	mInput = i;
	mOutput= *(mInput);
}

void ProcessStrategy::addInput(Grayscale1DImage i) {
	mInput->push_back(i);
	mOutput = *(mInput);
}

void ProcessStrategy::clearInput()
{
	mInput->clear();
}

ProcessStrategy::ProcessStrategy(std::vector<Grayscale1DImage>* input)
	:mInput{ input }, mOutput{ *(mInput) }
{
	
}
