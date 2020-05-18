#include "MeanStrategy.h"

//void MeanStrategy::iterationProcedure(std::vector<unsigned char*> &inputs, std::vector<unsigned char*>& outputs)
//{
//	size_t sum = 0;
//	for (auto& p : inputs) {
//		sum += *p;
//		++p;
//	}
//
//	*(outputs[0]) = sum/inputs.size();
//	++outputs[0];
//}

unsigned char MeanStrategy::iterationAction(const unsigned char * p)
{
	if (n % max_size == 0) {
		sum = 0;
		n = 0;
	}

	++n;
	sum += *p;
	return sum/n;
}





void MeanStrategy::process()
{
	auto [ins, outs] = prepOutput();
	ConvolutionProcessStrategy::iterate(ins, outs);
}


MeanStrategy::MeanStrategy()
	:ConvolutionProcessStrategy(), sum{0}, n{0}
{
	ConvolutionProcessStrategy::setOneToOne(false);
}
