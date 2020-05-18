#pragma once
#include <vector>
#include <QtWidgets/QMainWindow>

#include "channelType.h"
#include "pixelIterators.h"

//using LightMap1D = Grayscale1DImage; //so it can be recognized as such within processes without hard coding an index

 
class Custom1DChannel
{

private:
	int * mWidth;
	int * mHeight;
	channelType mType;



protected:
	pixels_t mVals;

public:
	Custom1DChannel() = default;
	Custom1DChannel(int * w, int * h, channelType c);

	channelType type();
	void setType(channelType g);

	unsigned char * getStart();
	unsigned char * getEnd();

};

