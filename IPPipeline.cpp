#include "IPPipeline.h"
#include "BoxFilterStrategy.h"
#include "MaxMinFilterStrategy.h"
#include "UniformizeStrategy.h"
#include "LightmapStrategy.h"
#include "MeanStrategy.h"
#include "DerivativeStrategy.h"
#include "Tiny1DGaussStrategy.h"
#include "TresholderStrategy.h"
#include "SobelDecoupleStrategy.h"
#include "SobelRecoupleStrategy.h"
#include "FindCircleStrategy.h"

IPPipeline::IPPipeline()
	:mCurrImage{ 2 }, mProcesses{ 20 }, currOutput{}, mBlueprint{}
{

}

void IPPipeline::execute()
{
	std::vector<Img_1D_channel>* lastImg{ &mCurrImage };


	int i{ 0 };
	for (auto &p : mProcesses) {
		if (p != NULL) {
			p->addInput(lastImg);
			p->process();
			lastImg = p->offerOutput();
			++i;
		}
	}

	Img_1D_channel * output = &(mProcesses[i-1]->offerOutput()->at(0));
	currOutput = output;
}

void IPPipeline::clearInput()
{
	mCurrImage.clear();
}

void IPPipeline::addStep(ProcessStrategy * step)
{
	UniformizeStrategy * a = new UniformizeStrategy();
	mProcesses[0] = a;

	BoxFilterStrategy * a1 = new BoxFilterStrategy();
	BoxFilterStrategy * a11 = new BoxFilterStrategy();
	a11->setKernelSize(0);
	a11->setVertical(true);
	a1->setKernelSize(0);

	mProcesses[1] = a1;
	mProcesses[2] = a11;
	mProcesses[3] = a1;
	mProcesses[4] = a11;
	mProcesses[5] = a1;
	mProcesses[6] = a11;

	SobelDecoupleStrategy * a2 = new SobelDecoupleStrategy();
	mProcesses[7] = a2;

	Tiny1DGaussStrategy * b = new Tiny1DGaussStrategy();
	b->setVertical(true);
	mProcesses[8] = b;

	DerivativeStrategy * c = new DerivativeStrategy();
	c->setVertical(true);
	mProcesses[9] = c;
	
	Tiny1DGaussStrategy * b2 = new Tiny1DGaussStrategy();
	b2->setVertical(false);
	mProcesses[10] = b2;

	DerivativeStrategy * c2 = new DerivativeStrategy();
	c2->setVertical(false);
	mProcesses[11] = c2;

	//MeanStrategy * e = new MeanStrategy();
	SobelRecoupleStrategy * e = new SobelRecoupleStrategy();
	mProcesses[12] = e;


	TresholderStrategy * d = new TresholderStrategy();
	mProcesses[13] = d;
	d->setTreshold(5);

	FindCircleStrategy * f = new FindCircleStrategy();
	mProcesses[14] = f;
}



void IPPipeline::defaultLightmapProcess(size_t gauss1, size_t maxfilter, size_t gauss2)
{
	mProcesses.resize(0);

	IPPipeline::simulGaussianFilter(gauss1);

	MeanStrategy * meanStrat = new MeanStrategy();
	mProcesses.push_back(meanStrat);

	//MAX
	MaxMinFilterStrategy * d = new MaxMinFilterStrategy();
	d->setKernelSize(maxfilter);
	d->setVertical(true);

	MaxMinFilterStrategy * e = new MaxMinFilterStrategy();
	e->setKernelSize(maxfilter);
	e->setVertical(false);

	mProcesses.push_back(d);
	mProcesses.push_back(e);
	///////////

	IPPipeline::simulGaussianFilter(gauss2);

}

void IPPipeline::simulGaussianFilter(size_t kernel, size_t precision)
{
	BoxFilterStrategy * a = new BoxFilterStrategy();
	BoxFilterStrategy * b = new BoxFilterStrategy();
	a->setKernelSize(kernel);
	b->setKernelSize(kernel);
	b->setVertical(true);

	for (size_t i = 0; i < precision; i++)
	{
		mProcesses.push_back(a);
		mProcesses.push_back(b);
	}
}

void IPPipeline::sobelProcess()
{

	SobelDecoupleStrategy * a = new SobelDecoupleStrategy();
	mProcesses.push_back(a);

	Tiny1DGaussStrategy * b = new Tiny1DGaussStrategy();
	b->setVertical(true);
	mProcesses.push_back(b);

	DerivativeStrategy * c = new DerivativeStrategy();
	c->setVertical(true);
	mProcesses.push_back(c);

	Tiny1DGaussStrategy * d = new Tiny1DGaussStrategy();
	d->setVertical(false);
	mProcesses.push_back(d);

	DerivativeStrategy * e = new DerivativeStrategy();
	e->setVertical(false);
	mProcesses.push_back(e);

	SobelRecoupleStrategy * f = new SobelRecoupleStrategy();
	mProcesses.push_back(f);
}

void IPPipeline::setCurrentImage(Img_1D_channel img, size_t index)
{
	//safe?
	mCurrImage[index] = img;
}

void IPPipeline::pushImg(Img_1D_channel img) {
	mCurrImage.push_back(img);
}

void IPPipeline::applyStep(std::pair<StepType, filter_args> s) {
	StepType currStep = s.first;
	filter_args args = s.second;

	if (currStep == StepType::DEFAULT_LIGHTMAP) {
		IPPipeline::defaultLightmapProcess(args[0], args[1], args[2]);
	}
	else if (currStep == StepType::APPLY_LIGHTMAP) {
		mProcesses.push_back(new UniformizeStrategy());
	}
	else if (currStep == StepType::GAUSS) {
	
		IPPipeline::simulGaussianFilter(args[0]);
	}
	else if (currStep == StepType::SOBEL) {
		IPPipeline::sobelProcess();
	}
	else if (currStep == StepType::TRESHOLD) {
		TresholderStrategy * s = new TresholderStrategy();
		s->setTreshold(args[0]);
		mProcesses.push_back(s);
	}
	else if (currStep == StepType::FIND_CIRCLES) {
	
		FindCircleStrategy * f = new FindCircleStrategy();
		f->setRadius(args[0]);
		mProcesses.push_back(f);
	}

}

void IPPipeline::applyBlueprint()
{
	const Procedure currSteps = mBlueprint.getSteps();
	
	for (auto s : currSteps) {
		IPPipeline::applyStep(s);
	}

}

void IPPipeline::setBlueprint(PipelineBlueprint bp)
{
	mBlueprint = bp;
}


int IPPipeline::inputSize() {

	return mCurrImage.size();
}


void IPPipeline::resetPipeline()
{
	mProcesses.clear();
}
