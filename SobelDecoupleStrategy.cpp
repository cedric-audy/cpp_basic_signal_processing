#include "SobelDecoupleStrategy.h"

void SobelDecoupleStrategy::process()
{
		mOutput.resize(2);
		mOutput[0].setType(GrayscaleType::SOBEL_V);
		mOutput[1] = mOutput[0];
		mOutput[1].setType(GrayscaleType::SOBEL_H);
	
}

SobelDecoupleStrategy::SobelDecoupleStrategy()
	:ProcessStrategy()
{
}
