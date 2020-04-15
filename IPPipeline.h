#pragma once
#include "Grayscale1DImage.h"
#include "ProcessStrategy.h"
#include "PipelineBlueprint.h"
#include <vector>
#include <string>

class IPPipeline
{
private:
	PipelineBlueprint mBlueprint;
	std::vector<Img_1D_channel> mCurrImage; //vect of color channels, typically for RGB 24 bits
	std::vector<ProcessStrategy *> mProcesses; //int for now, eventually ProcessStrategy
	Img_1D_channel * currOutput;
	void defaultLightmapProcess(size_t gauss1, size_t maxfilter, size_t gauss2);
	void simulGaussianFilter(size_t kernel, size_t precision=3);
	void sobelProcess();

	//pushtoOutputManager

public:

	IPPipeline();

	int nb{ 0 };
	void execute();
	int inputSize();
	void clearInput();
	void setCurrentImage(Img_1D_channel img, size_t index);
	void pushImg(Img_1D_channel img);
	unsigned char * getOutputPtr() { return currOutput->getStart(); }

	//blueprint tests
	void applyBlueprint();
	void applyStep(std::pair<StepType, filter_args> s);
	void setBlueprint(PipelineBlueprint bp);

	//to be eliminated eventually
	void resetPipeline();
	void addStep(ProcessStrategy* step);


	//Stats container for later
};

