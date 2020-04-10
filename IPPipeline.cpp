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
			if (i == 15) { //hardcoded for now
				p->addInput(mCurrImage.at(0));
			}
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

	SobelDecoupleStrategy * a2 = new SobelDecoupleStrategy();
	mProcesses[1] = a2;

	Tiny1DGaussStrategy * b = new Tiny1DGaussStrategy();
	b->setVertical(true);
	mProcesses[2] = b;

	DerivativeStrategy * c = new DerivativeStrategy();
	c->setVertical(true);
	mProcesses[3] = c;
	
	Tiny1DGaussStrategy * b2 = new Tiny1DGaussStrategy();
	b2->setVertical(false);
	mProcesses[4] = b2;

	DerivativeStrategy * c2 = new DerivativeStrategy();
	c2->setVertical(false);
	mProcesses[5] = c2;

	//MeanStrategy * e = new MeanStrategy();
	SobelRecoupleStrategy * e = new SobelRecoupleStrategy();
	mProcesses[6] = e;


	TresholderStrategy * d = new TresholderStrategy();
	mProcesses[7] = d;


}

void IPPipeline::defaultLightmapProcess()
{
	//mProcesses.push_back(step);

	//some tests

	//GAUSS
	BoxFilterStrategy * a = new BoxFilterStrategy();
	BoxFilterStrategy * b = new BoxFilterStrategy();
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

	f->setKernelSize(99);
	g->setKernelSize(99);
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
