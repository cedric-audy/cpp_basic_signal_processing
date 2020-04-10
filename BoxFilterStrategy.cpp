#include "BoxFilterStrategy.h"

void BoxFilterStrategy::process()
{
	for (size_t i = 0; i < mInput->size(); i++)
	{

		int width = mInput->at(i).width();
		int height = mInput->at(i).height();
		int offset = mVertical ? width : 1;
		int limit = mVertical ? height : width;

		unsigned char * in = mInput->at(i).getStart();
		unsigned char * in_end = mInput->at(i).getStart() + (width*height);
		unsigned char * out = mOutput.at(i).getStart();

		size_t sum{ 0 };
		float avr{ 0 };

		//var used to store the last (closest) valid neighbour, value is used when iterator is out of bounds (kernel wise) on x-y plane
		size_t lastVal{ 0 };

		int xyCount{ 0 };
		int j{ 0 };
		while (in != in_end) {
			lastVal = *in;
			for (int k = 0 - mKernelSize / 2; k < (mKernelSize / 2) + 1; k++) {

				//for test: remove 2/4 conditions here, shouldnt crash
				if (
					//i + k * offset > 0 
					//&& i + k * offset < width*height 
					k + xyCount > 0
					&& k + xyCount < limit) {

					lastVal = *(in + k * offset);
				}
				sum += lastVal;

			}

			avr = mKernelSize==0?*out:sum / mKernelSize;
			sum = 0;
			*out = avr;

			++in;
			++out;

			++j;


			if (j % offset == 0) {
				xyCount += 1;

				if (xyCount == limit) {
					xyCount = 0;
				}
			}
		}
	}
}

int BoxFilterStrategy::kernelSize()
{
	return mKernelSize;
}

void BoxFilterStrategy::setKernelSize(int s)
{
	mKernelSize = s;
}

void BoxFilterStrategy::setVertical(bool b)
{
	mVertical = b;
}

BoxFilterStrategy::BoxFilterStrategy()
	: ProcessStrategy{}, mKernelSize{ 11 }, mVertical{false}
{
}




