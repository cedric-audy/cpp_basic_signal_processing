#include "ProcessStrategy.h"

std::vector<Custom1DImg*> ProcessStrategy::offerOutput()
{
	std::vector<Custom1DImg*> v{};
	for (int i = 0; i < mOutput.size(); i++) {
		v.push_back(&mOutput[i]);
	}
	return v;
}


void ProcessStrategy::addInput(Custom1DImg * i) {
	mInput.push_back(i);
}

void ProcessStrategy::setInput(std::vector<Custom1DImg*> i)
{
	ProcessStrategy::clearInput();
	mInput = i;
}

void ProcessStrategy::clearInput()
{
	mInput.clear();
}


