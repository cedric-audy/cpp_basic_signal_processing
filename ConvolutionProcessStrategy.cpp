#include "ConvolutionProcessStrategy.h"

std::vector<unsigned char*> ConvolutionProcessStrategy::getChannelsPtrs(channelType c)
{
	std::vector<unsigned char*> queried_channels{};
	for (size_t i = 0; i < mInput.size(); i++)
	{
		queried_channels.push_back(mInput.at(i)->getChannel(c)->getStart());
	}
	return queried_channels;
}

const std::vector<unsigned char> ConvolutionProcessStrategy::formKernel(const unsigned char * c)
{
	return std::vector<unsigned char>(*c);
}

processPtrs ConvolutionProcessStrategy::prepOutput()
{
	std::vector<unsigned char*> outputs{};
	if (one_to_one) {

		for (size_t i = 0; i < mInput.size(); i++)
		{
			mOutput.push_back(*mInput[i]);
			outputs.push_back(mOutput[i].getChannel(channelType::GRAY)->getStart());
		}
	}
	else {
		mOutput.push_back(*mInput[0]);
		outputs.push_back(mOutput[0].getChannel(channelType::GRAY)->getStart());
	}
	std::vector<unsigned char*> inputs{};
	for (auto& i : mInput) {
		inputs.push_back(i->getChannel(channelType::GRAY)->getStart());
	}

	return std::make_pair(inputs, outputs);
}

void ConvolutionProcessStrategy::iterate(std::vector<unsigned char*>& inputs, std::vector<unsigned char*>& outputs)
{
	unsigned char * input_end = inputs.at(0) + mInput.at(0)->width() * mInput.at(0)->height();
	while (inputs.at(0) != input_end) {
		iterationProcedure(inputs, outputs);
	}
}

void ConvolutionProcessStrategy::setOneToOne(bool oneto1)
{
	one_to_one = oneto1;
}

ConvolutionProcessStrategy::ConvolutionProcessStrategy()
	:one_to_one{false}
{
}

void ConvolutionProcessStrategy::process()
{
	auto[ins, outs] = prepOutput();
	ConvolutionProcessStrategy::iterate(ins, outs);
}


void ConvolutionProcessStrategy::setMaxSize(size_t max)
{
	max_size = max;
}

void ConvolutionProcessStrategy::iterationProcedure(std::vector<unsigned char*>& inputs, std::vector<unsigned char*>& outputs) {

	size_t out_i{ 0 };
	for (size_t i = 0; i < inputs.size(); ++i)
	{
		out_i = one_to_one ? i :0;
		*(outputs.at(out_i)) = iterationAction(inputs[i]);
	}

	for (auto& i : inputs) {
		//std::string a{ typeid(i).name() };
		++i;
	}
	for (auto& o : outputs) {
		++o;
	}
}
