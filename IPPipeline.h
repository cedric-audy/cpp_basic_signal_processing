#pragma once
#include "Grayscale1DImage.h"
#include "ProcessStrategy.h"
#include <vector>
#include <string>

class IPPipeline
{
private:
	std::vector<Grayscale1DImage> mCurrImage; //vect of color channels, typically for RGB 24 bits
	std::vector<ProcessStrategy *> mProcesses; //int for now, eventually ProcessStrategy
	Grayscale1DImage * currOutput;
	//pushtoOutputManager

public:

	int nb{ 0 };
	IPPipeline();
	void execute();
	//void feedLightMap(Grayscale1DImage img);
	int inputSize();
	void clearInput();
	void addStep(ProcessStrategy* step);
	void defaultLightmapProcess();
	void setCurrentImage(Grayscale1DImage img, size_t index);
	void pushImg(Grayscale1DImage img);
	void resetPipeline();
	unsigned char * getOutputPtr() { return currOutput->getStart(); }



	//Stats container for later
};

