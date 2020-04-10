#include "IPPipeline.h"
#include "BoxFilterStrategy.h"
#include "MaxMinFilterStrategy.h"
#include "UniformizeStrategy.h"
#include "LightmapStrategy.h"
#include "MeanStrategy.h"
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
	d->setKernelSize(15);
	d->setVertical(true);

	MaxMinFilterStrategy * e = new MaxMinFilterStrategy();
	e->setKernelSize(15);
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

	//LightmapStrategy * e = new LightmapStrategy();

	//mProcesses[14] = e;

	//UniformizeStrategy * f = new UniformizeStrategy();

	//mProcesses[15] = f;


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
