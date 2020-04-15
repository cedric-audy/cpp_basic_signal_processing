#pragma once
#include <vector>
#include <QtWidgets/QMainWindow>

#include "pixelIterators.h"
#include "GrayscaleType.h"

//using LightMap1D = Grayscale1DImage; //so it can be recognized as such within processes without hard coding an index

 
class Img_1D_channel
{

private:
	int * mWidth;
	int * mHeight;
	channelType mType;

protected:
	pixels_t mVals;

public:
	Img_1D_channel() = default;
	Img_1D_channel(int * w, int * h, channelType c);

	channelType type();
	void setType(channelType g);

	unsigned char * getStart();
	unsigned char * getEnd();

};

