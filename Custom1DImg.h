#pragma once
#include <algorithm>
#include <vector>
#include "Grayscale1DImage.h"

class Custom1DImg
{
public:
	enum colorSpace
	{
		RGB,
		HSV
	};

	Custom1DImg(QImage & im, colorSpace cSpace = colorSpace::HSV);

	Img_1D_channel * getChannel(channelType ctype);

	void setWidth(size_t w) { mWidth = w; }
	size_t width() { return mWidth; }

	void setHeight(size_t h) { mHeight = h; }
	size_t height() { return mHeight; }

	colorSpace getColorSpace() { return mColorSpace; };
	void setColorSpace(colorSpace  cs) { mColorSpace = cs; };

private:

	int mWidth;
	int mHeight;
	//color space
	std::vector<Img_1D_channel> channels;
	colorSpace mColorSpace;

	void defaultChannels();

};

