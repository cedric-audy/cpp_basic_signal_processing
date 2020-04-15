#include "Grayscale1DImage.h"


Img_1D_channel::Img_1D_channel(int * w, int * h, channelType c)
	: mWidth{ w }, mHeight{ h }, mType{ c } {

}

channelType Img_1D_channel::type()
{
	return mType;
}

void Img_1D_channel::setType(channelType g)
{
	mType = g;
}

unsigned char * Img_1D_channel::getStart()
{
	return &mVals[0];
}

unsigned char * Img_1D_channel::getEnd()
{
	return &mVals[*(mWidth) * *(mHeight)];
}
