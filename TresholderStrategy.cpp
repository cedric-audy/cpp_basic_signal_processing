#include "TresholderStrategy.h"

void TresholderStrategy::process()
{
	for (size_t i = 0; i < mInput->size(); i++)
	{
		int width = mInput->at(i).width();
		int height = mInput->at(i).height();

		unsigned char * in = mInput->at(i).getStart();
		unsigned char * in_end = mInput->at(i).getStart() + (width*height);
		unsigned char * out = mOutput.at(i).getStart();

		while (in != in_end) {
			
			*out = *(in) > mTreshold?(mToBinary?255:*(in)):0 ;

			++in;
			++out;

		}
	}
}

void TresholderStrategy::setToBinary(bool b)
{
	mToBinary = b;
}

void TresholderStrategy::setTreshold(int t)
{
	mTreshold = t;
}

TresholderStrategy::TresholderStrategy()
	:ProcessStrategy(), mTreshold{7}, mToBinary{true}
{
}
