#include "Tiny1DGaussStrategy.h"

void Tiny1DGaussStrategy::process()
{
	for (size_t i = 0; i < mInput->size(); i++)
	{
		if ((mInput->at(i).type() == channelType::SOBEL_V) == mVertical) {
		
			int width = mInput->at(i).width();
			int height = mInput->at(i).height();
			int offset = mVertical ? width : 1;
			int limit = mVertical ? height : width;

			unsigned char * in = mInput->at(i).getStart();
			unsigned char * in_end = mInput->at(i).getStart() + (width*height);
			unsigned char * out = mOutput.at(i).getStart();

			float dx{ 0 };

			//var used to store the last (closest) valid neighbour, value is used when iterator is out of bounds (kernel wise) on x-y plane

			int xyCount{ 0 };
			int j{ 0 };
			while (in != in_end) {
				dx = 0;
				for (int k = -1; k < 2; k++) {

					if (k + xyCount > 0
						&& k + xyCount < limit) {
						dx += *(in + k * offset) * k / 4;
						if (k == 0) {
							dx += *(in + k * offset) / 2;
						}
					}
					else {
						k = 2;
						dx = 0;
					}

				}

				*out = dx;

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
}

void Tiny1DGaussStrategy::setVertical(bool v)
{
	mVertical = v;
}

Tiny1DGaussStrategy::Tiny1DGaussStrategy()
	:ProcessStrategy()
{
}