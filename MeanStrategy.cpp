#include "MeanStrategy.h"

void MeanStrategy::process()
{
	mOutput.resize(1);
	std::vector<unsigned char *> input_ptrs{};

	for (size_t i = 0; i < mInput->size(); i++)
	{
		input_ptrs.push_back(mInput->at(i).getChannel(channelType::GRAY)->getStart());
	}

	//marche pas !?
	//for (auto i : *mInput) {
	//	input_ptrs.push_back(i.getStart());
	//}

	unsigned char * input_end = input_ptrs.at(0) + mInput->at(0).width() * mInput->at(0).height();
	unsigned char * out = mOutput[0].getChannel(channelType::GRAY)->getStart();

	size_t nb{ input_ptrs.size() };
	size_t sum{ 0 };
	while (input_ptrs.at(0) != input_end) {
		sum = 0;
		for (auto& p : input_ptrs) {
			sum += *p;
			++p;
		}

		*out = sum / nb;
		++out;
	}
}

MeanStrategy::MeanStrategy()
	:ProcessStrategy()
{
}
