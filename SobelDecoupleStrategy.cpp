#include "SobelDecoupleStrategy.h"

void SobelDecoupleStrategy::process()
{
		mOutput.resize(2);
		mOutput[0].setType(channelType::SOBEL_V);
		mOutput[1] = mOutput[0];
		mOutput[1].setType(channelType::SOBEL_H);
	
}

SobelDecoupleStrategy::SobelDecoupleStrategy()
	:ProcessStrategy()
{
}
