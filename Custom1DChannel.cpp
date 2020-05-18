#include "Custom1DChannel.h"


Custom1DChannel::Custom1DChannel(int * w, int * h, channelType c)
	: mWidth{ w }, mHeight{ h }, mType{ c }, mVals{} {
	mVals.resize(*mWidth * *mHeight);
}

channelType Custom1DChannel::type()
{
	return mType;
}

void Custom1DChannel::setType(channelType g)
{
	mType = g;
}

unsigned char * Custom1DChannel::getStart()
{
	return &mVals[0];
}

unsigned char * Custom1DChannel::getEnd()
{
	return &mVals[*(mWidth) * *(mHeight)];
}
