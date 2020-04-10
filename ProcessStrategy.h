#pragma once
#include <vector>
#include "Grayscale1DImage.h"
//include stat object

class ProcessStrategy
{

private:


protected:
	//most processes will be 1 in 1 out, but might as well make it as modulary as possible
	//stat object on pipeline adress?
	std::vector<Grayscale1DImage>* mInput;
	std::vector<Grayscale1DImage> mOutput;

public:
	virtual void process()=0;
	std::vector<Grayscale1DImage>* offerOutput();
	void addInput(std::vector<Grayscale1DImage>* i);
	void addInput(Grayscale1DImage i);
	void clearInput();
	ProcessStrategy() = default;

};
