#include "ProcessStrategy.h"

std::vector<Img_1D_channel>* ProcessStrategy::offerOutput()
{
	return &mOutput;
}

void ProcessStrategy::addInput(std::vector<Img_1D_channel>* i)
{
	mInput = i;
	mOutput= *(mInput);
}

void ProcessStrategy::addInput(Img_1D_channel i) {
	mInput->push_back(i);
	mOutput = *(mInput);
}

void ProcessStrategy::clearInput()
{
	mInput->clear();
}


