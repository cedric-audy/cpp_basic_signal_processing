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
	:mCurrImage{2}, mProcesses{ 20 }, currOutput{}
{

}

void IPPipeline::execute()
{
	std::vector<Grayscale1DImage>* lastImg{ &mCurrImage };


	int i{ 0 };
	for (auto &p : mProcesses) {
		if (p != NULL) {
			p->addInput(lastImg);
			p->process();
			lastImg = p->offerOutput();
			++i;
		}
	}

	Grayscale1DImage * output = &(mProcesses[i-1]->offerOutput()->at(0));
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

void IPPipeline::defaultLightmapProcess()
{
	//mProcesses.push_back(step);

	//some tests

	//GAUSS
	BoxFilterStrategy * a = new BoxFilterStrategy();
	BoxFilterStrategy * b = new BoxFilterStrategy();
	a->setKernelSize(11);
	b->setKernelSize(11);
	b->setVertical(true);
	mProcesses[0] = a;
	mProcesses[1] = b;
	mProcesses[2] = a;
	mProcesses[3] = b;
	mProcesses[4] = a;
	mProcesses[5] = b;

	MeanStrategy * c = new MeanStrategy();
	mProcesses[6] = c;

	//MAX
	MaxMinFilterStrategy * d = new MaxMinFilterStrategy();
	d->setKernelSize(11);
	d->setVertical(true);

	MaxMinFilterStrategy * e = new MaxMinFilterStrategy();
	e->setKernelSize(11);
	e->setVertical(false);

	mProcesses[7] = d;
	mProcesses[8] = e;
	///////////

	//GAUSS 
	BoxFilterStrategy * f = new BoxFilterStrategy();
	BoxFilterStrategy * g = new BoxFilterStrategy();
	g->setVertical(true);

	f->setKernelSize(151);
	g->setKernelSize(151);
	mProcesses[9] = f;
	mProcesses[10] = g;
	mProcesses[11] = f;
	mProcesses[12] = g;
	mProcesses[13] = f;
	mProcesses[14] = g;

}

void IPPipeline::setCurrentImage(Grayscale1DImage img, size_t index)
{
	//safe?
	mCurrImage[index] = img;
}

void IPPipeline::pushImg(Grayscale1DImage img) {
	mCurrImage.push_back(img);
}


int IPPipeline::inputSize() {

	return mCurrImage.size();
}


void IPPipeline::resetPipeline()
{
	mProcesses.clear();
}
