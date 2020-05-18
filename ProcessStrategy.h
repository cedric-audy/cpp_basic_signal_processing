#pragma once
#include <vector>
#include "Custom1DImg.h"
//include stat object

class ProcessStrategy
{

private:

protected:
	std::vector<Custom1DImg*> mInput;
	std::vector<Custom1DImg> mOutput;

public:
	virtual void process()=0;
	std::vector<Custom1DImg*> offerOutput();
	void addInput(Custom1DImg* i);
	void setInput(std::vector<Custom1DImg*> i);
	void clearInput();

	ProcessStrategy() = default;
	//all else also default
	//test
};
