#include "MaxMinFilterStrategy.h"


void MaxMinFilterStrategy::process()
{
	int width = mInput->at(0).width();
	int height = mInput->at(0).height();
	int offset = mVertical ? width : 1;
	int limit = mVertical ? height : width;

	unsigned char * in = mInput->at(0).getStart();
	unsigned char * in_end = mInput->at(0).getStart() + (width*height);

	unsigned char * out = mOutput.at(0).getStart();


	int maxVal{ 0 };
	int xyCount{ 0 };
	int i{ 0 };

	while (in != in_end) {
		maxVal = *in;
		for (int k = 0 - mKernelSize / 2; k < (mKernelSize / 2) + 1; k++) {

			//for test: remove 2/4 conditions here, shouldnt crash
			if (
				//i + k * offset > 0 
				//&& i + k * offset < width*height 
				k + xyCount > 0
				&& k + xyCount < limit) {

					maxVal = *(in + k * offset) > maxVal? *(in + k * offset):maxVal;
			}

		}

		*out = maxVal;


		++in;
		++out;

		++i;


		if (i % offset == 0) {
			xyCount += 1;

			if (xyCount == limit) {
				xyCount = 0;
			}
		}

	}

}

int MaxMinFilterStrategy::kernelSize()
{
	return mKernelSize;
}

void MaxMinFilterStrategy::setKernelSize(int s)
{
	mKernelSize = s;
}

void MaxMinFilterStrategy::setMax(bool b)
{
	mMaxFilter= b;
}

void MaxMinFilterStrategy::setVertical(bool b)
{
	mVertical = b;
}
MaxMinFilterStrategy::MaxMinFilterStrategy() 
	:ProcessStrategy{}, mKernelSize{ 11 }, mVertical{ false }, mMaxFilter{ true }
{
}



//void MaxMinFilterStrategy::applyd1DBMaxMinFilter(bool vertical)
//{
//
//
//
//
//
//
////	//some leftovers from tentative iterator design pattern implementation, thought it didnt work but I was just forgetting to increment an iterator in imgdemo ... dunno if itd work as is
//
//	//int width = mInput[0]->width();
//	//int height = mInput[0]->height();
//	//int offset = vertical ? width : 1;
//	//int limit = vertical ? height : width;
//
//	//const_pixel_iter input_it = mInput[0]->cbegin();
//	//const_pixel_iter input_it_end = mInput[0]->cend();
//
//	//pixel_iter output_it = mOutput[0].begin();
//
//	////var used to store the last (closest) valid neighbour, value is used when iterator is out of bounds (kernel wise) on x-y plane
//	//
//	//size_t lastVal{ 0 };
//	//size_t max{ 0 };
//	//size_t min{ 0 };
//
//	//int xyCount{ 0 };
//	//int i{ 0 };
//	//while (input_it < input_it_end) {
//	//	lastVal = *input_it;
//	//	for (int k = 0 - mKernelSize / 2; k < (mKernelSize / 2) + 1; k++) {
//
//	//		//for test: remove 2/4 conditions here, shouldnt crash
//	//		if (i + k * offset > 0
//	//			&& i + k * offset < width*height
//	//			&& k + xyCount > 0
//	//			&& k + xyCount < limit) {
//
//	//			lastVal = *(input_it + k * offset);
//
//	//		}
//	//		max = lastVal > max ? lastVal : max;
//	//		min = lastVal < min ? lastVal : min;
//
//	//		*output_it = mMaxFilter?max:min;
//	//		++output_it;
//	//		++input_it;
//	//		xyCount = ((xyCount%limit) + 1)*offset;
//	//	}
//	//}
//}
