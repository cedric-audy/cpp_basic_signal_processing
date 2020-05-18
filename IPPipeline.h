#pragma once
#include "Custom1DImg.h"
#include "ProcessStrategy.h"
#include "PipelineBlueprint.h"
#include <vector>
#include <string>

class IPPipeline
{
private:
	PipelineBlueprint mBlueprint;
	std::vector<Custom1DImg> mCurrImage; //vect of color channels, typically for RGB 24 bits
	std::vector<ProcessStrategy *> mProcesses; //int for now, eventually ProcessStrategy
	Custom1DImg * currOutput;
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
	void setCurrentImage(Custom1DImg img, size_t index);
	void pushImg(Custom1DImg img);
	Custom1DImg * getOutput() { return currOutput; }

	//blueprint tests
	void applyBlueprint();
	void applyStep(std::pair<StepType, filter_args> s);
	void setBlueprint(PipelineBlueprint bp);

	//to be eliminated eventually
	void resetPipeline();
	void addStep(ProcessStrategy* step);


	//Stats container for later
};

