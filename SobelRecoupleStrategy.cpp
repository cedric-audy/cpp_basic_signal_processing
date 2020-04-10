#include "SobelRecoupleStrategy.h"

void SobelRecoupleStrategy::process()
{
	mOutput.resize(1);
	std::vector<unsigned char *> input_ptrs{};

	for (size_t i = 0; i < mInput->size(); i++)
	{
		input_ptrs.push_back(mInput->at(i).getStart());
	}

	unsigned char * input_end = input_ptrs.at(0) + mInput->at(0).width() * mInput->at(0).height();
	unsigned char * out = mOutput[0].getStart();
	int sum = 0;
	while (input_ptrs.at(0) != input_end) {

		for (auto& p : input_ptrs) {
			sum += *p;
			++p;
		}

		*out = sum>255?255:sum;
		sum = 0;
		++out;

	}

}

SobelRecoupleStrategy::SobelRecoupleStrategy()
	:ProcessStrategy()
{
}
