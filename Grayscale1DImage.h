#pragma once
#include <vector>
#include <QtWidgets/QMainWindow>

#include "pixelIterators.h"
#include "GrayscaleType.h"

//using LightMap1D = Grayscale1DImage; //so it can be recognized as such within processes without hard coding an index

 
class Grayscale1DImage
{

private:
	int mWidth;
	int mHeight;
	GrayscaleType mType;

protected:
	pixels_t mImg;

public:
	Grayscale1DImage() = default;
	Grayscale1DImage(QImage & im);

	void setWidth(size_t w) { mWidth = w; }
	size_t width() { return mWidth; }

	void setHeight(size_t h) { mHeight = h; }
	size_t height() { return mHeight; }

	GrayscaleType type() { return mType; }
	void setType(GrayscaleType g) { mType = g; }

	unsigned char * getStart() { return &mImg[0]; }
	//iterator pattern ?
};

