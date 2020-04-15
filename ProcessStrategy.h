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
	std::vector<Img_1D_channel>* mInput;
	std::vector<Img_1D_channel> mOutput;

public:
	virtual void process()=0;
	std::vector<Img_1D_channel>* offerOutput();
	void addInput(std::vector<Img_1D_channel>* i);
	void addInput(Img_1D_channel i);
	void clearInput();
	ProcessStrategy() = default;

};
